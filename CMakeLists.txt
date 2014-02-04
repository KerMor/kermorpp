PROJECT (KerMor++)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Default install prefix is "/usr/local"

SET(CMAKE_CXX_FLAGS "-Wall")
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

FIND_PACKAGE(Eigen3 REQUIRED)

# enable make test
ENABLE_TESTING()

# pathes where to look for header files
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Explicitly define where the binaries should go (needed for custom target documentation)
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})

# create mtocpp
file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(kermorpp_static STATIC ${sources})
add_library(kermorpp SHARED ${sources})

# create the test binary
add_executable(kermorpp_test test/test)
target_link_libraries(kermorpp_test kermorpp_static)

# add test target: test examples
ADD_TEST(test_kermorpp kermorpp_test "${CMAKE_CURRENT_BINARY_DIR}/../test")
SET_TESTS_PROPERTIES(test_kermorpp PROPERTIES FAIL_REGULAR_EXPRESSION "(failed!)")
