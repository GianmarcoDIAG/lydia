#pragma once
/*
 * This file is part of Lydia.
 *
 * Lydia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lydia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lydia.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "basic.hpp"
#include "types.hpp"

namespace whitemech {
namespace lydia {

class Visitor {
public:
  virtual void visit(const Symbol &){};
  virtual void visit(const LDLfBooleanAtom &){};
  virtual void visit(const LDLfAnd &){};
  virtual void visit(const LDLfOr &){};
  virtual void visit(const LDLfNot &){};
  virtual void visit(const LDLfDiamond<PropositionalRegExp> &x){};
  // TODO add all the combinations of temporal formulas + regular expression

  // callbacks for propositional logic
  virtual void visit(const PropositionalTrue &){};
  virtual void visit(const PropositionalFalse &){};
  virtual void visit(const PropositionalAtom &){};
  virtual void visit(const QuotedFormula &){};
  virtual void visit(const PropositionalAnd &){};
  virtual void visit(const PropositionalOr &){};
  virtual void visit(const PropositionalNot &){};
};

} // namespace lydia
} // namespace whitemech
