cmake_minimum_required(VERSION 3.22)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CXX_WARNINGS "-Wall -Wextra")

set(CMAKE_CXX_FLAGS "${CXX_WARNINGS}")

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/Common)

set(SRCS ${CMAKE_CURRENT_SOURCE_DIR}/Peripherals/Gpio.cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/Network/server.cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/Peripherals/Can.cpp)


add_executable(${PROJECT_NAME} main.cpp ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
