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

#include <cstddef>
#include <istream>
#include <string>
#include <utility>

#include <lydia/ast/base.hpp>
#include <lydia/logic/ppltl/base.hpp>
#include <lydia/logic/ldlf/base.hpp>
#include <lydia/logic/symbol.hpp>

#include "lydia/parser/ppltl/parser.tab.hh"
#include <lydia/parser/abstract_driver.hpp>
#include <lydia/parser/ppltl/scanner.hpp>

namespace whitemech::lydia::parsers::ppltl {

class PPLTLDriver : public AbstractDriver {
private:
  void parse_helper(std::istream& stream);

  PPLTLParser* parser = nullptr;
  PPLTLScanner* scanner = nullptr;

public:
  ppltl_ptr result;

  PPLTLDriver() : AbstractDriver() {}

  explicit PPLTLDriver(std::shared_ptr<AstManager> c) : AbstractDriver(c) {}

  virtual ~PPLTLDriver();

  ast_ptr get_result() override { return result; }

  /**
   * parse - parse from a file
   * @param filename - valid string with input file
   */
  void parse(const char* const filename) override;

  /**
   * parse - parse from a c++ input stream
   * @param is - std::istream&, valid input stream
   */
  void parse(std::istream& iss);

  ppltl_ptr add_PPLTLTrue() const;
  ppltl_ptr add_PPLTLFalse() const;
  ppltl_ptr add_PPLTLAtom(std::string s) const;
  ppltl_ptr add_PPLTLAnd(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
  ppltl_ptr add_PPLTLOr(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
  ppltl_ptr add_PPLTLNot(ppltl_ptr& formula) const;
  ppltl_ptr add_PPLTLYesterday(ppltl_ptr& formula) const;
  ppltl_ptr add_PPLTLWeakYesterday(ppltl_ptr& formula) const;
  ppltl_ptr add_PPLTLOnce(ppltl_ptr& formula) const;
  ppltl_ptr add_PPLTLHistorically(ppltl_ptr& formula) const;
  ppltl_ptr add_PPLTLSince(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
  ppltl_ptr add_PPLTLTriggered(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
  ppltl_ptr add_PPLTLImplication(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
  ppltl_ptr add_PPLTLEquivalence(ppltl_ptr& lhs, ppltl_ptr& rhs) const;
  ppltl_ptr add_PPLTLStart() const;
  ppltl_ptr add_PPLTLPropTrue() const;
  ppltl_ptr add_PPLTLPropFalse() const;

  std::ostream& print(std::ostream& stream) const;
};

} // namespace whitemech::lydia::parsers::ppltl
