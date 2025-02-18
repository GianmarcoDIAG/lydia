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

#include <lydia/logic/ppltl/duality.hpp>
#include <lydia/logic/nnf.hpp>
#include <lydia/logic/ppltlplus/duality.hpp>
#include <lydia/logic/pp_pnf.hpp>
#include <sstream>
#include <ostream>
#include <stdexcept>

namespace whitemech::lydia {

    void PPPNFTransformer::visit(const PPLTLPlusTrue& x) {
        ppltl_plus_result = x.ctx().makePpltlPlusTrue();
    }

    void PPPNFTransformer::visit(const PPLTLPlusFalse& x) {
        ppltl_plus_result = x.ctx().makePpltlPlusFalse();
    }

    void PPPNFTransformer::visit(const PPLTLPlusAnd& x) {
        auto container = x.get_container();
        set_ppltl_plus_formulas new_container;
        for (auto& a : container) {
            new_container.insert(apply(*a));
        }
        ppltl_plus_result = x.ctx().makePpltlPlusAnd(new_container);
    }

    void PPPNFTransformer::visit(const PPLTLPlusOr& x) {
        auto container = x.get_container();
        set_ppltl_plus_formulas new_container;
        for (auto& a : container) {
            new_container.insert(apply(*a));
        }
        ppltl_plus_result = x.ctx().makePpltlPlusOr(new_container);
    }

    void PPPNFTransformer::visit(const PPLTLPlusNot& x) {
        ppltl_plus_result = apply_negation(*x.get_arg());
    }

    void PPPNFTransformer::visit(const PPLTLPlusExists& x) {
        ppltl_plus_result = x.ctx().makePpltlPlusExists(x.get_arg());
    }

    void PPPNFTransformer::visit(const PPLTLPlusForall& x) {
        ppltl_plus_result = x.ctx().makePpltlPlusForall(x.get_arg());
    }

    void PPPNFTransformer::visit(const PPLTLPlusForallExists& x) {
        ppltl_plus_result = x.ctx().makePpltlPlusForallExists(x.get_arg());
    }

    void PPPNFTransformer::visit(const PPLTLPlusExistsForall& x) {
        ppltl_plus_result = x.ctx().makePpltlPlusExistsForall(x.get_arg());
    }

    void PPPNFVisitor::visit(const PPLTLPlusAnd& x) {
        auto container = x.get_container();
        std::ostringstream s;
        s << "(";
        s << apply(**container.begin()).color_formula_;
        for (auto it = ++(container.begin()); it != container.end(); ++it)
            s << " & " << apply(**it).color_formula_;
        s << ")";
        result.color_formula_ = s.str();
    }

    void PPPNFVisitor::visit(const PPLTLPlusOr& x) {
        auto container = x.get_container();
        std::ostringstream s;
        s << "(";
        s << apply(**container.begin()).color_formula_;
        for (auto it = ++(container.begin()); it != container.end(); ++it)
            s << " | " << apply(**it).color_formula_;
        s << ")";
        result.color_formula_ = s.str();
    }

    void PPPNFVisitor::visit(const PPLTLPlusExists& x) {
        ppltl_plus_ptr x_ptr = nullptr;
        bool exists = false;
        for (const auto& [key, _] : result.subformula_to_color_)
            if (key.get()->is_equal(x)) {exists = true; x_ptr = key; break;}
        if (!(exists)) {
            x_ptr = std::make_shared<PPLTLPlusExists>(x);
            result.subformula_to_color_.emplace(x_ptr, std::to_string(result.subformula_to_color_.size()));
            result.subformula_to_quantifier_.emplace(x_ptr, PrefixQuantifier::Exists);
        }
        result.color_formula_ = result.subformula_to_color_[x_ptr];
    }

    void PPPNFVisitor::visit(const PPLTLPlusForall& x) {
        ppltl_plus_ptr x_ptr = nullptr;
        bool exists = false;
        for (const auto& [key, _] : result.subformula_to_color_)
            if (key.get()->is_equal(x)) {exists = true; x_ptr = key; break;}
        if (!(exists)) {
            x_ptr = std::make_shared<PPLTLPlusForall>(x);
            result.subformula_to_color_.emplace(x_ptr, std::to_string(result.subformula_to_color_.size()));
            result.subformula_to_quantifier_.emplace(x_ptr, PrefixQuantifier::Forall);
        }
        result.color_formula_ = result.subformula_to_color_[x_ptr];
    }

    void PPPNFVisitor::visit(const PPLTLPlusExistsForall& x) {
        ppltl_plus_ptr x_ptr = nullptr;
        bool exists = false;
        for (const auto& [key, _] : result.subformula_to_color_)
            if (key.get()->is_equal(x)) {exists = true; x_ptr = key; break;}
        if (!(exists)) {
            x_ptr = std::make_shared<PPLTLPlusExistsForall>(x);
            result.subformula_to_color_.emplace(x_ptr, std::to_string(result.subformula_to_color_.size()));
            result.subformula_to_quantifier_.emplace(x_ptr, PrefixQuantifier::ExistsForall);
        }
        result.color_formula_ = "!(" + result.subformula_to_color_[x_ptr] + ")";
    }

    void PPPNFVisitor::visit(const PPLTLPlusForallExists& x) {
        ppltl_plus_ptr x_ptr = nullptr;
        bool exists = false;
        for (const auto& [key, _] : result.subformula_to_color_)
            if (key.get()->is_equal(x)) {exists = true; x_ptr = key; break;}
        if (!(exists)) {
            x_ptr = std::make_shared<PPLTLPlusForallExists>(x);
            result.subformula_to_color_.emplace(x_ptr, std::to_string(result.subformula_to_color_.size()));
            result.subformula_to_quantifier_.emplace(x_ptr, PrefixQuantifier::ForallExists);
        }
        result.color_formula_ = result.subformula_to_color_[x_ptr];
    }

    ppltl_plus_ptr PPPNFTransformer::apply(const PPLTLPlusFormula& b) {
        b.accept(*this);
        return ppltl_plus_result;
    }

    PPPNFResult PPPNFVisitor::apply(const PPLTLPlusFormula& b) {
        b.accept(*this);
        return result;
    }

    std::shared_ptr<const PPLTLPlusFormula> to_pnf(const PPLTLPlusFormula& x) {
        PPPNFTransformer pnfTransformer;
        return pnfTransformer.apply(x);
    }

    PPPNFResult get_pnf_result(const PPLTLPlusFormula& x) {
        auto pnf_x = to_pnf(x);
        PPPNFVisitor pnfVisitor;
        // apply pnfVisitor to *pnf_x, so that formula is in PPPNF
        return pnfVisitor.apply(*pnf_x);
    }
}