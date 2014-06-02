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


#ifndef TERMINALREGEXITERATOR_H
#define TERMINALREGEXITERATOR_H

#include <string.h>
#include <vector>
#include <librexgen/iterator/iterator.h>
#include <librexgen/debug.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/simplestring.h>
#include <librexgen/state/invaliditeratoridexception.h>

class TerminalRegexIterator : public Iterator {
 public:

  TerminalRegexIterator(int _id, const uchar_t* _terminal, size_t elements)
    : Iterator(_id) {
    terminal = new uchar_t[elements];
		memcpy(terminal, _terminal, elements*sizeof(terminal[0]));
    terminal_length = elements;
  }

  ~TerminalRegexIterator() { delete[] terminal; }

  bool next() {
    const bool res = (state == resetted);
    state = usable;
    return res;
  }
  void value(SimpleString& dst) const {
		for (unsigned int idx=0; idx<terminal_length; ++idx) {
			dst.push_back(terminal[idx]);
		}
	}
  bool hasNext() const { return state == resetted; }

  virtual void updateReferences(IteratorState* /* iterState */) {}
 private:
  uchar_t* terminal;
  size_t terminal_length;
};

#endif // TERMINALREGEXITERATOR_H
