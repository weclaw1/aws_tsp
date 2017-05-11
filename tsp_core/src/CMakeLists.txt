include_directories(.)

add_subdirectory(tsp)
add_subdirectory(dao)

set(SRCS
    main.cpp
)
set(HEADERS
)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} tsp dao ${PROTOBUF_LIBRARIES})
