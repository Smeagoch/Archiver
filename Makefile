TARGET = arxiv
CC = gcc

SRC = $(wildcard *.c)

$(TARGET) : $(SRC)
	$(CC) $(SRC) -o $(TARGET)

clean :
	rm $(TARGET)