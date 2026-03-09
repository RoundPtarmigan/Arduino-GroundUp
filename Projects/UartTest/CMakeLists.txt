add_executable(UartTest)
target_sources(UartTest
  PRIVATE 
    uartBash.c
)
target_link_libraries(UartTest
  PUBLIC
    UtilLibrary)