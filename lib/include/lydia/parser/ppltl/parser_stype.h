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

#include "lydia/logic/ppltl/base.hpp"
#include <string>

namespace whitemech::lydia::parsers::ppltl {

struct PPLTL_YYSTYPE {
  ppltl_ptr formula;
  std::string symbol_name;

  // Constructor
  PPLTL_YYSTYPE() = default;
  // Destructor
  ~PPLTL_YYSTYPE() = default;
  // Copy constructor and assignment
  PPLTL_YYSTYPE(const PPLTL_YYSTYPE&) = default;
  PPLTL_YYSTYPE& operator=(const PPLTL_YYSTYPE&) = default;
  // Move constructor and assignment
  PPLTL_YYSTYPE(PPLTL_YYSTYPE&&) = default;
  PPLTL_YYSTYPE& operator=(PPLTL_YYSTYPE&&) = default;
};

} // namespace whitemech::lydia::parsers::ppltl