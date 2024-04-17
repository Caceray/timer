TARGET = app
CC = g++
CFLAGS = -std=c++11 -Wall
SRCDIR = src
INCDIR = include

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

