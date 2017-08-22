set(SRCS
    jsonconverter.cpp
    taskUtils.cpp
)
set(HEADERS
    jsonconverter.h
    taskUtils.h
)

set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../externals/json)
add_library(Json INTERFACE)
target_include_directories(Json INTERFACE ${JSON_INCLUDE_DIR})

add_library(json_converter STATIC ${SRCS} ${HEADERS})
target_link_libraries(json_converter Json tsp)
