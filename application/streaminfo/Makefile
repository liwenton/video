OBJ	=streaminfo.o
TARGET	=streaminfo
CC	=gcc

LIBS	=-lavformat -lavcodec
#LKFLAGS	=-L /usr/local/lib/

$(TARGET):$(OBJ)
	$(CC)  $< $(LIBS) $(LKFLAGS) -o $@

%.o:%.c
	$(CC)  -c $< -o $@

clean:
	rm *.o $(TARGET)
