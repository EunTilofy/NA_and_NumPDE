all:
	g++ Problem-B.cpp -o solB --std=c++17
	g++ Problem-C.cpp -o solC --std=c++17
	g++ Problem-D.cpp -o solD --std=c++17
	g++ Problem-E.cpp -o solE --std=c++17

clean:
	rm -rf solB solC solD solE *.txt *.out

run:
	./solB
	./solC
	./solD
	./solE

latex:
	rm -rf res_latex.out
	./solB latex 2> /dev/null
	./solC latex 2> /dev/null
	./solD latex 2> /dev/null
	./solE latex 2> /dev/null

tikz:
	rm -rf res_tikz.out
	./solB tikz 2> /dev/null
	./solC tikz 2> /dev/null
	./solD tikz 2> /dev/null
	./solE tikz 2> /dev/null

python:
	rm -rf res_python.out
	./solB python 2> /dev/null
	./solC python 2> /dev/null
	./solD python 2> /dev/null
	./solE python 2> /dev/null


result: solB solC solD solE
	rm -rf result.txt
	./solB 2>>result.txt
	./solC 2>>result.txt
	./solD 2>>result.txt
	./solE 2>>result.txt

.PHONY: all clean run result
