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
#include <lydia/logic/ppltl/base.hpp>
#include <lydia/logic/ldlf/base.hpp>
#include <lydia/logic/ltlf/base.hpp>
#include <lydia/logic/pl/base.hpp>
#include <lydia/visitor.hpp>

namespace whitemech::lydia {

    /**
     * YNFTransformer. 
     * Visits a PPLTL formula and generates its YNF
     */
    class YNFTransformer : public Visitor {
        ppltl_ptr ynf_result;
        std::unordered_set<ppltl_ptr> y_sub; // Y subformulas
        std::unordered_set<ppltl_ptr> wy_sub; // WY subformulas
        std::unordered_set<ppltl_ptr> atoms; 

        public:
            void visit(const PPLTLTrue&) override;
            void visit(const PPLTLFalse&) override;
            void visit(const PPLTLAtom&) override;
            void visit(const PPLTLAnd&) override;
            void visit(const PPLTLOr&) override;
            void visit(const PPLTLNot&) override;
            void visit(const PPLTLYesterday&) override;
            void visit(const PPLTLWeakYesterday&) override;
            void visit(const PPLTLSince&) override;
            void visit(const PPLTLTriggered&) override;
            void visit(const PPLTLOnce&) override;
            void visit(const PPLTLHistorically&) override;

            std::unordered_set<ppltl_ptr> get_y_sub() const;
            std::unordered_set<ppltl_ptr> get_wy_sub() const;
            std::unordered_set<ppltl_ptr> get_atoms() const;

        ppltl_ptr apply(const PPLTLFormula& b);
    };

    std::shared_ptr<const PPLTLFormula> to_ynf(const PPLTLFormula&);

}