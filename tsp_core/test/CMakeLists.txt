set(TEST_SOURCES
            tests.cpp
)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../externals/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

configure_file(test_graph.txt test_graph.txt COPYONLY)
configure_file(test_graph2.txt test_graph2.txt COPYONLY)

add_executable(tsp_core_test ${TEST_SOURCES})
target_link_libraries(tsp_core_test tsp dao Catch Threads::Threads)
