TARGET = arxiv
CC = gcc

SRC = $(wildcard *.c)

$(TARGET) : $(SRC)
	$(CC) -g $(SRC) -o $(TARGET)

clean :
	rm $(TARGET)