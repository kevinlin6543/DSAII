CXX=g++
CFLAGS = -c
DEPS = heap.h hash.h graph.h

%.o: %.cpp $(DEPS)
	$(CXX) $(CFLAGS) -o $@ $< $(CFLAGS)

dijkstra.exe: testDijkstra.o heap.o hash.o graph.o
	$(CXX) -o dijkstra.exe testDijkstra.o heap.o hash.o graph.o

debug:
	$(CXX) $(CFLAGS) -g graph.exe heap.cpp hash.cpp graph.cpp

clean:
	rm *.exe *.o *.stackdump *~
