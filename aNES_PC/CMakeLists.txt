cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(aNES_PC LANGUAGES C)

#设置debug模式
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -mwindows")

add_executable(aNES_PC "")

target_sources(aNES_PC
  PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/main.c
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/main.h
  )

target_include_directories(aNES_PC
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )

include(${CMAKE_CURRENT_LIST_DIR}/NES/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/NESplay/CMakeLists.txt)