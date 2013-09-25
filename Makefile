CC		= g++
DEBUG		= -g
CFLAGS		= -v -c -Wall $(DEBUG)
LFLAGS 		= -v -Wall $(DEBUG)
LDFLAGS 	= -lpcap -lconfig++

BIN_DIR		= bin
BUILD_DIR	= build
DIST_DIR	= dist
INC_DIR		= include
SRC_DIR		= src
TEST_DIR	= test

vpath %.c $(SRC_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.h $(INC_DIR)
vpath %.hpp $(INC_DIR)
vpath %.o $(BUILD_DIR)

TARGET		= $(BIN_DIR)/packet-collector
OBJS		= Collector.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/Collector.o: Collector.cpp Collector.hpp
	$(CC) $(CFLAGS) $< -o $@
	
install:
	echo "Not yet implemented..." 

clean:
	\rm -rf ./bin/* ./build/*

