set(SRCS
    main.cpp
    weightedgraph.cpp
    farthestinsertiontsp.cpp
)
set(HEADERS
    weightedgraph.h
    node.h
    farthestinsertiontsp.h
)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARIES})
