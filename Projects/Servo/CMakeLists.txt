add_executable(Servo)
target_sources(Servo
  PRIVATE 
    servo.c
)
target_link_libraries(Servo
  PUBLIC
    UtilLibrary)