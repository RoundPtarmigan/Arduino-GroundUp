add_executable(Blink)
target_sources(Blink 
  PRIVATE 
    blink.c
)
target_link_libraries(Blink
  PUBLIC
    UtilLibrary)

include(GNUInstallDirs)
add_custom_command(
  TARGET Blink 
  POST_BUILD 
  COMMAND ${CMAKE_OBJCOPY} Blink
)

add_custom_command(
  TARGET Blink 
  POST_BUILD 
  COMMAND ${CMAKE_OBJDUMP} Blink
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/Blink.hex
  TYPE BIN
)