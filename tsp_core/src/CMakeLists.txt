include_directories(.)

add_subdirectory(tsp)

set(SRCS
    main.cpp
)
set(HEADERS
)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} tsp ${PROTOBUF_LIBRARIES} Threads::Threads)
