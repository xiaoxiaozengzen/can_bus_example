cmake_minimum_required(VERSION 3.5)
project(example)


add_executable(can_read ${CMAKE_CURRENT_SOURCE_DIR}/can_read.cpp)
add_executable(canfd_read ${CMAKE_CURRENT_SOURCE_DIR}/canfd_read.cpp)
add_executable(can_write ${CMAKE_CURRENT_SOURCE_DIR}/can_write.cpp)
add_executable(canfd_write ${CMAKE_CURRENT_SOURCE_DIR}/canfd_write.cpp)
add_executable(can_app ${CMAKE_CURRENT_SOURCE_DIR}/can_app.cpp)

install(TARGETS can_read canfd_read can_write canfd_write can_app
	RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/pragam
	LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/pragam
	ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/pragam
)



