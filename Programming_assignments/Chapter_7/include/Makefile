CFLAGS = --std=c++20
CPP_SRCS = ./serialization/json/jsoncpp.cpp ./serialization/xml/tinyxml2.cpp

clean:
	rm -rf test dataGen

all:
	rm -rf test
	g++ $(CPP_SRCS) test.cpp $(CFLAGS) -o test

dataGen:
	rm -rf dataGen
	g++ $(CPP_SRCS) dataGen.cpp $(CFLAGS) -o dataGen