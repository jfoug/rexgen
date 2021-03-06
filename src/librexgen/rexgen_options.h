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

#ifndef __rexgen_options_h__
#define __rexgen_options_h__

#include <cstdio>
#include <librexgen/string/uchar.h>
#include <librexgen/c/iterator.h>

class RexgenOptions {
 public:
  RexgenOptions()
    : ignore_case(false),
      encoding(CHARSET_UTF8),
      infile(NULL),
      stream_callback(NULL) { }
  bool ignore_case;
  charset encoding;
  FILE* infile;
  callback_fp stream_callback;
};

#endif

