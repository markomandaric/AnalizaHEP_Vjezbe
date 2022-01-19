CC=g++
CFLAGS=-I. $(shell root-config --cflags)  -lTMVA
LDFLAGS = $(shell root-config --libs)  -lTMVA
DEPS = Anlayzer.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

analyze: analyze.o Anlayzer.o
	$(CC) $(LDFLAGS) -o analyze analyze.o Anlayzer.o

clean:
	rm -rf *.o analyze
