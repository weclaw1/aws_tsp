include_directories(.)

add_subdirectory(tsp)
add_subdirectory(dao)
add_subdirectory(json_converter)
add_subdirectory(rest_server)

set(SRCS
    main.cpp
)
set(HEADERS
)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${PROJECT_NAME} json_converter tsp dao rest_server)
