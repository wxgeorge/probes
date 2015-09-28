set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -foo")
message("In parent, CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")

add_subdirectory("sub-directory")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -baz")
message("In parent, CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")