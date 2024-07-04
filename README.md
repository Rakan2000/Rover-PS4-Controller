Download the files from discord and replace the "sketch.cpp" with the one in this repository. You would need to also change the "Cmake" version and that is by adding the "@ 6.6.0" to the file "platformio.ini" at line "14".


[env:esp32-wroom]
platform = espressif32 @ 6.6.0
platform_packages = 
    framework-espidf@~3.40406.0
    toolchain-xtensa-esp32@8.4.0+2021r2-patch5
framework = espidf
board = upesy_wroom
monitor_speed = 115200
monitor_filters = direct
