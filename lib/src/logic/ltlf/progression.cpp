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

 #include<lydia/logic/ltlf/progression.hpp>

 namespace whitemech::lydia {

    // prog(true, π) = true
    void LTLfProgression::visit(const LTLfTrue& x) {
        result_ = x.ctx().makeLtlfTrue();
    }

    // prog(false, π) = false
    void LTLfProgression::visit(const LTLfFalse& x) {
        result_ = x.ctx().makeLtlfFalse();
    } 

    // prog(a, π) = true iff a ∈ π
    void LTLfProgression::visit(const LTLfAtom& x) {
        if (pi_->at(x.symbol->get_name())) result_ = x.ctx().makeLtlfTrue();
        else result_ = x.ctx().makeLtlfFalse();
    } 

    // prog(!a, π) = true iff a ∉ π
    void LTLfProgression::visit(const LTLfNot& x) {
        if (is_a<const LTLfAtom>(*x.get_arg())){
            auto r = apply(*x.get_arg());
            if (is_a<const LTLfTrue>(*r)) result_ = x.ctx().makeLtlfFalse();
            else if (is_a<const LTLfFalse>(*r)) result_ = x.ctx().makeLtlfTrue();
            else throw std::runtime_error("An unknown error has occured. Termination");
        }
        else throw std::runtime_error("Formula is NOT in NNF");
    }

    // prog(⋀_{i} φ_{i}, π) = ⋀_{i} prog(φ_{i}, π)
    void LTLfProgression::visit(const LTLfAnd& x) {
        auto container = x.get_container();
        set_ltlf_formulas new_container;
        for (auto& a : container) 
            new_container.insert(apply(*a));
        result_ = x.ctx().makeLtlfAnd(new_container);
    }

    // prog(V_{i} φ_{i}, π) = V_{i} prog(φ_{i}, π)
    void LTLfProgression::visit(const LTLfOr& x) {
        auto container = x.get_container();
        set_ltlf_formulas new_container;
        for (auto& a : container) 
            new_container.insert(apply(*a));
        result_ = x.ctx().makeLtlfOr(new_container);
    }

    // prog(X[!]φ, π) = φ
    void LTLfProgression::visit(const LTLfNext& x) {
        result_ = x.get_arg();
    }

    // prog(Xφ, π) = φ
    void LTLfProgression::visit(const LTLfWeakNext& x) {
        result_ = x.get_arg();
    }

    // prog(◇φ, π) = prog(φ, π) v ◇φ
    void LTLfProgression::visit(const LTLfEventually& x) {
        auto arg1 = apply(*x.get_arg()); // prog(φ)
        auto arg2 = x.ctx().makeLtlfEventually(x.get_arg()); // ◇φ
        result_ = x.ctx().makeLtlfOr({arg1, arg2}); // prog(φ) v ◇φ
    }

    // prog(□φ, π) = prog(φ, π) ∧ □φ
    void LTLfProgression::visit(const LTLfAlways& x) {
        auto arg1 = apply(*x.get_arg()); // prog(φ, π)
        auto arg2 = x.ctx().makeLtlfAlways(x.get_arg()); // □φ
        result_ = x.ctx().makeLtlfAnd({arg1, arg2}); // prog(φ, π) ∧ □φ
    }

    // prog(φ1 U φ2, π) = prog(φ2, π) v (prog(φ1, π) ∧ φ1 U φ2)
    void LTLfProgression::visit(const LTLfUntil& x) {
        auto p1 = apply(*x.get_args()[0]); // prog(φ1, π)
        auto p2 = apply(*x.get_args()[1]); // prog(φ2, π)
        auto u = x.ctx().makeLtlfUntil(x.get_args()[0], x.get_args()[1]); // φ1 U φ2
        auto a = x.ctx().makeLtlfAnd({p1, u}); // (prog(φ1, π) ∧ φ1 U φ2)
        result_ = x.ctx().makeLtlfOr({p2, a}); // prog(φ2, π) v (prog(φ1, π) ∧ φ1 U φ2)
    }

    // prog(φ1 R φ2, π) = prog(φ2, v) ∧ (prog(φ1, π) v φ1 R φ2)
    void LTLfProgression::visit(const LTLfRelease& x) {
        auto p1 = apply(*x.get_args()[0]); // prog(φ1, π)
        auto p2 = apply(*x.get_args()[1]); // prog(φ2, π)
        auto r = x.ctx().makeLtlfRelease(x.get_args()[0], x.get_args()[1]); // φ1 R φ2
        auto o = x.ctx().makeLtlfOr({p1, r}); // (prog(φ1, π) v φ1 R φ2)
        result_ = x.ctx().makeLtlfAnd({p2, o}); // prog(φ2, v) ∧ (prog(φ1, π) v φ1 R φ2)
    }

    LTLfProgression::LTLfProgression(const Interpretation& pi) {
        pi_ = std::make_shared<Interpretation>(pi);
    }

    ltlf_ptr LTLfProgression::apply(const LTLfFormula& x) {
        x.accept(*this);
        return result_;
    }

    void LTLfIsFinal::visit(const LTLfTrue& x) {
        result_ = x.ctx().makeLtlfTrue();
    }

    void LTLfIsFinal::visit(const LTLfFalse& x) {
        result_ = x.ctx().makeLtlfFalse();
    }

    void LTLfIsFinal::visit(const LTLfAtom& x) {
        result_ = x.ctx().makeLtlfFalse();
    }

    void LTLfIsFinal::visit(const LTLfNot& x) {
        result_ = x.ctx().makeLtlfFalse();
    }

    void LTLfIsFinal::visit(const LTLfAnd& x) {
        auto container = x.get_container();
        for (auto& a : container) 
            if (is_a<LTLfFalse>(*apply(*a))) result_ = x.ctx().makeLtlfFalse();
        result_ = x.ctx().makeLtlfTrue();  
    }

    void LTLfIsFinal::visit(const LTLfOr& x) {
        auto container = x.get_container();
        for (auto& a : container) 
            if (is_a<LTLfTrue>(*apply(*a))) result_ = x.ctx().makeLtlfTrue();
        result_ = x.ctx().makeLtlfFalse();  
    }

    void LTLfIsFinal::visit(const LTLfNext& x) {
        result_ = x.ctx().makeLtlfFalse();
    }

    void LTLfIsFinal::visit(const LTLfWeakNext& x) {
        result_ = x.ctx().makeLtlfTrue();
    }

    void LTLfIsFinal::visit(const LTLfEventually& x) {
        result_ = x.ctx().makeLtlfFalse();
    }

    void LTLfIsFinal::visit(const LTLfAlways& x) {
        result_ = x.ctx().makeLtlfTrue();
    }

    void LTLfIsFinal::visit(const LTLfUntil& x) {
        result_ = x.ctx().makeLtlfFalse();
    }

    void LTLfIsFinal::visit(const LTLfRelease& x) {
        result_ = x.ctx().makeLtlfTrue();
    }

    ltlf_ptr LTLfIsFinal::apply(const LTLfFormula& x) {
        x.accept(*this);
        return result_;
    }

    std::shared_ptr<const LTLfFormula> progression_aux(const LTLfFormula& x, History& h) {
        if (h.size() == 1) {
            LTLfProgression p(h[0]);
            return p.apply(x);
        } else {
            LTLfProgression p(h[0]);
            auto x_prime = p.apply(x);
            h.erase(h.begin());
            return progression_aux(*x_prime, h);
        }
    }

    std::shared_ptr<const LTLfFormula> progression(const LTLfFormula& x, History& h) {
        auto nnf = to_nnf(x);
        return progression_aux(*nnf, h);
    }
 }