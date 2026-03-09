add_executable(Shift)
target_sources(Shift 
  PRIVATE 
    shift.c
)
target_link_libraries(Shift
  PUBLIC
    UtilLibrary)

include(GNUInstallDirs)
add_custom_command(
  TARGET Shift
  POST_BUILD 
  COMMAND ${CMAKE_OBJCOPY} Shift
)

add_custom_command(
  TARGET Shift
  POST_BUILD 
  COMMAND ${CMAKE_OBJDUMP} Shift
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/Shift.hex
  TYPE BIN
)