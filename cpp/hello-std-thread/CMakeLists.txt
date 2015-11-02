cmake_minimum_required(VERSION 3.0)
project(std-thread-probe)

set(TIP "${CMAKE_CURRENT_SOURCE_DIR}/../..")
include_directories("${TIP}/plog/include")

set(CXX_STANDARD 11)

add_executable(std-thread-probe main.cc)
