CC = g++
CXXFLAGS= -Wall -pedantic -g -ggdb

main: folder obj/main.o obj/PageRank.o obj/SparseMatrix.o
	$(CC) $(CXXFLAGS) -o bin/main obj/main.o obj/PageRank.o obj/SparseMatrix.o

folder: 
	mkdir -p ./bin
	mkdir -p ./obj
	
obj/main.o : src/main.cpp
	$(CC) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/PageRank.o : src/PageRank.cpp
	$(CC) $(CXXFLAGS) -c src/PageRank.cpp -o obj/PageRank.o

obj/SparseMatrix.o : src/SparseMatrix.cpp
	$(CC) $(CXXFLAGS) -c src/SparseMatrix.cpp -o obj/SparseMatrix.o

clean:
	rm -rf bin/ obj/	
