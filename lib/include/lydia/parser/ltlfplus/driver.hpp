#pragma once
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

#include <cstddef>
#include <istream>
#include <string>
#include <utility>

#include <lydia/ast/base.hpp>
#include <lydia/logic/ltlf/base.hpp>
#include <lydia/logic/ltlfplus/base.hpp>
#include <lydia/logic/symbol.hpp>

#include "lydia/parser/ltlfplus/parser.tab.hh"
#include <lydia/parser/abstract_driver.hpp>
#include <lydia/parser/ltlfplus/scanner.hpp>
// #include <lydia/parser/ltlfplus/driver.hpp>

namespace whitemech::lydia::parsers::ltlfplus {

    class LTLfPlusDriver : public AbstractDriver {
        private:
            void parse_helper(std::istream& stream);

            LTLfPlusScanner* scanner = nullptr;
            LTLfPlusParser* parser = nullptr;

        public:
            ltlf_plus_ptr result;
            LTLfPlusDriver() : AbstractDriver() {}
            explicit LTLfPlusDriver(std::shared_ptr<AstManager> c): 
                AbstractDriver(c) {}
            virtual ~LTLfPlusDriver();
            ast_ptr get_result() override {return result;}
            void parse(const char* const filename) override;
            void parse(std::istream& iss);

            ltlf_ptr add_LTLfTrue() const;
            ltlf_ptr add_LTLfFalse() const;
            ltlf_ptr add_LTLfAtom(std::string s) const;
            ltlf_ptr add_LTLfAnd(ltlf_ptr& lhs, ltlf_ptr& rhs) const;
            ltlf_ptr add_LTLfOr(ltlf_ptr& lhs, ltlf_ptr& rhs) const;
            ltlf_ptr add_LTLfNot(ltlf_ptr& formula) const;
            ltlf_ptr add_LTLfNext(ltlf_ptr& formula) const;
            ltlf_ptr add_LTLfWeakNext(ltlf_ptr& formula) const;
            ltlf_ptr add_LTLfEventually(ltlf_ptr& formula) const;
            ltlf_ptr add_LTLfAlways(ltlf_ptr& formula) const;
            ltlf_ptr add_LTLfUntil(ltlf_ptr& lhs, ltlf_ptr& rhs) const;
            ltlf_ptr add_LTLfRelease(ltlf_ptr& lhs, ltlf_ptr& rhs) const;
            ltlf_ptr add_LTLfImplication(ltlf_ptr& lhs, ltlf_ptr& rhs) const;
            ltlf_ptr add_LTLfEquivalence(ltlf_ptr& lhs, ltlf_ptr& rhs) const;

            ltlf_plus_ptr add_LTLfPlusAnd(ltlf_plus_ptr& lhs, ltlf_plus_ptr& rhs) const;
            ltlf_plus_ptr add_LTLfPlusOr(ltlf_plus_ptr& lhs, ltlf_plus_ptr& rhs) const;
            ltlf_plus_ptr add_LTLfPlusNot(ltlf_plus_ptr& formula) const;
            ltlf_plus_ptr add_LTLfPlusImplication(ltlf_plus_ptr& lhs, ltlf_plus_ptr& rhs) const;
            ltlf_plus_ptr add_LTLfPlusEquivalence(ltlf_plus_ptr& lhs, ltlf_plus_ptr& rhs) const;
            ltlf_plus_ptr add_LTLfPlusExists(ltlf_ptr& ltlf_formula);
            ltlf_plus_ptr add_LTLfPlusForall(ltlf_ptr& ltlf_formula);
            ltlf_plus_ptr add_LTLfPlusExistsForall(ltlf_ptr& ltlf_formula);
            ltlf_plus_ptr add_LTLfPlusForallExists(ltlf_ptr& ltlf_formula);

            std::ostream& print(std::ostream& stream) const;
    };
}