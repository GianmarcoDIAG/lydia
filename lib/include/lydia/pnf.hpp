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

#include<lydia/logic/ltlfplus/base.hpp>
#include<lydia/logic/nnf.hpp>
#include<lydia/visitor.hpp>

namespace whitemech::lydia {

    enum PrefixQuantifier {
        Exists, // 0
        Forall, // 1
        ExistsForall, // 2
        ForallExists // 3
    };

    struct PNFResult {
        // ltlf_plus_ptr pnf_formula_; 
        std::unordered_map<ltlf_plus_ptr, PrefixQuantifier> subformula_to_quantifier_;
        std::unordered_map<ltlf_plus_ptr, std::string> subformula_to_color_;
        std::string color_formula_;
    };

    class PNFTransformer : public Visitor {
        private:
        protected:
            ltlf_plus_ptr ltlf_plus_result;

        public:
            // callbacks for LTLf+
            void visit(const LTLfPlusTrue&) override;
            void visit(const LTLfPlusFalse&) override;
            void visit(const LTLfPlusAnd&) override;
            void visit(const LTLfPlusOr&) override;
            void visit(const LTLfPlusNot&) override;
            void visit(const LTLfPlusExists&) override;
            void visit(const LTLfPlusForall&) override;
            void visit(const LTLfPlusExistsForall&) override;
            void visit(const LTLfPlusForallExists&) override;

            ltlf_plus_ptr apply(const LTLfPlusFormula& b);
    };

    class PNFVisitor : public Visitor {
        protected:
            PNFResult result;
        public:
            PNFVisitor() = default;
            // callbacks for LTLf+
            // void visit(const LTLfPlusTrue&) override;
            // void visit(const LTLfPlusFalse&) override; // (Gianmarco) never read. Use A(tt) and E(ff)
            void visit(const LTLfPlusAnd&) override;
            void visit(const LTLfPlusOr&) override;
            // void visit(const LTLfPlusNot&) override; (Gianmarco) not allowed in PNF LTLf+
            void visit(const LTLfPlusExists&) override;
            void visit(const LTLfPlusForall&) override;
            void visit(const LTLfPlusExistsForall&) override;
            void visit(const LTLfPlusForallExists&) override;

            PNFResult apply(const LTLfPlusFormula& b);
    };

    std::shared_ptr<const LTLfPlusFormula> to_pnf(const LTLfPlusFormula&);

    PNFResult get_pnf_result(const LTLfPlusFormula& pnf);

}