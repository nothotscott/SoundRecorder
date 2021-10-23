cmake_minimum_required(VERSION 3.8)
project("USBTools")

file(GLOB PROJ_SOURCES *.c)
file(GLOB PROJ_RESOURCES res/*)

add_definitions(-DUNICODE -D_UNICODE)

if(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	add_compile_options("$<$<CONFIG:RelWithDebInfo>:/MT>")
endif()

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${PROJ_SOURCES} resource.rc)
target_link_libraries(${CMAKE_PROJECT_NAME} setupapi.lib)
