add_executable(TimerTest)
target_sources(TimerTest
  PRIVATE 
    timerTest.c
)
target_link_libraries(TimerTest
  PUBLIC
    UtilLibrary)