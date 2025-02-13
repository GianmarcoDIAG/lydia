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

# PPTLPlus parser
FLEX_TARGET(lydia_ppltlplus_lexer include/lydia/parser/ppltlplus/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ppltlplus/lexer.yy.cc)
BISON_TARGET(lydia_ppltlplus_parser include/lydia/parser/ppltlplus/parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ppltlplus/parser.tab.cc )
ADD_FLEX_BISON_DEPENDENCY(lydia_ppltlplus_lexer lydia_ppltlplus_parser)