cmake_minimum_required(VERSION 3.20.0)

set(BOARD esp32s3_devkitc/esp32s3/procpu)
#set(BOARD esp32_devkitc/esp32/procpu)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(button_demo)
include_directories(include)

target_sources(app PRIVATE src/main.c src/ssd1306.c)