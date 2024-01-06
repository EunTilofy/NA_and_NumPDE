#include <bits/stdc++.h>
#include "serialization.hpp"
#include "linear.hpp"
#include "IO.hpp"
#include "function.hpp"
#include "calculator.hpp"

using namespace std;

class Solver {
    using db = double;
    int n;
public:
    Solver(int _n) : H(_n + 1, _n + 1), n(_n + 1){
        for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
            H[i][j] = 1.0 / (i + j + 1);
        }
    }
    Mat<double> H; 
    void calculator1(vector<db> &alpha, vector<db> &beta, vector<db> &gamma) {
        vector<db> b1(n), b2(n), b(n);
        for(int i = 0; i < n; ++i) {
            b1[i] = (i & 1) ? -1 : 1;
            for(int j = 1; j <= i; ++j) b2[i] += ((i + j) & 1 ? -1 : 1) / (db)(j);
            b[i] = b1[i]*0.69315+b2[i];
        }
        alpha = Gauss_elimination(H, Vec<db>(b)).toVector();
        beta = Gauss_elimination(H, Vec<db>(b1)).toVector();
        gamma = Gauss_elimination(H, Vec<db>(b2)).toVector();
    }
    void calculator2(vector<db> &alpha) {
        Mat<db> A = H;
        A = (~A) * A;
        for(int i = 0; i < n; ++i) A[i][i] = A[i][i] + (db)1e-10;
        Vec<db> b(n);
        for(int i = 0; i < n; ++i) {
            db b1 = (i & 1) ? -1 : 1, b2 = 0;
            for(int j = 1; j <= i; ++j) b2 += ((i + j) & 1 ? -1 : 1) / (db)(j);
            b[i] = b1*0.69315+b2;
        }
        b = ~H * b;
        alpha = Gauss_elimination(A, Vec<db>(b)).toVector();
    }
};

int main() {
    std::cerr << "--------------- results of 2nd + 4th subproblem ---------------\n";
    int N1 = 6;
    for(int i = 1; i <= N1; ++i) {
        Solver tmp(i);
        vector<double> a, b, c, d;
        tmp.calculator1(a, b, c);
        cerr << "alpha" + to_string(i) + " = " << a << "\n";
        cerr << "beta" + to_string(i) + " = " << b << "\n";
        cerr << "gamma" + to_string(i) + " = " << c << "\n";
        d.resize(i+1);
        for(int j = 0; j <= i; ++j) d[j] = log(2) * b[j] + c[j];
        cerr << "beta * ln2 + gamma = " << d << "\n";
        cerr << "H" + to_string(i) +" = " << tmp.H << "\n";
    }

    std::cerr << "--------------- results of 5th subproblem ---------------\n";
    int N2 = 6;
    for(int i = 1; i <= N2; ++i) {
        Solver tmp(i);
        vector<double> a;
        tmp.calculator2(a);
        cerr << "a" + to_string(i) + " = " << a << "\n";
    }
    return 0;
}