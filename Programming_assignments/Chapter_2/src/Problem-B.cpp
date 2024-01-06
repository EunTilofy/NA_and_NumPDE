#include "Interpolation.hpp"
#include "calculator.hpp"
#include <bits/stdc++.h>

using namespace polynomial_interpolation;
typedef double NUM;
const std::string title = "------------------------------ Problem B ---------------------------------";
const std::string latex = "latex", tikz = "tikz", python = "python";

class func : public Function<NUM> {
    NUM operator() (const NUM& x) const {
        return 1/(1+sq(x));
    }
};

// #define QUIET // whether print the Difference quotient table or not

int main(int argc, char** argv) {
    vector<Poly_n<NUM>> res;
    func f;
    std::cerr << title << std::endl;
    for(int n = 2; n <= 8; n += 2) {
        std::cerr << "case: n = " << n << std::endl;
        res.push_back(Grid_Interpolation<NUM>(-5, 5, n, f));
        std::cerr << "result  : " << res.back() << std::endl;
    }
    for(int arg = 0; arg < argc; ++arg) {
        if(argv[arg] == latex) {
            ofstream out;
            out.open("res_latex.out", std::ios::app);
            out << title << "\n";
            for(auto x : res) out << x.to_latex() << "\n";
            out.close();
        }
        if(argv[arg] == tikz) {
            ofstream out;
            out.open("res_tikz.out", std::ios::app);
            out << title << "\n";
            for(auto x : res) out << x.to_tikz() << "\n";
            out.close();
        }
        if(argv[arg] == python) {
            ofstream out;
            out.open("res_python.out", std::ios::app);
            out << title << "\n";
            for(auto x : res) out << x.to_python() << "\n";
            out.close();
        }
    }
    return 0;
}