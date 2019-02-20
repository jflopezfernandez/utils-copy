
vpath %.cpp src
vpath %.h include

CXX := g++
CXXFLAGS := -std=c++17 -g
CPPFLAGS := -I include -I /usr/include
COMPILE.cpp := $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) $(TARGET_ARCH)

LIB_BOOST_PROGRAM_OPTIONS := -lboost_program_options
LIBRARIES := $(LIB_BOOST_PROGRAM_OPTIONS)
LFLAGS := $(LIBRARIES)

DOXYGEN := doxygen
DOXYGEN_CONFIG := copy-config

PROJECT := copy

.DEFAULT: all

all: $(PROJECT)

$(PROJECT): Copy.o
	$(COMPILE.cpp) -o $@ $^ $(LFLAGS)
	$(MAKE) generate_docs

Copy.o: Copy.cpp Copy.h
	$(COMPILE.cpp) -c -o $@ $<

.PHONY: generate_docs
generate_docs:
	$(DOXYGEN) $(DOXYGEN_CONFIG)

.PHONY: clean
clean:
	rm -rf *.o $(PROJECT)
	rm -rf ./doc/*
