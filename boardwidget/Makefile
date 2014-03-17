TARGET	= boardwidget.o
OBJS	= $(wildcard *.c)
CFLAGS	= -I./
LIBS	= -lncurses

all : 
		gcc -c -o $(TARGET) $(OBJS) $(CFLAGS) $(LIBS) `pkg-config --cflags --libs glib-2.0`

clean :"
		rm -rf *.o $(TARGET)
