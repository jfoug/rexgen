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

#include <librexgen/regex/terminalregex.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/string/unicode.h>
#include <vector>


void TerminalRegex::prepend(const TerminalRegex* tre) {
  for (vector<uchar_t>::const_iterator iter=tre->value.begin();
       iter!=tre->value.end(); ++iter) {
    value.insert(value.begin(), *iter);
  }
}

