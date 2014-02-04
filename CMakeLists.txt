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
add_executable(kermorpp_test test/test)
target_link_libraries(kermorpp_test kermorpp_static)

# add test target: test examples
ADD_TEST(KERMORPP kermorpp_test "${CMAKE_CURRENT_SOURCE_DIR}/test") #WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}