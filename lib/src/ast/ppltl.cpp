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

#include <lydia/ast/base.hpp>
#include <lydia/logic/ppltl/base.hpp>

namespace whitemech::lydia {

ppltl_ptr AstManager::makePPLTLTrue() { return ppltl_true_; }
ppltl_ptr AstManager::makePPLTLFalse() { return ppltl_false_; }
ppltl_ptr AstManager::makePPLTLFirst() { return ppltl_first_; }
ppltl_ptr AstManager::makePPLTLEnd() { return ppltl_end_; }
ppltl_ptr AstManager::makePPLTLNotEnd() { return ppltl_not_end_; }
ppltl_ptr AstManager::makePPLTLBool(bool value) {
  return value ? ppltl_true_ : ppltl_false_;
}
ppltl_ptr AstManager::makePPLTLAtom(const std::string& name) {
  auto symbol_tmp = makeSymbol(name);
  auto tmp = std::make_shared<const PPLTLAtom>(*this, symbol_tmp);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLAtom(const symbol_ptr& symbol) {
  auto atom = std::make_shared<const PPLTLAtom>(*this, symbol);
  auto actual_atom = insert_if_not_available_(atom);
  return actual_atom;
}

ppltl_ptr AstManager::makePPLTLAnd(const set_ppltl_formulas& args) {
  ppltl_ptr (AstManager::*fun)(bool) = &AstManager::makePPLTLBool;
  auto tmp = and_or<const PPLTLFormula, PPLTLAnd, PPLTLTrue, PPLTLFalse, PPLTLNot,
                    PPLTLAnd, PPLTLOr>(*this, args, false, fun);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLOr(const set_ppltl_formulas& args) {
  ppltl_ptr (AstManager::*fun)(bool) = &AstManager::makePPLTLBool;
  auto tmp = and_or<const PPLTLFormula, PPLTLOr, PPLTLTrue, PPLTLFalse, PPLTLNot,
                    PPLTLAnd, PPLTLOr>(*this, args, true, fun);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLNot(const ppltl_ptr& arg) {
  auto tmp = std::make_shared<const PPLTLNot>(*this, arg);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLYesterday(const ppltl_ptr& arg) {
  auto tmp = std::make_shared<const PPLTLYesterday>(*this, arg);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLWeakYesterday(const ppltl_ptr& arg) {
  auto tmp = std::make_shared<const PPLTLWeakYesterday>(*this, arg);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLSince(const ppltl_ptr& arg_1,
                                   const ppltl_ptr& arg_2) {
  auto tmp = std::make_shared<const PPLTLSince>(*this, arg_1, arg_2);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLTriggered(const ppltl_ptr& arg_1,
                                     const ppltl_ptr& arg_2) {
  auto tmp = std::make_shared<const PPLTLTriggered>(*this, arg_1, arg_2);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLOnce(const ppltl_ptr& arg) {
  auto tmp = std::make_shared<const PPLTLOnce>(*this, arg);
  auto result = insert_if_not_available_(tmp);
  return result;
}
ppltl_ptr AstManager::makePPLTLHistorically(const ppltl_ptr& arg) {
  auto tmp = std::make_shared<const PPLTLHistorically>(*this, arg);
  auto result = insert_if_not_available_(tmp);
  return result;
}

} // namespace whitemech::lydia