add_executable(PassiveBuzz)
target_sources(PassiveBuzz
  PRIVATE 
    passiveBuzz.c
)
target_link_libraries(PassiveBuzz
  PUBLIC
    UtilLibrary)