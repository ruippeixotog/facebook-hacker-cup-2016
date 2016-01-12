QUAL_CC_FILES = $(wildcard qualification/*.cpp)
QUAL_BIN_FILES = $(patsubst qualification/%.cpp, %, $(QUAL_CC_FILES))

BIN_FILES = $(QUAL_BIN_FILES)
CC_FLAGS = -std=c++0x -Wall -O2 -lm
CC = g++

all: $(BIN_FILES)

$(QUAL_BIN_FILES):%: qualification/%.cpp
	$(CC) $(CC_FLAGS) -o $@ $<

clean:
	rm -f $(BIN_FILES)