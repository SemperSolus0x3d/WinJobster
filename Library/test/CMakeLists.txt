cmake_minimum_required(VERSION 3.24)

project(WinJobsterTest VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
)

target_link_libraries(${PROJECT_NAME} WinJobster)
add_test(NAME "${PROJECT_NAME}" COMMAND "$<TARGET_FILE:${PROJECT_NAME}>")
