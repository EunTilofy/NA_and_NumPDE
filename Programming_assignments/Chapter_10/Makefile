CFLAGS = -I include --std=c++20 -Ofast

clean:
	rm -rf test res data/ratetest.res *.pdf
	$(MAKE) -C doc clean

all: clean
	g++ test.cpp $(CFLAGS) -o test

run: all
	./test

plotrun: clean
	mkdir res
	g++ test.cpp $(CFLAGS) -DPLOT -o test
	./test

plot: plotrun
	python3 plot.py $(foreach res,$(shell find res -type f -name "*.csv" | sort -d),"$(res)")

story: plot
	$(MAKE) -C doc all
	rm -rf *.aux *.log *.out

testspeed: clean
	g++ test.cpp $(CFLAGS) -DTESTSPEED -o test
	./test
