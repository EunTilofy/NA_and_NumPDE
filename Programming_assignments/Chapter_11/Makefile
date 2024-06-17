CFLAGS = -I include --std=c++20 -Ofast

clean:
	rm -rf test res *.pdf
	$(MAKE) -C doc clean

all: clean
	g++ test.cpp $(CFLAGS) -o test

run: all
	mkdir res
	./test

plot:
	python3 plot.py $(foreach res,$(shell find res -type f -name "*.csv" | sort -d),"$(res)")

story: # run -> plot -> story
	$(MAKE) -C doc all
	rm -rf *.aux *.log *.out
