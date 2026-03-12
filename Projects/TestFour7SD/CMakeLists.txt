add_executable(TestFour7SD)
target_sources(TestFour7SD 
  PRIVATE 
    testFour7SD.c
)
target_link_libraries(TestFour7SD
  PUBLIC
    UtilLibrary)

include(GNUInstallDirs)
add_custom_command(
  TARGET TestFour7SD 
  POST_BUILD 
  COMMAND ${CMAKE_OBJCOPY} TestFour7SD
)

add_custom_command(
  TARGET TestFour7SD 
  POST_BUILD 
  COMMAND ${CMAKE_OBJDUMP} TestFour7SD
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/TestFour7SD.hex
  TYPE BIN
)