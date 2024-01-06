#include "EquationSolver.hpp"
#include "calculator.hpp"
#include <bits/stdc++.h>

const double Pi = acos(-1.);
const double EPS = 100*std::numeric_limits<NUM>::epsilon();

class Solve_F1 {
public:
    class func : public Function<double, double>{
    public:
        double operator() (const double& x) const {
            return 1.0/x-tan(x);
        }
    };
    double ans;
    void Solve() {
        Bisection_Method<double> SOLVER(func(), EPS, Pi/2-EPS);
        ans = SOLVER.solve();
    }
};

class Solve_F2 {
public:
    class func : public Function<double, double>{
    public:
        double operator() (const double& x) const {
            return 1.0/x-pow(2, x);
        }
    };
    double ans;
    void Solve() {
        Bisection_Method<double> SOLVER(func(), EPS, 1.0);
        ans = SOLVER.solve();
    }
};

class Solve_F3 {
public:
    class func : public Function<double, double>{
    public:
        double operator() (const double& x) const {
            return pow(2, -x)+exp(x)+2*cos(x)-6.0;
        }
    };
    double ans;
    void Solve() {
        Bisection_Method<double> SOLVER(func(), 1, 3);
        ans = SOLVER.solve();
    }
};

class Solve_F4 {
public:
    class func : public Function<double, double>{
    public:
        double operator() (const double& x) const {
            return (pw3(x)+4*sq(x)+3*x+5)/(2*pw3(x)-9*sq(x)+18*x-2);
        }
    };
    double ans;
    void Solve() {
        Bisection_Method<double> SOLVER(func(), 0, 4);
        ans = SOLVER.solve();
    }
};

int main() {
    std::cerr << "Solving x^{-1} - \\tan x on [0, \\pi/2]" << std::endl;
    Solve_F1 sol1; sol1.Solve();
    std::cerr << "\nSolving x^{-1} - 2^x on [0, 1]" << std::endl;
    Solve_F2 sol2; sol2.Solve();
    std::cerr << "\nSolving 2^{-x} + exp(x) + 2*cos(x) - 6 on [1, 3]" << std::endl;
    Solve_F3 sol3; sol3.Solve();
    std::cerr << "\nSolving (x^3+4*x^2+3*x+5)/(2*x^3-9x^2+18*x-2) on [0, 4]" << std::endl;
    Solve_F4 sol4; sol4.Solve();

    return 0;
}