add_library(SevenSegDisp)

target_link_libraries(SevenSegDisp
  PRIVATE
    Pins
    ShiftReg)
    
target_sources(SevenSegDisp
  PRIVATE 
    single7SD.c
  INTERFACE 
    codes7SD.h
  PUBLIC
    FILE_SET HEADERS 
    FILES
      single7SD.h)