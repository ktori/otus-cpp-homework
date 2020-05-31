cmake_minimum_required(VERSION 3.17)
project(06-matrix VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

add_executable(matrix)

install(TARGETS matrix RUNTIME DESTINATION bin)

add_subdirectory(src)

set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_LIST_DIR}/Doxyfile)

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tori@ktori.me)

include(CPack)

enable_testing()
if (NOT TARGET gtest)
    add_subdirectory(../../googletest googletest EXCLUDE_FROM_ALL)
endif ()

add_executable(matrix_test test/matrix_test.cpp src/matrix.hpp src/detail/indexer.hpp src/detail/generators.hpp src/detail/iterator.hpp)
target_link_libraries(matrix_test PRIVATE gtest gtest_main)
add_test(matrix_test matrix_test)
