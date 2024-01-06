/************************************************************************
 * Ver 1.0 updated on Sep. 29th, 2023, by EunTilofy
 * 3 basic method to solve nonlinear equation.
 * (a) Bisection Method
 * (b) Newton Method
 * (c) Secant Method
 * all the three mothod is derive from EquationSolver, which is an
 * abstract class. 
************************************************************************/
#ifndef _EQUATION_SOLVER
#define _EQUATION_SOLVER

#include "function.hpp"
#include "linear.hpp"
#include "calculator.hpp"
#include "IO.hpp"
#include<bits/stdc++.h>

typedef double NUM;
using namespace norm;

template <class Type=NUM>
class EquationSolver{
    virtual Type solve() = 0;
};

template <class Type>
class Bisection_Method : public EquationSolver<Type> {
private:
    const Function<Type> &F;
    Type a, b;
    NUM eps, delta;
    int Maxiter;
public:
    Bisection_Method(const Function<Type> &F, const Type &a, const Type &b, 
                    const NUM& eps = 1e-7, const NUM& delta = 1e-8, const int& Maxiter = 50) :
        F(F), a(a), b(b), Maxiter(Maxiter), eps(eps), delta(delta) {}
    virtual Type solve() {
        if((F(a) > 0) && F(b) > 0 || (F(a) < 0) && F(b) < 0) {
            std::cerr << "No root exists in the given internal." << std::endl;
            return Norm(F(a)) < Norm(F(b)) ? a : b;
        }
        Type u = a, v = b, mid, fmid, fu = F(a);
        int iter = 0;
        for(; iter < Maxiter; ++iter) {
            mid = (u + v) / 2;
            fmid = F(mid);
            if(Norm(fmid) < eps || Norm(u - v) < delta) break;
            if(fu < 0 && fmid < 0 || fu > 0 && fmid > 0) {
                u = mid; fu = fmid;
            } else {
                v = mid;
            }
        }
        if(iter > Maxiter) std::cerr << "Exceeded maximum iterations." << std::endl;
        else {
        std::cerr << "--------------------Using Bisection Method------------------------" << std::endl;
        std::cerr << "Iteration times = " << iter << std::endl;
        std::cerr << "Approximate root = " << fixed << setprecision(SETPRECISION) << mid << std::endl;
        std::cerr << "Function value = " << fixed << setprecision(SETPRECISION) << fmid << std::endl;
        std::cerr << "Norm(b-a) = " << fixed << setprecision(SETPRECISION) << Norm(v-u) << std::endl;
        std::cerr << "------------------------------------------------------------------" << std::endl;
        }
        return mid;
    }
};

template <class Type>
class Newton_Method : public EquationSolver<Type> {
private:
    const Function<Type> &F;
    Type x0;
    NUM eps;
    int Maxiter;
public:
    Newton_Method(const Function<Type> &F, const Type &x0, 
                    const NUM& eps = 1e-7, const int& Maxiter = 50) :
        F(F), x0(x0), Maxiter(Maxiter), eps(eps){}
    virtual Type solve() {
        Type x = x0, val = F(x0), df;
        int iter = 0; bool flag = 1;
        for(; iter < Maxiter; ++iter) {
            if(Norm(val) < eps) break;
            df = F.Diff(x);
            if(df == 0) {flag = 0; break;}
            x = x - val / df;
            val = F(x);
        }
        if(!flag) std::cerr << "Newton Method cannot solve this problem." << std::endl;
        else if(iter > Maxiter) std::cerr << "Exceeded maximum iterations." << std::endl;
        else {
        std::cerr << "--------------------Using Newton Method---------------------------" << std::endl;
        std::cerr << "Iteration times = " << iter << std::endl;
        std::cerr << "Approximate root = " << fixed << setprecision(SETPRECISION) << x << std::endl;
        std::cerr << "Function value = " << fixed << setprecision(SETPRECISION) << val << std::endl;
        std::cerr << "Norm of Derivative = " << fixed << setprecision(SETPRECISION) << Norm(df) << std::endl;
        std::cerr << "------------------------------------------------------------------" << std::endl;
        }
        return x;
    }
};

template <class Type>
class Secant_Method : public EquationSolver<Type> {
private:
    const Function<Type> &F;
    Type x0, x1;
    int Maxiter;
    NUM eps, delta;
public:
    Secant_Method(const Function<Type> &F, const Type& x0, const Type& x1,
                    const NUM& eps = 1e-7, const NUM& delta = 1e-8, const int& Maxiter = 50) :
        F(F), x0(x0), x1(x1), Maxiter(Maxiter), eps(eps), delta(delta){}
    virtual Type solve() {
        Type fu = F(x0), fv = F(x1), u = x0, v = x1, _v;
        int iter = 0; bool flag = 1;
        if(Norm(fu) < Norm(fv) && Norm(fu) < eps) swap(u, v); // x0 is ok
        else for(; iter < Maxiter; ++iter) {
            if(Norm(fv) < eps || Norm(u - v) < delta) break; // xk is ok
            if(fu - fv == 0) {flag = 0; break;}
            _v = v; v = (fv * u - fu * v) / (fv - fu); u = _v;
            fu = fv; fv = F(v);
        }
        if(!flag) std::cerr << "Secant Method cannot solve this problem." << std::endl;
        else if(iter > Maxiter) std::cerr << "Exceeded maximum iterations." << std::endl;
        else {
        std::cerr << "--------------------Using Secant Method---------------------------" << std::endl;
        std::cerr << "Using Secant Method:" << std::endl;
        std::cerr << "Iteration times = " << iter << std::endl;
        std::cerr << "Approximate root = " << fixed << setprecision(SETPRECISION) << v << std::endl;
        std::cerr << "Function value = " << fixed << setprecision(SETPRECISION) << fv << std::endl;
        std::cerr << "Norm(x(k)-x(k-1)) = " << fixed << setprecision(SETPRECISION) << Norm(v-u) << std::endl;
        std::cerr << "------------------------------------------------------------------" << std::endl;
        }
        return v;
    } 
};

#endif