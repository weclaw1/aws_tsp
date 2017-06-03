set(SRCS
    http_examples.cpp
    server.cpp
)
set(HEADERS
    server.h
)

set(SIMPLE_WEB_SERVER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../externals/simple_web_server)
add_library(SimpleWebServer INTERFACE)
target_include_directories(SimpleWebServer INTERFACE ${SIMPLE_WEB_SERVER_INCLUDE_DIR})

set(BOOST_COMPONENTS system thread filesystem date_time regex)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_BOOST_REGEX")

find_package(Boost 1.53.0 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

add_library(rest_server STATIC ${SRCS} ${HEADERS})
target_link_libraries(rest_server ${Boost_LIBRARIES} Threads::Threads SimpleWebServer)
