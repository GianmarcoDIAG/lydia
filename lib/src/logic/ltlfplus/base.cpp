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
#include <lydia/logic/ltlf/base.hpp>
#include <lydia/logic/ltlfplus/base.hpp>
#include <lydia/utils/compare.hpp>
#include <stdexcept>
#include <utility>

namespace whitemech::lydia {

    // LTLf+ True

    hash_t LTLfPlusTrue::compute_hash_() const { return type_code_id; }

    vec_ltlf_plus_formulas LTLfPlusTrue::get_args() const { return {}; }

    bool LTLfPlusTrue::is_equal(const Basic& o) const { return is_a<LTLfPlusTrue>(o); }

    int LTLfPlusTrue::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusTrue>(o));
        return 0;
    }

    ltlf_plus_ptr LTLfPlusTrue::logical_not() const {return ctx().makeLtlfPlusFalse(); }

    ltlf_ptr LTLfPlusTrue::ltlf_arg() const {
        throw InvalidLTLfPlusInput("LTLfPlusTrue has no LTLf arg");
    }

    // LTLf+ False

    hash_t LTLfPlusFalse::compute_hash_() const { return type_code_id; }

    vec_ltlf_plus_formulas LTLfPlusFalse::get_args() const { return {}; }

    bool LTLfPlusFalse::is_equal(const Basic& o) const { return is_a<LTLfPlusFalse>(o); }

    int LTLfPlusFalse::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusFalse>(o));
        return 0;
    }

    ltlf_plus_ptr LTLfPlusFalse::logical_not() const { return ctx().makeLtlfPlusTrue(); }

    ltlf_ptr LTLfPlusFalse::ltlf_arg() const {
        throw InvalidLTLfPlusInput("LTLfPlusFalse has no LTLf arg");
    }

    //  LTLf+ And
    hash_t LTLfPlusAnd::compute_hash_() const {
        hash_t seed = type_code_id;
        for (const auto&a : container_)
            hash_combine<Basic>(seed, *a);
        return seed;
    }

    LTLfPlusAnd::LTLfPlusAnd(AstManager&c, const set_ltlf_plus_formulas& s):
        LTLfPlusFormula(c), container_{s} {
            this->type_code_ = type_code_id;
            if (!is_canonical(s)) {
                throw std::invalid_argument("LTLfPlusAnd formula: arguments must be > 1");
            }
        }

    bool LTLfPlusAnd::is_canonical(const set_ltlf_plus_formulas& container_) const {
        return container_.size() > 1;
    }

    vec_ltlf_plus_formulas LTLfPlusAnd::get_args() const {
        vec_ltlf_plus_formulas v(container_.begin(), container_.end());
        return v;
    }

    int LTLfPlusAnd::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusAnd>(o));
        return unified_compare(container_,
                         dynamic_cast<const LTLfPlusAnd&>(o).get_container());
    }

    bool LTLfPlusAnd::is_equal(const Basic& o) const {
        return is_a<LTLfAnd>(o) and
            unified_eq(container_,
            dynamic_cast<const LTLfPlusAnd&>(o).get_container());
    }

    const set_ltlf_plus_formulas& LTLfPlusAnd::get_container() const { return container_; }

    ltlf_plus_ptr LTLfPlusAnd::logical_not() const {
        auto container = this->get_container();
        set_ltlf_plus_formulas cont;
        for (auto& a : container) {
            cont.insert(a->logical_not());
        }
        return m_ctx->makeLtlfPlusOr(cont);
    }

    ltlf_ptr LTLfPlusAnd::ltlf_arg() const {
        throw InvalidLTLfPlusInput("LTLfPlusAnd has no LTLf arg");
    }

    // LTLf+ Or
    LTLfPlusOr::LTLfPlusOr(AstManager& c, const set_ltlf_plus_formulas& s):
        LTLfPlusFormula(c), container_{s} {
            this->type_code_ = type_code_id;
            if (!is_canonical(s)) {
                throw std::invalid_argument("LTLfPlusOr formula: arguments must be > 1");
            }
        }

    hash_t LTLfPlusOr::compute_hash_() const {
        hash_t seed = type_code_id;
        for (const auto& a : container_)
            hash_combine<Basic>(seed, *a);
        return seed;
    }

    vec_ltlf_plus_formulas LTLfPlusOr::get_args() const {
        vec_ltlf_plus_formulas v(container_.begin(), container_.end());
        return v;
    }

    int LTLfPlusOr::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusOr>(o));
        return unified_compare(container_,
                         dynamic_cast<const LTLfPlusOr&>(o).get_container());
    }

    bool LTLfPlusOr::is_equal(const Basic& o) const {
        return is_a<LTLfPlusOr>(o) and
            unified_eq(container_, dynamic_cast<const LTLfPlusOr&>(o).get_container());
    }

    bool LTLfPlusOr::is_canonical(const set_ltlf_plus_formulas& container_) const {
        return container_.size() > 1;
    }

    const set_ltlf_plus_formulas& LTLfPlusOr::get_container() const { return container_; }

    ltlf_plus_ptr LTLfPlusOr::logical_not() const {
        auto container = this->get_container();
        set_ltlf_plus_formulas cont;
        for (auto& a : container) {
            cont.insert(a->logical_not());
        }
        return m_ctx->makeLtlfPlusAnd(cont);
    }

    ltlf_ptr LTLfPlusOr::ltlf_arg() const {
        throw InvalidLTLfPlusInput("LTLfPlusOr has no LTLf arg");
    }

    // LTLf+ Not
    LTLfPlusNot::LTLfPlusNot(AstManager& c, const ltlf_plus_ptr& in) :
        LTLfPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
        }

    hash_t LTLfPlusNot::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic LTLfPlusNot::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool LTLfPlusNot::is_equal(const Basic& o) const {
        return is_a<LTLfPlusNot>(o) and
            eq(*arg_, *dynamic_cast<const LTLfPlusNot&>(o).get_arg());
    }

    int LTLfPlusNot::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusNot>(o));
        return arg_->compare(*dynamic_cast<const LTLfPlusNot&>(o).get_arg());
    }

    ltlf_plus_ptr LTLfPlusNot::get_arg() const { return arg_; }

    ltlf_plus_ptr LTLfPlusNot::logical_not() const { return this->get_arg(); }

    bool LTLfPlusNot::is_canonical(const LTLfPlusFormula& in) const { return true; }

    ltlf_ptr LTLfPlusNot::ltlf_arg() const {
        throw InvalidLTLfPlusInput("LTLfPlusNot has no LTLf arg");
    }

    // LTLf+ Exists (E)
    LTLfPlusExists::LTLfPlusExists(AstManager& c, const ltlf_ptr& in) :
        LTLfPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
        }

    hash_t LTLfPlusExists::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic LTLfPlusExists::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool LTLfPlusExists::is_equal(const Basic& o) const {
        return is_a<LTLfPlusExists>(o) and 
            eq(*arg_, *dynamic_cast<const LTLfPlusExists&>(o).get_arg());
    }

    int LTLfPlusExists::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusExists>(o));
        return arg_->compare(*dynamic_cast<const LTLfPlusExists&>(o).get_arg());
    }

    bool LTLfPlusExists::is_canonical(const LTLfPlusFormula& s) const {
        return true;
    }

    ltlf_ptr LTLfPlusExists::get_arg() const {
        return arg_;
    }

    ltlf_plus_ptr LTLfPlusExists::logical_not() const {
        return m_ctx->makeLtlfPlusForall(m_ctx->makeLtlfNot(this->arg_));       
    } 

    ltlf_ptr LTLfPlusExists::ltlf_arg() const {
        auto ltlf_arg = arg_;
        // apply no-empty semantics
        auto not_end = m_ctx->makeLtlfNotEnd();
        return m_ctx->makeLtlfAnd({ltlf_arg, not_end});
    }

    // LTLf+ Forall (A)
    LTLfPlusForall::LTLfPlusForall(AstManager& c, const ltlf_ptr& in) :
        LTLfPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
        }

    hash_t LTLfPlusForall::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic LTLfPlusForall::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool LTLfPlusForall::is_equal(const Basic& o) const {
        return is_a<LTLfPlusForall>(o) and 
            eq(*arg_, *dynamic_cast<const LTLfPlusForall&>(o).get_arg());
    }

    int LTLfPlusForall::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusForall>(o));
        return arg_->compare(*dynamic_cast<const LTLfPlusForall&>(o).get_arg());
    }

    bool LTLfPlusForall::is_canonical(const LTLfPlusFormula& s) const {
        return true;
    }

    ltlf_ptr LTLfPlusForall::get_arg() const {
        return arg_;
    }

    ltlf_plus_ptr LTLfPlusForall::logical_not() const {
        return m_ctx->makeLtlfPlusExists(m_ctx->makeLtlfNot(this->arg_));       
    }

    ltlf_ptr LTLfPlusForall::ltlf_arg() const {
        auto ltlf_arg = arg_;
        // apply no-empty semantics
        auto not_end = m_ctx->makeLtlfNotEnd();
        return m_ctx->makeLtlfAnd({ltlf_arg, not_end});
    }

    // LTLf+ ExistsForall
    LTLfPlusExistsForall::LTLfPlusExistsForall(AstManager& c, const ltlf_ptr& in) :
        LTLfPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
        }

     hash_t LTLfPlusExistsForall::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic LTLfPlusExistsForall::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool LTLfPlusExistsForall::is_equal(const Basic& o) const {
        return is_a<LTLfPlusExistsForall>(o) and 
            eq(*arg_, *dynamic_cast<const LTLfPlusExistsForall&>(o).get_arg());
    }

    int LTLfPlusExistsForall::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusExistsForall>(o));
        return arg_->compare(*dynamic_cast<const LTLfPlusExistsForall&>(o).get_arg());
    }

    bool LTLfPlusExistsForall::is_canonical(const LTLfPlusFormula& s) const {
        return true;
    }

    ltlf_ptr LTLfPlusExistsForall::get_arg() const {
        return arg_;
    }

    ltlf_plus_ptr LTLfPlusExistsForall::logical_not() const {
        return m_ctx->makeLtlfPlusForallExists(m_ctx->makeLtlfNot(this->arg_));
    } 

    ltlf_ptr LTLfPlusExistsForall::ltlf_arg() const {
        auto ltlf_arg = arg_;
        // apply no-empty semantics
        auto not_end = m_ctx->makeLtlfNotEnd();
        return m_ctx->makeLtlfAnd({ltlf_arg, not_end});
    }

    // LTLf+ ForallExists
    LTLfPlusForallExists::LTLfPlusForallExists(AstManager& c, const ltlf_ptr& in) :
        LTLfPlusFormula(c), arg_{in} {
            type_code_ = type_code_id;
    }

    hash_t LTLfPlusForallExists::compute_hash_() const {
        hash_t seed = type_code_id;
        hash_combine<Basic>(seed, *arg_);
        return seed;
    }

    vec_basic LTLfPlusForallExists::get_args() const {
        vec_basic v;
        v.push_back(arg_);
        return v;
    }

    bool LTLfPlusForallExists::is_equal(const Basic& o) const {
        return is_a<LTLfPlusForallExists>(o) and 
            eq(*arg_, *dynamic_cast<const LTLfPlusForallExists&>(o).get_arg());
    }

    int LTLfPlusForallExists::compare_(const Basic& o) const {
        assert(is_a<LTLfPlusForallExists>(o));
        return arg_->compare(*dynamic_cast<const LTLfPlusForallExists&>(o).get_arg());
    }

    bool LTLfPlusForallExists::is_canonical(const LTLfPlusFormula& s) const {
        return true;
    }

    ltlf_ptr LTLfPlusForallExists::get_arg() const {
        return arg_;
    }

    ltlf_plus_ptr LTLfPlusForallExists::logical_not() const {
        return m_ctx->makeLtlfPlusExistsForall(m_ctx->makeLtlfNot(this->arg_));
    }

    ltlf_ptr LTLfPlusForallExists::ltlf_arg() const {
        auto ltlf_arg = arg_;
        // apply no-empty semantics
        auto not_end = m_ctx->makeLtlfNotEnd();
        return m_ctx->makeLtlfAnd({ltlf_arg, not_end});
    }
}