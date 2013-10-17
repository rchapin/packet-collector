CC		= g++ -DBOOST_LOG_DYN_LINK
DEBUG		= -g
CFLAGS		= -v -c -Wall $(DEBUG)
LFLAGS		= -v -Wall $(DEBUG)
LDFLAGS 	= -lpcap -lconfig++
BOOST_LDFLAGS	= -L /usr/local/boost/stage/lib/ -lboost_log -lpthread

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

TARGET	= $(BIN_DIR)/packet-collector
OBJS	= collector.o collector_main.o boost_logger.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(LDFLAGS) $(BOOST_LDFLAGS) $^ -o $@

$(BUILD_DIR)/collector.o: collector.cpp collector.hpp boost_logger.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/collector_main.o: collector_main.cpp collector.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/boost_logger.o: boost_logger.cpp
	$(CC) $(CFLAGS) $< -o $@

install:
	echo "Not yet implemented..." 

clean:
	\rm -rf ./bin/* ./build/*

