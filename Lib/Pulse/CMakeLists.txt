add_library(Pulse)

target_sources(Pulse
  PRIVATE 
    pulse.c
  PUBLIC 
    FILE_SET HEADERS
    FILES 
      pulse.h)

target_link_libraries(Pulse PRIVATE Pins Timer)