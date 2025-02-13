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

    class PPTLPlusDriver : public AbstractDriver<PPTLPlusFormula> {
        private:
            void parse_helper(std::istream& stream);

            PPTLPlusScanner* scanner = nullptr;
            PPTLPlusParser* parser = nullptr;

        public:
            ppltl_plus_ptr result;
            PPTLPlusDriver() : AbstractDriver() {}
            explicit PPTLPlusDriver(std::shared_ptr<AstManager> c):
                AbstractDriver(c) {}
            virtual ~PPTLPlusDriver();
            ppltl_plus_ptr get_result() override {return result;}
            void parse(const char* const filename) override;
            void parse(std::istream& iss);

            ppltl_ptr add_PPTLTrue() const;
            ppltl_ptr add_PPTLFalse() const;
            ppltl_ptr add_PPTLAtom(std::string s) const;
            ppltl_ptr add_PPTLAnd(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPTLOr(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPTLNot(ppltl_ptr& formula) const;
            ppltl_ptr add_PPTLYesterday(ppltl_ptr& formula) const;
            ppltl_ptr add_PPTLWeakYesterday(ppltl_ptr& formula) const;
            ppltl_ptr add_PPTLOnce(ppltl_ptr& formula) const;
            ppltl_ptr add_PPTLHistorically(ppltl_ptr& formula) const;
            ppltl_ptr add_PPTLSince(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPTLImplication(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPTLEquivalence(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
            ppltl_ptr add_PPTLStart() const;

            ppltl_plus_ptr add_PPTLPlusAnd(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const;
            ppltl_plus_ptr add_PPTLPlusOr(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const;
            ppltl_plus_ptr add_PPTLPlusNot(ppltl_plus_ptr& formula) const;
            ppltl_plus_ptr add_PPTLPlusImplication(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const;
            ppltl_plus_ptr add_PPTLPlusEquivalence(ppltl_plus_ptr& lhs, ppltl_plus_ptr& rhs) const;
            ppltl_plus_ptr add_PPTLPlusExists(ppltl_ptr& ppltl_formula);
            ppltl_plus_ptr add_PPTLPlusForall(ppltl_ptr& ppltl_formula);
            ppltl_plus_ptr add_PPTLPlusExistsForall(ppltl_ptr& ppltl_formula);
            ppltl_plus_ptr add_PPTLPlusForallExists(ppltl_ptr& ppltl_formula);

            std::ostream& print(std::ostream& stream) const;
    };
}