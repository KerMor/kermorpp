PROJECT (KerMor++)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

OPTION(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
OPTION(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
FIND_PACKAGE(Eigen3 REQUIRED)
include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# create library
file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(kermorpp ${sources})

# add test target: test examples
ENABLE_TESTING()

add_executable(test_load test/test_load)
target_link_libraries(test_load kermorpp)
add_executable(test_eval test/test_eval)
target_link_libraries(test_eval kermorpp)

ADD_TEST(KERMORPP_LOADING_GAUSSIAN ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/gaussian")
ADD_TEST(KERMORPP_LOADING_WENDLAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/wendland")
ADD_TEST(KERMORPP_EVALUATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_eval)