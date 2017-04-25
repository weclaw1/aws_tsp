set(TEST_SOURCES
            tests.cpp
)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../externals/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(tsp_core_test ${TEST_SOURCES})
target_link_libraries(tsp_core_test tsp Catch)

enable_testing()
add_test(NAME test_tsp_core COMMAND tsp_core_test)
