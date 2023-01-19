cmake_minimum_required(VERSION 3.0)

# Project name
project(MSP430G2553-practice VERSION 0.1.1)

set(MCU_MODEL MSP430G2553)

set(EXECUTABLE ${CMAKE_PROJECT_NAME})

#Headers
set(MSP_INCLUDE_DIRECTORIES
    ${TOOLCHAIN_DIR}/include)

set(INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/app
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/gpio
)

# Sources
file(GLOB_RECURSE MSP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/app/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/gpio/*.c
)

# Add executable files
add_executable(${EXECUTABLE}
    ${MSP_SOURCES}
)

# Embedded macros(defines)
target_compile_definitions(${EXECUTABLE} PRIVATE
    __${MCU_MODEL}__ 
)

# Add header directories
target_include_directories(${EXECUTABLE} PRIVATE
    ${MSP_INCLUDE_DIRECTORIES}
    ${INCLUDE_DIRECTORIES}
)

set(MCU_LINKER_SCRIPT ${TOOLCHAIN_DIR}/include/$<LOWER_CASE:${MCU_MODEL}>.ld)

target_compile_options(${EXECUTABLE} PRIVATE
    -mmcu=${MCU_MODEL}
    -Wall
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>
)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    -L${MSP_INCLUDE_DIRECTORIES}
    -mmcu=${MCU_MODEL}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--print-memory-usage
    -Wl,--gc-sections
)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin
)

add_custom_target(flash
    COMMAND mspdebug -q rf2500 "prog ${EXECUTABLE}.hex"
)

# Hello world
