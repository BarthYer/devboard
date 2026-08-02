cmake_minimum_required(VERSION 3.20.0)
set(BOARD xiao_esp32c3)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(devboard)

zephyr_include_directories(include)

target_sources(app PRIVATE
        src/main.c
        src/ssd1306.c)
