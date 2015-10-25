CC=clang++
CFLAGS=-std=c++11 -Wall -Iinclude -c -g
LDFLAGS=
EXECUTABLE=pmt


pmt: main.o matcher.o util.o kmp_matcher.o aho_corasick_matcher.o
	$(CC) main.o matcher.o util.o kmp_matcher.o aho_corasick_matcher.o -o pmt
#executáveis

kmp: main.o matcher.o util.o kmp_matcher.o
	$(CC) main.o matcher.o util.o kmp_matcher.o -o kmp

#objetos dos algoritmos
kmp_matcher.o:
	$(CC) $(CFLAGS) src/kmp_matcher.cpp

aho_corasick_matcher.o:
	$(CC) $(CFLAGS) src/aho_corasick_matcher.cpp

#objetos padrao
main.o: util.o matcher.o
	$(CC) $(CFLAGS) src/main.cpp

matcher.o: util.o
	$(CC) $(CFLAGS) src/matcher.cpp

util.o:
	$(CC) $(CFLAGS) src/util.cpp

clean:
	rm pmt *.o
