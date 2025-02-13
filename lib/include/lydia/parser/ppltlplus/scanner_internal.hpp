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

#include "lydia/parser/ppltlplus/location.hh"
#include "lydia/parser/ppltlplus/parser.tab.hh"
#include <lydia/parser/ppltlplus/parser_stype.h>

namespace whitemech::lydia::parsers::ppltlplus {

class PPTLPlusScanner : public ppltlPlusFlexLexer {
private:
public:
  whitemech::lydia::parsers::ppltlplus::PPTLPlus_YYSTYPE* yylval = nullptr;

  explicit PPTLPlusScanner(std::istream* in): ppltlPlusFlexLexer(in) {};
  virtual ~PPTLPlusScanner(){};

  using FlexLexer::yylex;

  virtual int yylex(whitemech::lydia::parsers::ppltlplus::PPTLPlus_YYSTYPE* lval,
                   PPTLPlusParser::location_type* location);
  // YY_DECL defined in lexer.l
  // Method body created by flex in lexer.yy.cc
};

} // namespace whitemech::lydia::parsers::ppltlplus