include ../common.mk

MAIN = $(basename $(wildcard *.cpp))
LIB_SRC = $(basename $(shell find ${ROOT_DIR}/src/ts_processor -name '*.cpp'))
SRC = ${MAIN} ${LIB_SRC}

.PHONY: all
all: ${MAIN}

.PHONY: lib
lib: ${LIB}

.PHONY: clean
clean:
	${RM} ${MAIN} ${LIB} $(addsuffix .d, ${SRC}) $(addsuffix .o, ${SRC})

.PHONY: rebuild
rebuild: clean all

${LIB}: $(addsuffix .o, ${LIB_SRC})
	${AR} r $@ $^

${MAIN}: $(addsuffix .o, ${MAIN}) ${LIB}
	${CXX} ${LDFLAGS} -o $@ $@.o

-include $(addsuffix .d, ${SRC})
