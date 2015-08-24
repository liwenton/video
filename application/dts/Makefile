OBJ	=dts.o
TARGET	=dts
CC	=gcc

LIBS	=-lavformat -lavcodec -lavutil
LKFLAGS	=-L /usr/local/lib/

$(TARGET):$(OBJ)
	$(CC)  $< $(LIBS) $(LKFLAGS) -o $@

%.o:%.c
	$(CC)  -c $< -o $@

clean:
	rm *.o $(TARGET)
