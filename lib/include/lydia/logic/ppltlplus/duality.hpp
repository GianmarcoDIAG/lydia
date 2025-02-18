#pragma once
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

#include<algorithm>
#include<cstdint>
#include<memory>

#include<lydia/logic/ppltl/duality.hpp>
#include<lydia/logic/ppltlplus/base.hpp>
#include<lydia/visitor.hpp>

namespace whitemech {
namespace lydia {

    /*
    * Apply a negation to PPLTL+
    * - in case of Boolean or prefix quantifier apply the 
    * duality of negation to push a negation down.
    * It also apply the negation to inner PPLTL
    */
   class PurePastPlusNegationTransformer: public Visitor {
    public:
    ppltl_plus_ptr result;
    void visit(const PPLTLPlusTrue&) override;
    void visit(const PPLTLPlusFalse&) override;
    void visit(const PPLTLPlusNot&) override;
    void visit(const PPLTLPlusAnd&) override;
    void visit(const PPLTLPlusOr&) override;
    void visit(const PPLTLPlusExists&) override;
    void visit(const PPLTLPlusForall&) override;
    void visit(const PPLTLPlusForallExists&) override;
    void visit(const PPLTLPlusExistsForall&) override;

    ppltl_plus_ptr apply(const PPLTLPlusFormula& f);
   };

  ppltl_plus_ptr apply_negation(const PPLTLPlusFormula& f);

  template<typename Function1, typename Function2, typename BinaryOp>
  inline ppltl_plus_ptr forward_call_in(const BinaryOp& formula,
  Function1 mapping_function, Function2 factory_function) {
    const auto& container = formula.get_args();
    auto new_container = vec_ppltl_plus_formulas(container.size());
    std::transform(container.begin(), container.end(), new_container.begin(), mapping_function);
    return factory_function(new_container);
  }
}
}    