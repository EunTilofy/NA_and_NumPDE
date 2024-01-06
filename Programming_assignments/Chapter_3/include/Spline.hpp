/************************************************************************
 * Ver 2.0 updated on Jan. 4th, 2023, by EunTilofy
************************************************************************/


#ifndef __Spline__
#define __Spline__

#include "function.hpp"
#include "calculator.hpp"
#include "linear.hpp"
using namespace std;

namespace Spline {
using namespace norm;
using namespace linear;
using NUM = double;

/************************************************************************
 * Spline Basic Class
*************************************************************************/

template <class Type = NUM>
class Spline {
protected:
    std::vector<Type> X, Y; // INPUT Point : 0 -> N, (N+1 in total)
    int N, Size; // Size = N + 1
    bool _spline_builded{};
	std::vector<Poly_n<Type>> splines;
	Spline () : _spline_builded(0) {}
    Spline (const vector<Type> &x, const vector<Type> &y) : 
        X(x.size()), Y(y.size()), Size(x.size()), N(x.size() - 1), 
		_spline_builded(0), splines(x.size() - 1), _self_checked(0) {
			custom_assert(x.size() == y.size(), "Spline: Input X, Y have different length.");
			custom_assert(x.size() >= 2, "Spline: Input shall not be too short.");
        	X = x; Y = y;
    }
    bool _self_checked{};
    void __self_check__() {
        custom_assert(is_sorted(X.begin(), X.end()), "Spline: Input points not be sorted by X-coordinates.");
        custom_assert(X.end()==unique(X.begin(), X.end()), "Spline: Input points X-coordinates duplicate.");
    }
public:
    virtual Type operator() (const Type &x) const {
        std::cerr << "Spline: operator() not implemented.\n";
        return Type();
    }
	
    Type get_error_i (const Function<Type>& func, vector<Type>& X) const {
        Type res = 0;
        return NormiVec(Vec(get_map_list(func, X)) - Vec(get_map_list(*this, X)));
    }
	Type get_error_1 (const Function<Type>& func, vector<Type>& X) const {
        Type res = 0;
        return Norm1Vec(Vec(get_map_list(func, X)) - Vec(get_map_list(*this, X)));
    }
	Type get_error_2 (const Function<Type>& func, vector<Type>& X) const {
        Type res = 0;
        return Norm2Vec(Vec(get_map_list(func, X)) - Vec(get_map_list(*this, X)));
    }
    Type get_midpoint_error (const Function<Type>& func) const {
        vector<Type> midpoints(N);
        for(int i = 0; i < N; ++i) midpoints[i] = (X[i] + X[i + 1]) / 2;
        return get_error_i(func, midpoints);
    }
    virtual const std::string to_python () {
        cerr << "Spline: \"to_string_python()\" Not implemented yet.\n";
        return "";
    }
};

/********************* begin (Cubic) Spline Type constraints **************/

enum Cubic_Spline_Type{
    Nature,
    Complete,
    Second_Derivatives,
    Not_Defined
};

template <class Type = NUM>
class Spline_Condition {};

template <class Type, Cubic_Spline_Type cType = Not_Defined> 
class Cubic_Spline_Condition : public Spline_Condition<Type> {};

template <class Type>
class Cubic_Spline_Condition<Type, Nature> : public Spline_Condition<Type> {
	// Second Derivatives of points a and b are both zero.
	// Nothing to provide
};

template <class Type>
class Cubic_Spline_Condition<Type, Complete> : public Spline_Condition<Type>{
public:
	// First Derivatives of points a and b are sa and sb.
    Type sa, sb;
    Cubic_Spline_Condition () : sa(0), sb(0) {}
	Cubic_Spline_Condition (Type a, Type b) : sa(a), sb(b) {}
};

template <class Type>
class Cubic_Spline_Condition<Type, Second_Derivatives> : public Spline_Condition<Type>{
public:
	// Second Derivatives of points a and b are sa and sb.
    Type sa, sb;
    Cubic_Spline_Condition () : sa(0), sb(0) {}
	Cubic_Spline_Condition (Type a, Type b) : sa(a), sb(b) {}
};

// @TODO : Add general Spline constraints class : n order
/********************* end (Cubic) Spline Type constraints **************/


/**************general template class of ppForm_Spline*******************/

template<class Type, int Order>
class ppForm_Spline : public Spline<Type> {
private: 
	using Spline<Type>::X, Spline<Type>::Y, Spline<Type>::N;
	using Spline<Type>::splines; // splines[id](x - X[id]) = s(x)
    // Although for Spline of order n (> 3), define spline[id](x) == s(x) is more suitable.
    // But in this project, I only implement n = 1, 3.
public:
	ppForm_Spline(const vector<Type> &x, const vector<Type> &y) : 
		Spline<Type>(x, y) {}
    Type operator() (const Type &x) const {
        // find which interval x lies in.
        custom_assert(this->_spline_builded, "ppForm Spline : Spline have not been built yet.");
        custom_assert(x >= X[0]-1e-10 && x <= X.back()+1e-10, "ppForm Spline : Input x is out of range.");
        auto getValue = [&](int id, const Type& x) -> Type {
            return splines[id](x - X[id]);
        };
		if(x >= X[N]) return Y[N];
        return getValue(upper_bound(X.begin(), X.end(), x) - X.begin() - 1, x);
    }

    /******************* begin Linear Spline *******************/
    void buildLinearSpline() { // build straightly 
        for(int i = 0; i < N; ++i) {
            splines[i] = Poly_n<Type>(vector<Type>({Y[i], (Y[i+1]-Y[i])/(X[i+1]-X[i])}));
        }
    }
    /******************* end Linear Spline *******************/

    /******************* begin Cubic Spline *******************/
    void buildCubicSpline(Cubic_Spline_Condition<Type, Nature> cond, Vec<Type> &x, 
	Vec<Type> &y, Vec<Type> &z, Vec<Type> &b, const vector<vector<Type>>& dd,
	const vector<Type> &lambda, const vector<Type> &mu) {
        b[0] = 0; b[N] = 0; y[0] = y[N] = 1;
		for(int i = 1; i < N; ++i) b[i] = 6*dd[1][i];

		for(int i = 1; i < N; ++i) y[i] = 2;
		for(int i = 1; i < N; ++i) x[i] = lambda[i]; x[0] = 0;
		for(int i = 1; i < N; ++i) z[i-1] = mu[i]; z[N-1] = 0;
    }
    void buildCubicSpline(Cubic_Spline_Condition<Type, Complete> cond, Vec<Type> &x, 
	Vec<Type> &y, Vec<Type> &z, Vec<Type> &b, const vector<vector<Type>>& dd,
	const vector<Type> &lambda, const vector<Type> &mu) {
        b[0] = 6*(cond.sa - dd[0][0]) / (X[0] - X[1]);
		b[N] = 6*(cond.sb - dd[0][N-1]) / (X[N] - X[N - 1]);
		for(int i = 1; i < N; ++i) b[i] = 6*dd[1][i];

		for(int i = 0; i <= N; ++i) y[i] = 2;
		for(int i = 1; i < N; ++i) x[i] = lambda[i]; x[0] = 1;
		for(int i = 1; i < N; ++i) z[i-1] = mu[i]; z[N-1] = 1;
    }
    void buildCubicSpline(Cubic_Spline_Condition<Type, Second_Derivatives> cond, Vec<Type> &x, 
	Vec<Type> &y, Vec<Type> &z, Vec<Type> &b, const vector<vector<Type>>& dd,
	const vector<Type> &lambda, const vector<Type> &mu) {
        b[0] = cond.sa; b[N] = cond.sb; y[0] = y[N] = 1;
		for(int i = 1; i < N; ++i) b[i] = 6*dd[1][i];

		for(int i = 1; i < N; ++i) y[i] = 2;
		for(int i = 1; i < N; ++i) x[i] = lambda[i]; x[0] = 0;
		for(int i = 1; i < N; ++i) z[i-1] = mu[i]; z[N-1] = 0;
    }
    /******************* end Cubic Spline *******************/

    void build() {
        if(this->_spline_builded) { return; }
        if(!this->_self_checked) { this->__self_check__(); this->_self_checked = 1; }
        if(Order == 1) buildLinearSpline();
        else { std::cerr << "ppForm_Spline: build() not implemented.\n"; return; }
        this->_spline_builded = 1;
    }

    template <Cubic_Spline_Type cType>
    void build(Cubic_Spline_Condition<Type, cType> cond) {
        if(this->_spline_builded) { return; }
        if(!this->_self_checked) { this->__self_check__(); this->_self_checked = 1; }
        if(Order == 3) {
			// divided differences calculate
			vector<vector<Type>> dd(2);
			dd[0].resize(N + 1); dd[1].resize(N + 1);
			for(int i = 0; i < N; ++i) dd[0][i] = (Y[i] - Y[i+1]) / (X[i] - X[i+1]);
			for(int i = 1; i < N; ++i) dd[1][i] = (dd[0][i] - dd[0][i-1]) / (X[i+1] - X[i-1]);

			// lambda & mu
			vector<Type> lambda(N), mu(N);
			for(int i = 1; i < N; ++i) lambda[i] = (X[i] - X[i-1]) / (X[i + 1] - X[i - 1]),
										   mu[i] = (X[i+1] - X[i]) / (X[i + 1] - X[i - 1]);

			
			// construct linear system Ax = b
			Vec<Type> x(N), y(N+1), z(N), b(N+1);
			buildCubicSpline(cond, x, y, z, b, dd, lambda, mu);
			Vec<Type> M = Thomas(y, z, x, b);
			Vec<Type> m(M.Size());

			// calculate m
			for(int i = 0; i < N; ++i) m[i] = dd[0][i]-(1.0/6)*(M[i+1]+2*M[i])*(X[i+1]-X[i]);
			m[N] = dd[0][N-1]-(1.0/6)*(M[N-1]+2*M[N])*(X[N-1]-X[N]);

			// get ppForm
			splines[0] = Poly_n<Type>(vector<Type>({Y[0], m[0], M[0]/2.0, (M[1]-M[0])/(X[1]-X[0])/6.0}));
			for(int i = 1; i < N; ++i) {
            	splines[i] = Poly_n<Type>(vector<Type>({Y[i], m[i], M[i]/2.0, (M[i+1]-M[i])/(X[i+1]-X[i])/6.0}));
        	}
		}
        else { std::cerr << "ppForm_Spline: build() not implemented.\n"; return; }
        this->_spline_builded = 1;
    }

    const std::string to_python () {
        // s(x) = splines[id](x - X[id]) -> shift right
		// To_string(x) : can give more precise float numbers
        std::string ret="";
        for(int i = 0; i < N; ++i) {
            ret.append("("+splines[i].shift(-X[i]).to_python()+")*((x>="+
                To_string(X[i])+")&(x<"+(i==N-1?"=":"")+To_string(X[i+1])+"))");
            if(i < N-1) ret.append("+");
        }
        return ret;
    }

	REGISTER_OUTPUT_NAME(ppForm_Spline, splines);
};

/************************************************************************
 * B-splines (B-Form)
*************************************************************************/

template <class Type, int Order>
class B_Spline : public Spline<Type> {
private:
	class B_Spline_Base { // B_{t_I}^n
		int n, I;
	public:
		vector<Poly_n<Type>> f; // polynomials of each interval [t_i, t_{i + 1})
		B_Spline_Base() {}
		B_Spline_Base(int _I) : I(_I), n(0), f{Poly_n<Type>(vector<Type>{1.})} {}
		int getL() const { return I - 1; }
		int getR() const { return I + f.size() - 1; }

		Type operator () (int pos, const Type &x) const { // x \in [t_pos, t_{pos + 1}]
			return f[pos - I + 1](x);
		}

		B_Spline_Base operator+(const B_Spline_Base &o) const {
			B_Spline_Base r;
			if(!f.size()) return o;
			if(!o.f.size()) return *this;
			r.I = min(I, o.I);
			r.f.resize(max(getR(), o.getR()) - r.getL());
			for(int i = 0; i < f.size(); ++i) r.f[i + getL() - r.getL()] += f[i];
			for(int i = 0; i < o.f.size(); ++i) r.f[i + o.getL() - r.getL()] += o.f[i];
			r.n = r.f.size() - 1;
			return r;
		}

		B_Spline_Base &operator*=(const Poly_n<Type> &o) {
			for (auto &g : f) g *= o;
			return *this;
		}

		B_Spline_Base operator*(const Poly_n<Type> &o) const {
			auto tmp = *this;
			for (auto &g : tmp.f) g *= o;
			return tmp;
		}

		B_Spline_Base operator*(const Type &o) const {
			auto tmp = *this;
			for (auto &g : tmp.f) g *= o;
			return tmp;
		}

		B_Spline_Base derivative() const {
			B_Spline_Base r;
			r.I = I;
			r.f.reserve(f.size());
			for (const auto &g : f) r.f.push_back(g.derivative());
			return r;
		}
		
		B_Spline_Base Derivative(int n) const {
			if(n == 0) return *this;
			if(n == 1) return derivative();
			return (this->derivative()).Derivative(n-1);
		}

		friend B_Spline_Base operator* (const Type& o, const B_Spline_Base& b) {
			return b * o;
		}
		REGISTER_OUTPUT_NAME(B_Spline_Base, I, n, f);
	};
protected:
	using Spline<Type>::X, Spline<Type>::Y, Spline<Type>::N, Spline<Type>::Size;
	using Spline<Type>::splines;  // ppForms : only for print
	vector<Type> a, t;
	int offset; // number of points extended

	bool _calculate_ppForm, _B_Spline_Base_build;

	Type T(int i) const { return t[i + offset]; } // T(-offset -> N) -> t(0 -> N + offset)
	vector<vector<B_Spline_Base>> B_Spline_Base_store;
	void build_B_Spline() {
		B_Spline_Base_store.resize(N+offset+offset+1);
		for(int i = -offset+1; i <= N+offset; ++i) {
			B_Spline_Base_store[i+offset].resize(Order+1);
			B_Spline_Base_store[i+offset][0] = B_Spline_Base(i);
		}
		for(int j = 1; j <= Order; ++j) 
		for(int i = -offset+1; i <= N+offset-j; ++i) {
			B_Spline_Base_store[i+offset][j] = 
				B_Spline_Base_store[i+offset][j-1] * (Poly_n<Type>(vector<Type>{-T(i-1), 1}) / (T(i+j-1)-T(i-1)))
			  + B_Spline_Base_store[i+1+offset][j-1] * (Poly_n<Type>(vector<Type>{T(i+j), -1}) / (T(i+j)-T(i)));
		}
		_B_Spline_Base_build = 1;
	}
	const B_Spline_Base get_B_Spline(int I, int n) const { // get B_{t_I}^n
		return B_Spline_Base_store[I+offset][n];
	}
public:
	B_Spline (const vector<Type> &x, const vector<Type> &y) : Spline<Type>(x, y), _calculate_ppForm(0), _B_Spline_Base_build(0) {
		this->__self_check__();
		this->_self_checked = 1;
		Type d = 0; // calculate difference
		for(int i = 0; i < N; ++i) d += X[i+1] - X[i];
		d /= N;
		offset = Order;
		for(int i = offset; i; --i) t.push_back(X[0] - i*d);
		for(int i = 0; i <= N; ++i) t.push_back(X[i]);
		for(int i = 1; i <= offset; ++i) t.push_back(X[N] + i*d);
		build_B_Spline();
	}
	Type operator() (const Type &x) const {
		custom_assert(this->_spline_builded, "B Spline : Spline have not been built yet.");
        custom_assert(x >= X[0] - 1e-10 && x <= X.back() + 1e-10, "B Spline : Input x is out of range.");
		if(x >= X.back()) return Y.back();
		if(x <= X[0]) return Y[0];
		Type ret = 0;
		int pos = upper_bound(t.begin(), t.end(), x) - t.begin() - 1 - offset;
		for(int i = max(0, pos); i <= pos + Order && i < N + Order; ++i)
			ret += a[i] * get_B_Spline(i-offset+1, Order)(pos, x);
		return ret;
	}
	void build(vector<tuple<bool, int, Type>> bc= vector<tuple<bool, int, Type>>(0)) {
        if(this->_spline_builded) { return; }
        if(!this->_self_checked) { this->__self_check__(); this->_self_checked = 1; }
		if(bc.size() < Order - 1) {
			std::cerr << "B Spline : Too few extra conditions.\n";
			return;
		}
		sort(bc.begin(), bc.end());
		
		Mat<Type> A(N+Order, N+Order); Vec<Type> b(N+Order);

		for(int i = 0; i <= N; ++i) b[i] = Y[i];

		for(int j = 0; j <= N; ++j){
			for(int i = j-offset+1; i <= j; ++i) {
				A[j][i+offset-1] += get_B_Spline(i, Order)(j, T(j));
			}
		}

		for(int i = 0, j = N+1; i < Order-1; ++i, ++j) {
			if(i < Order-2 && get<0>(bc[i]) == get<0>(bc[i+1]) && 
				get<1>(bc[i]) == get<1>(bc[i+1])) {
					std::cerr << "B Spline : extra condition not satisfiable.\n";
					return;
				}
			else if (get<1>(bc[i]) <= 0 && get<1>(bc[i]) > Order){
				std::cerr << "B Spline : extra condition not satisfiable.\n";
				return;
			}
			else {
				b[j]= get<2>(bc[i]);
				int nd = get<1>(bc[i]);
				if(get<0>(bc[i])) { // right bounder
					for(int k = 0; k < Order; ++k)
						A[j][N-k+offset-1] += (get_B_Spline(N-k, Order).Derivative(nd))(N, T(N));
				} else { // left bounder
					for(int k = 0; k < Order; ++k)
						A[j][k] += (get_B_Spline(k-Order+1, Order).Derivative(nd))(0, T(0));
				}
			}
		}
		a = Gauss_elimination(A, b).val;

        this->_spline_builded = 1;
    }
	const std::string to_python()  {
		custom_assert(this->_spline_builded, "B Spline : Spline have not been built yet.");
		if(!_calculate_ppForm) {
			B_Spline_Base ret = a[0] * get_B_Spline(-offset+1, Order);
			for(int i = -offset+2; i <= N; ++i) {
				ret = ret + a[i+offset-1] * get_B_Spline(i, Order);
			}
			auto all_splines = ret.f;
			for(int i = 0; i < N; ++i) splines[i] = all_splines[i + Order];
			_calculate_ppForm = 1;
		}
		std::string ret = "";
		for(int i = 0; i < N; ++i) {
            ret.append("("+splines[i].to_python()+")*((x>="+
                To_string(X[i])+")&(x<"+(i==N-1?"=":"")+To_string(X[i+1])+"))");
            if(i < N - 1) ret.append("+");
        }
        return ret;
	}
	REGISTER_OUTPUT_NAME(B_Spline, a);
};

/************************************************************************
 * Cardinal-B-splines (B-Form)
*************************************************************************/

template <class Type, int Order>
class Cardinal_B_Spline : public Spline<Type> {
	class Cardinal_B_Spline_Base {
	public:
		vector<Poly_n<Type>> f;
		int L; // L >= -1
		Cardinal_B_Spline_Base() : L(-1) {}
		Cardinal_B_Spline_Base(int i) : L(i-1), f{Poly_n<Type>(vector<Type>{1.})} {}
		int getL() const { return L; }
		int getR() const { return L + (int)f.size(); }
		Type operator() (const Type& x) const {
			if(x <= getL() && x >= getR()) return 0;
			return f[int(x - L)](x);
		}
		Cardinal_B_Spline_Base shift(const int &offset) const { // B_i -> B_{i + offset}
			Cardinal_B_Spline_Base r;
			r.L = L + offset;
			r.f.reserve(f.size());
			for(const auto &g : f) r.f.push_back(g.shift(-offset));
			return r;
		}
		Cardinal_B_Spline_Base shift(const Type &offset) const { // B_i -> B_{i + offset}
			Cardinal_B_Spline_Base r;
			r.L = L + (int)offset; // In fact, it seems useless.
			r.f.reserve(f.size());
			for(const auto &g : f) r.f.push_back(g.shift(-offset));
			return r;
		}
		Cardinal_B_Spline_Base changescale(const Type &rate) const { // B_i -> B_{i + offset}
			Cardinal_B_Spline_Base r;
			r.f.reserve(f.size());
			for(const auto &g : f) r.f.push_back(g.changescale(rate));
			return r;
		}
		Cardinal_B_Spline_Base operator+(const Cardinal_B_Spline_Base &o) const {
			Cardinal_B_Spline_Base r;
			if(!f.size()) return o;
			if(!o.f.size()) return *this;
			r.L = min(L, o.L);
			r.f.resize(max(getR(), o.getR()) - r.getL());
			for(int i = 0; i < f.size(); ++i) {
				r.f[i + getL() - r.getL()] += f[i];
			}
			for(int i = 0; i < o.f.size(); ++i) r.f[i + o.getL() - r.getL()] += o.f[i];
			return r;
		}
		Cardinal_B_Spline_Base &operator*=(const Poly_n<Type> &o) {
			for(auto &g : f) g *= o;
			return *this;
		}
		Cardinal_B_Spline_Base operator*(const Poly_n<Type> &o) const {
			auto tmp = *this;
			for (auto &g : tmp.f) g *= o;
			return tmp;
		}
		Cardinal_B_Spline_Base operator*(const Type &o) const {
			auto tmp = *this;
			for (auto &g : tmp.f) g *= o;
			return tmp;
		}
		Cardinal_B_Spline_Base derivative() const {
			Cardinal_B_Spline_Base r;
			r.L = L;
			r.f.reserve(f.size());
			for (const auto &g:f) r.f.push_back(g.derivative());
			return r;
		}
		friend Cardinal_B_Spline_Base operator* (const Type& o, const Cardinal_B_Spline_Base& b) {
			return b * o;
		}
		REGISTER_OUTPUT_NAME(Cardinal_B_Spline_Base, L, f);
	};
	const Cardinal_B_Spline_Base get_B_Spline(int i, int n) const {
		static vector<Cardinal_B_Spline_Base> Cardinal_B_Spline_Base_store = {Cardinal_B_Spline_Base(0)};
		if (n < Cardinal_B_Spline_Base_store.size()) return Cardinal_B_Spline_Base_store[n].shift(i);
		for(int nn = Cardinal_B_Spline_Base_store.size(); nn <= n; ++nn) {
			Cardinal_B_Spline_Base_store.push_back(
				Cardinal_B_Spline_Base_store[nn-1] * (Poly_n<Type>(vector<Type>({1./nn,1./nn}))) + 
				Cardinal_B_Spline_Base_store[nn-1].shift(1)*(Poly_n<Type>(vector<Type>({1,-1./nn}))));
		}
		return Cardinal_B_Spline_Base_store[n].shift(i);
	}
protected:
	vector<Type> a;
	Type d, L, R;
	bool _calculate_ppForm;
public:
	using Spline<Type>::Y, Spline<Type>::X, Spline<Type>::N;
	using Spline<Type>::splines;
	Cardinal_B_Spline(const Type &_L, const Type& _R, const int &_n, 
		const vector<Type>& y) :L(_L),R(_R),d((_R-_L)/(_n-1)),
		Spline<Type>(evenspace<Type>(_L, _R, _n), y), _calculate_ppForm(0), a(_n-1+Order){}
	Type operator() (const Type &x) const {
		custom_assert(this->_spline_builded, "Cardinal B Spline : Spline have not been built yet.");
        custom_assert(x >= X[0]-1e-10 && x <= X.back()+1e-10, "Cardinal B Spline : Input x is out of range.");
		Type ret = 0;
		int pos = (int)((x - L) / d);

		for(int j = max(-Order+1, pos-Order+1); j <= min(N, pos+1); ++j) {
			ret += a[j+Order-1]*get_B_Spline(j, Order)((x-L)/d);
		}
		return ret;
	}
	/******************* begin Linear Spline *******************/
    void buildLinearSpline() { // build straightly 
        for(int i = 0; i <= N; ++i) a[i] = Y[i];
    }
    /******************* end Linear Spline *******************/

    /******************* begin Cubic Spline *******************/
    void buildCubicSpline(Cubic_Spline_Condition<Type, Nature> cond) {
		Vec<Type> x(N), y(N+1), z(N), b(N+1);
        for(int i = 1; i < N; ++i) x[i] = 1; x[0] = 0;
		for(int i = 0; i < N-1; ++i) z[i] = 1; z[N-1] = 0;
		y[0] = y[N] = 6; for(int i = 1; i < N; ++i) y[i] = 4;
		for(int i = 0; i <= N; ++i) b[i] = 6*Y[i];
		auto _a = Thomas(y, z, x, b).val;
		for(int i = 1; i <= N+1; ++i) a[i] = _a[i-1];
		a[0] = 2*a[1]-a[2]; a[N+2] = 2*a[N+1]-a[N];
    }
    void buildCubicSpline(Cubic_Spline_Condition<Type, Complete> cond) {
		Vec<Type> x(N), y(N+1), z(N), b(N+1);
        for(int i = 0; i < N; ++i) x[i] = 1;
		for(int i = 0; i < N; ++i) z[i] = 1;
		y[0] = y[N] = 2; for(int i = 1; i < N; ++i) y[i] = 4;
		for(int i = 1; i < N; ++i) b[i] = 6*Y[i];
		b[0] = 3*Y[0] + 1/(d)*cond.sa;
		b[N] = 3*Y[N] - 1/(d)*cond.sb;
		auto _a = Thomas(y, z, x, b).val;
		for(int i = 1; i <= N+1; ++i) a[i] = _a[i-1];
		a[0] = a[2] - 2/d*cond.sa;
		a[N+2] = a[N] + 2/d*cond.sb;
    }
    void buildCubicSpline(Cubic_Spline_Condition<Type, Second_Derivatives> cond) {
		Vec<Type> x(N), y(N+1), z(N), b(N+1);
        for(int i = 1; i < N; ++i) x[i] = 1; x[0] = 0;
		for(int i = 0; i < N-1; ++i) z[i] = 1; z[N-1] = 0;
		y[0] = y[N] = 6; for(int i = 1; i < N; ++i) y[i] = 4;
		for(int i = 0; i <= N; ++i) b[i] = 6*Y[i];
		b[0] -= 1/(d*d)*cond.sa;
		b[N] -= 1/(d*d)*cond.sb;
		auto _a = Thomas(y, z, x, b).val;
		for(int i = 1; i <= N+1; ++i) a[i] = _a[i-1];
		a[0] = 2*a[1]-a[2]+1/(d*d)*cond.sa; a[N+2] = 2*a[N+1]-a[N]+1/(d*d)*cond.sb;
    }
    /******************* end Cubic Spline *******************/

    void build() {
        if(this->_spline_builded) { return; }
        if(!this->_self_checked) { this->__self_check__(); this->_self_checked = 1; }
        if(Order == 1) buildLinearSpline();
        else { std::cerr << "B Spline: build() not implemented.\n"; return; }
        this->_spline_builded = 1;
    }

    template <Cubic_Spline_Type cType>
    void build(Cubic_Spline_Condition<Type, cType> cond) {
        if(this->_spline_builded) { return; }
        if(!this->_self_checked) { this->__self_check__(); this->_self_checked = 1; }
        if(Order == 3) {
			// construct linear system Ax = b
			buildCubicSpline(cond);
        }
        else { std::cerr << "Cardinal_B_Spline: build() not implemented.\n"; return; }
        this->_spline_builded = 1;
    }

	const std::string to_python()  {
		custom_assert(this->_spline_builded, "B Spline : Spline have not been built yet.");
		if(!_calculate_ppForm) {
			Cardinal_B_Spline_Base ret = a[0] * get_B_Spline(-Order+1, Order);
			for(int i = -Order+2; i <= N; ++i) {
				ret = ret + a[i+Order-1] * get_B_Spline(i, Order);
			}
			auto all_splines = ret.changescale(d).shift(L);
			for(int i = 0; i < N; ++i) splines[i] = all_splines.f[i + Order];
			_calculate_ppForm = 1;
		}
		std::string ret = "";
		for(int i = 0; i < N; ++i) {
            ret.append("("+splines[i].to_python()+")*((x>="+
                To_string(X[i])+")&(x<"+(i==N-1?"=":"")+To_string(X[i+1])+"))");
            if(i < N - 1) ret.append("+");
        }
        return ret;
	}
};

/********************************************************
 * Quadratic_Cardinal_B_Spline
 * ! This is quite different from others
 * Support half integers only
 * (I think there is no need to implement more about it.)
********************************************************/

template <class Type>
class Quadratic_Cardinal_B_Spline : public Spline<Type> {
private:
	bool _calculate_ppForm;
	int L, R, n;
	vector<Type> a;
	Type B(int i, Type x) const { // get B_i^2(x)
		if(x <= i - 1) return 0;
		if(x <= i) {
			return sq(x - i + 1.0) / 2.0;
		}
		if(x <= i + 1) {
			return 0.75 - sq(x - (i + 0.5));
		}
		if(x <= i + 2) {
			return sq(i + 2.0 - x) / 2.0;
		}
		return 0;
	}
	Poly_n<Type> getB(int seg/*0, 1, 2*/, int i) {
		if(seg == 0) {
			return (Poly_n<Type>(vector<Type>({0.5*sq(i-1.0), -i+1.0, 0.5})));
		} if(seg == 1) {
			return Poly_n<Type>(vector<Type>({0.75-sq(i+0.5), 2.0*i+1, -1}));
		} if(seg == 2) {
			return Poly_n<Type>(vector<Type>({sq(i+2.0)*0.5, -i-2.0, 0.5}));
		}
		return (Poly_n<Type>());
	}
public:
	using Spline<Type>::splines, Spline<Type>::X, Spline<Type>::N;
	Type operator() (const Type& x) const {
		custom_assert(x >= L-1e-10 && x <= R+1e-10, "Quadratic_Cardinal_B_Spline : Input x out of range.");
		int i = floor(x);
		Type res = 0;
		if(i-1 >= L-1 && i-1 <= R) res += a[i-1-L+1] * B(i-1, x);
		if(i   >= L-1 && i   <= R) res += a[i  -L+1] * B(i  , x);
		if(i+1 >= L-1 && i+1 <= R) res += a[i+1-L+1] * B(i+1, x);
		return res;
	}
	Quadratic_Cardinal_B_Spline(const int& x0, const int& _n, const vector<Type>& f, const Type& f0, const Type& fn) 
	: L(x0), R(x0 + _n), n(_n), _calculate_ppForm(0) {
		this->X.resize(n+1);
		for(int i = 0; i <= n; ++i) this->X[i] = L + i;
		Vec<Type> x(n), y(n-1), z(n-1), b(n);
		for (int i = 1; i < n-1; ++i) {
			x[i] = 6; y[i-1] = 1;
			z[i] = 1; b[i] = 8 * f[i];
		}
		x[0] = 5, z[0] = 1, b[0] = 8 * f[0] - 2 * f0;
		x[n-1] = 5, y[n-2] = 1, b[n-1] = 8 * f[n-1] - 2 * fn;
		vector<Type> t = Thomas(x, y, z, b).val;
		a.resize(n+2);
		for (int i = 0; i < n; ++ i) a[i+1] = t[i];
		a[0] = 2 * f0 - a[1];
		a[n+1] = 2 * fn - a[n];
		this->_spline_builded = 1;
	}
	const std::string to_python() {
		custom_assert(this->_spline_builded, "B Spline : Spline have not been built yet.");
		if(!_calculate_ppForm) {
			splines.resize(n);
			for(int i = 0; i < n; ++i) for(int j = i; j <= i + 2; ++j) {
 				splines[i] += getB(2-j+i, j-1+L) * a[j];
			}
			_calculate_ppForm = 1;
		}
		std::string ret = "";
		for(int i = 0; i < n; ++i) {
            ret.append("("+splines[i].to_python()+")*((x>="+
                To_string(X[i])+")&(x<"+(i==n-1?"=":"")+To_string(X[i+1])+"))");
            if(i < n - 1) ret.append("+");
        }
        return ret;
	}
};

template <class Type>
Quadratic_Cardinal_B_Spline<Type> 
Quadratic_Cardinal_B_Spline_Interpolation(const Function<Type>& f, const int& l, const int& n) {
	vector<Type> y(n);
	for(int i = 0; i < n; ++ i) y[i] = f(l+i+0.5);
	Type f0 = f(l), fn = f(l+n);
	return Quadratic_Cardinal_B_Spline<Type>(l, n, y, f0, fn);
}

/************************************************************************
 * Curve fitting via splines
 * Support only Cardinal B Splines of order 3
 * (ppForm Splines, B Form is similar, a few changes in interface )
*************************************************************************/

using NUM = double;

class Curve_fitting_Order3 { // Here I use B_spline
	B_Spline<NUM, 3> x, y;
public:
	Curve_fitting_Order3 (vector<NUM> &_t, vector<NUM> &_x, vector<NUM> &_y) : x(_t, _x), y(_t, _y) {}
	void buildNature() {
		x.build({{0, 2, 0}, {1, 2, 0}});
		y.build({{0, 2, 0}, {1, 2, 0}});
	}
	void buildComplete(NUM xa, NUM xb, NUM ya, NUM yb) {
		x.build({{0, 1, xa}, {1, 1, xb}});
		y.build({{0, 1, ya}, {1, 1, yb}});	
	}
	void buildSecondDerivatives(NUM xa, NUM xb, NUM ya, NUM yb) {
		x.build({{0, 2, xa}, {1, 2, xb}});
		y.build({{0, 2, ya}, {1, 2, yb}});	
	}
	const std::string to_python () {
        return "X = " + x.to_python() + "\nY = " + y.to_python();
    }
};

}


#endif