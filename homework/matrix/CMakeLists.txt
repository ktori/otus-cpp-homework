cmake_minimum_required(VERSION 3.17)
project(matrix)
set(CMAKE_CXX_STANDARD 17)

add_executable(matrix)

add_subdirectory(src)

set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_LIST_DIR}/Doxyfile)

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)