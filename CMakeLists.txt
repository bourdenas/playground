cmake_minimum_required(VERSION 3.2)
project (playground)

include_directories(".")
if(MSVC)
  # Visual Studio compiler cannot compile range-v3 library, use alternative.
  include_directories("../vcpkg/packages/range-v3-vs2015_x86-windows/include")
endif()

add_subdirectory(libs/abseil-cpp)
add_subdirectory(libs/range-v3)
add_subdirectory(lib)
add_subdirectory(tests)
