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
            return sin(x/2.0)-1;
        }
    };
    double ans;
    void Solve(double x0, double x1) {
        Secant_Method<double> SOLVER(func(), x0, x1);
        ans = SOLVER.solve();
    }
};

class Solve_F2 {
public:
    class func : public Function<double, double>{
    public:
        double operator() (const double& x) const {
            return exp(x)-tan(x);
        }
    };
    double ans;
    void Solve(double x0, double x1) {
        Secant_Method<double> SOLVER(func(), x0, x1);
        ans = SOLVER.solve();
    }
};

class Solve_F3 {
public:
    class func : public Function<double, double>{
    public:
        double operator() (const double& x) const {
            return pw3(x)-12*sq(x)+3*x+1;
        }
    };
    double ans;
    void Solve(double x0, double x1) {
        Secant_Method<double> SOLVER(func(), x0, x1);
        ans = SOLVER.solve();
    }
};

int main() {
    std::cerr << "Solving sin(x/2)-1 with x0=0, x1=\\pi/2" << std::endl;
    Solve_F1 sol1; sol1.Solve(0, Pi/2);
    std::cerr << "Solving sin(x/2)-1 with x0=14, x1=15" << std::endl;
    sol1.Solve(14, 15);

    std::cerr << "\nSolving exp(x)-tan(x) with x0=1, x1=1.4" << std::endl;
    Solve_F2 sol2; sol2.Solve(1, 1.4);
    std::cerr << "\nSolving exp(x)-tan(x) with x0=-2.8, x1=-3.1" << std::endl;
    sol2.Solve(-2.8, -3.1);

    std::cerr << "\nSolving x^3-12x^2+3x+1 with x0=0, x1=-0.5" << std::endl;
    Solve_F3 sol3; sol3.Solve(0, -0.5);
    std::cerr << "\nSolving x^3-12x^2+3x+1 with x0=8, x1=9" << std::endl;
    sol3.Solve(8, 9);
    return 0;
}