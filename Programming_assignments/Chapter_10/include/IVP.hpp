#ifndef _IVP_
#define _IVP_

#include <bits/stdc++.h>
using namespace std;
using db = double;

using Func = function<valarray<db>(const valarray<db> &, db)>;
using Utype = valarray<db>;

class IVPsolution
{
    vector<Utype> U;
    vector<db> t;
    db L, R, N, k;
    int type;
public:
    IVPsolution(const vector<Utype>& U, const db& l, const db& r, int type = 0, const vector<db> t=vector<db>(0)):
        U(U), L(l), R(r), N(U.size()-1), k((r-l)/N), type(type), t(t) {}
    Utype operator() (db x) const
    {
        if(type)
        {
            int i = clamp<int>(upper_bound(t.begin(), t.end(), x) - t.begin() - 1, 0, N-1);
            return U[i] + (x-t[i])/(t[i+1]-t[i]) * (U[i+1]-U[i]);
        }
        int i = clamp<int>(floor((x-L)/k), 0, N-1);
        return U[i] + (x-L-i*k)/k * (U[i+1]-U[i]);
    }
    int size() const { return N+1; }
    db getlen(int i, int j) const { if(type) return (t[j]-t[i]); return (j-i)*k; }
    db gett(int i) const { if(type) return t[i]; return L+i*k; }
    Utype operator [] (const int& k) const { return U[k]; }
    Utype& operator [] (const int& k) { return U[k]; }
};

class IVPsolver
{
public:
    virtual IVPsolution solve(const Func& f, const Utype& ul, db L, db R, int N) const = 0;
    virtual ~IVPsolver() = default;
};

/*****************************************************
 * RK solver
******************************************************/

class RKsolver : public IVPsolver
{
protected:
    vector<valarray<db>> a;
    valarray<db> b, c;
public:
    RKsolver(const vector<valarray<db>> &a, const valarray<db>& b, 
    const valarray<db>& c) : a(a), b(b), c(c) {}
};

class Non_embedded_RK : public RKsolver
{
public:
    Non_embedded_RK(const vector<valarray<db>> &a, const valarray<db>& b, 
    const valarray<db>& c) : RKsolver(a, b, c) {}
    virtual Utype get_next(const Func& f, const Utype& U, const db k, const db t) const = 0;

    Utype Ex_iter(const Func& f, const Utype& U, int s, db k, db tn) const
    {
        Utype res(U);
        vector<Utype> y(s);
        for (int i = 0; i < s; ++i) {
            y[i] = U;
            for (int j = 0; j < i; ++ j)
                y[i] += k * a[i][j] * y[j];
            y[i] = f(y[i], tn + k*c[i]);
            res += k*b[i]*y[i];
        }
        return res;
    }
    Utype Im_iter_1(const Func& f, const Utype& U, int s, db k, db tn) const
    {
        vector<Utype> y(s);
        y[0] = f(U, tn);
        Utype res(U + k * b[0] * y[0]);
        for (int i = 1; i < s; ++i) {
            Utype tmp = y[0];
            bool flg = 0;
            auto Norm = [] (const Utype& u) -> db
            {
                db ret = 0;
                for(auto val : u) ret += val * val;
                return sqrt(ret);
            };
            auto cal = [&] (int i, const Utype& yi) -> Utype
            {
                Utype ret = a[i][i] * yi;
                for (int j = 0; j < i; ++j)
                {
                    ret += a[i][j] * y[j];
                }
                ret = f(U + k*ret, tn + k*c[i]);
                return ret;
            };
            static db eps = 1e-14;
            for (int k = 0; k <= 100 && (!flg); ++k)
            {
                Utype tmp1 = cal(i, tmp);
                if(Norm(tmp - tmp1) < eps) flg = 1;
                tmp = tmp1;
            }
            if (!flg) { /*cerr << "Cannot solve this Implicit iteration.";*/ }
            y[i] = tmp;
            res += k * b[i] * y[i];
        }
        return res;
    }
    Utype Im_iter_2(const Func& f, const Utype& U, int s, db k, db tn) const
    {
        vector<Utype> tmp(s), tmp1(s);
        for (int i = 0; i < s; ++i) tmp[i] = f(U, tn);
        bool flg = 0;
        static db eps = 1e-14;
        auto Dist = [] (const vector<Utype>& y, const vector<Utype>& z)
        {
            assert(y.size() == z.size());
            db res = 0;
            for (int i = 0; i < y.size(); ++i)
            {
                assert(y[i].size() == z[i].size());
                for (int j = 0; j < y[i].size(); ++ j)
                    res += (y[i][j]-z[i][j]) * (y[i][j]-z[i][j]);
            }
            return res;
        };
        auto cal = [&] (const vector<Utype>& y) -> vector<Utype>
        {
            vector<Utype> ret(y.size());
            for (int i = 0; i < s; ++i)
            {
                ret[i] = U;
                for (int j = 0; j < s; ++j) 
                    ret[i] += k * a[i][j] * y[j];
                ret[i] = f(ret[i], tn + k*c[i]);
            }
            return ret;
        };
        for (int k = 0; k <= 100 && (!flg); ++k)
        {
            tmp1 = cal(tmp);
            if (Dist(tmp, tmp1) < eps) flg = 1;
            tmp = tmp1;
        }
        if (!flg) { /*cerr << "Cannot solve this Implicit iteration.";*/ }
        Utype res(U);
        for (int i = 0; i < s; ++i) res += k * b[i] * tmp[i];
        return res;
    }

    IVPsolution solve(const Func& f, const Utype& ul, db L, db R, int N) const
    {
        db k = (R-L)/N;
        vector<Utype> U(N+1);
        U[0] = ul;
        for(int i = 0; i < N; ++i)
            U[i+1] = this->get_next(f, U[i], k, L+i*k);
        return IVPsolution(U, L, R);
    }
};

class classical_RK : public Non_embedded_RK
{
public:
    classical_RK() : Non_embedded_RK(
        vector<valarray<db>>{
	        valarray<db>{0,0,0,0},
		    valarray<db>{0.5,0,0,0},
		    valarray<db>{0,0.5,0,0},
		    valarray<db>{0,0,1,0}},
	    valarray<db>{1.0/6,1.0/3,1.0/3,1.0/6},
	    valarray<db>{0,0.5,0.5,1}) {}
    Utype get_next(const Func& f, const Utype& U, const db k, const db t) const
    { return this->Ex_iter(f, U, /*s*/4, k, t); }

    vector<Utype> Get_init_val(const Func& f, const Utype& ul, db L, db k, int N, int scale = 10) const
    {
        db R = L+k*N;
        IVPsolution tmp = solve(f, ul, L, R, N*scale);
        vector<Utype> U(N+1);
        for (int i = 0; i <= N; ++i) U[i] = tmp[i*scale];
        return U;
    }
};

class ESDIRK : public Non_embedded_RK
{
public:
    ESDIRK() : Non_embedded_RK(
        vector<valarray<db>>{
            valarray<db>{0,0,0,0,0,0},
			valarray<db>{1/4.,1/4.,0,0,0,0},
			valarray<db>{8611/62500.,-1743/31250.,1/4.,0,0,0},
			valarray<db>{5012029/34652500.,-654441/2922500.,174375/388108.,1/4.,0,0},
			valarray<db>{15267082809/155376265600.,-71443401/120774400.,730878875/902184768.,2285395/8070912.,1/4.,0},
			valarray<db>{82889/524892.,0,15625/83664.,69875/102672.,-2260/8211.,1/4.}},
		valarray<db>{82889/524892.,0,15625/83664.,69875/102672.,-2260/8211.,1/4.},
		valarray<db>{0,1/2.,89/250.,31/50.,17/20.,1}) {}
    Utype get_next(const Func& f, const Utype& U, const db k, const db t) const
    { return this->Im_iter_1(f, U, /*s*/6, k, t); }
};

class Gauss_Legendre_RK : public Non_embedded_RK
{
    const static vector<vector<valarray<db>>> A;
    const static vector<valarray<db>> B, C;
    int s;
public:
    Gauss_Legendre_RK(int s) : Non_embedded_RK(A[s-1], B[s-1], C[s-1]), s(s) {}
    Utype get_next(const Func& f, const Utype& U, const db k, const db t) const
    { return this->Im_iter_2(f, U, s, k, t); }
};
const vector<vector<valarray<db>>> Gauss_Legendre_RK::A={
	vector<valarray<db>>{
	valarray<db>{1/2.}
},vector<valarray<db>>{
	valarray<db>{1/4.,(3-2*sqrt(3))/12},
		valarray<db>{(3+2*sqrt(3))/12,1/4.}
},vector<valarray<db>>{
	valarray<db>{5/36.,2/9.-sqrt(15)/15,5/36.-sqrt(15)/30},
		valarray<db>{5/36.+sqrt(15)/24,2/9.,5/36.-sqrt(15)/24},
		valarray<db>{5/36.+sqrt(15)/30,2/9.+sqrt(15)/15,5/36.},
}
};
const vector<valarray<db>> Gauss_Legendre_RK::B={
	valarray<db>{1},
	valarray<db>{1/2.,1/2.},
	valarray<db>{5/18.,4/9.,5/18.}
};
const vector<valarray<db>> Gauss_Legendre_RK::C={
	valarray<db>{1/2.},
	valarray<db>{(3-sqrt(3))/6,(3+sqrt(3))/6},
	valarray<db>{5-sqrt(15)/10,1/2.,(5+sqrt(15))/10}
};

class Embedded_RK : public RKsolver
{
    using RKsolver::a, RKsolver::b, RKsolver::c;
    valarray<db> bh;
    int s, q;
public:
    Embedded_RK(int s, int q, const vector<valarray<db>> &a, const valarray<db>& b, 
    const valarray<db>& c, const valarray<db>& d) : RKsolver(a, b, c), bh(d), s(s), q(q) {}
    pair<Utype, db> Embedded_iter(const Func& f, const Utype& U, db k, db tn, db tolerance = 1e-6) const
    {
        static db rho_max = 5, rho = 0.8, rho_min = 0.2;
        db E_ind = 1;
        int iter = 0;
        Utype u1, u2;
        // std::cerr << tn << std::endl;
        while (E_ind >= 1)
        {
            u1 = U, u2 = U;
            vector<Utype> y(s);
            for (int i = 0; i < s; ++i)
            {
                y[i] = U;
                for (int j = 0; j < i; ++ j)
                    y[i] += k * a[i][j] * y[j];
                y[i] = f(y[i], tn + k*c[i]);
                u1 += k*b[i]*y[i];
                u2 += k*bh[i]*y[i];
            }
            E_ind = 0;
            for (int i = 0; i < U.size(); ++i)
            {
                E_ind += pow(fabs(u1[i] - u2[i]) / (tolerance * (1 + fabs(U[i]))), 2);
            }
            E_ind = sqrt(E_ind / U.size());
            k = k * min(rho_max, max(rho_min, rho*pow(E_ind, -1./(q+1))));
            ++ iter;
            if (iter > 100) { cerr << "Embbeded iteration failed!" << endl; throw("Iteration failed"); }
        }
        return make_pair(u1, k);
    }
    IVPsolution solve(const Func& f, const Utype& ul, db L, db R, int N) const
    {
        db k = (R-L)/100, t = L;
        vector<Utype> U;
        U.emplace_back(ul);
        vector<db> knots;
        knots.push_back(L);
        while (t < R)
        {
            auto [u, kp] = Embedded_iter(f, U.back(), k, t, 1.0/N);
            U.emplace_back(u);
            k = kp, t += k;
            knots.push_back(t);
        }
        return IVPsolution(U, L, R, true, knots);
    }
};

class Fehlberg_embedded_RK : public Embedded_RK
{
public:
    Fehlberg_embedded_RK() : Embedded_RK(6,4,
        vector<valarray<db>>{
		    valarray<db>{0,0,0,0,0,0},
			valarray<db>{1/4.,0,0,0,0,0},
			valarray<db>{3/32.,9/32.,0,0,0,0},
			valarray<db>{1932/2197.,-7200/2197.,7296/2197.,0,0,0},
			valarray<db>{439/216.,-8,3680/513.,-845/4104.,0,0},
			valarray<db>{-8/27.,2,-3544/2565.,1859/4104.,-11/40.,0}
	    },
		valarray<db>{25/216.,0,1408/2565.,2197/4104.,-1/5.,0},
		valarray<db>{0,1/4.,3/8.,12/13.,1,1/.2},
        valarray<db>{16/135.,0,6656/12825.,28561/56340.,-9/50.,2/55.}) {}
};

class Dormand_Prince_embedded_RK : public Embedded_RK
{
public:
    Dormand_Prince_embedded_RK() : Embedded_RK(7,4,
        vector<valarray<db>>{
	        valarray<db>{0,0,0,0,0,0,0},
		    valarray<db>{1/5.,0,0,0,0,0,0},
		    valarray<db>{3/40.,9/40.,0,0,0,0,0},
		    valarray<db>{44/45.,-56/15.,32/9.,0,0,0,0},
		    valarray<db>{19372/6561.,-25360/2187.,64448/6561.,-212/729.,0,0,0},
		    valarray<db>{9017/3168.,-355/33.,46732/5247.,49/176.,-5103/18656.,0,0},
		    valarray<db>{35/384.,0,500/1113.,125/192.,-2187/6784.,11/84.,0}
        },
        valarray<db>{35/384.,0,500/1113.,125/192.,-2187/6784.,11/84.,0},
        valarray<db>{0,1/5.,3/10.,4/5.,8/9.,1,1},
        valarray<db>{5179/57600.,0,7571/16695.,393/640.,-92091/339200.,187/2100.,1/40.}) {}
};

/*****************************************************
 * LMM solver
******************************************************/

class LMMsolver : public IVPsolver
{
protected: // U(n+s) + sum_(j=0)^(s-1) alpha_j U(n+j) = k sum_(j=0)^(s) beta_j f(U(n+j), t_(n+j))
    vector<db> alpha, beta;
public:
    LMMsolver() {}
    // calculate U(n+s)
    Utype Im_iter(const Func& f, vector<Utype>& U, int n, int s, db k, db tn) const 
    {
        Utype tmp = U[n+s-1];
        bool flg = 0;
        auto Norm = [] (const Utype& u) -> db { return sqrt((u*u).sum()); };
        auto cal = [&] (const Utype& u) -> Utype
        {
            Utype ret = k*beta[s]*f(u, tn+s*k);
            for (int j = 0; j < s; ++j)
            {
                ret += k*beta[j]*f(U[n+j], tn+j*k);
                ret -= alpha[j] * U[n+j];
            }
            return ret;
        };
        static db eps = 1e-14;
        for(int k = 0; k <= 100 && (!flg); ++k)
        {
            Utype tmp1 = cal(tmp);
            if(Norm(tmp - tmp1) < eps) flg = 1;
            tmp = tmp1;
        }
        if (!flg) { /*cerr << "Cannot solve this Implicit iteration.";*/ }
        return tmp;
    }
    Utype Ex_iter(const Func& f, vector<Utype>& U, int n, int s, db k, db tn) const
    {
        Utype tmp(U[0].size());
        for(int j = 0; j < s; ++j) 
        {
            tmp += k * beta[j] * f(U[n+j], tn+j*k);
            tmp -= alpha[j] * U[n+j]; 
        }
        return tmp;
    }
};

// only for test : not used in this project
class Euler : public IVPsolver
{
public:
    IVPsolution solve(const Func& f, const Utype& ul, db L, db R, int N) const
    {
        db k = (R - L) / N;
        vector<Utype> U(N+1); U[0] = ul;
        for (int i = 1; i <= N; ++i) U[i] = U[i-1] + k * f(U[i-1], L+k*i);
        return IVPsolution(U, L, R);
    }
    vector<Utype> Get_init_val(const Func& f, const Utype& ul, db L, db k, int N, int scale = 10) const
    {
        db R = L+k*N;
        IVPsolution tmp = solve(f, ul, L, R, N*scale);
        vector<Utype> U(N+1);
        for (int i = 0; i <= N; ++i) U[i] = tmp[i*scale];
        return U;
    }
};

class Adams_Bashforth : public LMMsolver
{
    using LMMsolver::beta, LMMsolver::alpha;
    const static vector<vector<db>> BETA;
    int p, s; 
public:
    Adams_Bashforth(int p) : p(p), s(p) { beta = BETA[p]; alpha = vector<db>(s,0), alpha[s-1] = -1; }
    IVPsolution solve(const Func& f, const Utype& ul, db L, db R, int N) const
    {
        db k = (R-L)/N;
        vector<Utype> U(N+1), initval = classical_RK().Get_init_val(f, ul, L, k, s-1);
        for(int i = 0; i < s; ++i) U[i] = initval[i];
        for(int i = 0; i <= N-s; ++i)
            U[i+s] = this->Ex_iter(f, U, i, s, k, L+i*k);
        return IVPsolution(U, L, R);
    }
};
const vector<vector<db>>
Adams_Bashforth::BETA= {{},{1, 0}, // p = 1
                        {-1/2.0, 3/2.0, 0}, // p = 2
                        {5/12.0, -16/12.0, 23/12.0, 0}, // p = 3
                        {-9/24.0, 37/24.0, -59/24.0, 55/24.0, 0}}; // p = 4

class Adams_Moulton : public LMMsolver
{
    using LMMsolver::beta;
    const static vector<vector<db>> BETA;
    int p, s;
public:
    Adams_Moulton(int p) : p(p), s(p-1) { beta = BETA[p]; alpha = vector<db>(s,0), alpha[s-1] = -1; }
    IVPsolution solve(const Func& f, const Utype& ul, db L, db R, int N) const
    {
        db k = (R-L)/N;
        vector<Utype> U(N+1), initval = classical_RK().Get_init_val(f, ul, L, k, s-1);
        for(int i = 0; i < s; ++i) U[i] = initval[i];
        for(int i = 0; i <= N-s; ++i)
            U[i+s] = this->Im_iter(f, U, i, s, k, L+i*k);
        return IVPsolution(U, L, R);
    }
};
const vector<vector<db>>
Adams_Moulton::BETA= {{},{0, 1}, // p = 1
                      {1/2.0, 1/2.0}, // p = 2
                      {-1/12.0, 8/12.0, 5/12.0}, // p = 3
                      {1/24.0, -5/24.0, 19/24.0, 9/24.0}, // p = 4
                      {-19/720.0, 106/720.0, -264/720.0, 646/720.0, 251/720.0}}; // p = 5

class BDF : public LMMsolver
{
    using LMMsolver::beta, LMMsolver::alpha;
    const static vector<vector<db>> ALPHA, BETA;
    int p, s;
public:
    BDF(int p) : p(p), s(p) { beta = BETA[p], alpha = ALPHA[p]; }
    IVPsolution solve(const Func& f, const Utype& ul, db L, db R, int N) const
    {
        db k = (R-L)/N;
        vector<Utype> U(N+1), initval = classical_RK().Get_init_val(f, ul, L, k, s-1);
        for(int i = 0; i < s; ++i) U[i] = initval[i];
        for(int i = 0; i <= N-s; ++i)
            U[i+s] = this->Im_iter(f, U, i, s, k, L+i*k);
        return IVPsolution(U, L, R);
    }
};
const vector<vector<db>>
BDF::ALPHA= {{},{-1}, // p = 1
             {1/3.0, -4/3.0}, // p = 2
             {-2/11.0, 9/11.0, -18/11.0}, // p = 3
             {3/25.0, -16/25.0, 36/25.0, -48/25.0}}; // p = 4
const vector<vector<db>>
BDF::BETA = {{}, {0, 1}, // p = 1
             {0, 0, 2/3.0}, // p = 2
             {0, 0, 0, 6/11.0}, // p = 3
             {0, 0, 0, 0, 12/25.0}}; // p = 4


#endif