set(SRCS
    abstractdao.cpp
)
set(HEADERS
    abstractdao.h
)


add_library(dao STATIC ${SRCS} ${HEADERS})
