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

# CMake build : library

#configure variables
set (LIB_NAME "lydia")

## generate lexer and parser
# LTLf
FLEX_TARGET(LTLfLydiaLexer include/lydia/parser/ltlf/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ltlf/lexer.yy.cc)
BISON_TARGET(LTLfLydiaParser include/lydia/parser/ltlf/parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ltlf/parser.tab.cc )
ADD_FLEX_BISON_DEPENDENCY(LTLfLydiaLexer LTLfLydiaParser)
# LDLf
FLEX_TARGET(LDLfLydiaLexer include/lydia/parser/ldlf/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ldlf/lexer.yy.cc)
BISON_TARGET(LDLfLydiaParser include/lydia/parser/ldlf/parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ldlf/parser.tab.cc )
ADD_FLEX_BISON_DEPENDENCY(LDLfLydiaLexer LDLfLydiaParser)
# LTLf+
FLEX_TARGET(LTLfPlusLydiaLexer include/lydia/parser/ltlfplus/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ltlfplus/lexer.yy.cc)
BISON_TARGET(LTLfPlusLydiaParser include/lydia/parser/ltlfplus/parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ltlfplus/parser.tab.cc )
ADD_FLEX_BISON_DEPENDENCY(LTLfPlusLydiaLexer LTLfPlusLydiaParser)
# PPLTL
FLEX_TARGET(PPLTLLydiaLexer include/lydia/parser/ppltl/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ppltl/lexer.yy.cc)
BISON_TARGET(PPLTLLydiaParser include/lydia/parser/ppltl/parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ppltl/parser.tab.cc )
ADD_FLEX_BISON_DEPENDENCY(PPLTLLydiaLexer PPLTLLydiaParser)
# PPLTL+
FLEX_TARGET(PPLTLPlusLydiaLexer include/lydia/parser/ppltlplus/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ppltlplus/lexer.yy.cc)
BISON_TARGET(PPLTLPlusLydiaParser include/lydia/parser/ppltlplus/parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/include/lydia/parser/ppltlplus/parser.tab.cc )
ADD_FLEX_BISON_DEPENDENCY(PPLTLPlusLydiaLexer PPLTLPlusLydiaParser)

#configure directories
set (LIBRARY_MODULE_PATH "${PROJECT_SOURCE_DIR}/lib")
set (LIBRARY_SRC_PATH  "${LIBRARY_MODULE_PATH}/src" )
set (LIBRARY_INCLUDE_PATH  "${LIBRARY_MODULE_PATH}/include")

#set includes
include_directories (${LIBRARY_INCLUDE_PATH} ${THIRD_PARTY_INCLUDE_PATH})
include_directories (${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

#set sources
file (GLOB_RECURSE LIB_HEADER_FILES "${LIBRARY_INCLUDE_PATH}/*.hpp" ${LIBRARY_INCLUDE_PATH}/*.h ${LIBRARY_INCLUDE_PATH}/*.hh)
file (GLOB_RECURSE LIB_SOURCE_FILES "${LIBRARY_SRC_PATH}/*.cpp" ${LIBRARY_INCLUDE_PATH}/*.cpp ${LIBRARY_INCLUDE_PATH}/*.cc)

#set library
add_library (${LIB_NAME}
        STATIC
        ${LIB_SOURCE_FILES}
        ${LIB_HEADER_FILES}
        ${BISON_LTLfLydiaParser_OUTPUTS}
        ${BISON_LDLfLydiaParser_OUTPUTS}
        ${FLEX_LTLfLydiaLexer_OUTPUTS}
        ${FLEX_LDLfLydiaLexer_OUTPUTS}
        ${BISON_LTLfPlusLydiaParser_OUTPUTS}
        ${FLEX_LTLfPlusLydiaLexer_OUTPUTS}
        ${BISON_PPLTLLydiaParser_OUTPUTS}
        ${FLEX_PPLTLLydiaLexer_OUTPUTS}
        ${BISON_PPLTLPlusLydiaParser_OUTPUTS}
        ${FLEX_PPLTLPlusLydiaLexer_OUTPUTS}
        )

target_link_libraries(${LIB_NAME}
        ${CUDD_LIBRARIES}
        ${MONA_LIBRARIES}
        ${SYFT_LIBRARIES}
        ${GRAPHVIZ_LIBRARIES}
        ${FLEX_LIBRARIES}
        ${BISON_LIBRARIES})

#export vars
set (LIBRARY_INCLUDE_PATH  ${LIBRARY_INCLUDE_PATH} PARENT_SCOPE)
set (LIB_NAME ${LIB_NAME} PARENT_SCOPE)

#test
if (LYDIA_ENABLE_TESTS)
  add_subdirectory (test)
else()
  message("-- Tests have been disabled because LYDIA_ENABLE_TESTS was set to false.")
endif()

