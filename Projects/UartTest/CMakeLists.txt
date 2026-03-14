add_executable(UartTest)
target_sources(UartTest
  PRIVATE 
    uartTest.c
)
target_link_libraries(UartTest
  PUBLIC
    UtilLibrary)

include(GNUInstallDirs)
add_custom_command(
  TARGET UartTest 
  POST_BUILD 
  COMMAND ${CMAKE_OBJCOPY} UartTest
)

add_custom_command(
  TARGET UartTest 
  POST_BUILD 
  COMMAND ${CMAKE_OBJDUMP} UartTest
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/UartTest.hex
  TYPE BIN
)