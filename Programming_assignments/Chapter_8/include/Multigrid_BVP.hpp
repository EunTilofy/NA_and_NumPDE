/**
 * @file Multigrid_BVP.hpp
 * @author EunTilofy (papercloud@zju.edu.com)
 * @brief Multigrid Method.
 * @version 1.0
 * @date 2024-02-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MULTIGRID_BVP_SOLVER
#define MULTIGRID_BVP_SOLVER

#include <bits/stdc++.h>
#include "function.hpp"
#include "calculator.hpp"
#include "serialization.hpp"
#include "function_generator/ExecCode2.hpp"
#include "IO.hpp"
#include "linear.hpp"

#define dbg1(x) std::cerr<<#x<<"="<<x<<" "
#define dbg2(x) std::cerr<<#x<<"="<<x<<"\n"
#define dbg3(x) std::cerr<<#x<<"\n"

using namespace std;
using NUM = double;
const NUM eps = 1e-10;

class func {
    FromString<NUM, NUM> getvalue;
public:
    func (const std::string &_str) : getvalue(_str) {}
    func () : getvalue() {}
    void set(const std::string &_str) { getvalue = FromString<NUM, NUM>(_str); }
    NUM operator() (const NUM &x, const NUM &y) const {
        NUM xx = x, yy = y;
        return getvalue.cal2({{"x", xx}, {"y", yy}});
    }
    NUM operator() (const NUM &x) const {
        return getvalue.cal(x);
    }
};

class Multigrid_BVP_Problem{
public:
    // common
    // Support : 1. Regular; 2. Irregular(not concerned yet)
    std::string BC_Type; /* boundary condition : mixed, Dirichlet, Neumann*/
    std::string Domain_Type; /* regular(default) irregular*/
    vector<NUM> Domain_Border; /* [xl, xr, yl, yr] (default : [0,1]x[0,1])*/
    NUM xl, xr, yl, yr, h;
    void getDomain() {
        if(Domain_Border.size() < 2 * Dimension) { throw "Domain Border not satisfiable."; }
        Domain_Border.resize(2 * Dimension);
        xl = Domain_Border[0];
        xr = Domain_Border[1];
        if(Dimension == 2) {
            yl = Domain_Border[2];
            yr = Domain_Border[3];
            if((xr - xl) > (yr - yl) + eps || (xr - xl) < (yr - yl) - eps)
                throw "Domain Border not a square.";
            xr = (yr - yl) + xl;
            if(xl > xr + eps || yl > yr + eps) throw "Illegal Domain.";
        }
        h = (xr - xl) / Grid_n;
    }
    int Grid_n; /* Grid_n x Grid_n */
    std::string f; /* - \Delta u (in Domain)*/
    func F;

    // calculate error
    bool Need_Error;
    std::string answer;
    func Answer;

    // Boundary Condition
    // Dirichlet / Neumann
    map<std::string, std::string> g; /* left, right, up, down -> function*/
                                     /* 0,    1,     2,  3*/
    vector<func> G;
    // mixed
    map<std::string, pair<std::string, std::string>> mixed_g; /* left, right, up, down -> function*/
                                                              /* 0,    1,     2,  3 */
    vector<std::string> _bc_types;

    int Dimension;
    std::string Cycle_Type; // FMG or V
    std::string Restriction_opt; // full_weight, linear
    std::string Interpolation_opt; // lenear, quadratic
    int Max_Iteration;
    NUM Accuracy;

    Multigrid_BVP_Problem() : 
        Domain_Border({0, 1, 0, 1}), Domain_Type("Regular"), Max_Iteration(20), Accuracy(1e-10), Need_Error(0) {}
    
    REGISTER_SERIALIZATION_JSON(BC_Type, Domain_Type, Domain_Border, Dimension, Restriction_opt, Interpolation_opt, Cycle_Type,
                    Grid_n, f, g, mixed_g, Need_Error, answer, Max_Iteration, Accuracy);
    
    void _self_checked () {
        if(Cycle_Type != "FMG" && Cycle_Type != "V") throw "Cycle Type not defined.";
        if(Restriction_opt != "full_weight" && Restriction_opt != "injection") throw "Restriction Opt not defined.";
        if(Interpolation_opt != "linear" && Interpolation_opt != "quadratic") throw "Interpolation Opt not defined.";
        if(Dimension != 1 && Dimension != 2) throw "Dimension not defined.";
        if(BC_Type != "mixed" && BC_Type != "Neumann" && BC_Type != "Dirichlet") throw "Boundary Condition Type not defined.";
        if(Domain_Type != "Regular" && Domain_Type != "Irregular") throw "Domain Type not defined.";
        if(Grid_n < 2) throw "Grid number shall be more than 1";
        getDomain();
        // inner domain laplace function
        F.set(f);
        // error
        if(Need_Error) Answer.set(answer);
        // BC
        _bc_types.clear();
        if(BC_Type == "mixed") {
            if(!mixed_g.count("left") || !mixed_g.count("right"))
                throw "Boundary conditions missed.";
            G.push_back(func(mixed_g["left"].second));
            G.push_back(func(mixed_g["right"].second));
            if(Dimension == 2) {
                if(!mixed_g.count("up") || !mixed_g.count("down"))
                    throw "Boundary conditions missed.";
                G.push_back(func(mixed_g["up"].second));
                G.push_back(func(mixed_g["down"].second));
            }
            _bc_types.push_back(mixed_g["left"].first);
            _bc_types.push_back(mixed_g["right"].first);
            if(Dimension == 2) {
                _bc_types.push_back(mixed_g["up"].first);
                _bc_types.push_back(mixed_g["down"].first);
            }
        }
        else {
            if(g.count("all")) { // Neumann/Dirichlet -> give only one function
                g["left"] = g["right"] = g["all"];
                if(Dimension == 2) g["up"] = g["down"] = g["all"];
                g.erase("all");
            }
            for(int i = 0; i < 2 * Dimension; ++i)
                _bc_types.push_back(BC_Type);
            if(!g.count("left") || !g.count("right"))
                throw "Boundary conditions missed.";
            if(Dimension == 2 && (!g.count("up") || !g.count("down")))
                throw "Boundary conditions missed.";
            G.push_back(func(g["left"]));
            G.push_back(func(g["right"]));
            if(Dimension == 2) {
                G.push_back(func(g["up"]));
                G.push_back(func(g["down"]));
            }
        }
    }

    void print() const {
        cerr << "----------------- BVP Problem Setting ------------------\n";
        cerr << "Boundary Condition Type : " << BC_Type << "\n";
        cerr << "Domain Type : " << Domain_Type << "\n";
        cerr << "Domain Border : " << Domain_Border << "\n";
        cerr << "Grid number : " << Grid_n; if(Dimension == 2) cerr << " x " << Grid_n; cerr << "\n";
        cerr << "Restriction Operator Type : " << Restriction_opt << "\n";
        cerr << "Interpolation Operator Type : " << Interpolation_opt << "\n";
        cerr << "Cycle Type : " << Cycle_Type << "\n";
        cerr << "f : " << f << "\n";
        cerr << "g : ";
        /*************** print g *****************/
        if(g.count("all")) {
            if(BC_Type == "mixed") cerr << "[ " << mixed_g.at("all").first << " , " << mixed_g.at("all").second << " ]\n";
            else cerr << g.at("all") << "\n";
        } else {
            cerr << "{\n";
            if(BC_Type == "mixed") {
                for(auto [x, y] : mixed_g) {
                    cerr << "     " << x << " : " << y << "\n";
                }
            } else {
                for(auto [x, y] : g) {
                    cerr << "     " << x << " -> " << y << "\n";
                }
            }
            cerr << "}\n";
        }
        cerr << "Maximum Iteration : " << Max_Iteration << "\n";
        cerr << "Accuracy of Cycles Part : " << Accuracy << "\n";
        if(Need_Error) {
            cerr << "Need to analysis error of this problem.\n";
            cerr << "The true answer is : " << answer << "\n";
        }
        cerr << "--------------------------------------------------------\n";
    }
};

enum Position { lef, rig, up, down };

class Regular_Multigrid_BVPsolver;
class Irregular_Multigrid_BVPsolver;
class Multigrid_BVPsolver {
    Multigrid_BVP_Problem prob;
public:
    void readProblem(const std::string file) {
        Multigrid_BVP_Problem newProb;
        deserialize_Json(newProb, file);
        try {
            newProb._self_checked();
        } catch (char const * e) {
            cerr << e << "\n";
            exit(-1);
        }
        prob = newProb;
    }
    void printProblem() const {
        prob.print();
    }
    void solveProblem(bool print = 0);
    void solveProblem(const Multigrid_BVP_Problem &_prob) {
        prob = _prob;
        solveProblem();
    }
    void solveProblem(std::string File, bool print = 0) {
        readProblem(File);
        if(print) printProblem();
        solveProblem(print); 
    }
    NUM norm1, norm2, normi;
    void Summary();
};

class Jacobi_Iteration {
    SparseMat<NUM> T, nD;
    Vec<NUM> c;
    NUM w;
    int n;
public:
    SparseMat<NUM> A;
    Jacobi_Iteration(const SparseMat<NUM>&_A, const int& _n, const NUM& _w = 2.0/3.0) : 
                     A(_A), w(_w), n(_n), T(-_A), nD(_n+1) {
                        for(int i = 0; i <= n; ++i) {
                            T[i][i] = 0;
                            nD[i][i] = 1.0 / _A[i][i];
                            T[i] = T[i] * nD[i][i];
                        }
                     }
    void GoIter(Vec<NUM> &x, const Vec<NUM>& b, int iter = 1) {
        c = nD * b;
        Vec<NUM> y;
        for(int i = 0; i < iter; ++i) {
            y = T * x + c;
            x = w * y + (1-w) * x;
        }
    }
};

using namespace norm;

class Regular_Multigrid_BVPsolver {
    const Multigrid_BVP_Problem& prob;
    int n;
    std::vector<Jacobi_Iteration> cal;
    map<int,int> calid;
    Vec<NUM> u, b;
    Vec<NUM> Interpolation(const Vec<NUM>& x, const int N) {
        Vec<NUM> ret;
        if(prob.Dimension == 1) {
            ret.resize(N<<1|1);
            if(prob.Interpolation_opt == "linear") {
                for(int i = 0; i < ret.size; ++i) {
                    if(i&1) ret[i] = 0.5*(x[i>>1] + x[(i>>1)+1]);
                    else ret[i] = x[i>>1];
                }
            } else { // prob.Interpolation_opt == "quadratic"
                for(int i = 0; i < ret.size; ++i) {
                    if(i&1) {
                        int j = i/2;
                        if(i == 1) ret[i] = (3*x[j]+6*x[j+1]-x[j+2])/8.0;
                        else if(i == (N<<1)-1) ret[i] = (3*x[j+1]+6*x[j]-x[j-1])/8.0;
                        else ret[i] = (-x[j-1]+9*x[j]+9*x[j+1]-x[j+2])/16.0;
                    }
                    else ret[i] = x[i>>1];
                }
            }
        } else {
            int N2 = N<<1;
            ret.resize((N2+1)*(N2+1));
            auto ID = [](int i, int j, int N) -> int { 
                return j * (N+1) + i; 
            }; // for 2d function
            if(prob.Interpolation_opt == "linear") {
                for(int i = 0; i <= N2; ++i)
                for(int j = 0; j <= N2; ++j) {
                    int I = i>>1, J = j>>1;
                    if((i&1) && (j&1)) ret[ID(i, j, N2)] = 0.25 * (
                        x[ID(I, J, N)] + x[ID(I+1, J, N)] + x[ID(I+1, J+1, N)] + x[ID(I, J+1, N)]);
                    else if(i&1) ret[ID(i, j, N2)] = 0.5 * (x[ID(I, J, N)] + x[ID(I+1, J, N)]);
                    else if(j&1) ret[ID(i, j, N2)] = 0.5 * (x[ID(I, J, N)] + x[ID(I, J+1, N)]);
                    else ret[ID(i, j, N2)] = x[ID(I, J, N)];
                }
            } else { // prob.Interpolation_opt == "quadratic"
                for(int i = 0; i <= N2; ++i)
                for(int j = 0; j <= N2; ++j) {
                    if((~i&1)&&(~j&1)) ret[ID(i, j, N2)] = x[ID(i>>1, j>>1, N)];
                    else if(~i&1) {
                        int I = i>>1, J = j>>1;
                        if(j == 1) ret[ID(i, j, N2)] = (3*x[ID(I, J, N)]+6*x[ID(I, J+1, N)]-x[ID(I, J+2, N)])/8.0;
                        else if(j == N2-1) ret[ID(i, j, N2)] = (3*x[ID(I, J+1, N)]+6*x[ID(I, J, N)]-x[ID(I, J-1, N)])/8.0;
                        else ret[ID(i, j, N2)] = (-x[ID(I, J-1, N)]+9*x[ID(I, J, N)]+9*x[ID(I, J+1, N)]-x[ID(I, J+2, N)])/16.0;
                    } else if(~j&1) {
                        int I = i>>1, J = j>>1;
                        if(i == 1) ret[ID(i, j, N2)] = (3*x[ID(I, J, N)]+6*x[ID(I+1, J, N)]-x[ID(I+2, J, N)])/8.0;
                        else if(i == N2-1) ret[ID(i, j, N2)] = (3*x[ID(I+1, J, N)]+6*x[ID(I, J, N)]-x[ID(I-1, J, N)])/8.0;
                        else ret[ID(i, j, N2)] = (-x[ID(I-1, J, N)]+9*x[ID(I, J, N)]+9*x[ID(I+1, J, N)]-x[ID(I+2, J, N)])/16.0;
                    } else {
                        int I = i>>1, J = j>>1, cnt = 0, id = ID(i, j, N2);
                        if(J + 2 <= N) { cnt += 8;
                            ret[id] += (4*x[ID(I,J+1,N)]+4*x[ID(I+1,J,N)]+2*x[ID(I+1,J+1,N)]-x[ID(I,J+2,N)]-x[ID(I+1,J+2,N)]);
                        }
                        if(I - 1 >= 0) { cnt += 8;
                            ret[id] += (4*x[ID(I,J,N)]+4*x[ID(I+1,J+1,N)]+2*x[ID(I,J+1,N)]-x[ID(I-1,J,N)]-x[ID(I-1,J+1,N)]);
                        }
                        if(J - 1 >= 0) { cnt += 8;
                            ret[id] += (4*x[ID(I,J+1,N)]+4*x[ID(I+1,J,N)]+2*x[ID(I,J,N)]-x[ID(I,J-1,N)]-x[ID(I+1,J-1,N)]);
                        }
                        if(I + 2 <= N) { cnt += 8;
                            ret[id] += (4*x[ID(I,J,N)]+4*x[ID(I+1,J+1,N)]+2*x[ID(I+1,J,N)]-x[ID(I+2,J,N)]-x[ID(I+2,J+1,N)]);
                        }
                        ret[id] /= (NUM)cnt;
                    }
                }
            }
        }
        return ret;
    }
    Vec<NUM> Restriction(const Vec<NUM>& x, const int N) {
        Vec<NUM> ret;
        if(prob.Dimension == 1) {
            ret.resize((N>>1)+1);
            if(prob.Restriction_opt == "injection") {
                for(int i = 0; i < ret.size; ++i) {
                    ret[i] = x[i<<1];
                }
            } else { // prob.Restriction_opt == "full_weight"
                ret[0] = x[0]; ret[N>>1] = x[N];
                for(int i = 1; i < ret.size-1; ++i) {
                    ret[i] = 0.25*(x[(i<<1)-1]+2*x[i<<1]+x[i<<1|1]);
                }
            }
        } else {
            auto ID = [](int i, int j, int N) -> int { 
                return j * (N+1) + i; 
            }; // for 2d function
            int N2 = N>>1;
            ret.resize((N2+1)*(N2+1));
            if(prob.Restriction_opt == "injection") {
                for(int j = 0; j <= N2; ++j) 
                for(int i = 0; i <= N2; ++i) 
                    ret[ID(i, j, N2)] = x[ID(i<<1, j<<1, N)];
            } else { // prob.Restriction_opt == "full_weight"
                for(int j = 0; j <= N2; ++j) 
                for(int i = 0; i <= N2; ++i) {
                    if((i == 0 || i == N2) && (j == 0 || j == N2)) {
                        ret[ID(i, j, N2)] = x[ID(i<<1, j<<1, N)];
                    } else if(i == 0 || i == N2) {
                        ret[ID(i, j, N2)] = 0.25 * (2*x[ID(i<<1,j<<1,N)]+x[ID(i<<1,(j<<1)-1,N)]+x[ID(i<<1,j<<1|1,N)]);
                    } else if(j == 0 || j == N2) {
                        ret[ID(i, j, N2)] = 0.25 * (2*x[ID(i<<1,j<<1,N)]+x[ID((i<<1)-1,j<<1,N)]+x[ID(i<<1|1,j<<1,N)]);
                    } else {
                        int I = i<<1, J = j<<1;
                        ret[ID(i, j, N2)] = (
                            x[ID(I-1,J-1,N)] + 2*x[ID(I,J-1,N)] + x[ID(I+1,J-1,N)]
                           +2*x[ID(I-1,J,N)] + 4*x[ID(I,J  ,N)] + 2*x[ID(I+1,J,N)]
                           +x[ID(I-1,J+1,N)] + 2*x[ID(I,J+1,N)] + x[ID(I+1,J+1,N)]
                        )/16.0;
                    }
                }
            }
        }
        return ret;
    }
    void VC(Vec<NUM> &vh, const Vec<NUM> &fh, const int nu1, const int nu2, const int N) {
        int id = calid[N];
        cal[id].GoIter(vh, fh, nu1);
        if(N > 2) {
            Vec<NUM> f2h = Restriction((fh - cal[id].A * vh), N);
            Vec<NUM> v2h(prob.Dimension==1?N/2+1:(N/2+1)*(N/2+1));
            VC(v2h, f2h, nu1, nu2, N/2);
            vh = vh + Interpolation(v2h, N/2);
        }
        cal[id].GoIter(vh, fh, nu2);
    }
    void FMG(Vec<NUM> &vh, const Vec<NUM> &fh, const int nu1, const int nu2, const int N) {
        int id = calid[N];
        if(N > 2) {
            Vec<NUM> f2h = Restriction(fh, N);
            Vec<NUM> v2h(prob.Dimension==1?N/2+1:(N/2+1)*(N/2+1));
            FMG(v2h, f2h, nu1, nu2, N/2);
            vh = Interpolation(v2h, N/2);
        }
        VC(vh, fh, nu1, nu2, N);
    }
public:
    Regular_Multigrid_BVPsolver(Multigrid_BVP_Problem& _) : prob(_) {}
    void solve() {
        n = prob.Grid_n; int len = (n+1)*(prob.Dimension==2?n+1:1);
        if(prob.Dimension == 1) sol1();
        if(prob.Dimension == 2) sol2();
        for(int iter = 0; iter < prob.Max_Iteration; ++iter) {
            Vec<NUM> v(len);
            if(prob.Cycle_Type == "V") {
                VC(v, b, 5, 5, n);
            } else {
                FMG(v, b, 5, 5, n);
            }
            u = u + v;
            b = b - cal[0].A * v;
            if(Norm2Vec(v) < prob.Accuracy) break;
        }
    }
    void sol1() {
        NUM l = prob.xl, r = prob.xr, h = prob.h;
        b.resize(n+1); u.resize(n+1);
        for(int N = n; N >= 2; N >>= 1) {
            SparseMat<NUM> A(N+1, N+1);
            if(prob._bc_types[lef] == "Dirichlet") {
                A[0][0] = 1;
            } else {
                A[0][0] = 1.5 * N;
                A[0][1] = -2 * N;
                A[0][2] = 0.5 * N;
            }
            if(prob._bc_types[rig] == "Dirichlet") {
                A[N][N]= 1;
            } else {
                A[N][N  ] = 1.5 * N;
                A[N][N-1] = -2 * N;
                A[N][N-2] = 0.5 * N;
            }
            for(int i = 1; i < N; ++i) {
                A[i][i] = 2 * N * N;
                A[i][i-1] = -1 * N * N;
                A[i][i+1] = -1 * N * N;
            }
            cal.push_back(Jacobi_Iteration(A, N, 2.0/3.0));
            calid[N] = cal.size() - 1;
        }
        b[0] = prob.G[lef](l);
        b[n] = prob.G[rig](r);
        for(int i = 1; i < n; ++i) b[i] = prob.F(l + i * h);
    }
    void sol2() {
        bool isd[4];
        for(int i = 0; i < 4; ++i) isd[i] = prob._bc_types[i] == "Dirichlet";
        
        pair<Position, bool> cho[4];
        cho[0] = cho[2] = {lef, 0};
        cho[1] = cho[3] = {rig, 0};
        if(isd[lef]) cho[0] = cho[2] = {lef, 1};
        if(isd[rig]) cho[1] = cho[3] = {rig, 1};
        if(isd[up])  cho[2] = cho[3] = {up,  1};
        if(isd[down])cho[0] = cho[1] = {down,1};

        NUM xl = prob.xl, yl = prob.yl, h = prob.h;
        NUM xr = prob.xr, yr = prob.yr;
        b.resize((n+1)*(n+1));
        u.resize((n+1)*(n+1));
        auto ID = [](int i, int j, int N) -> int { 
            return j * (N+1) + i; 
        }; // for 2d function
        for(int N = n; N >= 2; N >>= 1) {
            SparseMat<NUM> A((N+1)*(N+1));
            for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
                if(i == 0 || i == N || j == 0 || j == N) {
                    int id0 = ID(i, j, N), id1, id2;
                    pair<Position, bool> _;
                    if     (i == 0 && j == 0) _ = cho[0];
                    else if(i == N && j == 0) _ = cho[1];
                    else if(i == 0 && j == N) _ = cho[2];
                    else if(i == N && j == N) _ = cho[3];
                    else if(i == 0) _ = {lef, isd[lef]};
                    else if(i == N) _ = {rig, isd[rig]};
                    else if(j == 0) _ = {down,isd[down]};
                    else /*j == n*/ _ = {up,  isd[up]};
                    if(_.second) A[id0][id0] = 1;
                    else {
                        id1 = ID(i+(_.first==lef)-(_.first==rig), j+(_.first==down)-(_.first==up), N);
                        id2 = ID(i+2*(_.first==lef)-2*(_.first==rig), j+2*(_.first==down)-2*(_.first==up), N);
                        A[id0][id0] = 1.5 * N;
                        A[id0][id1] = -2 * N;
                        A[id0][id2] = 0.5 * N;
                    }
                }
                else {
                    int id = ID(i, j, N);
                    A[id][ID(i, j, N)] = 4 * N * N;
                    A[id][ID(i-1,j,N)] = - N * N;
                    A[id][ID(i+1,j,N)] = - N * N;
                    A[id][ID(i,j-1,N)] = - N * N;
                    A[id][ID(i,j+1,N)] = - N * N;
                }
            }
            cal.push_back(Jacobi_Iteration(A, (N+1)*(N+1)-1, 2.0/3.0));
            calid[N] = cal.size() - 1;
        }
        for(int i = 1; i < n; ++i) for(int j = 1; j < n; ++j)
            b[ID(i, j, n)] = prob.F(xl+i*h, yl+j*h);
        for(int i = 1; i < n; ++i) {
            b[ID(0, i, n)] = prob.G[lef](xl, yl+i*h);
            b[ID(n, i, n)] = prob.G[rig](xr, yl+i*h);
            b[ID(i, 0, n)] = prob.G[down](xl+i*h, yl);
            b[ID(i, n, n)] = prob.G[up](xl+i*h, yr);
        }
        b[ID(0, 0, n)] = prob.G[cho[0].first](xl, yl);
        b[ID(n, 0, n)] = prob.G[cho[1].first](xr, yl);
        b[ID(0, n, n)] = prob.G[cho[2].first](xl, yr);
        b[ID(n, n, n)] = prob.G[cho[3].first](xr, yr);
    }
    tuple<NUM,NUM,NUM> ErrorAnalysis(bool show) {
        Vec<NUM> err;
        if(prob.Dimension == 1) {
            err.resize(u.size);
            for(int i = 0; i <= prob.Grid_n; ++i) {
                err[i] = fabs(prob.Answer(prob.xl + i * prob.h) - u[i]);
            }
        } else if(prob.Dimension == 2) {
            err.resize(u.size - 4);
            int id = 0, ido = 0;
            for(int j = 0; j <= prob.Grid_n; ++j) 
                for(int i = 0; i <= prob.Grid_n; ++i) {
                    if((i == 0 || i == prob.Grid_n) && (j == 0 || j == prob.Grid_n)) { ido++; continue;}
                    err[id++] = fabs(prob.Answer(prob.xl+i*prob.h, prob.yl+j*prob.h) - u[ido++]);
                }
        }
        if(prob.BC_Type == "Neumann") {
            NUM av = avg(err);
            for(auto & x : err) x -= av;
        }
        return {Norm1Vec(err), Norm2Vec(err), NormiVec(err)};
    }
};

void Multigrid_BVPsolver::solveProblem(bool show) {
    if(this->prob.Domain_Type == "Regular") {
        Regular_Multigrid_BVPsolver solver(this->prob);
        solver.solve();
        if(this->prob.Need_Error == 1) {
            auto [_norm1, _norm2, _normi] = solver.ErrorAnalysis(show);
            this->norm1 = _norm1;
            this->norm2 = _norm2;
            this->normi = _normi;
            if(show) this->Summary();
        }
    } else {
        // not implement yet.
    }
}

void Multigrid_BVPsolver::Summary() { // call after solveProblem!
    if(this->prob.Need_Error == 1) {
        std::cerr << "Error norm-1   : " << fixed << setprecision(10) << this->norm1 << std::endl;
        std::cerr << "Error norm-2   : " << fixed << setprecision(10) << this->norm2 << std::endl;
        std::cerr << "Error norm-inf : " << fixed << setprecision(10) << this->normi << std::endl;
        std::cerr.unsetf(ios::floatfield);
    }
}

#endif