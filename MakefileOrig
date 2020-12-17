# Makefile

TARGET_EXEC ?= armadillo
BIN_DIR ?= ./bin
SRC_DIR ?= ./src

OBJS = bin/main.o bin/getData.o bin/motorControl.o bin/WheelsController.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
SRCS = $(SRC_DIR)/*.cpp

$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN_DIR)/armadillo

$(BIN_DIR)/main.o : src/main.cpp include/log.h include/getData.h include/motorControl.h include/WheelsController.h
	$(CC) $(CFLAGS) src/main.cpp -o bin/main.o

$(BIN_DIR)/getData.o : src/getData.cpp include/getData.h
	$(CC) $(CFLAGS) src/getData.cpp -o bin/getData.o

$(BIN_DIR)/motorControl.o : src/motorControl.cpp include/motorControl.h
	$(CC) $(CFLAGS) src/motorControl.cpp -o bin/motorControl.o

$(BIN_DIR)/WheelsController.o : src/WheelsController.cpp include/WheelsController.h
	$(CC) $(CFLAGS) src/WheelsController.cpp -o bin/WheelsController.o

clean: 
	rm $(BIN_DIR)/*.o $(BIN_DIR)/armadillo

tar:
	tar -zcvf BlueArmadillo.tar.gz Makefile *.cpp *.h
