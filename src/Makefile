include ../common.mk

MAIN = tssplitter
LIB_SRC = $(basename $(shell find ${ROOT_DIR}/src -name '*.cpp' $(addprefix -not -name , $(addsuffix .cpp, ${MAIN}))))
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

${MAIN}: $(addsuffix .o, ${SRC}) ${LIB}
	${CXX} ${LDFLAGS} -o $@ $<

-include $(addsuffix .d, ${SRC})
