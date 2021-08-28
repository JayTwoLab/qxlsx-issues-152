find_package(Qt5 COMPONENTS Test REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

option(SAVE_TEST_DOCUMENTS
    "Save xlsx documents after tests are done" OFF)

# Qt files (ui, rc)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

enable_testing(true)

add_executable(${PROJECT_NAME}
    "test_main.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Test)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

if(SAVE_TEST_DOCUMENTS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SAVE_TEST_DOCUMENTS)
endif()

set(SETUP_EXTERN_CPP_MODULES_SCRIPTS_DIR "${PROJECT_SOURCE_DIR}/cmake/setup/extern-cpp-modules")
include("${SETUP_EXTERN_CPP_MODULES_SCRIPTS_DIR}/setup-QXlsx.cmake")

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
