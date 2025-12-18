LibCliche:
	rm *.o
	i686-w64-mingw32-gcc *.c -c -lxml2
	i686-w64-mingw32-ar rcs libcliche.a *.o