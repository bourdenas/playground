project (test_algos)

set(TESTS 
  "main.cc"
)

add_executable(test_algo ${TESTS})

target_link_libraries(test_algo
  algo_lib
  absl::strings
)