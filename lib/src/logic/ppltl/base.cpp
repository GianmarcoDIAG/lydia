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
#include <lydia/utils/compare.hpp>
#include <stdexcept>
#include <utility>

namespace whitemech::lydia {

hash_t PPLTLTrue::compute_hash_() const { return type_code_id; }

vec_ppltl_formulas PPLTLTrue::get_args() const { return {}; }

bool PPLTLTrue::is_equal(const Basic& o) const { return is_a<PPLTLTrue>(o); }

int PPLTLTrue::compare_(const Basic& o) const {
  assert(is_a<PPLTLTrue>(o));
  return 0;
}

ppltl_ptr PPLTLTrue::logical_not() const { return ctx().makePPLTLFalse(); }

///////////////////////////////////

hash_t PPLTLFalse::compute_hash_() const { return type_code_id; }

vec_ppltl_formulas PPLTLFalse::get_args() const { return {}; }

bool PPLTLFalse::is_equal(const Basic& o) const { return is_a<PPLTLFalse>(o); }

int PPLTLFalse::compare_(const Basic& o) const {
  assert(is_a<PPLTLFalse>(o));
  return 0;
}

ppltl_ptr PPLTLFalse::logical_not() const { return ctx().makePPLTLTrue(); }

///////////////////////////////////

PPLTLAtom::PPLTLAtom(AstManager& c, const std::string& s)
    : PPLTLFormula(c), symbol{c.makeSymbol(s)} {
  this->type_code_ = type_code_id;
}

PPLTLAtom::PPLTLAtom(AstManager& c, const symbol_ptr& p)
    : PPLTLAtom(c, p->str()){};

hash_t PPLTLAtom::compute_hash_() const {
  hash_t seed = type_code_id;
  hash_combine<Basic>(seed, *this->symbol);
  return seed;
}

int PPLTLAtom::compare_(const Basic& rhs) const {
  assert(is_a<PPLTLAtom>(rhs));
  return this->symbol->compare(*dynamic_cast<const PPLTLAtom&>(rhs).symbol);
}

bool PPLTLAtom::is_equal(const Basic& rhs) const {
  return is_a<PPLTLAtom>(rhs) and
         this->symbol->is_equal(*dynamic_cast<const PPLTLAtom&>(rhs).symbol);
}

ppltl_ptr PPLTLAtom::logical_not() const {
  ppltl_ptr ptr = m_ctx->makePPLTLAtom(this->symbol->str());
  return m_ctx->makePPLTLNot(ptr);
}

PPLTLAnd::PPLTLAnd(AstManager& c, const set_ppltl_formulas& s)
    : PPLTLFormula(c), container_{s} {
  this->type_code_ = type_code_id;
  if (!is_canonical(s)) {
    throw std::invalid_argument("PPLTLAnd formula: arguments must be > 1");
  }
}

hash_t PPLTLAnd::compute_hash_() const {
  hash_t seed = type_code_id;
  for (const auto& a : container_)
    hash_combine<Basic>(seed, *a);
  return seed;
}

bool PPLTLAnd::is_canonical(const set_ppltl_formulas& container_) const {
  return container_.size() > 1;
}

vec_ppltl_formulas PPLTLAnd::get_args() const {
  vec_ppltl_formulas v(container_.begin(), container_.end());
  return v;
}

bool PPLTLAnd::is_equal(const Basic& o) const {
  return is_a<PPLTLAnd>(o) and
         unified_eq(container_,
                    dynamic_cast<const PPLTLAnd&>(o).get_container());
}

int PPLTLAnd::compare_(const Basic& o) const {
  assert(is_a<PPLTLAnd>(o));
  return unified_compare(container_,
                         dynamic_cast<const PPLTLAnd&>(o).get_container());
}

const set_ppltl_formulas& PPLTLAnd::get_container() const { return container_; }

ppltl_ptr PPLTLAnd::logical_not() const {
  auto container = this->get_container();
  set_ppltl_formulas cont;
  for (auto& a : container) {
    cont.insert(a->logical_not());
  }
  return m_ctx->makePPLTLOr(cont);
}

PPLTLOr::PPLTLOr(AstManager& c, const set_ppltl_formulas& s)
    : PPLTLFormula(c), container_{s} {
  this->type_code_ = type_code_id;
  if (!is_canonical(s)) {
    throw std::invalid_argument("PPLTLOr formula: arguments must be > 1");
  }
}

hash_t PPLTLOr::compute_hash_() const {
  hash_t seed = type_code_id;
  for (const auto& a : container_)
    hash_combine<Basic>(seed, *a);
  return seed;
}

vec_ppltl_formulas PPLTLOr::get_args() const {
  vec_ppltl_formulas v(container_.begin(), container_.end());
  return v;
}

bool PPLTLOr::is_equal(const Basic& o) const {
  return is_a<PPLTLOr>(o) and
         unified_eq(container_, dynamic_cast<const PPLTLOr&>(o).get_container());
}

int PPLTLOr::compare_(const Basic& o) const {
  assert(is_a<PPLTLOr>(o));
  return unified_compare(container_,
                         dynamic_cast<const PPLTLOr&>(o).get_container());
}

bool PPLTLOr::is_canonical(const set_ppltl_formulas& container_) const {
  return container_.size() > 1;
}

const set_ppltl_formulas& PPLTLOr::get_container() const { return container_; }

ppltl_ptr PPLTLOr::logical_not() const {
  auto container = this->get_container();
  set_ppltl_formulas cont;
  for (auto& a : container) {
    cont.insert(a->logical_not());
  }
  return m_ctx->makePPLTLAnd(cont);
}

PPLTLNot::PPLTLNot(AstManager& c, const ppltl_ptr& in) : PPLTLFormula(c), arg_{in} {
  type_code_ = type_code_id;
}

hash_t PPLTLNot::compute_hash_() const {
  hash_t seed = type_code_id;
  hash_combine<Basic>(seed, *arg_);
  return seed;
}

vec_basic PPLTLNot::get_args() const {
  vec_basic v;
  v.push_back(arg_);
  return v;
}

bool PPLTLNot::is_equal(const Basic& o) const {
  return is_a<PPLTLNot>(o) and
         eq(*arg_, *dynamic_cast<const PPLTLNot&>(o).get_arg());
}

int PPLTLNot::compare_(const Basic& o) const {
  assert(is_a<PPLTLNot>(o));
  return arg_->compare(*dynamic_cast<const PPLTLNot&>(o).get_arg());
}

bool PPLTLNot::is_canonical(const PPLTLFormula& in) const { return true; }

ppltl_ptr PPLTLNot::get_arg() const { return arg_; }

ppltl_ptr PPLTLNot::logical_not() const { return this->get_arg(); }

PPLTLYesterday::PPLTLYesterday(AstManager& c, const ppltl_ptr& in)
    : PPLTLFormula(c), arg_{in} {
  type_code_ = type_code_id;
}

hash_t PPLTLYesterday::compute_hash_() const {
  hash_t seed = type_code_id;
  hash_combine<Basic>(seed, *arg_);
  return seed;
}

vec_basic PPLTLYesterday::get_args() const {
  vec_basic v;
  v.push_back(arg_);
  return v;
}

bool PPLTLYesterday::is_equal(const Basic& o) const {
  return is_a<PPLTLYesterday>(o) and
         eq(*arg_, *dynamic_cast<const PPLTLYesterday&>(o).get_arg());
}

int PPLTLYesterday::compare_(const Basic& o) const {
  assert(is_a<PPLTLYesterday>(o));
  return arg_->compare(*dynamic_cast<const PPLTLYesterday&>(o).get_arg());
}

bool PPLTLYesterday::is_canonical(const PPLTLFormula& in) const { return true; }

ppltl_ptr PPLTLYesterday::get_arg() const { return arg_; }

ppltl_ptr PPLTLYesterday::logical_not() const { return this->get_arg(); }

PPLTLWeakYesterday::PPLTLWeakYesterday(AstManager& c, const ppltl_ptr& in)
    : PPLTLFormula(c), arg_{in} {
  type_code_ = type_code_id;
}

hash_t PPLTLWeakYesterday::compute_hash_() const {
  hash_t seed = type_code_id;
  hash_combine<Basic>(seed, *arg_);
  return seed;
}

vec_basic PPLTLWeakYesterday::get_args() const {
  vec_basic v;
  v.push_back(arg_);
  return v;
}

bool PPLTLWeakYesterday::is_equal(const Basic& o) const {
  return is_a<PPLTLWeakYesterday>(o) and
         eq(*arg_, *dynamic_cast<const PPLTLWeakYesterday&>(o).get_arg());
}

int PPLTLWeakYesterday::compare_(const Basic& o) const {
  assert(is_a<PPLTLWeakYesterday>(o));
  return arg_->compare(*dynamic_cast<const PPLTLWeakYesterday&>(o).get_arg());
}

bool PPLTLWeakYesterday::is_canonical(const PPLTLFormula& in) const { return true; }

ppltl_ptr PPLTLWeakYesterday::get_arg() const { return arg_; }

ppltl_ptr PPLTLWeakYesterday::logical_not() const { return this->get_arg(); }

PPLTLSince::PPLTLSince(AstManager& c, const ppltl_ptr& arg_1,
                     const ppltl_ptr& arg_2)
    : PPLTLFormula(c), arg_1_{arg_1}, arg_2_{arg_2}, container_{{arg_1, arg_2}} {
  type_code_ = type_code_id;
}

hash_t PPLTLSince::compute_hash_() const {
  hash_t seed = type_code_id;
  hash_combine<Basic>(seed, *arg_1_);
  hash_combine<Basic>(seed, *arg_2_);
  return seed;
}

vec_ppltl_formulas PPLTLSince::get_args() const {
  vec_ppltl_formulas v;
  v.push_back(arg_1_);
  v.push_back(arg_2_);
  return v;
}

bool PPLTLSince::is_equal(const Basic& o) const {
  return is_a<PPLTLSince>(o) and
         unified_eq(get_args(), dynamic_cast<const PPLTLSince&>(o).get_args());
}

int PPLTLSince::compare_(const Basic& o) const {
  auto arg_1_compare =
      unified_compare(this->arg_1_, dynamic_cast<const PPLTLSince&>(o).arg_1_);
  if (arg_1_compare != 0)
    return arg_1_compare;
  return unified_compare(this->arg_2_,
                         dynamic_cast<const PPLTLSince&>(o).arg_2_);
}

bool PPLTLSince::is_canonical(const set_ppltl_formulas& container_) const {
  return true;
}

const set_ppltl_formulas& PPLTLSince::get_container() const { return container_; }

ppltl_ptr PPLTLSince::logical_not() const {
  auto not_arg_1 = arg_1_->logical_not();
  auto not_arg_2 = arg_2_->logical_not();
  return m_ctx->makePPLTLTriggered(not_arg_1, not_arg_2);
}

PPLTLTriggered::PPLTLTriggered(AstManager& c, const ppltl_ptr& arg_1,
                         const ppltl_ptr& arg_2)
    : PPLTLFormula(c), arg_1_{arg_1}, arg_2_{arg_2}, container_{{arg_1, arg_2}} {
  type_code_ = type_code_id;
}

hash_t PPLTLTriggered::compute_hash_() const {
  hash_t seed = type_code_id;
  hash_combine<Basic>(seed, *arg_1_);
  hash_combine<Basic>(seed, *arg_2_);
  return seed;
}

vec_ppltl_formulas PPLTLTriggered::get_args() const {
  vec_ppltl_formulas v;
  v.push_back(arg_1_);
  v.push_back(arg_2_);
  return v;
}

bool PPLTLTriggered::is_equal(const Basic& o) const {
  return is_a<PPLTLTriggered>(o) and
         unified_eq(get_args(), dynamic_cast<const PPLTLTriggered&>(o).get_args());
}

int PPLTLTriggered::compare_(const Basic& o) const {
  auto arg_1_compare =
      unified_compare(this->arg_1_, dynamic_cast<const PPLTLTriggered&>(o).arg_1_);
  if (arg_1_compare != 0)
    return arg_1_compare;
  return unified_compare(this->arg_2_,
                         dynamic_cast<const PPLTLTriggered&>(o).arg_2_);
}

bool PPLTLTriggered::is_canonical(const set_ppltl_formulas& container_) const {
  return true;
}

const set_ppltl_formulas& PPLTLTriggered::get_container() const {
  return container_;
}

ppltl_ptr PPLTLTriggered::logical_not() const {
  auto not_arg_1 = arg_1_->logical_not();
  auto not_arg_2 = arg_2_->logical_not();
  return m_ctx->makePPLTLSince(not_arg_1, not_arg_2);
}

PPLTLOnce::PPLTLOnce(AstManager& c, const ppltl_ptr& in)
    : PPLTLFormula(c), arg_{in} {
  type_code_ = type_code_id;
}

hash_t PPLTLOnce::compute_hash_() const {
  hash_t seed = type_code_id;
  hash_combine<Basic>(seed, *arg_);
  return seed;
}

vec_basic PPLTLOnce::get_args() const {
  vec_basic v;
  v.push_back(arg_);
  return v;
}

bool PPLTLOnce::is_equal(const Basic& o) const {
  return is_a<PPLTLOnce>(o) and
         eq(*arg_, *dynamic_cast<const PPLTLOnce&>(o).get_arg());
}

int PPLTLOnce::compare_(const Basic& o) const {
  assert(is_a<PPLTLOnce>(o));
  return arg_->compare(*dynamic_cast<const PPLTLOnce&>(o).get_arg());
}

bool PPLTLOnce::is_canonical(const PPLTLFormula& in) const { return true; }

ppltl_ptr PPLTLOnce::get_arg() const { return arg_; }

ppltl_ptr PPLTLOnce::logical_not() const { return this->get_arg(); }

PPLTLHistorically::PPLTLHistorically(AstManager& c, const ppltl_ptr& in)
    : PPLTLFormula(c), arg_{in} {
  type_code_ = type_code_id;
}

hash_t PPLTLHistorically::compute_hash_() const {
  hash_t seed = type_code_id;
  hash_combine<Basic>(seed, *arg_);
  return seed;
}

vec_basic PPLTLHistorically::get_args() const {
  vec_basic v;
  v.push_back(arg_);
  return v;
}

bool PPLTLHistorically::is_equal(const Basic& o) const {
  return is_a<PPLTLHistorically>(o) and
         eq(*arg_, *dynamic_cast<const PPLTLHistorically&>(o).get_arg());
}

int PPLTLHistorically::compare_(const Basic& o) const {
  assert(is_a<PPLTLHistorically>(o));
  return arg_->compare(*dynamic_cast<const PPLTLHistorically&>(o).get_arg());
}

bool PPLTLHistorically::is_canonical(const PPLTLFormula& in) const { return true; }

ppltl_ptr PPLTLHistorically::get_arg() const { return arg_; }

ppltl_ptr PPLTLHistorically::logical_not() const { return this->get_arg(); }

} // namespace whitemech::lydia
