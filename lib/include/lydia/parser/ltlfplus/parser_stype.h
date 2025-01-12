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

#include"lydia/logic/ltlfplus/base.hpp"
#include<string>

namespace whitemech::lydia::parsers::ltlfplus {

    struct LTLfPlus_YYSTYPE {
        // (Gianmarco). The parse need information about types it can read?
        ltlf_plus_ptr formula;
        ltlf_ptr ltlf_arg;
        std::string symbol_name;
        // Constructor
        LTLfPlus_YYSTYPE() = default;
        // Destructor
        ~LTLfPlus_YYSTYPE() = default;
        // Copy constructor and assignment
        LTLfPlus_YYSTYPE(const LTLfPlus_YYSTYPE&) = default;
        LTLfPlus_YYSTYPE& operator=(const LTLfPlus_YYSTYPE&) = default;
        // Move constructor and assignment
        LTLfPlus_YYSTYPE(LTLfPlus_YYSTYPE&&) = default;
        LTLfPlus_YYSTYPE& operator=(LTLfPlus_YYSTYPE&&) = default;
    };
}