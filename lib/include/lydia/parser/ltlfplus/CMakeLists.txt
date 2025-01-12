#
# This file is part of Lydia.
#
# Lydia is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Lydia is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Lydia.  If not, see <https://www.gnu.org/licenses/>.
#


# LTLf+ parser
FLEX_TARGET(lydia_ltlfplus_lexer include/lydia/parser/ltlfplus/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ltlfplus/lexer.yy.cc)
BISON_TARGET(lydia_ltlfplus_parser include/lydia/parser/ltlfplus/parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ltlfplus/parser.tab.cc )
ADD_FLEX_BISON_DEPENDENCY(lydia_ltlfplus_lexer lydia_ltlfplus_parser)
