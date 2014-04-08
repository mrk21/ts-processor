include ../common.mk

TARGET = tssplitter
SRCS = $(basename $(shell find . -name '*.cpp'))

.PHONY: all
all: ${TARGET}

.PHONY: clean
clean:
	${RM} ${TARGET} $(addsuffix .d, ${SRCS}) $(addsuffix .o, ${SRCS})

.PHONY: rebuild
rebuild: clean all

${TARGET}: $(addsuffix .o, ${SRCS})
	${CXX} ${LDFLAGS} -o $@ $^

-include $(addsuffix .d, ${SRCS})
