project (graphs)
cmake_minimum_required(VERSION 2.8)
include(../vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(../vcpkg/packages/boost_x86-windows/include)
include_directories(../vcpkg/packages/range-v3_x86-windows/include)

file(GLOB SOURCES "*.cc")

add_executable(main ${SOURCES})

# target_link_libraries(bfs
#   ${Boost_FILESYSTEM_LIBRARY}
#   ${Boost_SYSTEM_LIBRARY}
#   ${PROTOBUF_LIBRARY}
# )
