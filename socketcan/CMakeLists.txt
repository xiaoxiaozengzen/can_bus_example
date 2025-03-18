cmake_minimum_required(VERSION 3.10)
project(CornerRadarFps)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
message("SRCS: ${SRCS}")

add_executable(${PROJECT_NAME}_exe ${SRCS})
target_include_directories(
    ${PROJECT_NAME}_exe
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)