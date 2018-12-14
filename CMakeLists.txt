cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME cpp_named_pipes)
project(${PROJECT_NAME})
find_package(Catch2 CONFIG REQUIRED)
add_executable(test test.cpp)
add_executable(main main.cpp npipe_server.cpp npipe_server.h)
target_link_libraries(test PRIVATE Catch2::Catch2)


