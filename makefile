OBJS	= main.o ID3V2.o Frame.o
SOURCE	= main.cpp ID3V2.cpp Frame.cpp
HEADER	= ID3V2.h Frame.h
OUT	= exec
CC	 = g++-8
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

ID3V2.o: ID3V2.cpp
	$(CC) $(FLAGS) ID3V2.cpp -std=c++11

Frame.o: Frame.cpp
	$(CC) $(FLAGS) Frame.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)