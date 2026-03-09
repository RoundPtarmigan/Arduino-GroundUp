add_executable(TestSingle7SD)
target_sources(TestSingle7SD 
  PRIVATE 
    testSingle7SD.c
)
target_link_libraries(TestSingle7SD
  PUBLIC
    UtilLibrary)

include(GNUInstallDirs)
add_custom_command(
  TARGET TestSingle7SD 
  POST_BUILD 
  COMMAND ${CMAKE_OBJCOPY} TestSingle7SD
)

add_custom_command(
  TARGET TestSingle7SD 
  POST_BUILD 
  COMMAND ${CMAKE_OBJDUMP} TestSingle7SD
)

#message("${CMAKE_OBJCOPY} ${CMAKE_OBJCOPY_FLAGS} TestSingle7SD TestSingle7SD.hex")
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/TestSingle7SD.hex
  TYPE BIN
)