#ifndef MULTIGRID_BVP_SOLVER
#define MULTIGRID_BVP_SOLVER

#include <bits/stdc++.h>
#include "function.hpp"
#include "calculator.hpp"
#include "serialization.hpp"
#include "function_generator/ExecCode2.hpp"
#include "IO.hpp"
#include "linear.hpp"

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
                                     /* 1,    2,     3,  0*/
    vector<func> G;
    // mixed
    map<std::string, pair<std::string, std::string>> mixed_g; /* left, right, up, down -> function*/
                                                              /* 2,    3,     4,  1 */
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
        if(Restriction_opt != "full_weight" && Restriction_opt != "linear") throw "Restriction Opt not defined.";
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
            for(auto [x, y] : mixed_g) {
                g[x] = y.second;
            }
        }
        if(g.count("all")) { // Neumann/Dirichlet -> give only one function
            g["left"] = g["right"] = g["up"] = g["down"] = g["all"];
            if(BC_Type == "mixed") {
                for(int i = 0; i < 3; ++i) _bc_types.push_back(_bc_types[0]);
            }
        }
        if(BC_Type != "mixed") {
            for(int i = 0; i < 4; ++i)
                _bc_types.push_back(BC_Type);
        }
        if(!g.count("left") || !g.count("right") || !g.count("up") || !g.count("down"))
            throw "Boundary conditions missed.";
        G.push_back(func(g["down"]));
        G.push_back(func(g["left"]));
        G.push_back(func(g["right"]));
        G.push_back(func(g["up"]));
    }

    void print() const {
        cerr << "----------------- BVP Problem Setting ------------------\n";
        cerr << "Boundary Condition Type : " << BC_Type << "\n";
        cerr << "Domain Type : " << Domain_Type << "\n";
        cerr << "Domain Border : " << Domain_Border << "\n";
        cerr << "Grid number : " << Grid_n << " x " << Grid_n << "\n";
        cerr << "Restriction Operator Type : " << Restriction_opt << "\n";
        cerr << "Interpolation Operator Type : " << Interpolation_opt << "\n";
        cerr << "Cycle Type" << Cycle_Type << "\n";
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
                    cerr << "\t" << x << " : " << y << "\n";
                }
            } else {
                for(auto [x, y] : g) {
                    cerr << "\t" << x << " -> " << y << "\n";
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

enum Position { down, lef, rig, up };

class Multigrid_BVPsolver {
    Multigrid_BVP_Problem prob;
    class Regular_Multigrid_BVPsolver;
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

class Multigrid_BVPsolver::Regular_Multigrid_BVPsolver {
    Multigrid_BVP_Problem& prob;
public:
    Regular_Multigrid_BVPsolver(Multigrid_BVP_Problem& _) : prob(_) {}
    void solve() {
        if(prob.Dimension == 1) sol1();
        if(prob.Dimension == 2) sol2();
    }
    void sol1() {}
    void sol2() {}
    tuple<NUM,NUM,NUM> ErrorAnalysis(bool show) {
        NUM norm1, norm2, normi;
        if(prob.Dimension == 1) {

        } else if(prob.Dimension == 2) {

        }
        return {norm1, norm2, normi};
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