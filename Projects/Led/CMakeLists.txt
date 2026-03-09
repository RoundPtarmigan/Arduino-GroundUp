add_executable(Led)
target_sources(Led
  PRIVATE 
    led.c
)
target_link_libraries(Led
  PUBLIC
    UtilLibrary)