/**********************************************************************
 * Ver 2.4 updated on Oct. 2nd, 2023, by EunTilofy
 * In this version, 
 * 1, change the two class function2d and functionVec to one class
 * 2, use funcion as the origin class, and make specializatino to
 *    each type of function
 * 3. In ver2.3 I added Poly_n (poly of degre n) which derives the Function class
 * 4. In ver2.4 I added more method in Poly_n (including : shift, integral)
 * (!IMPORTANT!) This version is still under testing, there may remains 
 *               some problems when compiling.
***********************************************************************/
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <bits/stdc++.h>

#include "linear.hpp"
#include "calculator.hpp"
#include "IO.hpp"

typedef double NUM;
extern const NUM EPS_MIN = 10*std::numeric_limits<NUM>::epsilon();

using namespace linear;

// The class of all kinds of functions which maps x(in X) to y(in Y).
template <class Xtype, class Ytype = Xtype> 
class Function{
public:
    virtual Ytype operator() (const Xtype& x) const = 0;
    virtual Ytype Diff (const Xtype& x) const {custom_assert(0, "Diff() has not be designed\n"); return Ytype();}
    virtual const std::string to_python () const {custom_assert(0, "to_python() has not be designed\n"); return "";}
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
    int d;
    virtual Ytype operator() (const Vec<Type>& x) const = 0;
    virtual Vec<Type> Diff (const Vec<Type>& x) const = 0;
    virtual Mat<Type> Hess (const Vec<Type>& x) const {
        return Mat(d, d);
    }
    Function(int _d = 0) : d(_d) {}
    virtual const std::string to_python () const {custom_assert(0, "to_python() has not be designed\n"); return "";}
};
template<class Type>
class Function<Vec<Type>,Vec<Type>>{
public:
    virtual Vec<Type> operator() (const Vec<Type>& x) const = 0;
    virtual Vec<Type> Diff (const Vec<Type>& x) const = 0;
    int d1, d2; // the dimension of the vector variable
    Function(int _d1 = 0, int _d2 = 0) : d1(_d1) {
        d2 = _d2 ? _d2 : _d1;
    }
    virtual const std::string to_python () const {custom_assert(0, "to_python() has not be designed\n"); return "";}
};

template<class Type=NUM>
class Poly_n: public Function<Type, Type> {
public:
    int n;
    int N() const {return n-1;}
    vector<Type> coef;
    Poly_n() : n(0), coef(0) {}
    explicit Poly_n(int n) : n(n), coef(n) {}
    Poly_n(const Poly_n& o) : n(o.n), coef(o.coef) {}
    explicit Poly_n(const vector<Type>& a) : n(a.size()), coef(a) {}
    Type &operator[] (const int &x) { return coef[x]; }
	const Type &operator[] (const int &x) const { return coef[x]; }
    void resize(const int &new_n) { n = new_n; coef.resize(new_n); }
    
    Type operator() (const Type& x) const {
        Type y = 0;
        for(int i = 0; i < n; ++i) y = y + coef[i]*pow(x, i);
        return y;
    }
    virtual Type Diff (const Type& x) const {
        Type r = 0;
        for(int i = 1; i < n; ++i) r = r + coef[i]*i*pow(x, i-1);
        return r;
    }
    Poly_n derivative () const {
        Poly_n ret(n-1);
        if(n < 0) return Poly_n(vector<NUM>({0}));
        for(int i = 1; i < n; ++i) ret.coef[i-1]=i*coef[i];
        return ret;
    }
    Poly_n integral () const {
        Poly_n ret(n+1);
        for(int i = 0; i < n; ++i) ret.coef[i+1]=coef[i]/(i+1);
        return ret;
    }
    Poly_n operator + (const Poly_n& o) const {
        Poly_n ret(max(o.n, n));
        for(int i = 0; i < ret.n; ++i) {
            if(i < o.n) ret.coef[i]+=o.coef[i];
            if(i < n) ret.coef[i]+=coef[i];
        }
        while(ret.n&&ret.coef[ret.n-1]==0) --ret.n, ret.coef.pop_back();
        return ret;
    }
    Poly_n &operator += (const Poly_n& o) {
        if (n < o.n) resize(o.n);
        for(int i = 0; i < n; ++i) coef[i] += o.coef[i];
        return *this;
    }
    Poly_n operator - (const Poly_n& o) const {
        Poly_n ret(max(o.n, n));
        for(int i = 0; i < ret.n; ++i) {
            if(i < o.n) ret.coef[i]-=o.coef[i];
            if(i < n) ret.coef[i]+=coef[i];
        }
        while(ret.n&&ret.coef[ret.n-1]==0) --ret.n, ret.coef.pop_back();
        return ret;
    }
    Poly_n &operator -= (const Poly_n& o) {
        if(n < o.n) resize(o.n);
        for(int i = 0; i < n; ++i) coef[i] -= o.coef[i];
        return *this;
    }
    Poly_n operator * (const Type& o) const {
        if(o == 0) return Poly_n(0);
        Poly_n ret(*this);
        for(auto &x : ret.coef) x*=o;
        while(ret.n&&ret.coef[ret.n-1]==0) --ret.n, ret.coef.pop_back();
        return ret;
    }
    Poly_n &operator *= (const Type& o) {
        if(o == 0) return *this = Poly_n(0);
        for(auto &x : coef) x*=o;
        while(n&&coef[n-1]==0) --n, coef.pop_back();
        return *this;
    }
    Poly_n operator * (const Poly_n& o) const {
        Poly_n ret(max(0, n+o.N()));
        for(int i = 0; i < n; ++i) for(int j = 0; j <= o.N(); ++j) {
            ret.coef[i+j] += coef[i] * o.coef[j];
        }
        while(ret.n&&ret.coef[ret.n-1]==0) --ret.n, ret.coef.pop_back();
        return ret;
    }
    Poly_n &operator *= (const Poly_n& o) {
        return *this = *this * o;
    }
    Poly_n operator / (const Type& o) const {
        assert( o != 0 );
        Poly_n ret(*this);
        for(auto &x : ret.coef) x/=o;
        return ret;
    }
    Poly_n &operator /= (const Type& o) {
        return *this = *this / o;
    }
    // the result is a poly g(z) : g(x - x0) = f(x) <=> g(x) = f(x + x0)
    Poly_n shift (const Type & x0) const {
        function<Type(int, int)> C=[&](int x, int y) -> Type {
            if(x < y || y < 0) return 0;
            if(y == 0 || x == 0) return 1;
            static std::vector<vector<Type>> c;
            if(c.size() <= x) c.resize(x + 1);
            if(c[x].size() <= y) c[x].resize(y + 1);
            if(c[x][y]) return c[x][y];
            c[x][y] = C(x-1, y-1) + C(x-1, y);
            return c[x][y];
        };
        vector<Type> tmp(n);
        for(int i = tmp[0] = 1; i < n; ++i) tmp[i] = tmp[i - 1]*x0;
        Poly_n ret = *this;
        for(int i = 1; i < n; ++i) for(int j = 0; j < i; ++j) 
            ret.coef[j] += C(i, j) * coef[i] * tmp[i - j];
        return ret;
    }

    Poly_n changescale (const Type& rate) const {
        Type tmp = 1;
        Poly_n ret = *this;
        for(int i = 0; i < n; ++i) ret[i] *= tmp, tmp *= (1/rate);
        return ret;
    }

    const std::string to_latex() const {
        std::stringstream ret; bool fl = 0;
        for(int i = n-1; ~i; --i) {
            if(coef[i] != 0) {
                if(!fl) {fl = 1;}
                else if(coef[i] >= 0) ret << "+"; 
                ret << (long double)coef[i];
                if(i) {
                    if(i == 1) ret << "x";
                    else ret << "x^{" << i << "}";
                }
            }
        }
        if(!fl) ret << "0";
        std::stringstream ret2;
        std::string s = ret.str();
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == 'e') {
                ret2 << "\\mathrm{e}";
                if(i+1<s.size() && (s[i+1] == '+'||s[i+1] == '-'))
                    ret2 << "{" << s[i+1] << "}", ++i;
            }
            else ret2 << s[i];
        }
        return ret2.str();
    }
    const std::string to_tikz() const {
        std::stringstream ret; bool fl = 0;
        for(int i = n-1; ~i; --i) {
            if(coef[i] != 0) {
                if(!fl) {fl = 1;}
                else if(coef[i] >= 0) ret << "+"; 
                ret << (long double)coef[i];
                if(i) {
                    if(i == 1) ret << "*x";
                    else ret << "*x^" << i;
                }
            }
        }
        if(!fl) ret << "0";
        return ret.str();
    }
    const std::string to_python() const {
        std::stringstream ret; bool fl = 0;
        for(int i = n-1; ~i; --i) {
            if(coef[i] != 0) {
                if(!fl) {fl = 1;}
                else if(coef[i] >= 0) ret << "+"; 
                ret << To_string(coef[i]);
                if(i) {
                    if(i == 1) ret << "*x";
                    else ret << "*x**" << i;
                }
            }
        }
        if(!fl) ret << "0";
        return ret.str();
    }
    REGISTER_OUTPUT_NAME(Poly_n, n, coef);
};

#define TLIMIT (long double)1e20

template<class Map>
class Curve2D {
	Map x, y;
	long double tl, tr;
public:
	Curve2D (const Map &_x, const Map &_y) : x(_x), y(_y), tl(-TLIMIT), tr(TLIMIT) {}
    Curve2D (const Map &_x, const Map &_y, long double _tl, long double _tr) : x(_x), y(_y), tl(_tl), tr(_tr) {}

	vector<pair<long double, long double>> get_points(int n) {
        auto T = evenspace<long double>(tl, tr, n);
		auto X = x.get_map_list(T);
		auto Y = y.get_map_list(T);
		vector<pair<long double, long double>> r(n);
		for(int i = 0; i < n; ++i) r[i] = {X[i], Y[i]};
		return r;
	}
};

#endif