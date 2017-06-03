set(SRCS
    weightedgraph.cpp
    farthestinsertiontsp.cpp
    asynctsprunner.cpp
    weightedgraphtextfilereader.cpp
)
set(HEADERS
    weightedgraph.h
    node.h
    farthestinsertiontsp.h
    abstracttspalgorithm.h
    asynctsprunner.h
    task.h
    weightedgraphtextfilereader.h
)


add_library(tsp STATIC ${SRCS} ${HEADERS})
target_link_libraries(tsp Threads::Threads)
