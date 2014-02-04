PROJECT (KerMor++)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Default install prefix is "/usr/local"

SET(CMAKE_CXX_FLAGS "-Wall -O3")
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

FIND_PACKAGE(Eigen3 REQUIRED)

# enable make test
ENABLE_TESTING()

# path where to look for header files
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include")

# create libraries
file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(kermorpp_static STATIC ${sources})
add_library(kermorpp SHARED ${sources})

# create the test binary
add_executable(test_load test/test_load)
target_link_libraries(test_load kermorpp_static)
add_executable(test_eval test/test_eval)
target_link_libraries(test_eval kermorpp_static)

# add test target: test examples
ADD_TEST(KERMORPP_LOADING_GAUSSIAN test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/gaussian")
ADD_TEST(KERMORPP_LOADING_WENDLAND test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/wendland")
ADD_TEST(KERMORPP_EVALUATION test_eval)