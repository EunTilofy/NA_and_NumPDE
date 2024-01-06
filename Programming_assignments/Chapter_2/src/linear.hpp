/**********************************************************************
 * Ver 2.1 updated on Sep. 27th, 2023, by EunTilofy
 * In this version, 
 * 1, use Vec instead of vector<Type>
 * 2, add RowVec, and completed a lot of new functions
 * 3, use a namespace to pack the three classes
 * 4, use 'REGISTER_OUTPUT' instead of overload << by myself
 * 5, add begin()/end() to ensure base_for loop
 * 6, add an argument Ftype to each class (default=double)
 *    representing the type of the number field of vector space.
 * 7, other changes for you to find out !
 * (!IMPORTANT!) This version is still under testing, there may remains 
 *               some problems when compiling.
***********************************************************************/
#ifndef _LINEAR_H_
#define _LINEAR_H_

#include <bits/stdc++.h>
#include "IO.hpp"
using namespace std;
typedef double NUM;

namespace linear { // vector space

template<class Type, class Ftype>
class Mat;
template<class Type, class Ftype>
class RowVec;
template <class Type, class Ftype>
class Vec;

template <class Type, class Ftype=NUM> // Ftype : the type of the number field of vector space
class Vec { // column vector
public:
    int16_t size;
    vector<Type> val;
    typedef Vec<Type,Ftype> VecT;
    Vec() {}
    Vec(const int& _size) : size(_size), val(size) {}
    Vec(const initializer_list<Type> initList) : size(initList.size()), val(initList) {}
    explicit Vec(const RowVec<Type, Ftype>& o) : size(o.size), val(o.val) {}
    explicit Vec(const vector<Type> &_val) : size(_val.size()), val(_val) {}
    int16_t Size() const {return size;}
    Type& operator[] (const int16_t x) {return val[x];}
    const Type& operator[] (const int16_t x) const {return val[x];}
    void resize(int16_t _size) {
        size = _size;
        val.resize(_size);
    }
    Vec operator + (const Vec& o) const {
        assert(size == o.size);
        Vec v(size);
        for(int i = 0; i < v.size; ++i) v[i] = (*this)[i] + o[i];
        return v;
    }
    Vec operator - (const Vec& o) const {
        assert(size == o.size);
        Vec v(size);
        for(int i = 0; i < v.size; ++i) v[i] = (*this)[i] - o[i];
        return v;
    }
    Vec operator * (const Ftype& num) const {
        Vec v(size);
        for(int i = 0; i < v.size; ++i) v[i] = (*this)[i] * num;
        return v;
    }
    Mat<Type, Ftype> operator * (const RowVec<Type, Ftype>& o) const {
        Mat<Type, Ftype> r(size, o.Size());
        for(int i = 0; i < size; ++i) for(int j = 0; j < o.Size(); ++j)
            r[i][j] = (*this)[i] * o[j];
        return r;
    }
    Vec operator / (const Ftype& num) const {
        assert(num != 0);
        Vec v(size);
        for(int i = 0; i < size; ++i) v[i] = (*this)[i] / num;
        return v;
    }
    Ftype dot(const Vec& o) const {
        assert(size == o.size);
        NUM r = 0;
        for(int i = 0; i < size; ++i) r += (*this)[i] * o[i];
        return r;
    }
    Mat<Type, Ftype> cross(const Vec& o) const {
        Mat<Type, Ftype> r(size, o.Size());
        for(int i = 0; i < size; ++i) for(int j = 0; j < o.Size(); ++j)
            r[i][j] = (*this)[i] * o[j];
        return r;
    }
    auto begin() const -> decltype(val.begin()) {
        return val.begin();
    }
    auto begin() -> decltype(val.begin()) {
        return val.begin();
    }
    auto end() const -> decltype(val.end()) {
        return val.end();
    }
    auto end() -> decltype(val.end()) {
        return val.end();
    }
    friend RowVec<Type, Ftype> operator ~ (const Vec &x) {
        RowVec<Type, Ftype> y(x);
        return y;
    }
    friend VecT operator * (const Ftype& num, const VecT& x) {
        vector<Type> v(x.size());
        for(int i = 0; i < v.size; ++i) v[i] = x[i] * num;
        return v;
    }
    friend Ftype dot(const VecT& x, const VecT& y) {
        assert(x.size == y.size);
        NUM r = 0; int siz = x.siz;
        for(int i = 0; i < siz; ++i) r += x[i] * y[i];
        return r;
    }
    friend VecT operator - (const VecT& x) {
        vector<Type> v(x.size());
        for(int i = 0; i < v.size; ++i) v[i] = -x[i];
        return v;
    }
    REGISTER_OUTPUT(Vec, val);
};

template<class Type, class Ftype=NUM>
class RowVec { // Row vector
public:
    int16_t size;
    vector<Type> val;
    typedef RowVec<Type,Ftype> VecT;
    RowVec() {}
    RowVec(const int &_size) : size(_size), val(size) {}
    RowVec(const initializer_list<Type> initList) : size(initList.size()), val(initList) {}
    explicit RowVec(const vector<Type> &_val) : size(_val.size()), val(_val) {}
    explicit RowVec(const Vec<Type, Ftype>& o) : size(o.size), val(o.val) {}
    RowVec(const Mat<Type, Ftype>& m) : size(m.d2), val(m.a[0]) {}

    int16_t Size() const {return size;}
    Type& operator[] (const int16_t x) {return val[x];}
    const Type& operator[] (const int16_t x) const {return val[x];}
    void resize(const int16_t _size) {
        size = _size;
        val.resize(_size);
    }
    RowVec& operator = (const Mat<Type, Ftype>& o) {
        size = o.d2; val.resize(size);
        for(int i = 0; i < size; ++i) val[i] = o.a[0][i];
        return *this;
    }
    RowVec operator + (const RowVec& o) const {
        assert(size == o.size);
        RowVec v(size);
        for(int i = 0; i < v.size; ++i) v[i] = (*this)[i] + o[i];
        return v;
    }
    RowVec operator - (const RowVec& o) const {
        assert(size == o.size);
        RowVec v(size);
        for(int i = 0; i < v.size; ++i) v[i] = (*this)[i] - o[i];
        return v;
    }
    RowVec operator * (const Ftype& num) const {
        RowVec v(size);
        for(int i = 0; i < v.size; ++i) v[i] = (*this)[i] * num;
        return v;
    }
    RowVec operator * (const Mat<Type, Ftype>& o) const {
        assert(size == o.d);
        RowVec r(o.d2);
        for(int i = 0; i < r.Size(); ++i) {
            for(int j = 0; j < size; ++j) r[i] = r[i] + (*this)[j]*o[j][i];
        }
        return r;
    }
    RowVec operator / (const Ftype& num) const {
        assert(num != 0);
        RowVec v(size);
        for(int i = 0; i < size; ++i) v[i] = (*this)[i] / num;
        return v;
    }
    Ftype operator * (const Vec<Type, Ftype>& o) const {
        assert(size == o.size);
        NUM r = 0;
        for(int i = 0; i < size; ++i) r += (*this)[i] * o[i];
        return r;
    }
    auto begin() const -> decltype(val.begin()) {
        return val.begin();
    }
    auto begin() -> decltype(val.begin()) {
        return val.begin();
    }
    auto end() const -> decltype(val.end()) {
        return val.end();
    }
    auto end() -> decltype(val.end()) {
        return val.end();
    }
    friend Vec<Type, Ftype> operator ~ (const RowVec &x) {
        Vec<Type, Ftype> y(x);
        return y;
    }
    friend VecT operator * (const Ftype& num, const VecT& x) {
        vector<Type> v(x.size());
        for(int i = 0; i < v.size; ++i) v[i] = x[i] * num;
        return v;
    }
    friend VecT operator - (const VecT& x) {
        vector<Type> v(x.size());
        for(int i = 0; i < v.size; ++i) v[i] = -x[i];
        return v;
    }
    REGISTER_OUTPUT(RowVec, val);
};

template<class Type, class Ftype=NUM>
class Mat {
public:
    int16_t d, d2; // the dimension of column vector and row vector.
    Vec<Vec<Type,Ftype>> a;
    typedef Vec<Type,Ftype> VecT;
    typedef Mat<Type,Ftype> MatT;
    Mat() {}
    Mat(const int16_t& _d, const Vec<VecT> &_a) : d(_d), d2(_d), a(_a) {
        for(auto &row : a) row.resize(d);
    }
    Mat(const int16_t& _d, const int16_t& _d2, const Vec<VecT> &_a) : d(_d), d2(_d2), a(_a) {}
    Mat(const int16_t& _d) : d(_d), d2(_d), a(_d){
        for(auto &row : a) row.resize(d);
    }
    Mat(const int16_t& _d, const int16_t& _d2) : d(_d), d2(_d2), a(_d) {
        for(auto &row : a) row.resize(d2);
    }
    Mat(const RowVec<Type, Ftype>& x) : d(1), d2(x.size), a(1){
        a[0].val = x.val;
    }
    explicit Mat(const Vec<Type, Ftype>& x) : d(x.size), d2(1), a(x.size) {
        for(int i = 0; i < d; ++i) (*this[i]) = {x[i]};
    }
    MatT& operator = (const RowVec<Type, Ftype>& x) {
        d = 1, d2 = x.size;
        a.resize(1); a[0].val = x.val;
        return *this;
    }
    VecT& operator[] (const int16_t &x) { return a[x]; }
    const VecT& operator[] (const int16_t &x) const { return a[x]; }
    auto begin() const -> decltype(a.begin()) {
        return a.begin();
    }
    auto begin() -> decltype(a.begin()) {
        return a.begin();
    }
    auto end() const -> decltype(a.end()) {
        return a.end();
    }
    auto end() -> decltype(a.end()) {
        return a.end();
    }

    template <typename T = Type>
    std::enable_if_t<std::is_arithmetic_v<T>, Mat> inv() {
        MatT _inv(d, d*2); // Mat<Num>
        assert(Mat::d == Mat::d2); // square matrix only
        for(int i = 0; i < d; ++i) for(int j = 0; j < d; ++j) _inv[i][j] = a[i][j];
        for(int i = 0; i < d; ++i) _inv[i][i+d] = 1;
        for(int i = 0; i < d; ++i) {
            Type tmp = _inv[i][i];
            if(tmp == 0) {
                for(int j = i + 1; j < d; ++j) {
                    if(_inv[j][i] != 0) {
                        swap(_inv[i], _inv[j]);
                        tmp = _inv[i][i];
                        break;
                    }
                }
            }
            for(int j = 0; j < d; ++j) if(i ^ j) {
                Type z = _inv[j][i] / _inv[i][i];
                for(int k = 0; k < d*2; ++k) _inv[j][k] -= _inv[i][k]*z;
            }
            for(int j = 0; j < d*2; ++j) _inv[i][j] /= tmp;
        }
        MatT ret(d);
        for(int i = 0; i < d; ++i) for(int j = 0; j < d; ++j) ret[i][j] = _inv[i][j+d];
        return ret;
    }
    VecT operator * (const VecT& y) const {
        VecT z(d);
        for(int i = 0; i < z.size; ++i) z[i] = (*this)[i]*y;
        return z;
    }
    friend MatT operator ~ (const MatT &x) {
        MatT y(x.d2, x.d);
        int r = x.d, c = x.d2;
        for(int i = 0; i < r; ++i) for(int j = 0; j < c; ++j)
            y[j][i] = x[i][j];
        return y;
    }
    MatT operator * (const MatT& y) const {
        Vec<VecT> z(d, y.d2); int r = d, c = d2;
        assert(c == y.d);
        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < z[i].size(); ++j)
                for(int k = 0; k < c; ++k)
                    z[i][j] = z[i][j] + (*this)[i][k] * y[k][j];
        }
    }
    MatT operator + (const MatT& y) const {
        assert(d == y.d && d2 == y.d2);
        MatT z(d, d2); int r = d, c = d2;
        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++ j)
                z[i][j] = (*this)[i][j] + y[i][j];
        }
        return z;
    }
    MatT operator - (const MatT& y) const {
        assert(d == y.d && d2 == y.d2);
        MatT z(d, d2); int r = d, c = d2;
        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++ j)
                z[i][j] = (*this)[i][j] - y[i][j];
        }
        return z;
    }
    MatT operator * (const Ftype &x) const {
        MatT z = (*this);
        for(int i = 0; i < z.d; ++i)
            for(auto &w : z[i]) w = w*x;
        return z;   
    }
    friend MatT operator * (const Type &x, const MatT &y) {
        MatT z = y;
        for(int i = 0; i < z.d; ++i) {
            for(auto &w : z[i]) w*=x;
        }
        return z;
    }
    MatT operator / (const Ftype& x) {
        assert(x != 0);
        MatT z = (*this);
        for(int i = 0; i < z.d; ++i) {
            for(auto &w : z[i]) w/=x;
        }
        return z;
    }
    MatT operator - (const MatT& y) {
        MatT z = y;
        for(int i = 0; i < z.d; ++i) {
            for(auto &w : z[i]) w=-w;
        }
        return z;
    }
    REGISTER_OUTPUT(Mat, a)
};

template<class Type, class std::enable_if<std::is_arithmetic<Type>::value>::type>
Mat<Type> Id(int16_t n) {
    Mat<Type> ret(n);
    for(int i = 0; i < n; ++i) ret[i][i] = 1;
    return ret;
}
// cross product
template<class Type, class Ftype>
Mat<Type, Ftype> cross(const Vec<Type, Ftype>& x, const Vec<Type, Ftype>& y) {
    Mat<Type, Ftype> r(x.Size(), y.Size());
    for(int i = 0; i < x.Size(); ++i) for(int j = 0; j < y.Size(); ++j)
        r[i][j] = x[i] * y[j];
    return r; 
}


}
#endif