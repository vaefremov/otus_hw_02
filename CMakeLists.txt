cmake_minimum_required(VERSION 3.5)

if("$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
  message("Warning: Could not find TRAVIS_BUILD_NUMBER environment variable")
  set(VERSION_NUMBER "0.1.42")
else()
  set(VERSION_NUMBER "0.1.$ENV{TRAVIS_BUILD_NUMBER}")
endif()

project(ip_filter VERSION ${VERSION_NUMBER})

find_package(GTest REQUIRED)
find_package(Threads)

configure_file(src/config.h.in config.h)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(benchmark)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(utilities src/utilities.cpp src/process_stl.cpp src/process_ranges.cpp)
target_include_directories(utilities
    PRIVATE "${CMAKE_BINARY_DIR}"
    "include"
)


add_executable(ip_filter src/main.cpp)
target_include_directories(ip_filter
    PRIVATE 
    "include"
    
)
target_link_libraries(ip_filter PRIVATE utilities)

add_executable(test_ipfilter tests/test_scan_ip4.cpp)
target_include_directories(test_ipfilter
    PRIVATE 
    "include"
    "src"
    "${CMAKE_BINARY_DIR}" "${CMAKE_HOME_DIRECTORY}"
    "${GTEST_INCLUDE_DIR}"
)
target_link_libraries(test_ipfilter
    utilities
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(test_process_stl tests/test_process_stl.cpp)
target_include_directories(test_process_stl
    PRIVATE 
    "include"
    "src"
    "${CMAKE_BINARY_DIR}" "${CMAKE_HOME_DIRECTORY}"
    "${GTEST_INCLUDE_DIR}"
    "${CONAN_INCLUDE_DIRS}"
)
target_link_libraries(test_process_stl
    utilities
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CONAN_LIBS}
)

add_executable(test_process_ranges tests/test_process_ranges.cpp)
target_include_directories(test_process_ranges
    PRIVATE 
    "include"
    "src"
    "${CMAKE_BINARY_DIR}" "${CMAKE_HOME_DIRECTORY}"
    "${GTEST_INCLUDE_DIR}"
    "${CONAN_INCLUDE_DIRS}"
)
target_link_libraries(test_process_ranges
    utilities
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CONAN_LIBS}
)

add_executable(benchmark_process tests/benchmark_process.cpp)
target_include_directories(benchmark_process
    PRIVATE 
    "include"
    "src"
    "${CMAKE_BINARY_DIR}" "${CMAKE_HOME_DIRECTORY}"
    "${GTEST_INCLUDE_DIR}"
    "${CONAN_INCLUDE_DIRS}"
)
target_link_libraries(benchmark_process
    utilities
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CONAN_LIBS}
    benchmark::benchmark
)

enable_testing()
add_test(test_utilities bin/test_ipfilter)
add_test(test_process_stl bin/test_process_stl)
add_test(test_process_ranges bin/test_process_ranges)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT vefremov@gmail.com)

include(CPack)
