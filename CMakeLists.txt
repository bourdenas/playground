project (graphs)
cmake_minimum_required(VERSION 2.8)

include_directories(".")
include_directories("../vcpkg/packages/abseil_x86-windows/include")
include_directories("../vcpkg/packages/range-v3-vs2015_x86-windows/include")

file(GLOB SOURCES "lib/*.cc" "tests/*.cc")

add_executable(main ${SOURCES})
