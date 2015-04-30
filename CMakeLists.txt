CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT (KerMor++ VERSION 1.0 LANGUAGES CXX)

OPTION(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
OPTION(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

if (NOT EIGEN3_INCLUDE_DIR)
    LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
    FIND_PACKAGE(Eigen3 REQUIRED)
endif()

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
add_custom_target(test_verbose COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

ADD_TEST(KERMORPP_LOADING_GAUSSIAN ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/data/gaussian")
ADD_TEST(KERMORPP_LOADING_WENDLAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/data/wendland")
ADD_TEST(KERMORPP_LOADING_2D3D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/data/2D3D")
ADD_TEST(KERMORPP_LOADING_MEDIUM_SIZE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/data/midsize")
ADD_TEST(KERMORPP_LOADING_SPINE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_load "${CMAKE_CURRENT_SOURCE_DIR}/test/data/spine")
ADD_TEST(KERMORPP_EVALUATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_eval)

# Install section
install(TARGETS kermorpp EXPORT kermorpp-config
    DESTINATION lib
    INCLUDES DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/kermorpp.h DESTINATION include)
install(EXPORT kermorpp-config DESTINATION cmake)
include(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(${CMAKE_CURRENT_BINARY_DIR}/kermorpp-config-version.cmake
    COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kermorpp-config-version.cmake DESTINATION cmake)