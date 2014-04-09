ROOT_DIR := $(shell echo $(dir $(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST))) | sed -e 's/\/$$//')

CXX = g++
CXXFLAGS += -std=c++11
CXXFLAGS += -MMD -MP -Wall
CXXFLAGS += $(addprefix -I, ${INCLUDE_PATH})

LDFLAGS += $(addprefix -L, ${LIBRARY_PATH})
LDFLAGS += $(addprefix -l, ${LIBRARY})

INCLUDE_PATH += ${ROOT_DIR}
INCLUDE_PATH += ${ROOT_DIR}/vendor/bitfield
LIBRARY_PATH += ${ROOT_DIR}/src
LIBRARY += ${LIB_NAME}

LIB_NAME = ts_processor
LIB = ${ROOT_DIR}/src/lib${LIB_NAME}.a
