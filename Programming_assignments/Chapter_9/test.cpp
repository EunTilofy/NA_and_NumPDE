#include <bits/stdc++.h>
#include "Multigrid_BVP.hpp"
#include "linear.hpp"
#include "calculator.hpp"
#include "function.hpp"
#include "function_generator/ExecCode2.hpp"

void warning()
{
    cerr << "usage: ./test [-v|--verbose] <input JSON file>\n";
    exit(1);
}

string getName(string s)
{
    for(auto &ch : s)
    {
        if(ch == '/') ch = '|';
    }
    s.erase(s.size() - 5); // remove ".json"
    return s;
}

int main(int argc, char ** argv) {
    Multigrid_BVPsolver solver;
    if(argc <= 1) warning();
    bool print = 0;
    int i = 1;
    if(string(argv[i]) == "-v" || string(argv[i]) == "--verbose") ++i, print = 1;
    if(argc <= i) warning();

    for(; i < argc; ++i)
    {
        ofstream OUT("result-["+std::string(argv[i])+"].out");
        std::cerr << "\033[0;32mSolve : " << argv[i] << " \033[0m" << std::endl;
        clock_t _start, _end;
        _start = clock();
        solver.solveProblem(argv[i], print);
        _end = clock();
        double dur = (double) (_end - _start) / CLOCKS_PER_SEC;
        std::cerr << "time cost (sec): " << dur << std::endl;
        solver.saveResults("res/res-["+getName(argv[i])+"].csv");
        OUT.close();
    }

    return 0;
}