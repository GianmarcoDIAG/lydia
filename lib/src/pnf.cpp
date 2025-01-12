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

#include <lydia/logic/ltlf/duality.hpp>
#include <lydia/logic/nnf.hpp>
#include <lydia/logic/ltlfplus/duality.hpp>
#include <lydia/logic/pnf.hpp>
#include <sstream>
#include <ostream>
#include <stdexcept>

namespace whitemech::lydia {

    void PNFTransformer::visit(const LTLfPlusTrue& x) {
        ltlf_plus_result = x.ctx().makeLtlfPlusTrue();
    }

    void PNFTransformer::visit(const LTLfPlusFalse& x) {
        ltlf_plus_result = x.ctx().makeLtlfPlusFalse();
    }

    void PNFTransformer::visit(const LTLfPlusAnd& x) {
        auto container = x.get_container();
        set_ltlf_plus_formulas new_container;
        for (auto& a : container) {
            new_container.insert(apply(*a));
        }
        ltlf_plus_result = x.ctx().makeLtlfPlusAnd(new_container);
    }

    void PNFTransformer::visit(const LTLfPlusOr& x) {
        auto container = x.get_container();
        set_ltlf_plus_formulas new_container;
        for (auto& a : container) {
            new_container.insert(apply(*a));
        }
        ltlf_plus_result = x.ctx().makeLtlfPlusOr(new_container);
    }

    void PNFTransformer::visit(const LTLfPlusNot& x) {
        ltlf_plus_result = apply_negation(*x.get_arg());
    }

    void PNFTransformer::visit(const LTLfPlusExists& x) {
        ltlf_plus_result = x.ctx().makeLtlfPlusExists(x.get_arg());
    }

    void PNFTransformer::visit(const LTLfPlusForall& x) {
        ltlf_plus_result = x.ctx().makeLtlfPlusForall(x.get_arg());
    }

    void PNFTransformer::visit(const LTLfPlusForallExists& x) {
        ltlf_plus_result = x.ctx().makeLtlfPlusForallExists(x.get_arg());
    }

    void PNFTransformer::visit(const LTLfPlusExistsForall& x) {
        ltlf_plus_result = x.ctx().makeLtlfPlusExistsForall(x.get_arg());
    }

    void PNFVisitor::visit(const LTLfPlusAnd& x) {
        auto container = x.get_container();
        std::ostringstream s;
        s << "(";        
        s << apply(**container.begin()).color_formula_;
        for (auto it = ++(container.begin()); it != container.end(); ++it)
            s << " & " << apply(**it).color_formula_;
        s << ")";
        result.color_formula_ = s.str();
    }

    void PNFVisitor::visit(const LTLfPlusOr& x) {
        auto container = x.get_container();
        std::ostringstream s;
        s << "(";        
        s << apply(**container.begin()).color_formula_;
        for (auto it = ++(container.begin()); it != container.end(); ++it)
            s << " | " << apply(**it).color_formula_;
        s << ")";
        result.color_formula_ = s.str();
    }

    void PNFVisitor::visit(const LTLfPlusExists& x) {
        ltlf_plus_ptr x_ptr = nullptr;
        bool exists = false;
        for (const auto& [key, _] : result.subformula_to_color_)
            if (key.get()->is_equal(x)) {exists = true; x_ptr = key; break;}
        if (!(exists)) {
            x_ptr = std::make_shared<LTLfPlusExists>(x);
            result.subformula_to_color_.emplace(x_ptr, std::to_string(result.subformula_to_color_.size())); 
            result.subformula_to_quantifier_.emplace(x_ptr, PrefixQuantifier::Exists);    
        }
        result.color_formula_ = result.subformula_to_color_[x_ptr];
    }

    void PNFVisitor::visit(const LTLfPlusForall& x) {
        ltlf_plus_ptr x_ptr = nullptr;
        bool exists = false;
        for (const auto& [key, _] : result.subformula_to_color_)
            if (key.get()->is_equal(x)) {exists = true; x_ptr = key; break;}
        if (!(exists)) {
            x_ptr = std::make_shared<LTLfPlusForall>(x);
            result.subformula_to_color_.emplace(x_ptr, std::to_string(result.subformula_to_color_.size())); 
            result.subformula_to_quantifier_.emplace(x_ptr, PrefixQuantifier::Forall);    
        }
        result.color_formula_ = result.subformula_to_color_[x_ptr];
    }

    void PNFVisitor::visit(const LTLfPlusExistsForall& x) {
        ltlf_plus_ptr x_ptr = nullptr;
        bool exists = false;
        for (const auto& [key, _] : result.subformula_to_color_)
            if (key.get()->is_equal(x)) {exists = true; x_ptr = key; break;}
        if (!(exists)) {
            x_ptr = std::make_shared<LTLfPlusExistsForall>(x);
            result.subformula_to_color_.emplace(x_ptr, std::to_string(result.subformula_to_color_.size())); 
            result.subformula_to_quantifier_.emplace(x_ptr, PrefixQuantifier::ExistsForall);    
        }
        result.color_formula_ = "!(" + result.subformula_to_color_[x_ptr] + ")";
    }

    void PNFVisitor::visit(const LTLfPlusForallExists& x) {
        ltlf_plus_ptr x_ptr = nullptr;
        bool exists = false;
        for (const auto& [key, _] : result.subformula_to_color_)
            if (key.get()->is_equal(x)) {exists = true; x_ptr = key; break;}
        if (!(exists)) {
            x_ptr = std::make_shared<LTLfPlusForallExists>(x);
            result.subformula_to_color_.emplace(x_ptr, std::to_string(result.subformula_to_color_.size())); 
            result.subformula_to_quantifier_.emplace(x_ptr, PrefixQuantifier::ForallExists);    
        }
        result.color_formula_ = result.subformula_to_color_[x_ptr];
    }

    ltlf_plus_ptr PNFTransformer::apply(const LTLfPlusFormula& b) {
        b.accept(*this);
        return ltlf_plus_result;
    }

    PNFResult PNFVisitor::apply(const LTLfPlusFormula& b) {
        b.accept(*this);
        return result;
    }

    std::shared_ptr<const LTLfPlusFormula> to_pnf(const LTLfPlusFormula& x) {
        PNFTransformer pnfTransformer;
        return pnfTransformer.apply(x);
    }

    PNFResult get_pnf_result(const LTLfPlusFormula& x) {
        auto pnf_x = to_pnf(x);
        PNFVisitor pnfVisitor;
        // apply pnfVisitor to *pnf_x, so that formula is in PNF
        return pnfVisitor.apply(*pnf_x);
    }
}