.PHONY: all build cmake clean format flash

BUILD_DIR       := build
BUILD_TYPE      ?= Debug

all: build

${BUILD_DIR}/Makefile:
	cmake \
		-B${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_TOOLCHAIN_FILE=msp430g2553.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake: ${BUILD_DIR}/Makefile

build: cmake
	$(MAKE) -C ${BUILD_DIR} --no-print-directory

SRCS := $(shell find . -name '*.[ch]' -or -name '*.[ch]pp')
format: $(addsuffix .format,${SRCS})

%.format: %
	clang-format -i $<

clean:
	@echo Removing ${BUILD_DIR} directory
	rm -rf ${BUILD_DIR}
	@echo Done.

flash: ${BUILD_DIR}/*.hex
	@echo Flashing ${BUILD_DIR}/*.hex
	$(MAKE) -C ${BUILD_DIR} flash --no-print-directory
