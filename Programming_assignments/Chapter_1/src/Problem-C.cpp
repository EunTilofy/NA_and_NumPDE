#include "EquationSolver.hpp"
#include "calculator.hpp"
#include <bits/stdc++.h>

class Solve_tan {
public:
    class func : public Function<double, double>{
    public:
        double operator() (const double& x) const {
            return x-tan(x);
        }
        double Diff(const double& x) const {
            return 1-1/(sq(cos(x)));
        }
    };
    double ans;
    void Solve(double x0) {
        Newton_Method<double> SOLVER(func(), x0);
        ans = SOLVER.solve();
    }
};

int main() {
    Solve_tan sol;
    std::cerr << "Solving x-tan(x)=0 with initial point x0 = 4.5" << std::endl;
    sol.Solve(4.5);
    std::cerr << "\nSolving x-tan(x)=0 with initial point x0 = 7.7" << std::endl;
    sol.Solve(7.7);
    return 0;
}