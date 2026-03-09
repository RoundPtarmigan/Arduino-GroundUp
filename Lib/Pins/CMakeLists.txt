add_library(Pins)


target_sources(Pins
  PRIVATE 
    ioPort.c
    pwm.c
    extInterrupts.c
  PUBLIC
    FILE_SET HEADERS
    FILES 
      ioPort.h
      pwm.h
      extInterrupts.h
)
target_link_libraries(Pins
    PUBLIC
      ExtHeaders)