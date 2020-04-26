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

#include <cassert>
#include <delta.hpp>
#include <logger.hpp>
#include <nnf.hpp>

namespace whitemech {
namespace lydia {

Logger DeltaVisitor::logger = Logger("delta");

void DeltaVisitor::visit(const LDLfBooleanAtom &x) {
  if (x.get_value())
    result = std::make_shared<PropositionalTrue>();
  else
    result = std::make_shared<PropositionalFalse>();
}

void DeltaVisitor::visit(const LDLfNot &b) {
  DeltaVisitor::logger.error("Delta function should not be called with a not.");
  assert(false);
}

void DeltaVisitor::visit(const LDLfAnd &x) {
  auto container = x.get_container();
  set_prop_formulas new_container;
  for (auto &a : container) {
    new_container.insert(apply(*a));
  }
  result = std::make_shared<PropositionalAnd>(new_container);
}

void DeltaVisitor::visit(const LDLfOr &x) {
  auto container = x.get_container();
  set_prop_formulas new_container;
  for (auto &a : container) {
    new_container.insert(apply(*a));
  }
  result = std::make_shared<PropositionalOr>(new_container);
}

void DeltaVisitor::visit(const LDLfDiamond<PropositionalRegExp> &f) {
  //  TODO epsilon return false only if regexp is propositional
  if (epsilon) {
    result = std::make_shared<PropositionalFalse>();
  } else {
    assert(this->prop_interpretation.has_value());
    auto prop = f.get_regex()->get_arg();

    if (eval(*prop, this->prop_interpretation.value())) {
      // TODO Implement the "E(phi)" in the delta function (Brafman et. al 2018)
      result = std::make_shared<PropositionalAtom>(quote(f.get_formula()));
    } else {
      result = std::make_shared<PropositionalFalse>();
    }
  }
}

void DeltaVisitor::visit(const LDLfBox<PropositionalRegExp> &f) {
  //  TODO epsilon return false only if regexp is propositional
  if (epsilon) {
    result = std::make_shared<PropositionalTrue>();
  } else {
    assert(this->prop_interpretation.has_value());
    auto prop = f.get_regex()->get_arg();

    if (eval(*prop, this->prop_interpretation.value())) {
      // TODO Implement the "E(phi)" in the delta function (Brafman et. al 2018)
      result = std::make_shared<PropositionalAtom>(quote(f.get_formula()));
    } else {
      result = std::make_shared<PropositionalTrue>();
    }
  }
}

std::shared_ptr<const PropositionalFormula>
DeltaVisitor::apply(const LDLfFormula &b) {
  b.accept(*this);
  return result;
}

void DeltaVisitor::visit(const LDLfDiamond<TestRegExp> &x) {
  auto regex_delta = apply(*x.get_regex()->get_arg());
  auto ldlf_delta = apply(*x.get_formula());
  result = std::make_shared<PropositionalAnd>(
      set_prop_formulas{regex_delta, ldlf_delta});
}

void DeltaVisitor::visit(const LDLfBox<TestRegExp> &x) {
  NNFTransformer nnfTransformer;
  auto regex_delta =
      apply(*nnfTransformer.apply(LDLfNot(x.get_regex()->get_arg())));
  auto ldlf_delta = apply(*x.get_formula());
  result = std::make_shared<PropositionalOr>(
      set_prop_formulas{regex_delta, ldlf_delta});
}

std::shared_ptr<const PropositionalFormula> delta(const LDLfFormula &x) {
  // epsilon = true
  DeltaVisitor deltaVisitor;
  return deltaVisitor.apply(x);
}

std::shared_ptr<const PropositionalFormula> delta(const LDLfFormula &x,
                                                  const set_atoms_ptr &i) {
  DeltaVisitor deltaVisitor{i};
  return deltaVisitor.apply(x);
}

} // namespace lydia
} // namespace whitemech