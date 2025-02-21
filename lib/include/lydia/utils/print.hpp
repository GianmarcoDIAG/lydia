#pragma once
/*
 * This file is part of Lydia.
 *
 * Lydia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lydia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Lydia.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <lydia/logic/ldlf/base.hpp>
#include <lydia/logic/nnf.hpp>
#include <lydia/logic/pl/base.hpp>
#include <lydia/visitor.hpp>
#include <lydia/logic/ltlf/base.hpp>
#include <lydia/logic/ltlf/base.hpp>
#include <lydia/logic/ppltl/base.hpp>
#include <lydia/logic/ltlfplus/base.hpp>
#include <lydia/logic/ppltlplus/base.hpp>

namespace whitemech::lydia {

class StrPrinter : public Visitor {
private:
  static const std::vector<std::string> names_;

protected:
  std::string result;

public:
  // callbacks for LTLf
  void visit(const LTLfTrue&) override;
  void visit(const LTLfFalse&) override;
  void visit(const LTLfAtom&) override;
  void visit(const LTLfAnd&) override;
  void visit(const LTLfOr&) override;
  void visit(const LTLfNot&) override;
  void visit(const LTLfNext&) override;
  void visit(const LTLfWeakNext&) override;
  void visit(const LTLfUntil&) override;
  void visit(const LTLfRelease&) override;
  void visit(const LTLfEventually&) override;
  void visit(const LTLfAlways&) override;

  // callbacks for LDLf
  void visit(const Symbol&) override;
  void visit(const LDLfTrue&) override;
  void visit(const LDLfFalse&) override;
  void visit(const LDLfAnd&) override;
  void visit(const LDLfOr&) override;
  void visit(const LDLfNot&) override;
  void visit(const LDLfDiamond&) override;
  void visit(const LDLfBox&) override;

  // callbacks for regular expressions
  void visit(const PropositionalRegExp&) override;
  void visit(const TestRegExp&) override;
  void visit(const UnionRegExp&) override;
  void visit(const SequenceRegExp&) override;
  void visit(const StarRegExp&) override;

  // callbacks for propositional logic
  void visit(const PropositionalTrue&) override;
  void visit(const PropositionalFalse&) override;
  void visit(const PropositionalAtom&) override;
  void visit(const PropositionalAnd&) override;
  void visit(const PropositionalOr&) override;
  void visit(const PropositionalNot&) override;

  void visit(const QuotedFormula&) override{};

  // callbacks for PPLTL
  void visit(const PPLTLTrue&) override;
  void visit(const PPLTLFalse&) override;
  void visit(const PPLTLAtom&) override;
  void visit(const PPLTLAnd&) override;
  void visit(const PPLTLOr&) override;
  void visit(const PPLTLNot&) override;
  void visit(const PPLTLYesterday&) override;
  void visit(const PPLTLWeakYesterday&) override;
  void visit(const PPLTLSince&) override;
  void visit(const PPLTLTriggered&) override;
  void visit(const PPLTLOnce&) override;
  void visit(const PPLTLHistorically&) override;

  // callbacks for LTLf+
  void visit(const LTLfPlusTrue&) override;
  void visit(const LTLfPlusFalse&) override;
  void visit(const LTLfPlusAnd&) override;
  void visit(const LTLfPlusOr&) override;
  void visit(const LTLfPlusNot&) override;
  void visit(const LTLfPlusExists&) override;
  void visit(const LTLfPlusForall&) override;
  void visit(const LTLfPlusExistsForall&) override;
  void visit(const LTLfPlusForallExists&) override;

  // callbacks for PPLTL+
  void visit(const PPLTLPlusTrue&) override;
  void visit(const PPLTLPlusFalse&) override;
  void visit(const PPLTLPlusAnd&) override;
  void visit(const PPLTLPlusOr&) override;
  void visit(const PPLTLPlusNot&) override;
  void visit(const PPLTLPlusExists&) override;
  void visit(const PPLTLPlusForall&) override;
  void visit(const PPLTLPlusExistsForall&) override;
  void visit(const PPLTLPlusForallExists&) override;

  std::string apply(const vec_basic& v);
  std::string apply(const set_formulas& v);
  std::string apply(const Basic& b);
};

std::string to_string(const Basic&);

} // namespace whitemech::lydia