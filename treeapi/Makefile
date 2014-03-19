TARGET	:= treeapi.o
OBJS	:= $(wildcard *.c)

all :
	gcc -c -o $(TARGET) $(OBJS) `pkg-config --cflags glib-2.0`

clean :
	rm -rf *.o $(TARGET)
