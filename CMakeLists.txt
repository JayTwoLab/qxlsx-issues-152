cmake_minimum_required(VERSION 3.14)

include(FetchContent)
project(qxlsx-issue-152
    VERSION 1.0
    DESCRIPTION "Test suite for [QXlsx] issue #152"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
add_subdirectory(tests)
