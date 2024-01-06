#include "EquationSolver.hpp"
#include "calculator.hpp"
#include <bits/stdc++.h>

const double Pi = acos(-1.);

class Solver {
public:
    class func : public Function<double, double>{
    public:
        double A, B, C, E;
        func(const double& l, const double& h, const double& D, const double& beta) : 
            A(l*sin(beta/180*Pi)), B(l*cos(beta/180*Pi)), C((h+0.5*D)*sin(beta/180*Pi)-0.5*D*tan(beta/180*Pi)),
            E((h+0.5*D)*cos(beta/180*Pi)-0.5*D) {}
        double operator() (const double& x) const {
            double si=sin(x/180*Pi), co=cos(x/180*Pi);
            return A*si*co+B*sq(si)-C*co-E*si;
        }
        double Diff(const double& x) const {
            double si=sin(x/180*Pi), co=cos(x/180*Pi);
            return Pi/180*(A*(sq(co)-sq(si))+B*(2*si*co)+C*si-E*co);
        }
    };
    double ans;
    void Solve_Newton(double x0, double l, double h, double D, double beta) {
        Newton_Method<double> SOLVER(func(l, h, D, beta), x0);
        ans = SOLVER.solve();
    }
    void Solve_Secant(double x0, double x1, double l, double h, double D, double beta) {
        Secant_Method<double> SOLVER(func(l, h, D, beta), x0, x1);
        ans = SOLVER.solve();
    }
};

int main() {
    Solver solver;
    std::cerr << "Solving Problem F(a) : x0=33, l = 89, h = 49, D = 55, beta1 = 11.5" << std::endl;
    solver.Solve_Newton(33, 89, 49, 55, 11.5);
    std::cerr << "Solving Problem F(b) : x0=33, l = 89, h = 49, D = 30, beta1 = 11.5" << std::endl;
    solver.Solve_Newton(33, 89, 49, 30, 11.5);
    for(int i = 0; i <= 150; i += 10) {
        std::cerr << "Solving Problem F(c) : x0=" << i << ", x1=" << i + 10 << ", l = 89, h = 49, D = 55, beta1 = 11.5" << std::endl;
        solver.Solve_Secant(i, i+10, 89, 49, 55, 11.5);
    }
    return 0;
}