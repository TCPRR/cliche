LibCliche:
	i686-w64-mingw32-gcc -I/usr/i686-w64-mingw32/include/libxml2 *.c -c
	i686-w64-mingw32-ar rcs libcliche.a *.o