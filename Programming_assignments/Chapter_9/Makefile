CFLAGS = -I include --std=c++20 -Ofast
CPP_SRCS = ./include/serialization/json/jsoncpp.cpp
TESTFILES := $(shell find data -type f -name "*.json" | sort -d)
RESULTS := $(shell find res -type f -name "*.csv" | sort -d)

clean:
	rm -rf test dataGen adddata res/*

all: clean
	g++ $(CPP_SRCS) test.cpp $(CFLAGS) -o test

dataGen:
	g++ $(CPP_SRCS) dataGen.cpp $(CFLAGS) -o dataGen

addData:
	rm -rf data/*
	g++ $(CPP_SRCS) dataGen2.cpp $(CFLAGS) -o adddata

run:
	rm -rf res/*.csv
	./test $(foreach res,$(TESTFILES),"$(res)")

plot:
	rm -rf res/*.png
	python3 plot.py $(foreach res,$(RESULTS),"$(res)")
