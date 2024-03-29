#############################################
# Unit tests

cmake_minimum_required(VERSION 3.20)

project (google_tests)

# Add an library for the example classes
add_library(google_tests
    Reverse.cpp
    Palindrome.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${HTTPMOCKSERVER_INCLUDE_DIRS}
    ${CPR_INCLUDE_DIRS}
    ${MHD_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

find_package(include(GoogleTest))

# enable CTest testing
enable_testing()

# Add a testing executable
add_executable(unit_tests unit_tests.cpp)

target_link_libraries(unit_tests
    google_tests
    GTest::GTest 
    GTest::Main
)

target_link_libraries(test-server
    ${HTTPMOCKSERVER_LIBRARIES}
    ${MHD_LIBRARIES}
    ${CPR_LIBRARIES}
    ${GTEST_LIBRARIES}
    -lpthread
)


add_test(test_all unit_tests)



