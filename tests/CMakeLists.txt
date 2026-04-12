cmake_minimum_required(VERSION 3.14)
include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG v1.14.0)
FetchContent_MakeAvailable(googletest)
enable_testing()
file(GLOB TEST_SOURCES "*_test.cpp")
add_executable(tofupilot_tests ${TEST_SOURCES})
target_link_libraries(tofupilot_tests PRIVATE tofupilot GTest::gtest_main)
target_include_directories(tofupilot_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(tofupilot_tests PRIVATE
    <httplib.h>
    <nlohmann/json.hpp>
    <gtest/gtest.h>
    "${CMAKE_SOURCE_DIR}/include/tofupilot/tofupilot.hpp"
)
include(GoogleTest)
gtest_discover_tests(tofupilot_tests)
