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

#include <lydia/logic/ltlf/duality.hpp>
#include <lydia/logic/ppltl/duality.hpp>
#include <lydia/logic/nnf.hpp>

namespace whitemech::lydia {

void NNFTransformer::visit(const LTLfTrue& x) {
  ltlf_result = x.ctx().makeLtlfTrue();
}

void NNFTransformer::visit(const PPLTLTrue& x) {
  ppltl_result = x.ctx().makePPLTLTrue();
}

void NNFTransformer::visit(const LTLfFalse& x) {
  ltlf_result = x.ctx().makeLtlfFalse();
}

void NNFTransformer::visit(const PPLTLFalse& x) {
  ppltl_result = x.ctx().makePPLTLFalse();
}

void NNFTransformer::visit(const LTLfAtom& x) {
  ltlf_result = x.ctx().makeLtlfAtom(x.symbol);
}

void NNFTransformer::visit(const PPLTLAtom& x) {
  ppltl_result = x.ctx().makePPLTLAtom(x.symbol);
}

void NNFTransformer::visit(const LTLfAnd& x) {
  auto container = x.get_container();
  set_ltlf_formulas new_container;
  for (auto& a : container) {
    new_container.insert(apply(*a));
  }
  ltlf_result = x.ctx().makeLtlfAnd(new_container);
}

void NNFTransformer::visit(const PPLTLAnd& x) {
  auto container = x.get_container();
  set_ppltl_formulas new_container;
  for (auto& a : container) {
    new_container.insert(apply(*a));
  }
  ppltl_result = x.ctx().makePPLTLAnd(new_container);
}

void NNFTransformer::visit(const LTLfOr& x) {
  auto container = x.get_container();
  set_ltlf_formulas new_container;
  for (auto& a : container) {
    new_container.insert(apply(*a));
  }
  ltlf_result = x.ctx().makeLtlfOr(new_container);
}

void NNFTransformer::visit(const PPLTLOr& x) {
  auto container = x.get_container();
  set_ppltl_formulas new_container;
  for (auto& a : container) {
    new_container.insert(apply(*a));
  }
  ppltl_result = x.ctx().makePPLTLOr(new_container);
}

void NNFTransformer::visit(const LTLfNot& x) {
  if (is_a<const LTLfAtom>(*x.get_arg())) {
    ltlf_result = x.ctx().makeLtlfNot(x.get_arg());
  } else {
    ltlf_result = apply_negation(*x.get_arg());
  }
}

void NNFTransformer::visit(const PPLTLNot& x) {
  if (is_a<const PPLTLAtom>(*x.get_arg())) {
    ppltl_result = x.ctx().makePPLTLNot(x.get_arg());
  } else {
    ppltl_result = apply_negation(*x.get_arg());
  }
}

void NNFTransformer::visit(const LTLfNext& x) {
  ltlf_result = x.ctx().makeLtlfNext(apply(*x.get_arg()));
}

void NNFTransformer::visit(const PPLTLYesterday& x) {
  ppltl_result = x.ctx().makePPLTLYesterday(apply(*x.get_arg()));
}

void NNFTransformer::visit(const LTLfWeakNext& x) {
  ltlf_result = x.ctx().makeLtlfWeakNext(apply(*x.get_arg()));
}

void NNFTransformer::visit(const PPLTLWeakYesterday& x) {
  ppltl_result = x.ctx().makePPLTLWeakYesterday(apply(*x.get_arg()));
}

void NNFTransformer::visit(const LTLfUntil& x) {
  auto arg1 = apply(*x.get_args()[0]);
  auto arg2 = apply(*x.get_args()[1]);
  ltlf_result = x.ctx().makeLtlfUntil(arg1, arg2);
}

void NNFTransformer::visit(const PPLTLSince& x) {
  auto arg1 = apply(*x.get_args()[0]);
  auto arg2 = apply(*x.get_args()[1]);
  ppltl_result = x.ctx().makePPLTLSince(arg1, arg2);
}

void NNFTransformer::visit(const LTLfRelease& x) {
  auto arg1 = apply(*x.get_args()[0]);
  auto arg2 = apply(*x.get_args()[1]);
  ltlf_result = x.ctx().makeLtlfRelease(arg1, arg2);
}

void NNFTransformer::visit(const PPLTLTriggered& x) {
  auto arg1 = apply(*x.get_args()[0]);
  auto arg2 = apply(*x.get_args()[1]);
  ppltl_result = x.ctx().makePPLTLTriggered(arg1, arg2);
}

void NNFTransformer::visit(const LTLfEventually& x) {
  auto arg = apply(*x.get_arg());
  ltlf_result = x.ctx().makeLtlfEventually(arg);
}

void NNFTransformer::visit(const PPLTLOnce& x) {
  auto arg = apply(*x.get_arg());
  ppltl_result = x.ctx().makePPLTLOnce(arg);
}

void NNFTransformer::visit(const LTLfAlways& x) {
  auto arg = apply(*x.get_arg());
  ltlf_result = x.ctx().makeLtlfAlways(arg);
}

void NNFTransformer::visit(const PPLTLHistorically& x) {
  auto arg = apply(*x.get_arg());
  ppltl_result = x.ctx().makePPLTLHistorically(arg);
}

void NNFTransformer::visit(const LDLfTrue& x) {
  result = x.ctx().makeLdlfTrue();
}

void NNFTransformer::visit(const LDLfFalse& x) {
  result = x.ctx().makeLdlfFalse();
}

void NNFTransformer::visit(const LDLfAnd& x) {
  auto container = x.get_container();
  set_formulas new_container;
  for (auto& a : container) {
    new_container.insert(apply(*a));
  }
  result = x.ctx().makeLdlfAnd(new_container);
}

void NNFTransformer::visit(const LDLfOr& x) {
  auto container = x.get_container();
  set_formulas new_container;
  for (auto& a : container) {
    new_container.insert(apply(*a));
  }
  result = x.ctx().makeLdlfOr(new_container);
}

void NNFTransformer::visit(const LDLfNot& x) {
  auto new_formula = apply(*x.get_arg()->logical_not());
  result = new_formula;
}

void NNFTransformer::visit(const LDLfDiamond& x) {
  result =
      x.ctx().makeLdlfDiamond(apply(*x.get_regex()), apply(*x.get_formula()));
}

void NNFTransformer::visit(const LDLfBox& x) {
  result = x.ctx().makeLdlfBox(apply(*x.get_regex()), apply(*x.get_formula()));
}

void NNFTransformer::visit(const PropositionalRegExp& x) {
  regex_result = x.ctx().makePropRegex(apply(*x.get_arg()));
}

void NNFTransformer::visit(const TestRegExp& x) {
  regex_result = x.ctx().makeTestRegex(apply(*x.get_arg()));
}

void NNFTransformer::visit(const UnionRegExp& x) {
  auto container = x.get_container();
  set_regex new_container;
  for (auto& a : container) {
    new_container.insert(apply(*a));
  }
  regex_result = x.ctx().makeUnionRegex(new_container);
}

void NNFTransformer::visit(const SequenceRegExp& x) {
  auto container = x.get_container();
  vec_regex new_container;
  for (auto& a : container) {
    new_container.push_back(apply(*a));
  }
  regex_result = x.ctx().makeSeqRegex(new_container);
}

void NNFTransformer::visit(const StarRegExp& x) {
  regex_result = x.ctx().makeStarRegex(apply(*x.get_arg()));
}

void NNFTransformer::visit(const LDLfF& x) { result = apply(*x.get_arg()); }

void NNFTransformer::visit(const LDLfT& x) { result = apply(*x.get_arg()); }

void NNFTransformer::visit(const PropositionalTrue& f) {
  prop_result = f.ctx().makeTrue();
}
void NNFTransformer::visit(const PropositionalFalse& f) {
  prop_result = f.ctx().makeFalse();
}
void NNFTransformer::visit(const PropositionalAtom& f) {
  prop_result = f.ctx().makePropAtom(f.symbol);
}
void NNFTransformer::visit(const PropositionalAnd& f) {
  prop_result = f.ctx().makePropAnd(f.get_container());
}
void NNFTransformer::visit(const PropositionalOr& f) {
  prop_result = f.ctx().makePropOr(f.get_container());
}
void NNFTransformer::visit(const PropositionalNot& f) {
  if (is_a<PropositionalAtom>(*f.get_arg()))
    prop_result = f.ctx().makePropNot(f.get_arg());
  else
    prop_result = apply(*f.get_arg()->logical_not());
}

ltlf_ptr NNFTransformer::apply(const LTLfFormula& b) {
  b.accept(*this);
  return ltlf_result;
}

ppltl_ptr NNFTransformer::apply(const PPLTLFormula& b) {
  b.accept(*this);
  return ppltl_result;
}

ldlf_ptr NNFTransformer::apply(const LDLfFormula& b) {
  b.accept(*this);
  return result;
}

regex_ptr NNFTransformer::apply(const RegExp& b) {
  b.accept(*this);
  return regex_result;
}

prop_ptr NNFTransformer::apply(const PropositionalFormula& b) {
  b.accept(*this);
  return prop_result;
}

std::shared_ptr<const LDLfFormula> to_nnf(const LDLfFormula& x) {
  NNFTransformer nnfTransformer;
  return nnfTransformer.apply(x);
}

std::shared_ptr<const LTLfFormula> to_nnf(const LTLfFormula& x) {
  NNFTransformer nnfTransformer;
  return nnfTransformer.apply(x);
}

std::shared_ptr<const PPLTLFormula> to_nnf(const PPLTLFormula& x) {
  NNFTransformer nnfTransformer;
  return nnfTransformer.apply(x);
}

} // namespace whitemech::lydia