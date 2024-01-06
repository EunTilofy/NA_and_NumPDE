all:
	g++ Problem-B.cpp -o solB --std=c++20
	g++ Problem-C.cpp -o solC --std=c++20
	g++ Problem-D.cpp -o solD --std=c++20
	g++ Problem-E.cpp -o solE --std=c++20
	g++ Problem-F.cpp -o solF --std=c++20

clean:
	rm -f solB solC solD solE solF *.txt

run:
	./solB
	./solC
	./solD
	./solE
	./solF

result: solB solC solD solE solF
	echo "Result of ProblemB : \n" >> result.txt
	./solB 2>>result.txt
	echo "\n\nResult of ProblemC : \n" >> result.txt
	./solC 2>>result.txt
	echo "\n\nResult of ProblemD : \n" >> result.txt
	./solD 2>>result.txt
	echo "\n\nResult of ProblemE : \n" >> result.txt
	./solE 2>>result.txt
	echo "\n\nResult of ProblemF : \n" >> result.txt
	./solF 2>>result.txt

.PHONY: all clean run result
