set(SRCS
    weightedgraph.cpp
    farthestinsertiontsp.cpp
)
set(HEADERS
    weightedgraph.h
    node.h
    farthestinsertiontsp.h
)


add_library(tsp STATIC ${SRCS} ${HEADERS})
