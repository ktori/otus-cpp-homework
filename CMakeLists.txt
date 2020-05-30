cmake_minimum_required(VERSION 3.17)

project(homework)

add_subdirectory(googletest EXCLUDE_FROM_ALL)
enable_testing()

set(INSTALL_GMOCK OFF)
set(INSTALL_GTEST OFF)

add_subdirectory(homework)