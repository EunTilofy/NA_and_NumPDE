CFLAGS = -I include --std=c++20 -Ofast

clean:
	rm -rf test res data/alltest.res *.pdf
	$(MAKE) -C doc clean

all: 
	rm -rf test res data/alltest.res
	g++ test.cpp $(CFLAGS) -o test

run: all
	mkdir res
	./test

plot: run
	python3 plot.py $(foreach res,$(shell find res -type f -name "*.csv" | sort -d),"$(res)")

story: plot
	$(MAKE) -C doc all
	rm -rf *.aux *.log *.out

make testspeed:
	g++ test.cpp $(CFLAGS) -DTESTSPEED -o test
	./test
