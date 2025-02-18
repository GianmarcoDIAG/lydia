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

#include "lydia/logic/ppltlplus/base.hpp"
#include <string>

namespace whitemech::lydia::parsers::ppltlplus {

struct PPLTLPlus_YYSTYPE {
  // The parser needs information about types it can read
  ppltl_plus_ptr formula;
  ppltl_ptr ppltl_arg;
  std::string symbol_name;

  // Constructor
  PPLTLPlus_YYSTYPE() = default;
  // Destructor
  ~PPLTLPlus_YYSTYPE() = default;
  // Copy constructor and assignment
  PPLTLPlus_YYSTYPE(const PPLTLPlus_YYSTYPE&) = default;
  PPLTLPlus_YYSTYPE& operator=(const PPLTLPlus_YYSTYPE&) = default;
  // Move constructor and assignment
  PPLTLPlus_YYSTYPE(PPLTLPlus_YYSTYPE&&) = default;
  PPLTLPlus_YYSTYPE& operator=(PPLTLPlus_YYSTYPE&&) = default;
};

} // namespace whitemech::lydia::parsers::ppltlplus