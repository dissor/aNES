cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(aNES_PC LANGUAGES C)

add_executable(aNES_PC "")

target_sources(aNES_PC
  PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/main.c
  )

include(${CMAKE_CURRENT_LIST_DIR}/NESplay/CMakeLists.txt)