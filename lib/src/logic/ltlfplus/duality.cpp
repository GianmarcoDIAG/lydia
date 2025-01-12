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

#include<lydia/logic/ltlfplus/duality.hpp>
#include<lydia/logic/nnf.hpp>
#include<lydia/logic/pnf.hpp>

namespace whitemech {
namespace lydia {

    void PlusNegationTransformer::visit(const LTLfPlusTrue& formula) {
        result = formula.ctx().makeLtlfPlusFalse();
    }

    void PlusNegationTransformer::visit(const LTLfPlusFalse& formula) {
        result = formula.ctx().makeLtlfPlusTrue();
    } 

    void PlusNegationTransformer::visit(const LTLfPlusAnd& formula) {
        result = forward_call_in(
            formula, [this](const ltlf_plus_ptr& formula){return apply(*formula); },
            [formula](const vec_ltlf_plus_formulas& container) {
                set_ltlf_plus_formulas set(container.begin(), container.end());
                return formula.ctx().makeLtlfPlusOr(set);
            }); 
    }

    void PlusNegationTransformer::visit(const LTLfPlusOr& formula) {
        result = forward_call_in(
            formula, [this](const ltlf_plus_ptr& formula){return apply(*formula);},
            [formula](const vec_ltlf_plus_formulas& container) {
                set_ltlf_plus_formulas set(container.begin(), container.end());
                return formula.ctx().makeLtlfPlusAnd(set);
            });
    }

    void PlusNegationTransformer::visit(const LTLfPlusNot& formula) {
        result = to_pnf(*formula.get_arg());
    }

    void PlusNegationTransformer::visit(const LTLfPlusExists& formula) {
        NegationTransformer ltlf_trans;
        ltlf_ptr ltlf_neg = ltlf_trans.apply(*formula.get_arg());
        result = formula.ctx().makeLtlfPlusForall(ltlf_neg);
    }

    void PlusNegationTransformer::visit(const LTLfPlusForall& formula) {
        NegationTransformer ltlf_trans;
        ltlf_ptr ltlf_neg = ltlf_trans.apply(*formula.get_arg());
        result = formula.ctx().makeLtlfPlusExists(ltlf_neg);
    }

    void PlusNegationTransformer::visit(const LTLfPlusForallExists& formula) {
        NegationTransformer ltlf_trans;
        ltlf_ptr ltlf_neg = ltlf_trans.apply(*formula.get_arg());
        result = formula.ctx().makeLtlfPlusExistsForall(ltlf_neg);
    }

    void PlusNegationTransformer::visit(const LTLfPlusExistsForall& formula) {
        NegationTransformer ltlf_trans;
        ltlf_ptr ltlf_neg = ltlf_trans.apply(*formula.get_arg());
        result = formula.ctx().makeLtlfPlusForallExists(ltlf_neg);
    }

    ltlf_plus_ptr PlusNegationTransformer::apply(const LTLfPlusFormula& f) {
        f.accept(*this);
        return result;
    }

    ltlf_plus_ptr apply_negation(const LTLfPlusFormula& f) {
        auto visitor = PlusNegationTransformer{};
        return visitor.apply(f);
    }
}
}