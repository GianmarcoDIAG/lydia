/*
 * This file is part of Nike.
 *
 * Nike is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nike is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nike.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <lydia/logic/ppltl/duality.hpp>
#include <lydia/logic/nnf.hpp>

namespace whitemech {
namespace lydia {

void PurePastNegationTransformer::visit(const PPLTLTrue& formula) {
  result = formula.ctx().makePPLTLFalse();
}

void PurePastNegationTransformer::visit(const PPLTLFalse& formula) {
  result = formula.ctx().makePPLTLTrue();
}

void PurePastNegationTransformer::visit(const PPLTLAtom& formula) {
  // (Marco) nnf(~a) = !a | end
  // (Gianmarco) for LTLf+, we need to drop the end part (?)
  // For now we keep it like this...
  auto& context = formula.ctx();
  auto atom = context.makePPLTLAtom(formula.symbol);
  // auto not_atom = context.makeLtlfNot(atom);
  // auto end = context.makeLtlfEnd();
  // result = context.makeLtlfOr(set_ltlf_formulas{not_atom, end});
  result = context.makePPLTLNot(atom);
}

void PurePastNegationTransformer::visit(const PPLTLNot& formula) {
  if (is_a<PPLTLAtom>(*formula.get_arg())) {
    // keep the not if arg is an atom
    auto atom = std::static_pointer_cast<const PPLTLAtom>(formula.get_arg());
    result = formula.ctx().makePPLTLAtom(atom->symbol);
  } else {
    // nnf(~~f) = nnf(f)
    result = to_nnf(*formula.get_arg());
  }
}

void PurePastNegationTransformer::visit(const PPLTLAnd& formula) {
  result = forward_call_to_arguments(
      formula, [this](const ppltl_ptr& formula) { return apply(*formula); },
      [formula](const vec_ppltl_formulas& container) {
        set_ppltl_formulas set(container.begin(), container.end());
        return formula.ctx().makePPLTLOr(set);
      });
}

void PurePastNegationTransformer::visit(const PPLTLOr& formula) {
  result = forward_call_to_arguments(
      formula, [this](const ppltl_ptr& formula) { return apply(*formula); },
      [formula](const vec_ppltl_formulas& container) {
        set_ppltl_formulas set(container.begin(), container.end());
        return formula.ctx().makePPLTLAnd(set);
      });
}

void PurePastNegationTransformer::visit(const PPLTLYesterday& formula) {
  result = formula.ctx().makePPLTLWeakYesterday(apply(*formula.get_arg()));
}

void PurePastNegationTransformer::visit(const PPLTLWeakYesterday& formula) {
  result = formula.ctx().makePPLTLYesterday(apply(*formula.get_arg()));
}

void PurePastNegationTransformer::visit(const PPLTLSince& formula) {
  result = forward_call_to_arguments(
      formula, [this](const ppltl_ptr& formula) { return apply(*formula); },
      [formula](const vec_ppltl_formulas& container) {
        assert(container.size() == 2);
        return formula.ctx().makePPLTLTriggered(container[0], container[1]);
      });
}
void PurePastNegationTransformer::visit(const PPLTLTriggered& formula) {
  result = forward_call_to_arguments(
      formula, [this](const ppltl_ptr& formula) { return apply(*formula); },
      [formula](const vec_ppltl_formulas& container) {
        assert(container.size() == 2);
        return formula.ctx().makePPLTLSince(container[0], container[1]);
      });
}

void PurePastNegationTransformer::visit(const PPLTLOnce& formula) {
  result = formula.ctx().makePPLTLHistorically(apply(*formula.get_arg()));
}

void PurePastNegationTransformer::visit(const PPLTLHistorically& formula) {
  result = formula.ctx().makePPLTLOnce(apply(*formula.get_arg()));
}

ppltl_ptr PurePastNegationTransformer::apply(const PPLTLFormula& f) {
  f.accept(*this);
  return result;
}

ppltl_ptr apply_negation(const PPLTLFormula& f) {
  auto visitor = PurePastNegationTransformer{};
  return visitor.apply(f);
}

} // namespace lydia
} // namespace whitemech