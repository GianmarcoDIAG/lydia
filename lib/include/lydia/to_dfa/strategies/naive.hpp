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

#include <lydia/atom_visitor.hpp>
#include <lydia/dfa.hpp>
#include <lydia/nnf.hpp>
#include <lydia/pl/logic.hpp>
#include <lydia/to_dfa/core.hpp>
#include <lydia/to_dfa/dfa_state.hpp>
#include <lydia/utils/misc.hpp>
#include <queue>
#include <utility>

namespace whitemech {
namespace lydia {

class NaiveStrategy : public Strategy {
private:
  const CUDD::Cudd &mgr;
  const size_t max_nb_bits;

public:
  explicit NaiveStrategy(const CUDD::Cudd &mgr, uint32_t max_nb_bits = 10)
      : mgr{mgr}, max_nb_bits{max_nb_bits} {};

  std::shared_ptr<dfa> to_dfa(const LDLfFormula &formula);
};

} // namespace lydia
} // namespace whitemech