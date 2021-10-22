cmake_minimum_required (VERSION 3.8)
project ("SoundRecorder")

file(GLOB PROJ_SOURCES *.c)

add_definitions(-DUNICODE -D_UNICODE)

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${PROJ_SOURCES})