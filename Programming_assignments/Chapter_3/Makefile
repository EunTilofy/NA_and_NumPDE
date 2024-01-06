CFLAGS = -I ./include --std=c++17
CPP_SRCS = ./include/serialization/json/jsoncpp.cpp ./include/serialization/xml/tinyxml2.cpp

clean:
	rm -rf solA solC genE solE als tmp solB als.txt

all:
	rm -rf solA solC genE solE als tmp
	g++ $(CPP_SRCS) Problem-A.cpp $(CFLAGS) -o solA
	g++ $(CPP_SRCS) BForm.cpp $(CFLAGS) -o solB
	g++ $(CPP_SRCS) Problem-C.cpp $(CFLAGS) -o solC
	g++ $(CPP_SRCS) Problem-E-genData.cpp $(CFLAGS) -o genE
	g++ $(CPP_SRCS) Problem-E.cpp $(CFLAGS) -o solE
	g++ Convergence-analysis.cpp $(CFLAGS) -o als

run:
	rm -rf res/A.txt res/BForm.txt res/C.txt res/E.txt tmp
	mkdir tmp
	./solA > res/A.txt
	./solB > res/BForm.txt
	./solC > res/C.txt
	./genE > res/E.txt
	./solE >> res/E.txt
	rm -rf tmp

analysis:
	rm -rf als.txt
	./als > als.txt