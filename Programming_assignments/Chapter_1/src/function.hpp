/**********************************************************************
 * Ver 2.2 updated on Sep. 29th, 2023, by EunTilofy
 * In this version, 
 * 1, change the two class function2d and functionVec to one class
 * 2, use funcion as the origin class, and make specializatino to
 *    each type of function
 * (!IMPORTANT!) This version is still under testing, there may remains 
 *               some problems when compiling.
***********************************************************************/
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include<bits/stdc++.h>

#include "linear.hpp"
#include "calculator.hpp"
typedef double NUM;
extern const NUM EPS_MIN = 10*std::numeric_limits<NUM>::epsilon();

using namespace linear;

// The class of all kinds of functions which maps x(in X) to y(in Y).
template <class Xtype, class Ytype = Xtype> 
class Function{
public:
    virtual Ytype operator() (const Xtype& x) const = 0;
    virtual Ytype Diff (const Xtype& x) const {custom_assert(0, "Diff() has not be designed\n");}
};

// The class of a 2d function which maps a double variable to a double one.
template<>
NUM Function<NUM, NUM>::Diff (const NUM& x) const {
    // the default difference calculator
    return ((*this)(x+EPS_MIN)-(*this)(x-EPS_MIN))/(2*EPS_MIN);
}

// all specialized
template<class Type, class Ytype>
class Function<Vec<Type>, Ytype>{
public:
    int16_t d;
    virtual Ytype operator() (const Vec<Type>& x) const = 0;
    virtual Vec<Type> Diff (const Vec<Type>& x) const = 0;
    virtual Mat<Type> Hess (const Vec<Type>& x) const {
        return Mat(d, d);
    }
    Function<Vec<Type>, Ytype>(int16_t _d = 0) : d(_d) {}
};
template<class Type>
class Function<Vec<Type>,Vec<Type>>{
public:
    virtual Vec<Type> operator() (const Vec<Type>& x) const = 0;
    virtual Vec<Type> Diff (const Vec<Type>& x) const = 0;
    int16_t d1, d2; // the dimension of the vector variable
    Function<Vec<Type>,Vec<Type>>(int16_t _d1 = 0, int16_t _d2 = 0) : d1(_d1) {
        d2 = _d2 ? _d2 : _d1;
    }
};

#endif