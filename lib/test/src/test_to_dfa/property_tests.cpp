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
#include "../data/formulas.hpp"
#include "../utils/to_dfa.hpp"
#include <catch.hpp>

namespace whitemech::lydia::Test {

TEST_CASE("Duality", "[to_dfa]") {
  auto strategy_maker = GENERATE(strategies());
  auto mgr_1 = CUDD::Cudd();
  auto mgr_2 = CUDD::Cudd();
  auto strategy_1 = strategy_maker(mgr_1);
  auto strategy_2 = strategy_maker(mgr_2);
  for (const auto &formula : FORMULAS) {
    SECTION("Test duality of " + formula) {
      adfa_ptr automaton_1 = to_dfa_from_formula_string(formula, *strategy_1);
      adfa_ptr automaton_2 =
          to_dfa_from_formula_string("!(" + formula + ")", *strategy_2);
      REQUIRE(compare<5>(*automaton_1, *automaton_2,
                         automaton_1->get_nb_variables(), not_equal));
    }
  }
}
} // namespace whitemech::lydia::Test