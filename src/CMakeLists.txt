set(core_SRCS zstring.cpp helpers.cpp)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(core ${core_SRCS})
