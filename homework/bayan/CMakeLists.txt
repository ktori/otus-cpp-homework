cmake_minimum_required(VERSION 3.17)
project(09-bayan VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.72.0 REQUIRED COMPONENTS filesystem program_options)
find_package(OpenSSL REQUIRED)

add_executable(bayan)

target_link_libraries(bayan OpenSSL::Crypto Boost::filesystem Boost::program_options)

install(TARGETS bayan RUNTIME DESTINATION bin)

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
