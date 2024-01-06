#include "Interpolation.hpp"
#include "calculator.hpp"
#include <bits/stdc++.h>

using namespace polynomial_interpolation;
typedef double NUM;
const std::string title = "------------------------------ Problem E ---------------------------------";
const std::string latex = "latex", tikz = "tikz", python = "python";

class func : public Function<NUM> {
    NUM operator() (const NUM& x) const {
        return 1/(1+sq(5*x));
    }
};

// #define QUIET // whether print the Difference quotient table or not

int main(int argc, char** argv) {
    /*
    x.resize(7);
    vector <double> y1(7), y2(7);
    x[0] = 0, x[1] = 6, x[2] = 10, x[3] = 13, x[4] = 17, x[5] = 20, x[6] = 28;
    y1[0] = 6.67, y1[1] = 17.3, y1[2] = 42.7, y1[3] = 37.3, y1[4] = 30.1, y1[5] = 29.3, y1[6] = 28.7;
    y2[0] = 6.67, y2[1] = 16.1, y2[2] = 18.9, y2[3] = 15.0, y2[4] = 10.6, y2[5] = 9.44, y2[6] = 8.89;
    Newton_Interpolation<double> ip4_1(x, y1);
    Polynomial<double> p4_1 = ip4_1.GetPolynomial();
    Newton_Interpolation<double> ip4_2(x, y2);
    Polynomial<double> p4_2 = ip4_2.GetPolynomial();
    cout << p4_1 << endl;
    cout << p4_2 << endl;
    cout << p4_1(43) << ' ' << p4_2(43) << endl;
    */
    Poly_n<NUM> res1, res2;
    vector<NUM> x ({   0,    6,   10,   13,   17,   20,   28});
    vector<NUM> y1({6.67, 17.3, 42.7, 37.3, 30.1, 29.3, 28.7});
    vector<NUM> y2({6.67, 16.1, 18.9, 15.0, 10.6, 9.44, 8.89});
    
    std::cerr << title << std::endl;
    Newton_Interpolation sol1(x, y1), sol2(x, y2);
    res1 = sol1.solve();
    std::cerr << "result : " << res1 << std::endl;
    res2 = sol2.solve();
    std::cerr << "result : " << res2 << std::endl;
    std::cerr << "f1(28+15) = " << res1(43) << " f2(28+15) = " << res2(43) << std::endl;
    

    for(int arg = 0; arg < argc; ++arg) {
        if(argv[arg] == latex) {
            ofstream out;
            out.open("res_latex.out", std::ios::app);
            out << title << "\n";
            out << res1.to_latex() << "\n";
            out << res2.to_latex() << "\n";
            out.close();
        }
        if(argv[arg] == tikz) {
            ofstream out;
            out.open("res_tikz.out", std::ios::app);
            out << title << "\n";
            out << res1.to_tikz() << "\n";
            out << res2.to_tikz() << "\n";
            out.close();
        }
        if(argv[arg] == python) {
            ofstream out;
            out.open("res_python.out", std::ios::app);
            out << title << "\n";
            out << res1.to_python() << "\n";
            out << res2.to_python() << "\n";
            out.close();
        }
    }
    return 0;
}