CC=g++
CFLAGS=-std=c++11 -Wall -Iinclude -c
LDFLAGS=
EXECUTABLE=pmt

#executáveis
kmp: main.o matcher.o util.o kmp.o
	$(CC) main.o matcher.o util.o KMP_matcher.o -o kmp

#objetos dos algoritmos
kmp.o:
	$(CC) $(CFLAGS) src/kmp_matcher.cpp

#objetos padrao
main.o: util.o matcher.o
	$(CC) $(CFLAGS) src/main.cpp

matcher.o: util.o
	$(CC) $(CFLAGS) src/matcher.cpp

util.o:
	$(CC) $(CFLAGS) src/util.cpp

clean:
	rm pmt *.o
