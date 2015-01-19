cmake_minimum_required(VERSION 2.8.4)
project(judged)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(SOURCE_FILES
    judged_test.c)

add_executable(judged_test ${SOURCE_FILES})
