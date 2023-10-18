cmake_minimum_required(VERSION 3.14)
project(clustering)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################################
# GTest
################################
ADD_SUBDIRECTORY (googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Dataset example
################################

file(COPY Mall_Customers.csv DESTINATION "${CMAKE_BINARY_DIR}")

################################
# Exec
################################
add_subdirectory(Points)
add_executable(clustering main.cpp )
target_link_libraries(clustering points)
