CXX = g++
CXXFLAGS += -std=c++11
CXXFLAGS += -MMD -MP -Wall
CXXFLAGS += $(addprefix -I, ${INCLUDE_PATH})

LDFLAGS += $(addprefix -L, ${LIBRARY_PATH})
LDFLAGS += $(addprefix -l, ${LIBRARY})

INCLUDE_PATH += ..
INCLUDE_PATH += ../vendor/bitfield
INCLUDE_PATH += ../vendor/bandit
INCLUDE_PATH += ../vendor/bandit_with_gmock
INCLUDE_PATH += ../vendor/googlemock/include
INCLUDE_PATH += ../vendor/googlemock/gtest/include

LIBRARY_PATH += ../vendor/googlemock
LIBRARY_PATH += ../vendor/googlemock/gtest

LIBRARY += gmock
LIBRARY += gtest
LIBRARY += pthread
