cmake_minimum_required(VERSION 3.12)

if("$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
  message("Warning: Could not find TRAVIS_BUILD_NUMBER environment variable")
  set(VERSION_NUMBER "0.0.42")
else()
  set(VERSION_NUMBER "0.0.$ENV{TRAVIS_BUILD_NUMBER}")
endif()

project(ip_filter VERSION ${VERSION_NUMBER})

find_package(GTest REQUIRED)
find_package(Threads)

configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ip_filter main.cpp)
target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)
