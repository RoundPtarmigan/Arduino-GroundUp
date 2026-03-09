add_library(Uart)

target_sources(Uart
  PRIVATE 
    uart.c
  PUBLIC
    FILE_SET HEADERS 
    FILES
      uart.h)