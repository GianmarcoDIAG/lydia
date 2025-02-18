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

#include<lydia/logic/ppltlplus/duality.hpp>
#include<lydia/logic/nnf.hpp>
#include<lydia/logic/pp_pnf.hpp>

namespace whitemech {
namespace lydia {

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusTrue& formula) {
        result = formula.ctx().makePpltlPlusFalse();
    }

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusFalse& formula) {
        result = formula.ctx().makePpltlPlusTrue();
    } 

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusAnd& formula) {
        result = forward_call_in(
            formula, [this](const ppltl_plus_ptr& formula){return apply(*formula); },
            [formula](const vec_ltlf_plus_formulas& container) {
                set_ppltl_plus_formulas set(container.begin(), container.end());
                return formula.ctx().makePpltlPlusOr(set);
            }); 
    }

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusOr& formula) {
        result = forward_call_in(
            formula, [this](const ppltl_plus_ptr& formula){return apply(*formula);},
            [formula](const vec_ltlf_plus_formulas& container) {
                set_ppltl_plus_formulas set(container.begin(), container.end());
                return formula.ctx().makePpltlPlusAnd(set);
            });
    }

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusNot& formula) {
        result = to_pnf(*formula.get_arg());
    }

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusExists& formula) {
        PurePastNegationTransformer ppltl_trans;
        ppltl_ptr ppltl_neg = ppltl_trans.apply(*formula.get_arg());
        result = formula.ctx().makePpltlPlusForall(ppltl_neg);
    }

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusForall& formula) {
        PurePastNegationTransformer ppltl_trans;
        ppltl_ptr ppltl_neg = ppltl_trans.apply(*formula.get_arg());
        result = formula.ctx().makePpltlPlusExists(ppltl_neg);
    }

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusForallExists& formula) {
        PurePastNegationTransformer ppltl_trans;
        ppltl_ptr ppltl_neg = ppltl_trans.apply(*formula.get_arg());
        result = formula.ctx().makePpltlPlusExistsForall(ppltl_neg);
    }

    void PurePastPlusNegationTransformer::visit(const PPLTLPlusExistsForall& formula) {
        PurePastNegationTransformer ppltl_trans;
        ppltl_ptr ppltl_neg = ppltl_trans.apply(*formula.get_arg());
        result = formula.ctx().makePpltlPlusForallExists(ppltl_neg);
    }

    ppltl_plus_ptr PurePastPlusNegationTransformer::apply(const PPLTLPlusFormula& f) {
        f.accept(*this);
        return result;
    }

    ppltl_plus_ptr apply_negation(const PPLTLPlusFormula& f) {
        auto visitor = PurePastPlusNegationTransformer{};
        return visitor.apply(f);
    }
}
}