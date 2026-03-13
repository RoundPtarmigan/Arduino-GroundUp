add_library(Timer)

target_sources(Timer
  PRIVATE 
    timer.c
    clocks.h
  PUBLIC
    FILE_SET HEADERS
    FILES 
      timer.h
      clocks.h
)

target_link_libraries(Timer
  PRIVATE
    Pins)