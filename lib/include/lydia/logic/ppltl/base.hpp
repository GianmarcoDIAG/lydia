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
#include <lydia/logic/pl/base.hpp>
#include <lydia/logic/symbol.hpp>
#include <lydia/utils/compare.hpp>
#include <utility>

namespace whitemech::lydia {

class RegExp;

class PPLTLFormula : public Ast {
public:
  explicit PPLTLFormula(AstManager& c) : Ast(c) {}
  virtual ppltl_ptr logical_not() const = 0;
};

class PPLTLTrue : public PPLTLFormula {
public:
  const static TypeID type_code_id = TypeID::t_PPLTLTrue;
  explicit PPLTLTrue(AstManager& c) : PPLTLFormula(c) {
    type_code_ = type_code_id;
  }
  void accept(Visitor& v) const override;
  hash_t compute_hash_() const override;
  virtual vec_ppltl_formulas get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  ppltl_ptr logical_not() const override;
};

class PPLTLFalse : public PPLTLFormula {
public:
  const static TypeID type_code_id = TypeID::t_PPLTLFalse;
  explicit PPLTLFalse(AstManager& c) : PPLTLFormula(c) {
    type_code_ = type_code_id;
  }
  void accept(Visitor& v) const override;
  hash_t compute_hash_() const override;
  virtual vec_ppltl_formulas get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  ppltl_ptr logical_not() const override;
};

class PPLTLAtom : public PPLTLFormula {
public:
  const static TypeID type_code_id = TypeID::t_PPLTLAtom;
  const symbol_ptr symbol;
  explicit PPLTLAtom(AstManager& c, const std::string&);
  explicit PPLTLAtom(AstManager& c, const symbol_ptr& p);
  void accept(Visitor& v) const override;
  hash_t compute_hash_() const override;
  int compare_(const Basic& rhs) const override;
  bool is_equal(const Basic& rhs) const override;
  ppltl_ptr logical_not() const override;
  set_ppltl_formulas get_container() const {
    return set_ppltl_formulas{
        std::static_pointer_cast<const PPLTLAtom>(this->shared_from_this())};
  };
};

class PPLTLAnd : public PPLTLFormula {
private:
  const set_ppltl_formulas container_;

public:
  const static TypeID type_code_id = TypeID::t_PPLTLAnd;
  void accept(Visitor& v) const override;
  explicit PPLTLAnd(AstManager& c, const set_ppltl_formulas& s);
  bool is_canonical(const set_ppltl_formulas& container_) const;
  hash_t compute_hash_() const override;
  virtual vec_ppltl_formulas get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  const set_ppltl_formulas& get_container() const;
  ppltl_ptr logical_not() const override;
};

class PPLTLOr : public PPLTLFormula {
private:
  const set_ppltl_formulas container_;

public:
  const static TypeID type_code_id = TypeID::t_PPLTLOr;
  void accept(Visitor& v) const override;
  explicit PPLTLOr(AstManager& c, const set_ppltl_formulas& s);
  bool is_canonical(const set_ppltl_formulas& container_) const;
  hash_t compute_hash_() const override;
  virtual vec_ppltl_formulas get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  const set_ppltl_formulas& get_container() const;
  ppltl_ptr logical_not() const override;
};

class PPLTLNot : public PPLTLFormula {
private:
  const ppltl_ptr arg_;

public:
  const static TypeID type_code_id = TypeID::t_PPLTLNot;
  void accept(Visitor& v) const override;
  explicit PPLTLNot(AstManager& c, const ppltl_ptr& in);
  bool is_canonical(const PPLTLFormula& s) const;
  hash_t compute_hash_() const override;
  virtual vec_basic get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  ppltl_ptr get_arg() const;
  ppltl_ptr logical_not() const override;
};

class PPLTLYesterday : public PPLTLFormula {
private:
  const ppltl_ptr arg_;

public:
  const static TypeID type_code_id = TypeID::t_PPLTLYesterday;
  void accept(Visitor& v) const override;
  explicit PPLTLYesterday(AstManager& c, const ppltl_ptr& in);
  bool is_canonical(const PPLTLFormula& s) const;
  hash_t compute_hash_() const override;
  virtual vec_basic get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  ppltl_ptr get_arg() const;
  ppltl_ptr logical_not() const override;
};

class PPLTLWeakYesterday : public PPLTLFormula {
private:
  const ppltl_ptr arg_;

public:
  const static TypeID type_code_id = TypeID::t_PPLTLWeakYesterday;
  void accept(Visitor& v) const override;
  explicit PPLTLWeakYesterday(AstManager& c, const ppltl_ptr& in);
  bool is_canonical(const PPLTLFormula& s) const;
  hash_t compute_hash_() const override;
  virtual vec_basic get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  ppltl_ptr get_arg() const;
  ppltl_ptr logical_not() const override;
};

class PPLTLSince : public PPLTLFormula {
private:
  const ppltl_ptr arg_1_;
  const ppltl_ptr arg_2_;
  const set_ppltl_formulas container_;

public:
  const static TypeID type_code_id = TypeID::t_PPLTLSince;
  void accept(Visitor& v) const override;
  explicit PPLTLSince(AstManager& c, const ppltl_ptr& arg_1,
                     const ppltl_ptr& arg_2);
  bool is_canonical(const set_ppltl_formulas& container_) const;
  hash_t compute_hash_() const override;
  virtual vec_ppltl_formulas get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  const set_ppltl_formulas& get_container() const;
  ppltl_ptr logical_not() const override;
  ppltl_ptr tail() const { return arg_2_; };
  ppltl_ptr head() const { return arg_1_; };
};

class PPLTLTriggered : public PPLTLFormula {
private:
  const ppltl_ptr arg_1_;
  const ppltl_ptr arg_2_;
  const set_ppltl_formulas container_;

public:
  const static TypeID type_code_id = TypeID::t_PPLTLTriggered;
  void accept(Visitor& v) const override;
  explicit PPLTLTriggered(AstManager& c, const ppltl_ptr& arg_1,
                       const ppltl_ptr& arg_2);
  bool is_canonical(const set_ppltl_formulas& container_) const;
  hash_t compute_hash_() const override;
  virtual vec_ppltl_formulas get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  const set_ppltl_formulas& get_container() const;
  ppltl_ptr logical_not() const override;
  ppltl_ptr tail() const { return arg_2_; };
  ppltl_ptr head() const { return arg_1_; };
};

class PPLTLOnce : public PPLTLFormula {
private:
  const ppltl_ptr arg_;

public:
  const static TypeID type_code_id = TypeID::t_PPLTLOnce;
  void accept(Visitor& v) const override;
  explicit PPLTLOnce(AstManager& c, const ppltl_ptr& in);
  bool is_canonical(const PPLTLFormula& s) const;
  hash_t compute_hash_() const override;
  virtual vec_basic get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  ppltl_ptr get_arg() const;
  ppltl_ptr logical_not() const override;
};

class PPLTLHistorically : public PPLTLFormula {
private:
  const ppltl_ptr arg_;

public:
  const static TypeID type_code_id = TypeID::t_LTLfAlways;
  void accept(Visitor& v) const override;
  explicit PPLTLHistorically(AstManager& c, const ppltl_ptr& in);
  bool is_canonical(const PPLTLFormula& s) const;
  hash_t compute_hash_() const override;
  virtual vec_basic get_args() const;
  bool is_equal(const Basic& o) const override;
  int compare_(const Basic& o) const override;
  ppltl_ptr get_arg() const;
  ppltl_ptr logical_not() const override;
};

} // namespace whitemech::lydia
