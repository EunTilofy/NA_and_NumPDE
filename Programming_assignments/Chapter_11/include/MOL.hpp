#ifndef _MOL_
#define _MOL_

#include <bits/stdc++.h>
using namespace std;
using db = double;

using BFunc = function<db(const db &)>;
using Func = function<db(const db &, const db &)>;
using SpaceVec = valarray<db>;

class IBVPsolution
{
    vector<SpaceVec> U;
    db xL, tL, xh_i, th_i;
    db getv(db dl, db dr, db vl, db vr) const { return (dl*vr+dr*vl)/(dl+dr); }
public:
    IBVPsolution(const vector<valarray<db>> &u, db xl, db xr, db tl, db tr):
        U(u), xL(xl), tL(tl), xh_i((u[0].size()-1)/(xr-xl)), th_i((u.size()-1)/(tr-tl)) {}
    db operator () (db x, db t) const 
    {
        int xid = clamp<int>(floor((x-xL)*xh_i), 0, U[0].size()-2);
        int tid = clamp<int>(floor((t-tL)*th_i), 0, U.size()-2);
        db dxl = x-(xL+xid/xh_i), dxr = 1/xh_i-dxl;
        db dtl = t-(tL+tid/th_i), dtr = 1/th_i-dtl;
        return getv(dxl, dxr, getv(dtl, dtr, U[tid][xid], U[tid+1][xid]), 
                            getv(dtl, dtr, U[tid][xid+1], U[tid+1][xid+1]));
    }
};

/********************************************
 * Heat Solver
********************************************/

class Heat_Solver
{
public:
    virtual IBVPsolution solve(const Func& f, db nu, db xl, db xr, db tl, db tr, db xh, db th) const = 0;
    virtual ~Heat_Solver() = default;
};

class ThetaMethod : public Heat_Solver
{
    db theta;
    valarray<db> EquationSolver(valarray<db> l, valarray<db> d, valarray<db> u, valarray<db> b) const
    {
    	int n=b.size();
    	assert(d.size()==n&&l.size()==n-1&&u.size()==n-1);
    	for (int i=0; i<n-1; i++)
    	{
    		u[i]/=d[i];
    		d[i+1]-=l[i]*u[i];
    		b[i+1]-=l[i]/d[i]*b[i];
    	}
    	valarray<db> x=b/d;
    	for (int i=n-2; i>=0; i--) x[i]-=u[i]*x[i+1];
    	return x;
    }
public:
    ThetaMethod(db th) : theta(th) {}
    IBVPsolution solve(const Func& f, db nu, db xl, db xr, db tl, db tr, db xh, db th) const
    {
        int m = round((xr-xl)/xh), n = round((tr-tl)/th);
        db r = nu*th/xh/xh;
        vector y(n+1, SpaceVec(m+1));
        for (int i=0; i<=m; ++i) y[0][i] = f(xl+i*xh, tl);
        for (int j=1; j<=n; ++j)
        {
            const auto &y0=y[j-1];
            SpaceVec l(m), d(m+1), u(m), b(m+1);
            l=-theta*r; d=1+2*theta*r; u=-theta*r;
            d[0]=1; b[0]=f(xl,tl+j*th);
            d[m]=1; b[m]=f(xr,tl+j*th);
            l[m-1]=0;u[0]=0;
            for (int i=1; i<m; ++i)
                b[i]=(1-theta)*r*y0[i-1]+(1-2*(1-theta)*r)*y0[i]+(1-theta)*r*y0[i+1];
            y[j]=EquationSolver(l,d,u,b);
        }
        return IBVPsolution(y, xl, xr, tl, tr);
    }
};

class FTCS : public ThetaMethod
{
public:
	FTCS() : ThetaMethod(0){}
};
class Crank_Nicolson : public ThetaMethod
{
public:
	Crank_Nicolson() : ThetaMethod(0.5){}
};
class BTCS : public ThetaMethod
{
public:
	BTCS() : ThetaMethod(1){}
};

class RKMethod : public Heat_Solver
{
    vector<valarray<db>> a;
    valarray<db> b, c;
    valarray<db> EquationSolver(vector<valarray<db>> a,valarray<db> b) const
    {
    	auto A=a; auto B=b;
    	int n=a[0].size(), m=a.size();
    	assert(n&&n<=m&&m==b.size());
    	for (int i=0; i<n; ++i)
    	{
    		int k=i;
    		for (int j=i+1; j<m; j++) if (abs(a[k][i])<abs(a[j][i])) k=j;
    		swap(a[i],a[k]); swap(b[i],b[k]);
    		for (int j=0; j<m; j++) if (j!=i)
    		{
    			db xs=a[j][i]/a[i][i];
    			for (k=i; k<n; k++) a[j][k]-=a[i][k]*xs;
    			b[j]-=b[i]*xs;
    		}
    	}
    	valarray<db> x(n);
    	for (int i=0; i<n; i++) x[i]=b[i]/a[i][i];
    	return x;
    }
public: 
    RKMethod(const vector<valarray<db>> &a, const valarray<db> &b, const valarray<db> &c)
	: a(a), b(b), c(c) {}
    IBVPsolution solve(const Func& f, db nu, db xl, db xr, db tl, db tr, db xh, db th) const
    {
        int s = a.size();
        int m = round((xr-xl)/xh), n = round((tr-tl)/th);
        db r = nu*th/xh/xh;
        vector y(n+1, SpaceVec(m+1));
        for (int i=0; i<=m; ++i) y[0][i]=f(xl+i*xh, tl);
        for (int I=1; I<=n; ++I)
        {
            vector coef((m+1)*s, valarray<db> ((m+1)*s));
            valarray<db> rhs((m+1)*s);
            for (int i=0; i<s; ++i)
            {
                coef[i*(m+1)][i*(m+1)]=1;
				coef[i*(m+1)+m][i*(m+1)+m]=1;
				for (int j=1; j<m; ++j)
				{
					int x=i*(m+1)+j;
                    auto &co=coef[x];
					rhs[x] = y[I-1][j+1]-2*y[I-1][j]+y[I-1][j-1];
					co[x] += th/r;
					for (int l=0; l<s; ++l)
					{
						x = l*(m+1)+j;
						co[x+1] -= th*a[i][l];
						co[x  ] += 2*th*a[i][l];
						co[x-1] -= th*a[i][l];
					}
				}
            }
            const auto &ans = EquationSolver(coef, rhs);
			for (int i=0; i<=m; ++i) for (int j=0; j<s; ++j)
                y[I][i]+=b[j]*ans[j*(m+1)+i];
			y[I] = y[I-1]+th*y[I];
        }
        return IBVPsolution(y, xl, xr, tl, tr);
    }
};

class RKMethod_2 : public RKMethod
{
public:
	RKMethod_2 () : RKMethod(vector{ valarray<db>{5/12.,-1/12.}, valarray<db>{3/4.,1/4.}}, valarray<db>{3/4.,1/4.}, valarray<db>{1/3.,1}) {}
};
class Gauss_Legendre_RKMehod_1 : public RKMethod
{
public:
	Gauss_Legendre_RKMehod_1(): RKMethod(vector{valarray<db>{1/2.}}, valarray<db>{1}, valarray<db>{1/2.}){}
};

/********************************************
 * Advection Solver
********************************************/


class Advection_Solver
{
public:
    virtual IBVPsolution solve(const BFunc &f, db a, db xl, db xr, db tl, db tr, db xh, db th) const = 0;
    virtual ~Advection_Solver() = default;
};

class LeapFrog : public Advection_Solver
{
    IBVPsolution solve(const BFunc &f, db a, db xl, db xr, db tl, db tr, db xh, db th) const
    {
        xl+=ceil((tr-tl)/th)*xh*(-2);
        xr+=ceil((tr-tl)/th)*xh*2;
        int m = round((xr-xl)/xh), n = round((tr-tl)/th);
        db mu=a*th/xh;
        vector y(n+1, SpaceVec(m+1));
        for (int i=0; i<=m; ++i) y[0][i]=f(xl+i*xh);
        for (int i=0; i<=m; ++i)
            y[1][i]=0.5*(y[0][(i+1)%m]+y[0][(i+m-1)%m])-(mu/2)*(y[0][(i+1)%m]-y[0][(i+m-1)%m]);
        for (int i=2; i<=n; ++i) for (int j=0; j<=m; ++j)
            y[i][j]=y[i-2][j]-mu*(y[i-1][(j+1)%m]-y[i-1][(j+m-1)%m]);
        return IBVPsolution(y, xl, xr, tl, tr);
    }
};

class OneStepMethod : public Advection_Solver
{
    using ARG = vector<pair<int, db>>;
    ARG A0, A1, A2; // 1, mu, mu*2
protected:
    OneStepMethod(const ARG &A0, const ARG &A1, const ARG &A2) : A0(A0), A1(A1), A2(A2) {}
public:
    IBVPsolution solve(const BFunc &f, db a, db xl, db xr, db tl, db tr, db xh, db th) const 
    { // u_t + a u_x = 0
        xl+=ceil((tr-tl)/th)*xh*(-2);
        xr+=ceil((tr-tl)/th)*xh*2;
        int m = round((xr-xl)/xh), n = round((tr-tl)/th);
        db mu = a*th/xh;
        vector y(n+1, SpaceVec(m+1));
        for (int i=0; i<=m; ++i) y[0][i]=f(xl+i*xh);
        for (int i=1; i<=n; ++i) 
        {
            for (int j=0; j<=m; ++j)
            {
                for(auto [o,v]: A0) y[i][j]+=y[i-1][(m+j+o)%m]*v;
                for(auto [o,v]: A1) y[i][j]+=y[i-1][(m+j+o)%m]*v*mu;
                for(auto [o,v]: A2) y[i][j]+=y[i-1][(m+j+o)%m]*v*mu*mu;
            } 
        }
        return IBVPsolution(y, xl, xr, tl, tr);
    }
};
class Lax_Friedrichs : public OneStepMethod
{
public:
    Lax_Friedrichs() : OneStepMethod({{1,1/2.},{-1,1/2.}},{{1,-1/2.},{-1,1/2.}},{}){}
};
class Lax_Wendroff : public OneStepMethod
{
public:
    Lax_Wendroff() : OneStepMethod({{0,1.}},{{1,-1/2.},{-1,1/2.}},{{1,1/2.},{0,-1.},{-1,1/2.}}){}
};
class Upwind : public OneStepMethod
{
public:
    Upwind() : OneStepMethod({{0,1.}},{{0,-1.},{-1,1.}},{}){}
};
class Beam_Warming : public OneStepMethod
{
public:
    Beam_Warming() : OneStepMethod({{0,1.}},{{0,-3/2.},{-1,2.},{-2,-1/2.}},{{0,1/2.},{-1,-1.},{-2,1/2.}}){}
};

#endif