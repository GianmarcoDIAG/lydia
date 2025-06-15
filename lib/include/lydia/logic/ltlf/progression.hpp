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

#include <cassert>
#include <lydia/basic.hpp>
#include <lydia/logic/symbol.hpp>
#include <lydia/logic/ltlf/base.hpp>
#include <lydia/utils/compare.hpp>
#include <lydia/logic/nnf.hpp>
#include <utility>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <lydia/utils/print.hpp>


namespace whitemech::lydia {

    typedef std::unordered_map<std::string, bool> Interpretation;
    typedef std::vector<Interpretation> History;

    class LTLfProgression : Visitor {

        protected:
            ltlf_ptr result_;
            std::shared_ptr<Interpretation> pi_;

        public:
            void visit(const LTLfTrue&) override;
            void visit(const LTLfFalse&) override;
            void visit(const LTLfAtom&) override;
            void visit(const LTLfAnd&) override;
            void visit(const LTLfOr&) override;
            void visit(const LTLfNot&) override; // ATTENTION: we assume formulas in NNFs. Negation appears only before atoms
            void visit(const LTLfNext&) override;
            void visit(const LTLfWeakNext&) override;
            void visit(const LTLfUntil&) override;
            void visit(const LTLfRelease&) override;
            void visit(const LTLfEventually&) override;
            void visit(const LTLfAlways&) override;

            ltlf_ptr apply(const LTLfFormula&);
            LTLfProgression(const Interpretation& pi);
    };

    class LTLfIsFinal : Visitor {

        protected:
            ltlf_ptr result_;

        public:
            void visit(const LTLfTrue&) override;
            void visit(const LTLfFalse&) override;
            void visit(const LTLfAtom&) override;
            void visit(const LTLfAnd&) override;
            void visit(const LTLfOr&) override;
            void visit(const LTLfNot&) override; // ATTENTION: we assume formulas in NNFs. Negation appears only before atoms
            void visit(const LTLfNext&) override;
            void visit(const LTLfWeakNext&) override;
            void visit(const LTLfUntil&) override;
            void visit(const LTLfRelease&) override;
            void visit(const LTLfEventually&) override;
            void visit(const LTLfAlways&) override;

            ltlf_ptr apply(const LTLfFormula&);
            // LTLfIsFinal(const LTLfFormula&);
    };

    // progression wrt history (interpretation is a history of length 1)
    std::shared_ptr<const LTLfFormula> progression_aux(const LTLfFormula&, History&);
    std::shared_ptr<const LTLfFormula> progression(const LTLfFormula&, History&);
    // progression wrt empty trace
    std::shared_ptr<const LTLfFormula> progression_aux(const LTLfFormula&);
    std::shared_ptr<const LTLfFormula> progression(const LTLfFormula&);
}
