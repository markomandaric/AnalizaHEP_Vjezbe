CXX=g++
CXXFLAGS=-I.
DEPS = ElementaryParticle.h

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

analyzer: analyzer.o ElementaryParticle.o 
	$(CXX) -o analyzer analyzer.o ElementaryParticle.o  