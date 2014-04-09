include ../common.mk

INCLUDE_PATH += .
INCLUDE_PATH += ${ROOT_DIR}/vendor/bandit
INCLUDE_PATH += ${ROOT_DIR}/vendor/bandit_with_gmock
INCLUDE_PATH += ${ROOT_DIR}/vendor/googlemock/include
INCLUDE_PATH += ${ROOT_DIR}/vendor/googlemock/gtest/include

LIBRARY_PATH += ${ROOT_DIR}/vendor/googlemock
LIBRARY_PATH += ${ROOT_DIR}/vendor/googlemock/gtest

LIBRARY += gmock
LIBRARY += gtest
LIBRARY += pthread

TARGET = spec_main
SRC = ${TARGET} $(basename $(shell find spec -name '*_spec.cpp'))


.PHONY: all
all: lib ${TARGET}
	./$(word 2, $^) ${args}

.PHONY: lib
lib:
	${MAKE} -C ../src lib

.PHONY: clean
clean:
	${RM} ${TARGET} $(addsuffix .d, ${SRC}) $(addsuffix .o, ${SRC})

.PHONY: rebuild
rebuild: clean all


${TARGET}: ${LIB} $(addsuffix .o, ${SRC})
	${CXX} ${LDFLAGS} -o $@ $(wordlist 2, $(words $^), $^)

-include $(addsuffix .d, ${SRC})
