add_executable(Button)
target_sources(Button
  PRIVATE 
    button.c
)
target_link_libraries(Button
  PUBLIC
    UtilLibrary)