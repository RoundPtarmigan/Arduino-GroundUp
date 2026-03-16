add_executable(TimerClockTest)
target_sources(TimerClockTest 
  PRIVATE 
    timerClockTest.c
)
target_link_libraries(TimerClockTest
  PUBLIC
    UtilLibrary)

include(GNUInstallDirs)
add_custom_command(
  TARGET TimerClockTest 
  POST_BUILD 
  COMMAND ${CMAKE_OBJCOPY} TimerClockTest
)

add_custom_command(
  TARGET TimerClockTest 
  POST_BUILD 
  COMMAND ${CMAKE_OBJDUMP} TimerClockTest
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/TimerClockTest.hex
  TYPE BIN
)