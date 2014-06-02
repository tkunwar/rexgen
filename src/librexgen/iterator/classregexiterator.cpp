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

#include <librexgen/iterator/classregexiterator.h>
#include <librexgen/iterator/iteratorstate.h>

ClassRegexIterator::ClassRegexIterator(
  int _id, IteratorState* iterstate, const uchar_t* classcontent, size_t elements)
  :Iterator(_id),
   current(-1),
   randomize(iterstate->getRandomize()) {
  for (size_t n=0; n<elements; ++n) {
    characters.push_back(classcontent[n]);
  }
  state = usable;
}

bool ClassRegexIterator::next() {
  ++current;
  if (current >= (int)characters.size()) {
    if (randomize) {shuffle();}
    current = 0;
    return false;
  }
  return true;
}

SerializableState* ClassRegexIterator::getCurrentState() const {
  SerializableState* s = Iterator::getCurrentState();
  s->addValue(current);
  return s;
}

void ClassRegexIterator::setCurrentState(const SerializableState* s) {
  Iterator::setCurrentState(s);
  current = s->getValue(0);
}


