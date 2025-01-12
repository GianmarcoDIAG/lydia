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

#include<lydia/logic/ltlf/duality.hpp>
#include<lydia/logic/ltlfplus/base.hpp>
#include<lydia/visitor.hpp>

namespace whitemech {
namespace lydia {

    /*
    * Apply a negation to LTLf+
    * - in case of Boolean or prefix quantifier apply the 
    * duality of negation to push a negation down.
    * It also apply the negation to inner LTLf
    */
   class PlusNegationTransformer: public Visitor {
    public:
    ltlf_plus_ptr result;
    void visit(const LTLfPlusTrue&) override;
    void visit(const LTLfPlusFalse&) override;
    void visit(const LTLfPlusNot&) override;
    void visit(const LTLfPlusAnd&) override;
    void visit(const LTLfPlusOr&) override;
    void visit(const LTLfPlusExists&) override;
    void visit(const LTLfPlusForall&) override;
    void visit(const LTLfPlusForallExists&) override;
    void visit(const LTLfPlusExistsForall&) override;

    ltlf_plus_ptr apply(const LTLfPlusFormula& f);
   };

  ltlf_plus_ptr apply_negation(const LTLfPlusFormula& f);

  template<typename Function1, typename Function2, typename BinaryOp>
  inline ltlf_plus_ptr forward_call_in(const BinaryOp& formula,
  Function1 mapping_function, Function2 factory_function) {
    const auto& container = formula.get_args();
    auto new_container = vec_ltlf_plus_formulas(container.size());
    std::transform(container.begin(), container.end(), new_container.begin(), mapping_function);
    return factory_function(new_container);
  }
}
}    