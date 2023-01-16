cmake_minimum_required(VERSION 3.14)

set(REPOSITORY_NAME "QXlsx")
set(REPOSITORY_URL  "https://github.com/QtExcel/QXlsx.git")
set(REPOSITORY_TAG  "00380c3ffad1fad1fb63b1a244aa2864db1d3b8d")

FetchContent_Declare(
    "${REPOSITORY_NAME}"
    GIT_REPOSITORY "${REPOSITORY_URL}"
    GIT_TAG "${REPOSITORY_TAG}"
)

string(TOLOWER "${REPOSITORY_NAME}" REPOSITORY_NAME_TO_POPULATE)
FetchContent_MakeAvailable("${REPOSITORY_NAME_TO_POPULATE}")

set(QXLSX_ROOT "${${REPOSITORY_NAME_TO_POPULATE}_SOURCE_DIR}/${REPOSITORY_NAME}")
add_subdirectory("${QXLSX_ROOT}" ${${REPOSITORY_NAME_TO_POPULATE}_BINARY_DIR})

set(QXLSX_HEADERPATH "${QXLSX_ROOT}/header")
target_include_directories(${PROJECT_NAME} PRIVATE "${QXLSX_HEADERPATH}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${REPOSITORY_NAME})

