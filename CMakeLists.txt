cmake_minimum_required(VERSION 3.0.0)
project(project2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(project2 main.cpp)
add_test(project2 test.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
