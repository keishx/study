TARGET = main
INC=../protocol
INC2=../link
INC3=../file
INC4=../public

CC = gcc

OBJS= main.o  server.o $(INC)/protocol.o $(INC2)/link.o $(INC3)/fileope.o

INCLUDES=-I$(INC) -I$(INC2) -I$(INC3) -I$(INC4)
CFLAGS= -pthread -g

all:$(TARGET)

%.o:%.c
#	$(CC) -c $(INCLUDES) $< -o $@
	$(CC) -c $(INCLUDES) $(CFLAGS) $< -o $@

$(TARGET):$(OBJS)
#	$(CC) -o $@ $^ $(LDFLAGS)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

clean:
	rm *.o $(TARGET)
