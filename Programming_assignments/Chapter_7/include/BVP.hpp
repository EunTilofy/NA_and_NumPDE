#ifndef BVP_SOLVER
#define BVP_SOLVER

#include <bits/stdc++.h>
#include "function.hpp"
#include "calculator.hpp"
#include "serialization.hpp"
#include "function_generator/ExecCode2.hpp"
#include "IO.hpp"

using namespace std;

const double eps = 1e-10;

double dis(pair<double, double> x, pair<double, double> y) {
    return sqrt(sq(x.first - y.first) + sq(x.second - y.second));
}

class func2D : Function2D<double, double> {
    FromString<double, double> getvalue;
public:
    func2D (const std::string &_str) : getvalue(_str) {}
    func2D () : getvalue() {}
    void set(const std::string &_str) { getvalue = FromString<double, double>(_str); }
    double operator() (const double &x, const double &y) const {
        double xx = x, yy = y;
        return getvalue.cal2({{"x", xx}, {"y", yy}});
    }
};

enum Position { left, right, up, down, D };
class Square_BVP_Problem{
public:
    // common
    // Support : 1. Regular; 2. Irregular(with a circle not in the reigeon)
    std::string BC_Type; /* boundary condition : mixed, Dirichlet, Neumann*/
    std::string Domain_Type; /* regular irregular*/
    vector<double> Domain_Border; /* [xl, xr, yl, yr] */
    double xl, xr, yl, yr, h;
    void getDomain() {
        if(Domain_Border.size() < 4) { throw "Domain Border not satisfiable."; }
        xl = Domain_Border[0];
        xr = Domain_Border[1];
        yl = Domain_Border[2];
        yr = Domain_Border[3];
        if((xr - xl) > (yr - yl) + eps || (xr - xl) < (yr - yl) - eps)
            throw "Domain Border not a square.";
        xr = (yr - yl) + xl;
        h = (xr - xl) / Grid_n;
        if(xl > xr + eps || yl > yr + eps) throw "Illegal Domain.";
    }
    bool inBorder(double x, double y) {
        return (x >= xl && x <= xr) && (y >= yl && y <= yr);
    }
    int Grid_n; /* Grid_n x Grid_n */
    std::string f; /* - \Delta u (in Domain)*/
    func2D F;

    // Irregular
    std::pair<double, double> Center; double cx, cy;
    double R;
    bool inCircle(double x, double y) {
        return (dis({x, y}, Center) < R);
    }
    void checkDomain() {
        cx = Center.first; cy = Center.second;
        if(!inBorder(cx, cy)) throw "Illegal Domain.";
        double u, d, l, r;
        u = xl + h * floor((cx - xl) / h);
        d = u + h;
        l = yl + h * floor((cy - yl) / h);
        r = l + h;
        if(!inCircle(u, l) || !inCircle(u, r) || !inCircle(d, l) || !inCircle(d, r)) 
            throw "Illegal Domain : less than 4 grid points in D.";
        if((cx + R > xr) + (cx - R < xl) + (cy + R > yr) + (cy - R < yl) > 1) 
            throw "Illegal Domain : not continuous.";
    }
    bool inDomain(double x, double y) {
        return inDomain(x, y) && !inCircle(x, y);
    }

    // calculate error
    bool Need_Error;
    std::string answer;
    func2D Answer;

    // Boundary Condition
    // Dirichlet / Neumann
    map<std::string, std::string> g; /* left, right, up, down, D -> function*/
                                     /* 2,    3,     4,  1,    0*/
    vector<func2D> G;
    // mixed
    map<std::string, pair<std::string, std::string>> mixed_g; /* left, right, up, down, D -> function*/
                                                              /* 2,    3,     4,  1,    0*/
    vector<std::string> _bc_types;

    Square_BVP_Problem() : Center({0, 0}), R(-1) {}
    void _self_checked () {
        getDomain();
        if(Domain_Type == "Irregular") checkDomain();

        // inner domain laplace function
        F.set(f);

        // error
        if(Need_Error) Answer.set(answer);

        // BC
        if(BC_Type == "mixed") {
            for(auto [x, y] : mixed_g) g[x] = y.second, _bc_types.push_back(y.first);
        }
        if(g.count("all")) { // Neumann/Dirichlet -> give only one function
            g["left"] = g["right"] = g["up"] = g["down"] = g["D"] = g["all"];
            if(BC_Type == "mixed") {
                for(int i = 0; i < 4; ++i) _bc_types.push_back(_bc_types[0]);
            }
        }
        if(!g.count("left") || !g.count("right") || !g.count("up") || !g.count("down"))
            throw "Boundary conditions missed.";
        if(Domain_Type == "Irregular") {
            if(!g.count("D")) throw "Boundary conditions missed.";
            G.push_back(g["D"]);
        }
        G.push_back(func2D(g["down"]));
        G.push_back(func2D(g["left"]));
        G.push_back(func2D(g["right"]));
        G.push_back(func2D(g["up"]));
    }

    void print() const {
        cerr << "----------------- BVP Problem Setting ------------------\n";
        cerr << "Boundary Condition Type : " << BC_Type << "\n";
        cerr << "Domain Type : " << Domain_Type << "\n";
        cerr << "Domain Border : " << Domain_Border << "\n";
        cerr << "Grid number : " << Grid_n << " x " << Grid_n << "\n";
        if(Domain_Type == "Irregular") {
        cerr << "D : { Center : " << Center << " , R : " << R << " }\n";
        }
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
        if(Need_Error) {
            cerr << "Need to analysis error of this problem.\n";
            cerr << "The true answer is : " << answer << "\n";
        }
        cerr << "--------------------------------------------------------\n";
    }

    REGISTER_SERIALIZATION_JSON(BC_Type, Domain_Type, Domain_Border, 
                    Grid_n, Center, R, f, g, mixed_g, Need_Error, answer);
};

class Square_BVPsolver {
    Square_BVP_Problem prob;
public:
    void readProblem(const std::string file) {
        Square_BVP_Problem newProb;
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

    void solveProblem() {
        if(prob.Domain_Type == "Regular") {
            // 
        } else {
            // 
        }
    }
    
};

#endif