#include <bits/stdc++.h>
#include "factory.hpp"
#include "IVP.hpp"
#include "IO.hpp"

using namespace std;
using db = double;
const db mu=0.012277471;

class Prob
{
public:
    string name;
    db T;
    valarray<db> u0;
    Prob(const string& name, const db& T, const valarray<db>& u0) : name(name), T(T), u0(u0) {}
};
class Task {
public:
    string id; int N; 
    Task(const string id, int N) : id(id), N(N) {}
    Task() {}
};

int main(int argc, char** argv)
{
    Prob prob1("IVP10199"s, 17.06521656015796, {0.994, 0, 0, 0, -2.0015851063790825224, 0});
    Prob prob2("IVP10200"s, 19.140540691377, {0.879779227778, 0, 0, 0, -0.379677780949, 0});
    
    function<valarray<db>(const valarray<db>&, db)> f = [](const valarray<db>& u, db t)
    {
        if(u.size() != 6) throw "[Error]: Dimension Error";
        db tmp1 = pow(u[1]*u[1]+u[2]*u[2]+(u[0]+mu-1)*(u[0]+mu-1),1.5);
        db tmp2 = pow(u[1]*u[1]+u[2]*u[2]+(u[0]+mu)*(u[0]+mu),1.5);
        return valarray<db>
        {
            u[3], u[4], u[5],
			2*u[4]+u[0]-mu*(u[0]+mu-1)/tmp1-(1-mu)*(u[0]+mu)/tmp2,
			-2*u[3]+u[1]-mu*u[1]/tmp1-(1-mu)*u[1]/tmp2,
			-mu*u[2]/tmp1-(1-mu)*u[2]/tmp2
        };
    };

    // begin: initialize IVPsolver Factory
    auto& fac = Factory<IVPsolver>::CreateFactory();
    {
        for (int p : {1, 2, 3, 4})
            fac.insert("Adams-Bashforth("s+to_string(p)+")"s, shared_ptr<IVPsolver>((IVPsolver *)(new Adams_Bashforth(p))));
        for (int p : {2, 3, 4, 5})
            fac.insert("Adams-Moulton("s+to_string(p)+")"s, shared_ptr<IVPsolver>((IVPsolver *)(new Adams_Moulton(p))));
        for (int p : {1, 2, 3, 4})
            fac.insert("BDF("s+to_string(p)+")"s, shared_ptr<IVPsolver>((IVPsolver *)(new BDF(p))));
        fac.insert("classical-RK"s, shared_ptr<IVPsolver>((IVPsolver *)(new classical_RK())));
        fac.insert("ESDIRK"s, shared_ptr<IVPsolver>((IVPsolver *)(new ESDIRK)));
        for (int p : {2, 4, 6})
            fac.insert("Gauss-Legendre("s+to_string(p)+")"s, shared_ptr<IVPsolver>((IVPsolver *)(new Gauss_Legendre_RK(p/2))));
        fac.insert("Fehlberg"s, shared_ptr<IVPsolver>((IVPsolver *)(new Fehlberg_embedded_RK)));
        fac.insert("Dormand-Prince"s, shared_ptr<IVPsolver>((IVPsolver *)(new Dormand_Prince_embedded_RK)));
    }
    // end initialization
    
    // test
    auto readTask = [] (istream& in, Task& task) -> bool
    {
        string s;
        if (getline(in, s))
        {
            stringstream IN(s);
            IN >> task.id >> task.N;
            return 1;
        }
        return 0;
    };

    auto Richard_err = [&] (shared_ptr<Non_embedded_RK> p, IVPsolution ans, int pval) -> db
    {
        db res = 0; int N = ans.size()-1;
        for(int i = 0; i < N; ++i) 
        {
            db k = ans.getlen(i,i+1); k/=2;
            Utype Uh = p->get_next(f, ans[i], k, ans.gett(i));
            Uh = p->get_next(f, Uh, k, ans.gett(i)+k);
            res = max(res, sqrt(((Uh - ans[i+1])*(Uh - ans[i+1])).sum()));
        }
        return res * pow(2, pval) / (pow(2, pval) - 1);
    };
    
    auto solve = [&](const Prob pb, const Task task) -> tuple<IVPsolution, db, db, db>
    {
        auto p = fac[task.id];

        db err1 = 0, err2 = 0, dur = 0;
        auto begin =  chrono::steady_clock::now();
        auto ans = p->solve(f, pb.u0, 0, pb.T, task.N);
        auto end = chrono::steady_clock::now();
        dur = ((chrono::duration<db>)(end-begin)).count();
        err1 = abs(pb.u0 - ans(pb.T)).max();
        err2 = -1;
        if(task.id == "classical-RK") err2 = Richard_err(dynamic_pointer_cast<Non_embedded_RK>(p), ans, 4);
        if(task.id == "ESDIRK") err2 = Richard_err(dynamic_pointer_cast<Non_embedded_RK>(p), ans, 4);
        if(task.id == "Gauss-Legendre(2)") err2 = Richard_err(dynamic_pointer_cast<Non_embedded_RK>(p), ans, 2);
        if(task.id == "Gauss-Legendre(4)") err2 = Richard_err(dynamic_pointer_cast<Non_embedded_RK>(p), ans, 4);
        if(task.id == "Gauss-Legendre(6)") err2 = Richard_err(dynamic_pointer_cast<Non_embedded_RK>(p), ans, 6);
        return {ans, dur, err1, err2};
    };

    auto print = [] (const IVPsolution& ans, const string& FILE, db l, db r, int n)
    {
        ofstream OUT(FILE);
        db k = (r - l) / n;
        for(int i = 0; i <= n; ++i) 
        {
            auto u = ans(l+i*k);
            OUT<<u[0]<<","<<u[1]<<"\n";
        }
        OUT.close();
    };

    auto ratetest = [&]()
    {
        ifstream in("data/ratetest.txt");
        ofstream out("data/ratetest.res");
        Task task;
        while(readTask(in, task))
            for (Prob pb : {prob1, prob2})
            {
                auto [ans, dur, err1, err2] = solve(pb, task);
                out<<scientific<<setprecision(2)<<pb.name<<" with "<<task.id
                   <<": N = "<<ans.size()-1<<", err1 = "<<err1<<", err2 = ";
                if(err2<0)out<<"/";
                else out<<err2;
                out<<fixed<<setprecision(3)<<", Timecost = "<<dur<<endl;
            }
        out.close();
    };
    
    auto plottest = [&]()
    {
        ifstream in("data/alltest.txt");
        // ofstream out("data/alltest.res");
        Task task;
        while(readTask(in, task))
            for (Prob pb : {prob1, prob2})
            {
                auto [ans, dur, err1, err2] = solve(pb, task);
                // out<<scientific<<setprecision(2)<<pb.name<<" with "<<task.id
                //    <<": N = "<<ans.size()-1<<", err1 = "<<err1<<", err2 = ";
                // if(err2<0)out<<"/";
                // else out<<err2;
                // out<<fixed<<setprecision(3)<<", Timecost = "<<dur<<endl;
                print(ans, "res/"s+pb.name+"_"+task.id+"_"+to_string(task.N)+".csv", 0, pb.T, 5000);
            } 
    };
#ifndef TESTSPEED
    #ifndef PLOT
        ratetest();
    #else
        plottest();
    #endif
#else
    { // least time to make eps <= 1e-3 (use IVP10.199)
    auto bi_search = [&] (const Prob& pb, string id) -> pair<db, int> /*Timecost, Numstep*/
    {
        int L = 10000, R = 2000000, ret = -1;
        if(id == "Dormand-Prince"s) R = 100000000, L = 1000000;
        db tim = -1;
        while(L <= R)
        {
            int mid = (L+R)>>1;
            auto [ans, dur, err1, err2] = solve(pb, Task(id, mid));
            if(err1 < 1e-3) ret = ans.size()-1, tim = dur, R = mid - 1;
            else L = mid + 1;
        }
        return make_pair(tim, ret);
    };
    for(auto [name, p] : fac)
    {
        auto [Time, Step] = bi_search(prob1, name);
        cerr << name << " : ";
        if(Step == -1) cerr << " Cannot achieve [error<1e-03]\n";
        else cerr<<" Timecost = "<<fixed<<setprecision(3)<<Time<<", Steps = "<<Step<<"\n";
    }
    }
#endif
    return 0;
}