# Generic flags
set(FLAGS "-ffunction-sections -fdata-sections" CACHE STRING "MSP430 compilation flags"
)

# Define toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(TOOLCHAIN_DIR /opt/msp430-gcc)

set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/msp430-elf-gcc ${FLAGS} CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/msp430-elf-g++ CACHE PATH "" FORCE)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_DIR}/bin/msp430-elf-gcc CACHE PATH "" FORCE)
set(CMAKE_OBJCOPY ${TOOLCHAIN_DIR}/bin/msp430-elf-objcopy CACHE PATH "" FORCE)
set(CMAKE_SIZE ${TOOLCHAIN_DIR}/bin/msp430-elf-size CACHE PATH "" FORCE)

set(MSP_DEBUG mspdebug)