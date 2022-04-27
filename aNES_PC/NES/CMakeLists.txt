add_library(nes "")

target_sources(nes
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/conversion.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/conversion.hpp
  )

target_include_directories(nes
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )