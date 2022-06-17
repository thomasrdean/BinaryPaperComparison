/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#include <string.h>

#include "Exceptions.h"
#include "misc/Interval.h"
#include "IntStream.h"

#include "support/Utf8.h"
#include "support/StringUtils.h"
#include "support/CPPUtils.h"

#include "ByteInputStream.h"

using namespace antlr4;
using namespace antlrcpp;

using misc::Interval;

ByteInputStream::ByteInputStream() {
  InitializeInstanceFields();
}

ByteInputStream::ByteInputStream(const char *data, size_t length) {
  load(data, length);
}

// fix here
void ByteInputStream::load(const char *data, size_t length) {
   char32_t *wideChars = (char32_t*)malloc(sizeof(char32_t) * length);
   if(wideChars == NULL) {
     throw std::runtime_error("malloc returned NULL");
   }
   for (int i = 0; i < length; i++){
       wideChars[i] = (unsigned char)data[i];
   }
  _data = std::u32string(wideChars, wideChars + length);
  p = 0;
}

#ifdef NOTNOW
void ByteInputStream::load(std::istream &stream) {
  if (!stream.good() || stream.eof()) // No fail, bad or EOF.
    return;

  _data.clear();

  std::string s((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
  load(s.data(), s.length());
}
#endif

void ByteInputStream::reset() {
  p = 0;
}

void ByteInputStream::consume() {
  if (p >= _data.size()) {
    assert(LA(1) == IntStream::EOF);
    throw IllegalStateException("cannot consume EOF");
  }

  if (p < _data.size()) {
    p++;
  }
}

size_t ByteInputStream::LA(ssize_t i) {
  if (i == 0) {
    return 0; // undefined
  }

  ssize_t position = static_cast<ssize_t>(p);
  if (i < 0) {
    i++; // e.g., translate LA(-1) to use offset i=0; then _data[p+0-1]
    if ((position + i - 1) < 0) {
      return IntStream::EOF; // invalid; no char before first char
    }
  }

  if ((position + i - 1) >= static_cast<ssize_t>(_data.size())) {
    return IntStream::EOF;
  }

  return _data[static_cast<size_t>((position + i - 1))];
}

size_t ByteInputStream::LT(ssize_t i) {
  return LA(i);
}

size_t ByteInputStream::index() {
  return p;
}

size_t ByteInputStream::size() {
  return _data.size();
}

// Mark/release do nothing. We have entire buffer.
ssize_t ByteInputStream::mark() {
  return -1;
}

void ByteInputStream::release(ssize_t /* marker */) {
}

void ByteInputStream::seek(size_t index) {
  if (index <= p) {
    p = index; // just jump; don't update stream state (line, ...)
    return;
  }
  // seek forward, consume until p hits index or n (whichever comes first)
  index = std::min(index, _data.size());
  while (p < index) {
    consume();
  }
}

std::string ByteInputStream::getText(const Interval &interval) {
  if (interval.a < 0 || interval.b < 0) {
    return "";
  }

  size_t start = static_cast<size_t>(interval.a);
  size_t stop = static_cast<size_t>(interval.b);


  if (stop >= _data.size()) {
    stop = _data.size() - 1;
  }

  size_t count = stop - start + 1;
  if (start >= _data.size()) {
    return "";
  }
  std::string retval = "";
  for (int i = start; i <= stop; i++){
      char c = (char) _data[i];
      retval.append(&c,1);
  }

  return retval;
}

std::string ByteInputStream::getSourceName() const {
  if (name.empty()) {
    return IntStream::UNKNOWN_SOURCE_NAME;
  }
  return name;
}

// here...
std::string ByteInputStream::toString() const {
std::cerr << "did we get here??" << std::endl;
  auto maybeUtf8 = Utf8::strictEncode(std::u32string_view(_data));
  if (!maybeUtf8.has_value()) {
    throw IllegalArgumentException("Input stream contains invalid Unicode code points");
  }
  return std::move(maybeUtf8).value();
}

void ByteInputStream::InitializeInstanceFields() {
  p = 0;
}
