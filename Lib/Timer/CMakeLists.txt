add_library(Timer)

target_sources(Timer
  PRIVATE 
    timer.c
  INTERFACE
    FILE_SET HEADERS
    FILES 
      timer.h
)

target_link_libraries(Timer
  PRIVATE
    Pins)