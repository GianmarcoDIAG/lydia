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

# CMake build : main application

#configure variables
# we append '-bin' because 'lydia' conflicts with the library.
set (APP_NAME "lydia-bin")

#configure directories
set (APP_MODULE_PATH "${PROJECT_SOURCE_DIR}/app/lydia")
set (APP_SRC_PATH  "${APP_MODULE_PATH}/src" )

#set includes
include_directories (${APP_SRC_PATH} ${LIBRARY_INCLUDE_PATH} ${THIRD_PARTY_INCLUDE_PATH})

#set sources
file (GLOB APP_SOURCE_FILES "${APP_SRC_PATH}/*.cpp")
list(REMOVE_ITEM APP_SOURCE_FILES "${APP_SRC_PATH}/main.cpp")  
list(REMOVE_ITEM APP_SOURCE_FILES "${APP_SRC_PATH}/parse.cpp")

#set target executable
add_executable (${APP_NAME} src/main.cpp ${APP_SOURCE_FILES})
add_executable (parser_tester src/parse.cpp ${APP_SOURCE_FILES})

#add the library
target_link_libraries (${APP_NAME} ${LIB_NAME} Threads::Threads)
target_link_libraries (parser_tester ${LIB_NAME} Threads::Threads)

set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME lydia)
set_target_properties(parser_tester PROPERTIES OUTPUT_NAME parser_tester)

#test
enable_testing ()
add_subdirectory (test)

install(TARGETS lydia-bin
    DESTINATION ${CMAKE_INSTALL_BINDIR})
