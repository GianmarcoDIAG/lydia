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
#include <lydia/logic/ppltl/base.hpp>
#include <lydia/logic/ppltlplus/base.hpp>
#include <lydia/utils/compare.hpp>
#include <stdexcept>
#include <utility>

namespace whitemech::lydia {

    // PPLTL+ True

    hash_t PPLTLPlusTrue::compute_hash_() const { return type_code_id; }

    vec_ppltl_plus_formulas PPLTLPlusTrue::get_args() const { return {}; }

    bool PPLTLPlusTrue::is_equal(const Basic& o) const { return is_a<PPLTLPlusTrue>(o); }

    int PPLTLPlusTrue::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusTrue>(o));
        return 0;
    }

    ppltl_plus_ptr PPLTLPlusTrue::logical_not() const {return ctx().makePpltlPlusFalse(); }

    ppltl_ptr PPLTLPlusTrue::ppltl_arg() const {
        throw InvalidPPLTLPlusInput("PPLTLPlusTrue has no PPLTL arg");
    }

    // PPLTL+ False

    hash_t PPLTLPlusFalse::compute_hash_() const { return type_code_id; }

    vec_ppltl_plus_formulas PPLTLPlusFalse::get_args() const { return {}; }

    bool PPLTLPlusFalse::is_equal(const Basic& o) const { return is_a<PPLTLPlusFalse>(o); }

    int PPLTLPlusFalse::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusFalse>(o));
        return 0;
    }

    ppltl_plus_ptr PPLTLPlusFalse::logical_not() const { return ctx().makePpltlPlusTrue(); }

    ppltl_ptr PPLTLPlusFalse::ppltl_arg() const {
        throw InvalidPPLTLPlusInput("PPLTLPlusFalse has no PPLTL arg");
    }

    //  PPLTL+ And
    hash_t PPLTLPlusAnd::compute_hash_() const {
        hash_t seed = type_code_id;
        for (const auto&a : container_)
            hash_combine<Basic>(seed, *a);
        return seed;
    }

    PPLTLPlusAnd::PPLTLPlusAnd(AstManager&c, const set_ppltl_plus_formulas& s):
        PPLTLPlusFormula(c), container_{s} {
            this->type_code_ = type_code_id;
            if (!is_canonical(s)) {
                throw std::invalid_argument("PPLTLPlusAnd formula: arguments must be > 1");
            }
        }

    bool PPLTLPlusAnd::is_canonical(const set_ppltl_plus_formulas& container_) const {
        return container_.size() > 1;
    }

    vec_ppltl_plus_formulas PPLTLPlusAnd::get_args() const {
        vec_ppltl_plus_formulas v(container_.begin(), container_.end());
        return v;
    }

    int PPLTLPlusAnd::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusAnd>(o));
        return unified_compare(container_,
                         dynamic_cast<const PPLTLPlusAnd&>(o).get_container());
    }

    bool PPLTLPlusAnd::is_equal(const Basic& o) const {
        return is_a<PPLTLAnd>(o) and
            unified_eq(container_,
            dynamic_cast<const PPLTLPlusAnd&>(o).get_container());
    }

    const set_ppltl_plus_formulas& PPLTLPlusAnd::get_container() const { return container_; }

    ppltl_plus_ptr PPLTLPlusAnd::logical_not() const {
        auto container = this->get_container();
        set_ppltl_plus_formulas cont;
        for (auto& a : container) {
            cont.insert(a->logical_not());
        }
        return m_ctx->makePpltlPlusOr(cont);
    }

    ppltl_ptr PPLTLPlusAnd::ppltl_arg() const {
        throw InvalidPPLTLPlusInput("PPLTLPlusAnd has no PPLTL arg");
    }

    // PPLTL+ Or
    PPLTLPlusOr::PPLTLPlusOr(AstManager& c, const set_ppltl_plus_formulas& s):
        PPLTLPlusFormula(c), container_{s} {
            this->type_code_ = type_code_id;
            if (!is_canonical(s)) {
                throw std::invalid_argument("PPLTLPlusOr formula: arguments must be > 1");
            }
        }

    hash_t PPLTLPlusOr::compute_hash_() const {
        hash_t seed = type_code_id;
        for (const auto& a : container_)
            hash_combine<Basic>(seed, *a);
        return seed;
    }

    vec_ppltl_plus_formulas PPLTLPlusOr::get_args() const {
        vec_ppltl_plus_formulas v(container_.begin(), container_.end());
        return v;
    }

    int PPLTLPlusOr::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusOr>(o));
        return unified_compare(container_,
                         dynamic_cast<const PPLTLPlusOr&>(o).get_container());
    }

    bool PPLTLPlusOr::is_equal(const Basic& o) const {
        return is_a<PPLTLPlusOr>(o) and
            unified_eq(container_, dynamic_cast<const PPLTLPlusOr&>(o).get_container());
    }

    bool PPLTLPlusOr::is_canonical(const set_ppltl_plus_formulas& container_) const {
        return container_.size() > 1;
    }

    const set_ppltl_plus_formulas& PPLTLPlusOr::get_container() const { return container_; }

    ppltl_plus_ptr PPLTLPlusOr::logical_not() const {
        auto container = this->get_container();
        set_ppltl_plus_formulas cont;
        for (auto& a : container) {
            cont.insert(a->logical_not());
        }
        return m_ctx->makePpltlPlusAnd(cont);
    }

    ppltl_ptr PPLTLPlusOr::ppltl_arg() const {
        throw InvalidPPLTLPlusInput("PPLTLPlusOr has no PPLTL arg");
    }

    // PPLTL+ Not
    PPLTLPlusNot::PPLTLPlusNot(AstManager& c, const ppltl_plus_ptr& in) :
        PPLTLPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
        }

    hash_t PPLTLPlusNot::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic PPLTLPlusNot::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool PPLTLPlusNot::is_equal(const Basic& o) const {
        return is_a<PPLTLPlusNot>(o) and
            eq(*arg_, *dynamic_cast<const PPLTLPlusNot&>(o).get_arg());
    }

    int PPLTLPlusNot::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusNot>(o));
        return arg_->compare(*dynamic_cast<const PPLTLPlusNot&>(o).get_arg());
    }

    ppltl_plus_ptr PPLTLPlusNot::get_arg() const { return arg_; }

    ppltl_plus_ptr PPLTLPlusNot::logical_not() const { return this->get_arg(); }

    bool PPLTLPlusNot::is_canonical(const PPLTLPlusFormula& in) const { return true; }

    ppltl_ptr PPLTLPlusNot::ppltl_arg() const {
        throw InvalidPPLTLPlusInput("PPLTLPlusNot has no PPLTL arg");
    }

    // PPLTL+ Exists (E)
    PPLTLPlusExists::PPLTLPlusExists(AstManager& c, const ppltl_ptr& in) :
        PPLTLPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
        }

    hash_t PPLTLPlusExists::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic PPLTLPlusExists::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool PPLTLPlusExists::is_equal(const Basic& o) const {
        return is_a<PPLTLPlusExists>(o) and 
            eq(*arg_, *dynamic_cast<const PPLTLPlusExists&>(o).get_arg());
    }

    int PPLTLPlusExists::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusExists>(o));
        return arg_->compare(*dynamic_cast<const PPLTLPlusExists&>(o).get_arg());
    }

    bool PPLTLPlusExists::is_canonical(const PPLTLPlusFormula& s) const {
        return true;
    }

    ppltl_ptr PPLTLPlusExists::get_arg() const {
        return arg_;
    }

    ppltl_plus_ptr PPLTLPlusExists::logical_not() const {
        return m_ctx->makePpltlPlusForall(m_ctx->makePPLTLNot(this->arg_));
    } 

    ppltl_ptr PPLTLPlusExists::ppltl_arg() const {
        auto ppltl_arg = arg_;
        // apply no-empty semantics
        auto not_end = m_ctx->makePPLTLNotEnd();
        return m_ctx->makePPLTLAnd({ppltl_arg, not_end});
    }

    // PPLTL+ Forall (A)
    PPLTLPlusForall::PPLTLPlusForall(AstManager& c, const ppltl_ptr& in) :
        PPLTLPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
        }

    hash_t PPLTLPlusForall::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic PPLTLPlusForall::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool PPLTLPlusForall::is_equal(const Basic& o) const {
        return is_a<PPLTLPlusForall>(o) and 
            eq(*arg_, *dynamic_cast<const PPLTLPlusForall&>(o).get_arg());
    }

    int PPLTLPlusForall::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusForall>(o));
        return arg_->compare(*dynamic_cast<const PPLTLPlusForall&>(o).get_arg());
    }

    bool PPLTLPlusForall::is_canonical(const PPLTLPlusFormula& s) const {
        return true;
    }

    ppltl_ptr PPLTLPlusForall::get_arg() const {
        return arg_;
    }

    ppltl_plus_ptr PPLTLPlusForall::logical_not() const {
        return m_ctx->makePpltlPlusExists(m_ctx->makePPLTLNot(this->arg_));
    }

    ppltl_ptr PPLTLPlusForall::ppltl_arg() const {
        auto ppltl_arg = arg_;
        // apply no-empty semantics
        auto not_end = m_ctx->makePPLTLNotEnd();
        return m_ctx->makePPLTLAnd({ppltl_arg, not_end});
    }

    // PPLTL+ ExistsForall
    PPLTLPlusExistsForall::PPLTLPlusExistsForall(AstManager& c, const ppltl_ptr& in) :
        PPLTLPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
        }

     hash_t PPLTLPlusExistsForall::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic PPLTLPlusExistsForall::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool PPLTLPlusExistsForall::is_equal(const Basic& o) const {
        return is_a<PPLTLPlusExistsForall>(o) and 
            eq(*arg_, *dynamic_cast<const PPLTLPlusExistsForall&>(o).get_arg());
    }

    int PPLTLPlusExistsForall::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusExistsForall>(o));
        return arg_->compare(*dynamic_cast<const PPLTLPlusExistsForall&>(o).get_arg());
    }

    bool PPLTLPlusExistsForall::is_canonical(const PPLTLPlusFormula& s) const {
        return true;
    }

    ppltl_ptr PPLTLPlusExistsForall::get_arg() const {
        return arg_;
    }

    ppltl_plus_ptr PPLTLPlusExistsForall::logical_not() const {
        return m_ctx->makePpltlPlusForallExists(m_ctx->makePPLTLNot(this->arg_));
    } 

    ppltl_ptr PPLTLPlusExistsForall::ppltl_arg() const {
        auto ppltl_arg = arg_;
        // apply no-empty semantics
        auto not_end = m_ctx->makePPLTLNotEnd();
        return m_ctx->makePPLTLAnd({ppltl_arg, not_end});
    }

    // PPLTL+ ForallExists
    PPLTLPlusForallExists::PPLTLPlusForallExists(AstManager& c, const ppltl_ptr& in) :
        PPLTLPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
    }

    hash_t PPLTLPlusForallExists::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic PPLTLPlusForallExists::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool PPLTLPlusForallExists::is_equal(const Basic& o) const {
        return is_a<PPLTLPlusForallExists>(o) and 
            eq(*arg_, *dynamic_cast<const PPLTLPlusForallExists&>(o).get_arg());
    }

    int PPLTLPlusForallExists::compare_(const Basic& o) const {
        assert(is_a<PPLTLPlusForallExists>(o));
        return arg_->compare(*dynamic_cast<const PPLTLPlusForallExists&>(o).get_arg());
    }

    bool PPLTLPlusForallExists::is_canonical(const PPLTLPlusFormula& s) const {
        return true;
    }

    ppltl_ptr PPLTLPlusForallExists::get_arg() const {
        return arg_;
    }

    ppltl_plus_ptr PPLTLPlusForallExists::logical_not() const {
        return m_ctx->makePpltlPlusExistsForall(m_ctx->makePPLTLNot(this->arg_));
    }

    ppltl_ptr PPLTLPlusForallExists::ppltl_arg() const {
        auto ppltl_arg = arg_;
        // apply no-empty semantics
        auto not_end = m_ctx->makePPLTLNotEnd();
        return m_ctx->makePPLTLAnd({ppltl_arg, not_end});
    }
}