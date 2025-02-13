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

#include <algorithm>
#include <cstdint>
#include <memory>

#include <lydia/visitor.hpp>

namespace whitemech {
namespace lydia {

/*
 * Apply a negation.
 * - in case of boolean or temporal operator, apply the
 *   duality of negation to push a negation down;
 * - in case of atomic formula, return the negation of it
 */
class PurePastNegationTransformer : public Visitor {
public:
  ppltl_ptr result;
  void visit(const PPLTLTrue&) override;
  void visit(const PPLTLFalse&) override;
  void visit(const PPLTLAtom&) override;
  void visit(const PPLTLNot&) override;
  void visit(const PPLTLAnd&) override;
  void visit(const PPLTLOr&) override;
  void visit(const PPLTLYesterday&) override;
  void visit(const PPLTLWeakYesterday&) override;
  void visit(const PPLTLSince&) override;
  void visit(const PPLTLTriggered&) override;
  void visit(const PPLTLOnce&) override;
  void visit(const PPLTLHistorically&) override;

  ppltl_ptr apply(const PPLTLFormula& f);
};

ppltl_ptr apply_negation(const PPLTLFormula& f);

template <typename Function1, typename Function2, typename BinaryOp>
inline ppltl_ptr forward_call_to_arguments(const BinaryOp& formula,
                                          Function1 mapping_function,
                                          Function2 factory_function) {
  const auto& container = formula.get_args();
  auto new_container = vec_ppltl_formulas(container.size());
  std::transform(container.begin(), container.end(), new_container.begin(),
                 mapping_function);
  return factory_function(new_container);
}

} // namespace lydia
} // namespace whitemech