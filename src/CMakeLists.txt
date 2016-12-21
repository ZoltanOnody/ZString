set(core_SRCS riesenie.cpp helpers.cpp helpers.h)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(core ${core_SRCS})
