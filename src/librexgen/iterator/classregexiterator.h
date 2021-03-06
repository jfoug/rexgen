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


#ifndef CLASSREGEXITERATOR_H
#define CLASSREGEXITERATOR_H

#include <vector>
#include <algorithm>
#include <cstdio>
#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/uchar.h>

using namespace std;

class ClassRegexIterator : public Iterator {

 public:
  ClassRegexIterator(int _id,
                     const uchar_t* classcontent,
                     size_t elements
                    );
  virtual ~ClassRegexIterator() {}

  inline void value(SimpleString& dst) const {
    dst.push_back(characters[current]);
  }

  bool next();
  bool previous();

  size_t size() const { return characters.size(); }

  inline bool hasNext() const { return  (current < ((int)characters.size()-1)); }
  inline bool canUseValue() const { return (current < (int)characters.size()); }

  virtual void updateReferences(IteratorState* /* iterState */) {}
  virtual void updateAttributes(IteratorState* /* iterState */) {}

  SerializableState* getCurrentState() const;
  void setCurrentState(const SerializableState* state);
 private:
  int current;
  vector<uchar_t> characters;
};

#endif // CLASSREGEXITERATOR_H
