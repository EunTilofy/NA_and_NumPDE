#ifndef _INTERPOLATION_H_
#define _INTERPOLATION_H_

typedef double NUM;

#include<bits/stdc++.h>
#include "function.hpp"

namespace polynomial_interpolation {

template<class Type=NUM>
class Polynomial_Interpolation {
private:
    bool init_d_table = 0;
protected:
    vector<Type> d_table;
    virtual void make_d_table() = 0;
    vector<Type> x, y; int n;
public:
    Polynomial_Interpolation() : n(-1) {}
    Polynomial_Interpolation (const vector<Type> &x, const vector<Type> &y) : x(x), y(y), n(x.size()-1) {}
    const Poly_n<Type> solve() {
        custom_assert(n>0, "Interpolation method not initialized yet.");
        if(!init_d_table) make_d_table();
#ifndef QUIET
        std::cerr << "d_table : " << d_table << "\n";
#endif
        Poly_n<Type> ret(0), pi(vector<Type>({1}));
        for(int i = 0; i <= n; ++i) {
            ret = ret + d_table[i]*pi;
            pi = pi * Poly_n<Type>(vector<Type>({-x[i], 1}));
        }
        return ret;
    }
    const vector<Type> get_d_table() {if(!init_d_table) make_d_table(); return d_table;}
};

template<class Type=NUM>
class Newton_Interpolation : public Polynomial_Interpolation<Type>{
private:
    using Polynomial_Interpolation<Type>::d_table;
    using Polynomial_Interpolation<Type>::x;
    using Polynomial_Interpolation<Type>::y;
    using Polynomial_Interpolation<Type>::n;
    
    void make_d_table() {
        d_table = y;
        for(int i = 1; i <= n; ++i) {
            for(int j = n; j>=i ; --j) {
                if(x[j-i]==x[j]) d_table[j] = d_table[j]/i;
                else d_table[j]=(d_table[j]-d_table[j-1])/(x[j]-x[j-i]);
            }
        }
    }
public:
    Newton_Interpolation(const vector<Type> &x, const vector<Type> &y) : Polynomial_Interpolation<Type>(x, y) {}

    void Init() { // Interface for interaction with user -- Not used
        std::cout << "Number of points : ";
        std::cin >> n;
        std::cout << "Enter the pairs {x, y}[f(x) = y]: \n";
        x.resize(n); y.resize(n);
        for(int i = 0; i < n; ++i) {
            std::cin >> x[i] >> y[i];
        } --n;
    }
};

template<class Type=NUM>
class Hermite_Interpolation : public Polynomial_Interpolation<Type> {
private:
    using Polynomial_Interpolation<Type>::d_table;
    using Polynomial_Interpolation<Type>::x;
    using Polynomial_Interpolation<Type>::y;
    using Polynomial_Interpolation<Type>::n;

    void make_d_table() {
        vector<int16_t> start(n+1);
        d_table.resize(n+1); d_table[0] = y[0]; start[0] = 0;
        for(int i = 1; i <= n; ++i) {
            if(x[i] == x[i-1]) d_table[i] = d_table[i-1], start[i]=start[i-1];
            else d_table[i] = y[i], start[i] = i;
        }
        Type fac = 1.;
        for(int i = 1; i <= n; ++i, fac *= i) {
            for(int j = n; j>=i ; --j) {
                if(x[j-i]==x[j]) d_table[j] = y[start[j]+i]/fac;
                else d_table[j]=(d_table[j]-d_table[j-1])/(x[j]-x[j-i]);
            }
        }
    }
public:
    Hermite_Interpolation(const vector<Type> &x, const vector<Type> &y) : Polynomial_Interpolation<Type>(x, y) {}
    Hermite_Interpolation(const vector<pair<Type, vector<Type>>>& val) {
        for(auto &[vx, Y] : val) {
            for(auto &vy : Y) {
                x.push_back(vx), y.push_back(vy);
            }
        }
        n = x.size() - 1;
    }
    void Init() {  // Interface for interaction with user -- Not used
        std::cout << "Number of points : ";
        int nn; std::cin >> nn;
        std::cout << "Enter the restrictions {x, n, y_0, ..., y_{n-1}}[f^(i)(x) = y_i]: \n";
        for(int i = 1; i <= nn; ++i) {
            Type _x, _y; int _n; std::cin >> _x >> _n;
            for(int j = 0; j < _n; ++j) {
                x.push_back(_x); cin >> _y;
                y.push_back(_y);
            }
        }
        n = x.size() - 1;
    }
};

// Some special interfaces that use polynomial interpolation.
template<class T=NUM>
const Poly_n<T> Grid_Interpolation (const T& l, const T& r, const int16_t& n, const Function<T>& f) {
    vector<T> x(n+1), y(n+1);
    for(int i = 0; i <= n; ++i) x[i]=l+i*(r-l)/n, y[i]=f(x[i]);
    Newton_Interpolation<T> solver(x, y);
    return solver.solve();
}
template<class T=NUM>
const Poly_n<T> Chebyshev_Interpolation (const T& l, const T& r, const int16_t& n, const Function<T>& f) {
    static const T Pi = acos(-1.); // 3.14159265358979323846 maybe more precise
    vector <T> x(n+1), y(n+1);
    for (int i = 0; i <= n; ++ i) x[i] = (l+r)/2+(r-l)/2*cos(Pi*(2*i+1)/(2*n+2)), y[i] = f(x[i]);
    Newton_Interpolation<T> solver(x, y);
    return solver.solve();
}

}

#endif