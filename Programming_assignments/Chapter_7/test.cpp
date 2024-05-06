#include <bits/stdc++.h>
using namespace std;
#include "BVP.hpp"
#include "linear.hpp"
#include "calculator.hpp"
#include "function.hpp"
#include "function_generator/ExecCode2.hpp"

void warning() {
    cerr << "usage: ./test [-v|--verbose] <input JSON file>\n";
    exit(1);
}

std::string getName(std::string s) {
    for(auto &ch : s) {
        if(ch == '/') ch = '|';
    }
    s.erase(s.size() - 5);
    return s;
}

int main(int argc, char ** argv) {
    Square_BVPsolver solver;
    if(argc <= 1) warning();
    bool print = 0;
    int i = 1;
    if(std::string(argv[i]) == "-v" || std::string(argv[i]) == "--verbose") ++i, print = 1;;
    if(argc <= i) warning();
    
    for(; i < argc; ++i) {
        ofstream OUT("result-["+std::string(argv[i])+"].out");
        std::cerr << "\033[0;32mSolve : " << argv[i] << " \033[0m" << std::endl;
        solver.solveProblem(argv[i], print);
        solver.saveResults("res/res-["+getName(argv[i])+"].csv");
        OUT.close();
    }
    
    return 0;
}