# Makefile

CC = gcc
CFLAGS = -Wall -g

SRC = my_cJSON.c
TEST = test.c
TARGET = test_my_cjson

all: $(TARGET)

$(TARGET): $(SRC) $(TEST)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TARGET)
	
run:
	$(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

