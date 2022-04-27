target_sources(aNES_PC
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/nes_main.c
    # ${CMAKE_CURRENT_LIST_DIR}/cpu6502.c
    # ${CMAKE_CURRENT_LIST_DIR}/PPU.c
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/nes_main.h
    # ${CMAKE_CURRENT_LIST_DIR}/cpu6502.h
    # ${CMAKE_CURRENT_LIST_DIR}/PPU.h
  )

target_include_directories(aNES_PC
  PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
  )