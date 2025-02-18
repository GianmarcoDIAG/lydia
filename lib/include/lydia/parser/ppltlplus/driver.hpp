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
#include <lydia/logic/ppltl/base.hpp>
#include <lydia/logic/ppltlplus/base.hpp>
#include <lydia/logic/symbol.hpp>

#include "lydia/parser/ppltlplus/parser.tab.hh"
#include <lydia/parser/abstract_driver.hpp>
#include <lydia/parser/ppltlplus/scanner.hpp>

namespace whitemech::lydia::parsers::ppltlplus {

    class PPLTLPlusDriver : public AbstractDriver {
        private:
            void parse_helper(std::istream& stream);

            PPLTLPlusScanner* scanner = nullptr;
            PPLTLPlusParser* parser = nullptr;

        public:
            ppltl_plus_ptr result;
            PPLTLPlusDriver() : AbstractDriver() {}
            explicit PPLTLPlusDriver(std::shared_ptr<AstManager> c):
                AbstractDriver(c) {}
            virtual ~PPLTLPlusDriver();
            ast_ptr get_result() override {return result;}
            void parse(const char* const filename) override;
            void parse(std::istream& iss);

            ppltl_ptr add_PPLTLTrue() const;
            ppltl_ptr add_PPLTLFalse() const;
            ppltl_ptr add_PPLTLAtom(std::string s) const;
            ppltl_ptr add_PPLTLAnd(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPLTLOr(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPLTLNot(ppltl_ptr& formula) const;
            ppltl_ptr add_PPLTLYesterday(ppltl_ptr& formula) const;
            ppltl_ptr add_PPLTLWeakYesterday(ppltl_ptr& formula) const;
            ppltl_ptr add_PPLTLOnce(ppltl_ptr& formula) const;
            ppltl_ptr add_PPLTLHistorically(ppltl_ptr& formula) const;
            ppltl_ptr add_PPLTLSince(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPLTLImplication(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPLTLEquivalence(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPLTLStart() const;

            ppltl_plus_ptr add_PPLTLPlusAnd(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const;
            ppltl_plus_ptr add_PPLTLPlusOr(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const;
            ppltl_plus_ptr add_PPLTLPlusNot(ppltl_plus_ptr& formula) const;
            ppltl_plus_ptr add_PPLTLPlusImplication(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const;
            ppltl_plus_ptr add_PPLTLPlusEquivalence(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const;
            ppltl_plus_ptr add_PPLTLPlusExists(ppltl_ptr& ppltl_formula);
            ppltl_plus_ptr add_PPLTLPlusForall(ppltl_ptr& ppltl_formula);
            ppltl_plus_ptr add_PPLTLPlusExistsForall(ppltl_ptr& ppltl_formula);
            ppltl_plus_ptr add_PPLTLPlusForallExists(ppltl_ptr& ppltl_formula);

            std::ostream& print(std::ostream& stream) const;
    };
}