add_executable(TiltBall)
target_sources(TiltBall
  PRIVATE 
    tiltBall.c
)
target_link_libraries(TiltBall
  PUBLIC
    UtilLibrary)