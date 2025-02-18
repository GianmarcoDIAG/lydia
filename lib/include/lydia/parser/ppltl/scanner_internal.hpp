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

#include "lydia/parser/ppltl/location.hh"
#include "lydia/parser/ppltl/parser.tab.hh"
#include <lydia/parser/ppltl/parser_stype.h>

namespace whitemech::lydia::parsers::ppltl {

class PPLTLScanner : public ppltlFlexLexer {
private:
public:
  /* yyval ptr */
  whitemech::lydia::parsers::ppltl::PPLTL_YYSTYPE* yylval = nullptr;

  explicit PPLTLScanner(std::istream* in) : ppltlFlexLexer(in){};
  virtual ~PPLTLScanner(){};

  // get rid of override virtual function warning
  using FlexLexer::yylex;

  virtual int yylex(whitemech::lydia::parsers::ppltl::PPLTL_YYSTYPE* lval,
                    PPLTLParser::location_type* location);
  // YY_DECL defined in lexer.l
  // Method body created by flex in lexer.yy.cc
};

} // namespace whitemech::lydia::parsers::ppltl