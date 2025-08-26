CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = grep

all: $(TARGET)

$(TARGET): ./src/main.c
	$(CC) $(CFLAGS) ./src/main.c -o $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

clean:
	rm -f $(TARGET)
