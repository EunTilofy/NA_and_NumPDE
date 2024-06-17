#include <bits/stdc++.h>
#include "factory.hpp"
#include "IO.hpp"
#include "MOL.hpp"

using namespace std;

int main()
{
    auto& fac_heat = Factory<Heat_Solver>::CreateFactory();
    {
        fac_heat.insert("CN"s, shared_ptr<Heat_Solver>((Heat_Solver *)(new Crank_Nicolson())));
        fac_heat.insert("BTCS"s, shared_ptr<Heat_Solver>((Heat_Solver *)(new BTCS())));
        fac_heat.insert("FTCS"s, shared_ptr<Heat_Solver>((Heat_Solver *)(new FTCS())));
        fac_heat.insert("RKM2"s, shared_ptr<Heat_Solver>((Heat_Solver *)(new RKMethod_2())));
        fac_heat.insert("GLRKM1"s, shared_ptr<Heat_Solver>((Heat_Solver *)(new Gauss_Legendre_RKMehod_1())));
    }
    auto& fac_adve = Factory<Advection_Solver>::CreateFactory();
    {
        fac_adve.insert("leapfrog", shared_ptr<Advection_Solver>((Advection_Solver *)(new LeapFrog())));
        fac_adve.insert("LF", shared_ptr<Advection_Solver>((Advection_Solver *)(new Lax_Friedrichs())));
        fac_adve.insert("LW", shared_ptr<Advection_Solver>((Advection_Solver *)(new Lax_Wendroff())));
        fac_adve.insert("upwind", shared_ptr<Advection_Solver>((Advection_Solver *)(new Upwind())));
        fac_adve.insert("BW", shared_ptr<Advection_Solver>((Advection_Solver *)(new Beam_Warming())));
    }

    auto task1 = [&]()
    {
        Func f = [&](db x, db t) -> db
        {
            if (x ==0 || x == 1) return 0;
            return 1 - min<db>(1, 20*abs(x-0.5));
        };
        auto ans = [&](db x, db t) -> db
        {
            db pi = acos(-1.);
            auto sum = [&](int l, int r) -> db
            {
                db ret = 0;
                for (int k=l; k<=r; ++k)
                    ret += 1.0/(k*k)*(-sin(9.0/20*k*pi)+2*sin(0.5*k*pi)-sin(11.0/20*k*pi))*(exp(-k*k*pi*pi*t)*sin(k*pi*x));
                return ret;
            };
            return 40/(pi*pi)*sum(1, 10);
        };
        db h = 1.0/20, nu = 1; int n = 10;
        vector<int> id = {1, 2, 10};
        auto sol = [&](string name, db r, string _)
        {
            db k=r*h*h/nu;
            int m=round(1/h);
            auto res=fac_heat[name]->solve(f, nu, 0, 1, 0, n*k, h, k);
            for (int t : id)
            {
                ofstream out("res/"+name+"(r="+_+",t="+to_string(t)+").csv");
                for (int i = 0; i <= 10000; ++i)
                {
                    out << i/10000.0 << "," << res(i/10000.0, k*t) << "," << ans(i/10000.0, k*t) << "\n";
                }
                out.close();
            }
        };
        sol("FTCS", 1, "1"); sol("FTCS", 0.5, "0.5");
        sol("BTCS", 1, "1"); sol("BTCS", 10, "10");
        sol("CN", 1, "1"); sol("CN", 2, "2");
        sol("RKM2", 1, "1"); sol("RKM2", 10, "10");
        sol("GLRKM1", 1, "1"); sol("GLRKM1", 10, "10");
    };

    auto task2 = [&]()
    {
        BFunc f = [&](db x) -> db
        {
            return exp(-20*(x-2)*(x-2))+exp(-(x-5)*(x-5));
        };
        auto ans = [&](db x, db t) -> db
        {
            return exp(-20*(x-t-2)*(x-t-2))+exp(-(x-t-5)*(x-t-5));
        };
        db h=1.0/20, a=1, T=17;
        db xl=15,xr=25,tl=0,tr=T;
        auto sol = [&](string name, db k)
        {
            string _ = (k==1)?"":"0.8";
            ofstream out("res/"+name+"(k="+_+"h).csv");
            auto res = fac_adve[name]->solve(f, a, xl, xr, tl, tr, h, k*h);
            int m=round((xr-xl)/h);
            for (int i=0; i<=10000; ++i)
            {
                db x = xl+(xr-xl)/10000*i;
                out << x << "," << res(x, T) << "," << ans(x, T) << "\n";
            }
        };
        sol("leapfrog", 0.8);
        sol("LF", 0.8);
        sol("LW", 0.8); sol("upwind", 0.8); sol("BW", 0.8);
        sol("LW", 1); sol("leapfrog", 1);
    };

    task1(); task2();
}