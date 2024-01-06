/**********************************************************************
 * Ver 1.2 updated on Sep. 29th, 2023, by EunTilofy
 * some calculators tools to make calculation easy!
 * not implemented yet, to be continue ...
***********************************************************************/
#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

template<class Type>
Type sq(Type x) {return x*x;}
template<class Type>
Type pw3(Type x) {return x*x*x;}
template<class Type>
Type pw4(Type x) {return x*x*x*x;}

#define all(x) x.begin(), x.end()
#define SETPRECISION 10
#include <bits/stdc++.h>
#include "function.hpp"
#include "linear.hpp"

// custom_assert
void custom_assert(bool condition, const std::string& error_message) {
    if (!condition) {
        std::cerr << "Assertion failed: " << error_message << std::endl;
        std::terminate(); // Terminate the program
    }
}

// random number
std::mt19937 seed(std::random_device{}());
template <class Type> Type rand_real(const Type& l, const Type& r) {
    std::uniform_real_distribution<Type> nd(l, r);
    return nd(seed);
}
template <class Type> Type rand_int(const Type& l, const Type& r) {
    std::uniform_int_distribution<Type> nd(l, r);
    return nd(seed);
}

namespace norm {
    using namespace linear;

    // norm of a vector
    template<class Type, class Ftype>
    double Norm(const Vec<Type, Ftype>& x) {
        double r = 0;
        for(auto &y : x) r += fabs(y * y);
        return sqrt(r);
    }
    template<class Type, class Ftype>
    double Norm1(const Vec<Type, Ftype>& x) {
        double r = 0;
        for(auto y : x) r += fabs(y);
        return r;
    }
    template<class Type, class Ftype>
    double Normi(const Vec<Type, Ftype>& x) {
        double r = 0;
        for(Type y : x) {
            r = max(r, fabs(y));
        }
        return r;
    }

    // norm of a matrix
    template<class Type, class Ftype>
    double Normi(const Mat<Type, Ftype>& x) {
        double r = 0;
        for(Vec<Type,Ftype> y : x) {
            r += Normi(y);
        }
        return r;
    }
    template<class Type, class Ftype>
    double Norm1(const Mat<Type, Ftype>& x) {
        return Normi(~x);
    }
    // @TODO : 2-norm, need SVD

    // norm of a number
    template<class Type>
    Type Norm(const Type &x) {
        return fabs(x);
    }
}


#endif