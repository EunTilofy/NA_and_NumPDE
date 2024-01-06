#include "Interpolation.hpp"
#include "calculator.hpp"
#include <bits/stdc++.h>

using namespace polynomial_interpolation;
typedef double NUM;
const std::string title = "------------------------------ Problem D ---------------------------------";
const std::string latex = "latex", tikz = "tikz", python = "python";

// #define QUIET // whether print the Difference quotient table or not

int main(int argc, char** argv) {
    std::cerr << title << std::endl;
    Poly_n<NUM> res;

    vector<NUM> x({0,  0,   3,  3,   5,  5,   8,  8,  13, 13});
    vector<NUM> y({0, 75, 225, 77, 383, 80, 623, 74, 993, 72});

    Hermite_Interpolation solver(x, y);
    res = solver.solve();
    std::cerr << "result : " << res << std::endl;
    std::cerr << "f(10) = " << res(10) << " f'(10) = " << res.Diff(10) << std::endl;
    std::cerr << "diff function : " << res.get_diff_function() << std::endl;
    
    for(int arg = 0; arg < argc; ++arg) {
        if(argv[arg] == latex) {
            ofstream out;
            out.open("res_latex.out", std::ios::app);
            out << title << "\n";
            out << res.to_latex() << "\n";
            auto diff = res.get_diff_function();
            out << diff.to_latex() << "\n";
            out.close();
        }
        if(argv[arg] == tikz) {
            ofstream out;
            out.open("res_tikz.out", std::ios::app);
            out << title << "\n";
            out << res.to_tikz() << "\n";
            auto diff = res.get_diff_function();
            out << diff.to_tikz() << "\n";
            out.close();
        }
        if(argv[arg] == python) {
            ofstream out;
            out.open("res_python.out", std::ios::app);
            out << title << "\n";
            out << res.to_python() << "\n";
            auto diff = res.get_diff_function();
            out << diff.to_python() << "\n";
            out.close();
        }
    }
    return 0;
}