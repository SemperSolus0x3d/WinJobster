cmake_minimum_required(VERSION 3.24)

project(WinJobster VERSION 1.0.0 LANGUAGES CXX)

set(BUILD_SHARED_LIBS ON)

set(WINJOBSTER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Defines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Process.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Process.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Wrappers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Wrappers.cpp
)

add_library(${PROJECT_NAME} ${WINJOBSTER_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "D")

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    WINJOBSTER_EXPORT
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

install(TARGETS ${PROJECT_NAME})
