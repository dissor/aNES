target_sources(aNES_PC
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/nesplay.c
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/nesplay.h
  )

target_include_directories(aNES_PC
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )
