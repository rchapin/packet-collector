CC := g++
DEBUG := -g
CFLAGS := -v -c -Wall $(DEBUG)
LFLAGS := -v -Wall $(DEBUG)
LDFLAGS := -lpcap

BIN_DIR		:= bin
BUILD_DIR	:= build
DIST_DIR	:= dist
INC_DIR		:= include
SRC_DIR		:= src
TEST_DIR	:= test

TARGET		:= $(BIN_DIR)/packetCollector
OBJS		:= $(BUILD_DIR)/packetCollector.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/packetCollector.o: $(SRC_DIR)/packetCollector.cpp $(INC_DIR)/packet_structs.h
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/packetCollector.o $(SRC_DIR)/packetCollector.cpp
	  
install:
	echo "Not yet implemented..." 

clean:
	\rm -rf ./bin/* ./build/*

