GTEST_DIR = ../gtest-1.7.0
OBJECTS = bin/MagnetTorrent.o
TESTS = src/Test/*

Magneto : src/main.cpp $(OBJECTS)
	g++ -Iinclude src/main.cpp $(OBJECTS) -o Magneto

test : src/test.cpp $(OBJECTS) $(TESTS)
	g++ -isystem $(GTEST_DIR)/include -Iinclude/ -pthread src/test.cpp $(OBJECTS) $(TESTS) lib/libgtest.a -o MagnetoTest

bin/MagnetTorrent.o : src/Torrent/MagnetTorrent.cpp
	g++ -std=c++0x -c -Iinclude/ src/Torrent/MagnetTorrent.cpp -o bin/MagnetTorrent.o

clean :
	@rm -f MagnetoWithTest bin/*
