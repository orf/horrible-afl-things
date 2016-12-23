build:
	$(CC) xpath1.c -I/root/program/libxml2-2.9.4/include/ -c -O3
	$(CC) xpath1.o /root/program/libxml2-2.9.4/.libs/*.o -ldl -lz -L/root/program/libxml2-2.9.4/.libs/ -lm -o xpath1 -O3 -v
afl:
	~/afl-2.35b/afl-fuzz -i testcases -o fuzz /root/program/xpath1 @@
