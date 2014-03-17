all : stockapi/stockapi.o boardwidget/boardwidget.o yahoo_scans.o
	gcc -o yahoo_scans $^ -lform -lncurses -lcurl `pkg-config --cflags --libs glib-2.0`

stockapi/stockapi.o :
	cd stockapi && make

boardwidget/boardwidget.o :
	cd boardwidget && make

yahoo_scans.o : yahoo_scans.c
	gcc -c -o $@ $^

clean :
	rm -rf *.o yahoo_scans
	cd stockapi && make clean
	cd boardwidget && make clean

