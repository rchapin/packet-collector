# Use the c++ compiler
CC := g++

BIN_DIR		:= bin
BUILD_DIR	:= build
DIST_DIR	:= dist
INCLUDE_DIR	:= include
SRC_DIR		:= src
TEST_DIR	:= test

# SRC_EXT		:= cpp c


# Compile with all warnings and debug info for use with gdb
CFLAGS :=-v -c -Wall -g

# Add libpap to the linker
LDFLAGS=-lpcap

all: ./build/packetCollector.o
	$(CC) -v $(LDFLAGS) -o ./bin/packetCollector ./build/packetCollector.o

./build/packetCollector.o: ./src/packetCollector.cpp
	$(CC) $(CFLAGS) -o ./build/packetCollector.o ./src/packetCollector.cpp

clean:
	rm -rf ./bin/* ./build/*

