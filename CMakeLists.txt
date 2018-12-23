cmake_minimum_required(VERSION 3.2)
project (playground)

include_directories(".")
include_directories("../vcpkg/packages/abseil_x86-windows/include")
include_directories("../vcpkg/packages/range-v3-vs2015_x86-windows/include")

add_subdirectory(lib)
add_subdirectory(tests)
