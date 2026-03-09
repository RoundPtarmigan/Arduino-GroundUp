add_library(UtilLibrary INTERFACE)

add_subdirectory(ExtHeaders)
add_subdirectory(Pins)
add_subdirectory(Timer)
add_subdirectory(Pulse)
add_subdirectory(Uart)
add_subdirectory(ShiftReg)
add_subdirectory(SevenSegDisp)

target_link_libraries(UtilLibrary
  INTERFACE
    ExtHeaders
    Pins
    Timer
    Pulse
    Uart
    ShiftReg
    SevenSegDisp
)
