#include "EquationSolver.hpp"
#include "calculator.hpp"
#include <bits/stdc++.h>

const double Pi = acos(-1.);
const double EPS = 1e-2;

class Solver {
public:
    class func : public Function<double, double>{
    public:
        double V, L, r;
        func(const double& V, const double& L, const double& r):V(V), L(L), r(r) {}
        double operator() (const double& x) const {
            double r2 = sq(r);
            return V - L*(0.5*Pi*r2-r2*asin(x/r)-x*sqrt(r2-sq(x)));
        }
        double Diff(const double& x) const {
            return L*(r/sqrt(1-sq(x/r))+sq(x)/sqrt(sq(r)-sq(x))+sqrt(sq(r)-sq(x)));
        }
        double Diff2(const double& x) const {
            return ((*this)(x+1e-8)-2*(*this)(x)+(*this)(x-1e-8))*1e16;
        }
    };
    double ans;
    void Solve_Bisection(double a, double b, func& F) {
        Bisection_Method<double> SOLVER(F, a, b, 1e-7, EPS*2);
        ans = SOLVER.solve();
    }
    void Solve_Newton(double x0, func& F) {
        // std::cerr << F.Diff(0.1661449795) << std::endl; (OUTPUT: 20.2819)
        Newton_Method<double> SOLVER(F, x0, EPS*20);
        ans = SOLVER.solve();
    }
    void Solve_Secant(double x0, double x1, func& F) {
        // std::cerr << F.Diff2(0.1661449795)/F.Diff(0.1661449795)/2 << std::endl; (OUTPUT: 0.5473962042)
        double EPSN = 0.5*(pow(EPS/0.5473962042,0.618)-EPS);
        Secant_Method<double> SOLVER(F, x0, x1, 1e-7, EPSN);
        ans = SOLVER.solve();
    }
    void Main(double V, double L, double r) {
        func F(V, L, r);
        std::cerr << "Solving Problem E with : V = " << V << ", L = " << L << ", r = " << r << std::endl;
        Solve_Bisection(0, r, F);
        Solve_Newton(0, F);
        Solve_Secant(0, r, F);
    }
};

int main() {
    Solver solver; solver.Main(12.4, 10, 1);
    return 0;
}