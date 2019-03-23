cc	 = gcc
CFLAGS	 = -Wall -Wextra -g
LDFLAGS  =
DEPS	 = ex3.c makefile
OBJFILES = ex3.o
TARGET	 = main

all: $(TARGET)

$(TARGET): $(OBJFILES) $(DEPS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

