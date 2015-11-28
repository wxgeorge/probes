cmake_minimum_required(VERSION 3.2)
project(provision-probing)

set(CMAKE_CXX_STANDARD 11)
set(TIP ../../..)

add_subdirectory(${TIP}/api ${CMAKE_CURRENT_BINARY_DIR}/api)
include_directories(${TIP}/api/src/api)

add_executable(provision-api with-api.cpp)
target_link_libraries(provision-api napi)
