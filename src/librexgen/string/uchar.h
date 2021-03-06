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


#ifndef __uchar_h__
#define __uchar_h__

#include <stdint.h>
#include <stddef.h>
#include <librexgen/string/unicode.h>
#include <librexgen/osdepend.h>
#include <ctype.h>
#include <assert.h>
#include <unicode/uchar.h>

typedef uint8_t charset;
#define CHARSET_ANSI    1
#define CHARSET_UTF8    2
#define CHARSET_UTF16BE 3
#define CHARSET_UTF32BE 4
#define CHARSET_UTF16LE 5
#define CHARSET_UTF32LE 6

#if ! defined(__cplusplus) || defined(_WIN32) || __cplusplus==1 || __cplusplus==199711L
typedef uint16_t char16_t;
typedef uint32_t char32_t;
#endif

typedef uint8_t uchar_flags_t;
typedef uint8_t uchar_info_t;
typedef uint16_t uchar_codepoint_t;

#define UCHAR_FLAGS_CHANGE_CASE         0x01
#define UCHAR_FLAGS_PRESERVE_CASE       0x02
#define UCHAR_FLAGS_USE_CASEFOLDED      0x04


#define UCHAR_CAN_CHANGE_CASE(a) (!((a).flags&UCHAR_FLAGS_PRESERVE_CASE))
#define UCHAR_MUST_CHANGE_CASE(a) ((a).flags&UCHAR_CHANGE_CASE && !((a).flags&UCHAR_PRESERVE_CASE))
#define UCHAR_MUST_PRESERVE_CASE(a) ((a).flags&UCHAR_FLAGS_PRESERVE_CASE)
#define UCHAR_SET_CHANGE_CASE(a) do {            \
  (a).flags |= UCHAR_FLAGS_CHANGE_CASE;          \
  (a).flags &= (! UCHAR_FLAGS_PRESERVE_CASE );   \
} while (0)
#define UCHAR_SET_PRESERVE_CASE(a) do {          \
  (a).flags &= (! UCHAR_FLAGS_CHANGE_CASE );     \
  (a).flags |= UCHAR_FLAGS_PRESERVE_CASE;        \
} while (0)

typedef byte unicode_plane_t;
static const unicode_plane_t BMP   =  0;               /* Basic Multilingual Plane            */
static const unicode_plane_t SMP   =  1;               /* Supplementary Multilingual Plane    */
static const unicode_plane_t SIP   =  2;               /* Supplementary Ideographic Plane     */
static const unicode_plane_t SSP   = 14;               /* Supplementary Special-purpose Plane */
static const unicode_plane_t PUA_A = 15;               /* Supplementary Private Use Area-A    */
static const unicode_plane_t PUA_B = 16;               /* Supplementary Private Use Area-B    */

static const char32_t UCHAR_UNASSIGNED = 0xffffffff;

struct __uchar_t {
  uchar_flags_t     flags;      /* 1 byte */
  unicode_plane_t   plane;      /* 1 byte, currently not used */
  uchar_codepoint_t codepoint;

#ifdef __cplusplus
  __uchar_t() :flags(0), plane(BMP), codepoint(0xfffe) {}
	__uchar_t(uchar_codepoint_t cp): flags(0), plane(BMP), codepoint(cp) {}
  __uchar_t(const struct __uchar_t &other) :flags(other.flags), plane(other.plane), codepoint(other.codepoint) {}
	/*
  __uchar_t& operator= (const __uchar_t& other) {
    if (this != &other) {
      flags = other.flags;
      plane = other.plane;
      codepoint = other.codepoint;
    }
    return *this;
  }
	*/
  bool operator==(const __uchar_t& other) const { return codepoint == other.codepoint; }
  uint32_t full_codepoint() const {return ((uint32_t)plane)<<16 | (uint32_t)codepoint;}

public:
  inline
  void toggle_case() {
    if (codepoint<128 && plane==BMP) {
      codepoint ^= 0x0020;
    } else {
      if (u_isULowercase(codepoint)) {
        codepoint = u_toupper(codepoint);
      } else if(u_isUUppercase(codepoint)){
        codepoint = u_tolower(codepoint);
      }
    }
  }
#endif
};
typedef struct __uchar_t uchar_t;

#endif
