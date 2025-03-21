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
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include <lydia/basic.hpp>

namespace whitemech::lydia {

class Ast;

// This is the internal comparison functor for hash-consing AST nodes.
struct ast_eq_proc {
  bool operator()(basic_ptr const& b1, basic_ptr const& b2) const {
    return b1 == b2 || b1->compare(*b2) == 0;
  }
};

struct compute_hash {
  bool operator()(basic_ptr const& b1) const { return b1->hash(); }
};

class AstManager {

private:
  prop_ptr prop_true_;
  prop_ptr prop_false_;
  ltlf_ptr ltlf_true_;
  ltlf_ptr ltlf_false_;
  ltlf_ptr ltlf_last_;
  ltlf_ptr ltlf_end_;
  ltlf_ptr ltlf_not_end_;
  ppltl_ptr ppltl_true_;
  ppltl_ptr ppltl_false_;
  ppltl_ptr ppltl_first_;
  ppltl_ptr ppltl_end_;
  ppltl_ptr ppltl_not_end_;
  ldlf_ptr ldlf_true_;
  ldlf_ptr ldlf_false_;
  ltlf_plus_ptr ltlf_plus_true_;
  ltlf_plus_ptr ltlf_plus_false_;
  ppltl_plus_ptr ppltl_plus_true_;
  ppltl_plus_ptr ppltl_plus_false_;
  std::unordered_set<basic_ptr, compute_hash, ast_eq_proc> table;
  void init();

  template <typename T, typename = typename std::enable_if<
                            std::is_base_of<Basic, T>::value>::type>
  std::shared_ptr<T> insert_if_not_available_(const std::shared_ptr<T>& ptr) {
    auto it = table.find(ptr);
    if (it == table.end()) {
      table.insert(ptr);
      return ptr;
    } else {
      return std::static_pointer_cast<T>(*it);
    }
  }

public:
  AstManager() { init(); }

  size_t table_size() { return table.size(); };

  symbol_ptr makeSymbol(const std::string& name);

  prop_ptr makeTrue();
  prop_ptr makeFalse();
  prop_ptr makeBool(bool value);
  atom_ptr makePropAtom(const std::string& name);
  atom_ptr makePropAtom(const basic_ptr& ptr);
  prop_ptr makePropAnd(const set_prop_formulas& args);
  prop_ptr makePropOr(const set_prop_formulas& args);
  prop_ptr makePropNot(const prop_ptr& arg);

  ltlf_ptr makeLtlfTrue();
  ltlf_ptr makeLtlfFalse();
  ltlf_ptr makeLtlfLast();
  ltlf_ptr makeLtlfEnd();
  ltlf_ptr makeLtlfNotEnd();
  ltlf_ptr makeLtlfBool(bool x);
  ltlf_ptr makeLtlfAtom(const std::string& name);
  ltlf_ptr makeLtlfAtom(const symbol_ptr& symbol);
  ltlf_ptr makeLtlfAnd(const set_ltlf_formulas& args);
  ltlf_ptr makeLtlfOr(const set_ltlf_formulas& args);
  ltlf_ptr makeLtlfNot(const ltlf_ptr& arg);
  ltlf_ptr makeLtlfNext(const ltlf_ptr& arg);
  ltlf_ptr makeLtlfWeakNext(const ltlf_ptr& arg);
  ltlf_ptr makeLtlfUntil(const ltlf_ptr& arg_1, const ltlf_ptr& arg_2);
  ltlf_ptr makeLtlfRelease(const ltlf_ptr& arg_1, const ltlf_ptr& arg_2);
  ltlf_ptr makeLtlfEventually(const ltlf_ptr& arg);
  ltlf_ptr makeLtlfAlways(const ltlf_ptr& arg);

  ppltl_ptr makePPLTLTrue();
  ppltl_ptr makePPLTLFalse();
  ppltl_ptr makePPLTLFirst();
  ppltl_ptr makePPLTLEnd();
  ppltl_ptr makePPLTLNotEnd();
  ppltl_ptr makePPLTLBool(bool x);
  ppltl_ptr makePPLTLAtom(const std::string& name);
  ppltl_ptr makePPLTLAtom(const symbol_ptr& symbol);
  ppltl_ptr makePPLTLAnd(const set_ppltl_formulas& args);
  ppltl_ptr makePPLTLOr(const set_ppltl_formulas& args);
  ppltl_ptr makePPLTLNot(const ppltl_ptr& arg);
  ppltl_ptr makePPLTLYesterday(const ppltl_ptr& arg);
  ppltl_ptr makePPLTLWeakYesterday(const ppltl_ptr& arg);
  ppltl_ptr makePPLTLSince(const ppltl_ptr& arg_1, const ppltl_ptr& arg_2);
  ppltl_ptr makePPLTLTriggered(const ppltl_ptr& arg_1, const ppltl_ptr& arg_2);
  ppltl_ptr makePPLTLOnce(const ppltl_ptr& arg);
  ppltl_ptr makePPLTLHistorically(const ppltl_ptr& arg);

  ldlf_ptr makeLdlfTrue();
  ldlf_ptr makeLdlfFalse();
  ldlf_ptr makeLdlfEnd();
  ldlf_ptr makeLdlfNotEnd();
  ldlf_ptr makeLdlfBool(bool x);
  ldlf_ptr makeLdlfAnd(const set_formulas& args);
  ldlf_ptr makeLdlfOr(const set_formulas& args);
  ldlf_ptr makeLdlfNot(const ldlf_ptr& arg);
  ldlf_ptr makeLdlfBox(const regex_ptr& arg_r, const ldlf_ptr& arg);
  ldlf_ptr makeLdlfDiamond(const regex_ptr& arg_r, const ldlf_ptr& arg_f);
  ldlf_ptr makeLdlfT(const ldlf_ptr& arg);
  ldlf_ptr makeLdlfF(const ldlf_ptr& arg);
  ldlf_ptr makeLdlfQ(const ldlf_ptr& arg);

  regex_ptr makePropRegex(const prop_ptr& ptr);
  regex_ptr makeSeqRegex(const vec_regex& ptr);
  regex_ptr makeUnionRegex(const set_regex& ptr);
  regex_ptr makeStarRegex(const regex_ptr& ptr);
  regex_ptr makeTestRegex(const ldlf_ptr& ptr);

  ltlf_plus_ptr makeLtlfPlusBool(bool x); 
  ltlf_plus_ptr makeLtlfPlusTrue();
  ltlf_plus_ptr makeLtlfPlusFalse();
  ltlf_plus_ptr makeLtlfPlusAnd(const set_ltlf_plus_formulas& args);
  ltlf_plus_ptr makeLtlfPlusOr(const set_ltlf_plus_formulas& args);
  ltlf_plus_ptr makeLtlfPlusNot(const ltlf_plus_ptr& arg);
  ltlf_plus_ptr makeLtlfPlusExists(const ltlf_ptr& arg);
  ltlf_plus_ptr makeLtlfPlusForall(const ltlf_ptr& arg);
  ltlf_plus_ptr makeLtlfPlusForallExists(const ltlf_ptr& arg);
  ltlf_plus_ptr makeLtlfPlusExistsForall(const ltlf_ptr& arg);

  ppltl_plus_ptr makePpltlPlusBool(bool x);
  ppltl_plus_ptr makePpltlPlusTrue();
  ppltl_plus_ptr makePpltlPlusFalse();
  ppltl_plus_ptr makePpltlPlusAnd(const set_ppltl_plus_formulas& args);
  ppltl_plus_ptr makePpltlPlusOr(const set_ppltl_plus_formulas& args);
  ppltl_plus_ptr makePpltlPlusNot(const ppltl_plus_ptr& arg);
  ppltl_plus_ptr makePpltlPlusExists(const ppltl_ptr& arg);
  ppltl_plus_ptr makePpltlPlusForall(const ppltl_ptr& arg);
  ppltl_plus_ptr makePpltlPlusForallExists(const ppltl_ptr& arg);
  ppltl_plus_ptr makePpltlPlusExistsForall(const ppltl_ptr& arg);
};

class Ast : public Basic {
protected:
  AstManager* m_ctx;

public:
  explicit Ast(AstManager& c) : m_ctx(&c) {}
  Ast(const Ast& s) : m_ctx(s.m_ctx) {}
  AstManager& ctx() const { return *m_ctx; }
  friend void check_context(Ast const& a, Ast const& b) {
    assert(a.m_ctx == b.m_ctx);
  };
};

template <typename T, typename caller, typename True, typename False,
          typename Not, typename And, typename Or>
std::shared_ptr<T>
and_or(AstManager& context,
       const std::set<std::shared_ptr<T>, SharedComparator>& s, bool op_x_notx,
       std::shared_ptr<T> (AstManager::*const& fun_ptr)(bool x)) {
  std::set<std::shared_ptr<T>, SharedComparator> args;
  for (auto& a : s) {
    // handle the case when a subformula is true
    if (is_a<True>(*a)) {
      if (op_x_notx)
        return a;
      else
        continue;
    }
    // handle the case when a subformula is false
    else if (is_a<False>(*a)) {
      if (!op_x_notx)
        return a;
      else
        continue;
    }
    // handle the case when a subformula is of the same type of the caller
    else if (is_a<caller>(*a)) {
      const auto& to_insert = dynamic_cast<const caller&>(*a);
      const auto& container = to_insert.get_container();
      args.insert(container.begin(), container.end());
      continue;
    } else {
      args.insert(a);
    }
  }
  //  for (auto &a : args) {
  //    if (args.find(a->logical_not()) != args.end())
  //      return (context.*fun_ptr)(op_x_notx);
  //  }
  if (args.size() == 1)
    return *(args.begin());
  else if (args.empty())
    return (context.*fun_ptr)(not op_x_notx);
  return std::make_shared<caller>(context, args);
}

template <typename T, typename caller>
std::shared_ptr<T>
flatten_bin_op_set(AstManager& context,
                   const std::set<std::shared_ptr<T>, SharedComparator>& s) {
  std::set<std::shared_ptr<T>, SharedComparator> args;
  for (auto& a : s) {
    // handle the case when a subformula is of the same type of the caller
    if (is_a<caller>(*a)) {
      const auto& to_insert = dynamic_cast<const caller&>(*a);
      const auto& container = to_insert.get_container();
      args.insert(container.begin(), container.end());
      continue;
    } else {
      args.insert(a);
    }
  }
  if (args.size() == 1)
    return *(args.begin());
  else if (args.empty())
    assert(false);
  return std::make_shared<caller>(context, args);
}

template <typename T, typename caller>
std::shared_ptr<T>
flatten_bin_op_vec(AstManager& context,
                   const std::vector<std::shared_ptr<T>>& s) {
  std::vector<std::shared_ptr<T>> args;
  args.reserve(s.size());
  for (auto& a : s) {
    // handle the case when a subformula is of the same type of the caller
    if (is_a<caller>(*a)) {
      const auto& to_insert = dynamic_cast<const caller&>(*a);
      const auto& container = to_insert.get_container();
      args.insert(args.end(), container.begin(), container.end());
      continue;
    } else {
      args.push_back(a);
    }
  }
  if (args.size() == 1)
    return *(args.begin());
  else if (args.empty())
    assert(false);
  return std::make_shared<caller>(context, args);
}

} // namespace whitemech::lydia