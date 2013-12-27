GTEST_DIR = ../gtest-1.7.0
OBJECTS = bin/MagnetLink.o bin/InvalidTracker.o bin/UDPRequest.o bin/Networking.o bin/ConnectRequest.o bin/ConnectResponse.o bin/UDPResponse.o bin/InvalidUDPResponse.o bin/URL.o bin/InvalidURL.o bin/VariableTimeout.o bin/ConnectionID.o bin/Tracker.o
TESTS = src/Test/MagnetLinkTest.cpp src/Test/URLTest.cpp src/Test/TrackerTest.cpp

main : src/main.cpp $(OBJECTS)
	g++ -Iinclude src/main.cpp $(OBJECTS) -o Magneto

test : src/test.cpp $(OBJECTS) $(TESTS)
	g++ -std=c++0x -DMAGNETO_TEST -isystem $(GTEST_DIR)/include -Iinclude/ -pthread src/test.cpp $(OBJECTS) $(TESTS) lib/libgtest.a -o MagnetoTest -lboost_system

bin/MagnetLink.o : src/Link/MagnetLink.cpp
	g++ -std=c++0x -c -Iinclude/ src/Link/MagnetLink.cpp -o bin/MagnetLink.o

bin/Tracker.o : src/Tracker/Tracker.cpp
	g++ -std=c++0x -c -Iinclude/ src/Tracker/Tracker.cpp -o bin/Tracker.o

bin/InvalidTracker.o : src/Tracker/InvalidTracker.cpp
	g++ -c -Iinclude/ src/Tracker/InvalidTracker.cpp -o bin/InvalidTracker.o

bin/UDPResponse.o : src/Networking/UDPResponse.cpp
	g++ -std=c++0x -c -Iinclude src/Networking/UDPResponse.cpp -o bin/UDPResponse.o

bin/UDPRequest.o : src/Networking/UDPRequest.cpp
	g++ -std=c++0x -c -Iinclude/ src/Networking/UDPRequest.cpp -o bin/UDPRequest.o

bin/Networking.o : src/Networking/Networking.cpp
	g++ -std=c++0x -c -Iinclude/ src/Networking/Networking.cpp -o bin/Networking.o

bin/ConnectRequest.o : src/Networking/ConnectRequest.cpp
	g++ -std=c++0x -c -Iinclude/ src/Networking/ConnectRequest.cpp -o bin/ConnectRequest.o

bin/ConnectResponse.o : src/Networking/ConnectResponse.cpp
	g++ -std=c++0x -c -Iinclude/ src/Networking/ConnectResponse.cpp -o bin/ConnectResponse.o

bin/InvalidUDPResponse.o : src/Networking/InvalidUDPResponse.cpp
	g++ -c -Iinclude/ src/Networking/InvalidUDPResponse.cpp -o bin/InvalidUDPResponse.o

bin/URL.o : src/Networking/URL.cpp
	g++ -std=c++0x -c -Iinclude/ src/Networking/URL.cpp -o bin/URL.o

bin/InvalidURL.o : src/Networking/InvalidURL.cpp
	g++ -c -Iinclude/ src/Networking/InvalidURL.cpp -o bin/InvalidURL.o

bin/ConnectionID.o : src/Tracker/ConnectionID.cpp
	g++ -std=c++0x -c -Iinclude/ src/Tracker/ConnectionID.cpp -o bin/ConnectionID.o

bin/VariableTimeout.o : src/VariableTimeout/VariableTimeout.cpp
	g++ -std=c++0x -c -Iinclude/ src/VariableTimeout/VariableTimeout.cpp -o bin/VariableTimeout.o

clean :
	@rm -f MagnetoWithTest bin/*
