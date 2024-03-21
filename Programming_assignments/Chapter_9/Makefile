CFLAGS = -I include --std=c++20
CPP_SRCS = ./include/serialization/json/jsoncpp.cpp

clean:
	rm -rf test dataGen

all:
	rm -rf test
	g++ $(CPP_SRCS) test.cpp $(CFLAGS) -o test

dataGen:
	rm -rf dataGen
	g++ $(CPP_SRCS) dataGen.cpp $(CFLAGS) -o dataGen