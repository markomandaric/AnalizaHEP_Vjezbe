CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Statistics.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

analyze: analyze.o Statistics.o
	$(CC) $(LDFLAGS) -o analyze analyze.o Statistics.o

clean:
	rm -rf *.o analyze
