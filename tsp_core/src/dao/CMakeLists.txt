set(SRCS
    abstractdao.cpp
    sqlitedao.cpp
)
set(HEADERS
    abstractdao.h
    sqlitedao.h
)

find_package (sqlite3)
include_directories(${SQLITE3_INCLUDE_DIRS})

set(SQLITE_3PP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../externals/sqlite3pp)
add_library(sqlite3pp INTERFACE)
target_include_directories(sqlite3pp INTERFACE ${SQLITE_3PP_INCLUDE_DIR})

add_library(dao STATIC ${SRCS} ${HEADERS})
target_link_libraries(dao ${SQLITE3_LIBRARIES} sqlite3pp tsp)


