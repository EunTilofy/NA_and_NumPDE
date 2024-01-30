CFLAGS = -I ./include --std=c++17
CPP_SRCS = ./include/serialization/json/jsoncpp.cpp ./include/serialization/xml/tinyxml2.cpp

clean:
	rm -rf solA

all:
	rm -rf solA
	g++ $(CPP_SRCS) Problem-A.cpp $(CFLAGS) -o solA

run:
	rm -rf res/A.txt
	./solA > res/A.txt