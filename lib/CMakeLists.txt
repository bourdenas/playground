project (algos)

set(SOURCES
  "algorithms.cc"
  "backtracking.cc"
)

add_library(algo_lib ${SOURCES})

# Depend on a libraries defined in the top-level file.
# target_link_libraries(algo_lib
#     abseil
#     range-v3
# )
