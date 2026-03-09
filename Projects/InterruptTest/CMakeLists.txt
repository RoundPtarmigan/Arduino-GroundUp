add_executable(InterruptTest)
target_sources(InterruptTest
  PRIVATE 
    intTest.c
)
target_link_libraries(InterruptTest
  PUBLIC
    UtilLibrary)