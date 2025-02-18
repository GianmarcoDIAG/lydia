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

#include<lydia/logic/ppltlplus/base.hpp>
#include<lydia/logic/nnf.hpp>
#include<lydia/visitor.hpp>

namespace whitemech::lydia {

    enum PrefixQuantifier {
        Exists, // 0
        Forall, // 1
        ExistsForall, // 2
        ForallExists // 3
    };

    struct PPPNFResult {
        // ppltl_plus_ptr pnf_formula_; 
        std::unordered_map<ppltl_plus_ptr, PrefixQuantifier> subformula_to_quantifier_;
        std::unordered_map<ppltl_plus_ptr, std::string> subformula_to_color_;
        std::string color_formula_;
    };

    class PPPNFTransformer : public Visitor {
        private:
        protected:
            ppltl_plus_ptr ppltl_plus_result;

        public:
            // callbacks for PPLTL+
            void visit(const PPLTLPlusTrue&) override;
            void visit(const PPLTLPlusFalse&) override;
            void visit(const PPLTLPlusAnd&) override;
            void visit(const PPLTLPlusOr&) override;
            void visit(const PPLTLPlusNot&) override;
            void visit(const PPLTLPlusExists&) override;
            void visit(const PPLTLPlusForall&) override;
            void visit(const PPLTLPlusExistsForall&) override;
            void visit(const PPLTLPlusForallExists&) override;

            ppltl_plus_ptr apply(const PPLTLPlusFormula& b);
    };

    class PPPNFVisitor : public Visitor {
        protected:
            PPPNFResult result;
        public:
            PPPNFVisitor() = default;
            // callbacks for PPLTL+
            // void visit(const PPLTLPlusTrue&) override;
            // void visit(const PPLTLPlusFalse&) override; // (Gianmarco) never read. Use A(tt) and E(ff)
            void visit(const PPLTLPlusAnd&) override;
            void visit(const PPLTLPlusOr&) override;
            // void visit(const PPLTLPlusNot&) override; (Gianmarco) not allowed in PPPNF PPLTL+
            void visit(const PPLTLPlusExists&) override;
            void visit(const PPLTLPlusForall&) override;
            void visit(const PPLTLPlusExistsForall&) override;
            void visit(const PPLTLPlusForallExists&) override;

            PPPNFResult apply(const PPLTLPlusFormula& b);
    };

    std::shared_ptr<const PPLTLPlusFormula> to_pnf(const PPLTLPlusFormula&);

    PPPNFResult get_pnf_result(const PPLTLPlusFormula& pnf);

}