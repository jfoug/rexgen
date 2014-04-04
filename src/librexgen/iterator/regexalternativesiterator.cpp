/*
    rexgen - a tool to create words based on regular expressions    
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/

#include <librexgen/iterator/regexalternativesiterator.h>
#include <librexgen/debug.h>
#include <librexgen/unicode.h>
#include <assert.h>
#include <cstring>
#include <deque>
#include <vector>
#include <set>

RegexAlternativesIterator::RegexAlternativesIterator(int _id)
  : Iterator(_id), iter(iterators.begin()) {
  state = resetted;
}

void RegexAlternativesIterator::value(SimpleString& dst) const {
  ENTER_METHOD;
  (*iter)->value(dst);
  LEAVE_METHOD;
}


bool RegexAlternativesIterator::next() {
  ENTER_METHOD;

  if (state == resetted) {
    state = usable;
    RETURN(true);
  }

  if ((*iter)->next()) {
    RETURN(true);
  }
  ++iter;
  if (iter == iterators.end()) {
    iter = iterators.begin();
    RETURN(false);
  }
  (*iter)->next();
  RETURN (true);
}

bool RegexAlternativesIterator::hasNext() const {
  ENTER_METHOD;
  if (iterators.size() == 0 || state == not_usable) {
    /* if we don't have any iterator, you cannot call next() */
    RETURN(false);
  }

  if (state == resetted) {
    /* we can return true here,
     * because we know that we have at least one iterator
     */
    RETURN(true);
  }

  if (iter == iterators.end()) {
    RETURN(false);
  }

  if ((*iter)->hasNext()) {
    RETURN(true);
  } else {
    deque<Iterator*>::iterator tmp = iter;
    ++tmp;
    RETURN(tmp != iterators.end());
  }
}

void RegexAlternativesIterator::addChild(Iterator* i) {
  ENTER_METHOD;
  iterators.push_back(i);
  iter = iterators.begin();
  i->next();
  LEAVE_METHOD;
}

bool RegexAlternativesIterator::canUseValue() const {
  if (!Iterator::canUseValue()) {
    return false;
  }
  if (iter == iterators.end()) {
    return false;
  }
  return ((*iter)->canUseValue());
}

RegexAlternativesIterator::~RegexAlternativesIterator() {
	for(deque<Iterator*>::iterator i=iterators.begin(); i!=iterators.end(); ++i) {
		if ((*i)->isSingleton()) {
			delete (*i);
		}
	}
  iterators.clear();
}

void RegexAlternativesIterator::updateReferences(IteratorState* iterState) {
	for(deque<Iterator*>::iterator i=iterators.begin(); i!=iterators.end(); ++i) {
		(*i)->updateReferences(iterState);
	}
}

SerializableState* RegexAlternativesIterator::getCurrentState() const
{
  SerializableState* s = Iterator::getCurrentState();
  s->addValue(iter - iterators.begin());
    
	for(deque<Iterator*>::const_iterator i=iterators.begin(); i!=iterators.end(); ++i) {
    s->addValue((*i)->getCurrentState());
  }
  return s;
}

void RegexAlternativesIterator::setCurrentState(const SerializableState* s)
{
    Iterator::setCurrentState(s);
    
		for(deque<Iterator*>::iterator i=iterators.begin(); i!=iterators.end(); ++i) {
      (*i)->setCurrentState(s->getChildState((*i)->getId()));
    }
    
    iter = iterators.begin() + s->getValue(0);
}
