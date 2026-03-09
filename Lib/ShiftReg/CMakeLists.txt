add_library(ShiftReg)

target_link_libraries(ShiftReg
  PRIVATE
    Pins)
target_sources(ShiftReg
  PRIVATE 
    shiftReg.c
  PUBLIC
    FILE_SET HEADERS 
    FILES
      shiftReg.h)