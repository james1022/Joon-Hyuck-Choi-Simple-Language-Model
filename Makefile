



CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -pedantic
#CFLAGS = -std=c++11 -g -Wextra -Wall -pedantic

bin: hw5

test: testLang.cc lang.o
	./testLang

testLang: lang.o testLang.cc
	$(CC) $(CFLAGS) -o testLang -O testLang.cc lang.o

lang.o: lang.cc lang.h
	$(CC) $(CFLAGS) -c lang.cc

hw.o: hw5.cc lang.o
	$(CC) $(CFLAGS) -c hw5.cc

hw5: lang.o hw5.cc
	$(CC) $(CFLAGS) -o hw5 -O hw5.cc lang.o

clean:
	rm -f *.o hw5 testLang
