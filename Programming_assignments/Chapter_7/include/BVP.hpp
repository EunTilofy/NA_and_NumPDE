#ifndef BVP_SOLVER
#define BVP_SOLVER

#include <bits/stdc++.h>
#include "function.hpp"
#include "calculator.hpp"
#include "serialization.hpp"
#include "function_generator/ExecCode2.hpp"
#include "ProgressBar.hpp"
#include "IO.hpp"
#include "linear.hpp"

using namespace std;

const double eps = 1e-10;

double dis(pair<double, double> x, pair<double, double> y) {
    return sqrt((x.first - y.first)*(x.first - y.first)
              + (x.second - y.second)*(x.second - y.second));
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

class Square_BVP_Problem{
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
    void checkDomain() {
        double cx, cy;
        cx = Center.first; cy = Center.second;
        if(!inBorder(cx, cy)) throw "Illegal Domain.";
        double u, d, l, r;
        u = xl + h * floor((cx - xl) / h);
        d = u + h;
        l = yl + h * floor((cy - yl) / h);
        r = l + h;
        if(!inCircle(u, l) || !inCircle(u, r) || !inCircle(d, l) || !inCircle(d, r)) 
            throw "Illegal Domain : less than 4 grid points in D.";
        if((cx + R >= xr) + (cx - R <= xl) + (cy + R >= yr) + (cy - R <= yl)) 
            throw "Illegal Domain : Circle not [in] the domain.";
        if((cx + R + h*2 + 1e-8 >= xr) + (cx - R - h*2 - 1e-8 <= xl) + 
            (cy + R + h*2 + 1e-8 >= yr) + (cy - R - h*2 - 1e-8 <= yl)) {
                std::cerr << "[warning] the circle is too near to the border, we may use another method to solve your problem.\n";
                use_old = 1;
            }
    }
public:
    // common
    // Support : 1. Regular; 2. Irregular(with a circle not in the reigeon)
    std::string BC_Type; /* boundary condition : mixed, Dirichlet, Neumann*/
    std::string Domain_Type; /* regular irregular*/
    vector<double> Domain_Border; /* [xl, xr, yl, yr] */
    double xl, xr, yl, yr, h;

    bool inBorder(double x, double y) const {
        return (x >= xl && x <= xr) && (y >= yl && y <= yr);
    }
    int Grid_n; /* Grid_n x Grid_n */
    std::string f; /* - \Delta u (in Domain)*/
    func2D F;

    // Irregular
    std::pair<double, double> Center;
    double R;
    bool inCircle(double x, double y) const {
        return (dis({x, y}, Center) < R);
    }
    bool use_old;
    bool inDomain(double x, double y) const {
        return inBorder(x, y) && !inCircle(x, y);
    }

    // calculate error
    bool Need_Error;
    std::string answer;
    func2D Answer;

    // Boundary Condition
    // Dirichlet / Neumann
    map<std::string, std::string> g; /* left, right, up, down, D -> function*/
                                     /* 1,    2,     3,  0,    4*/
    vector<func2D> G;
    // mixed
    map<std::string, pair<std::string, std::string>> mixed_g; /* left, right, up, down, D -> function*/
                                                              /* 2,    3,     4,  1,    0*/
    vector<std::string> _bc_types;

    Square_BVP_Problem() : Center({0, 0}), R(-1), use_old(0) {}
    void _self_checked () {
        getDomain();
        if(Domain_Type == "Irregular") checkDomain();
        // inner domain laplace function
        F.set(f);
        // error
        if(Need_Error) Answer.set(answer);
        // BC
        _bc_types.clear();
        if(BC_Type == "mixed") {
            for(auto [x, y] : mixed_g) {
                g[x] = y.second;
                if(x != "D") _bc_types.push_back(y.first);
            }
            if(mixed_g.count("D")) _bc_types.push_back(mixed_g["D"].first);
        }
        if(g.count("all")) { // Neumann/Dirichlet -> give only one function
            g["left"] = g["right"] = g["up"] = g["down"] = g["D"] = g["all"];
            if(BC_Type == "mixed") {
                for(int i = 0; i < 4; ++i) _bc_types.push_back(_bc_types[0]);
            }
        }
        if(BC_Type != "mixed") {
            for(int i = 0; i < 4 + (Domain_Type == "Irregular"); ++i)
                _bc_types.push_back(BC_Type);
        }
        if(!g.count("left") || !g.count("right") || !g.count("up") || !g.count("down"))
            throw "Boundary conditions missed.";
        if(Domain_Type == "Irregular" && !g.count("D"))
            throw "Boundary conditions missed.";
        G.push_back(func2D(g["down"]));
        G.push_back(func2D(g["left"]));
        G.push_back(func2D(g["right"]));
        G.push_back(func2D(g["up"]));
        if(Domain_Type == "Irregular") {
            if(!g.count("D")) throw "Boundary conditions missed.";
            G.push_back(g["D"]);
        }
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

enum Position { down, lef, rig, up, Cir };
typedef std::vector<std::pair<pair<double, double>, double>> RES;

class Square_BVPsolver {
    Square_BVP_Problem prob;
    class Regular_Square_BVPsolver;
    class Irregular_Square_BVPsolver;
    class Irregular_Square_BVPsolver_2;
    RES results;
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
    void solveProblem(bool print = 0);
    void solveProblem(const Square_BVP_Problem &_prob) {
        prob = _prob;
        solveProblem();
    }
    void solveProblem(std::string File, bool print = 0) {
        readProblem(File);
        if(print) printProblem();
        solveProblem(print); 
    }
    void saveResults(std::string file = "res.csv") const {
        ofstream OUT(file);
        if(!OUT.is_open()) {
            throw "[Error] open file " + file;
            return;
        }
        for(auto [x, y]: results) {
            OUT << x.first << "," << x.second << "," << y << std::endl;
        }
        OUT.close();
    }
    double norm1, norm2, normi;
    void Summary();
};

class Square_BVPsolver::Regular_Square_BVPsolver {
    int N;
    vector<pair<Point, bool>> nodes; /* nodes & if it is extended*/
    Vec<double> U;
    map<pair<int,int>, int> nodeID; // the position in 'nodes'
    bool allNeumann, isn[4];
public:
    void solve(const Square_BVP_Problem& p, ProgressBar &pro) {
        N = p.Grid_n;
        { pro.addTip(">>> Adding nodes...");
            allNeumann = 0;
            for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
                if((i == 0 || i == N) && (j == 0 || j == N)) continue;
                nodes.push_back({Point(i*p.h+p.xl, j*p.h+p.yl), 0});
                nodeID[{i, j}] = nodes.size() - 1;
            }
            isn[0] = isn[1] = isn[2] = isn[3] = 0;
            if(p.BC_Type == "mixed" || p.BC_Type == "Neumann") {
                int num = 0;
                for(int i = 0; i < 4; ++i) isn[i] = (p._bc_types[i] == "Neumann");
                for(int i = 0; i < 4; ++i) if(isn[i]) {
                    ++num;
                    switch (i)
                    {
                    case down: for(int j = 1; j < N; ++j)
                        nodes.push_back({Point(p.xl+p.h*j, p.yl-p.h), 1}),
                        nodeID[{j, -1}] = nodes.size() - 1;
                        break;
                    case up: for(int j = 1; j < N; ++j) 
                        nodes.push_back({Point(p.xl+p.h*j, p.yr+p.h), 1}),
                        nodeID[{j, N+1}] = nodes.size() - 1;
                        break;
                    case lef: for(int j = 1; j < N; ++j)
                        nodes.push_back({Point(p.xl-p.h, p.yl+p.h*j), 1}),
                        nodeID[{-1, j}] = nodes.size() - 1;
                        break;
                    case rig: for(int j = 1; j < N; ++j) 
                        nodes.push_back({Point(p.xr+p.h, p.yl+p.h*j), 1}),
                        nodeID[{N+1, j}] = nodes.size() - 1;
                        break;
                    }
                }
                allNeumann = (num == 4);

                { // corner : when one side near it is Neumann
                    if(isn[lef] || isn[down]) {
                        nodes.push_back({Point(p.xl, p.yl), 1});
                        nodeID[{0, 0}] = nodes.size() - 1;
                    }
                    if(isn[lef] || isn[up]) {
                        nodes.push_back({Point(p.xl, p.yr), 1});
                        nodeID[{0, N}] = nodes.size() - 1;
                    }
                    if(isn[rig] || isn[down]) {
                        nodes.push_back({Point(p.xr, p.yl), 1});
                        nodeID[{N, 0}] = nodes.size() - 1;
                    }
                    if(isn[rig] || isn[up]) {
                        nodes.push_back({Point(p.xr, p.yr), 1});
                        nodeID[{N, N}] = nodes.size() - 1;
                    }
                }
                { // corner : when both sides near it is Neumann
                    if(isn[lef] && isn[down]) {
                        nodes.push_back({Point(p.xl - p.h, p.yl), 1});
                        nodeID[{-1, 0}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xl, p.yl - p.h), 1});
                        nodeID[{0, -1}] = nodes.size() - 1;
                    }
                    if(isn[lef] && isn[up]) {
                        nodes.push_back({Point(p.xl - p.h, p.yr), 1});
                        nodeID[{-1, N}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xl, p.yr + p.h), 1});
                        nodeID[{0, N+1}] = nodes.size() - 1;
                    }
                    if(isn[rig] && isn[down]) {
                        nodes.push_back({Point(p.xr + p.h, p.yl), 1});
                        nodeID[{N+1, 0}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xr, p.yl - p.h), 1});
                        nodeID[{N, -1}] = nodes.size() - 1;
                    }
                    if(isn[rig] && isn[up]) {
                        nodes.push_back({Point(p.xr + p.h, p.yr), 1});
                        nodeID[{N+1, N}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xr, p.yr + p.h), 1});
                        nodeID[{N, N+1}] = nodes.size() - 1;
                    }
                }
            }
            pro.updateTip(">>> Adding nodes... done ( " + to_string(nodes.size()) + " nodes in total. )");
            pro.updateProgress(20);
        }
        { // boundary conditions
            pro.addTip(">>> Construct linear system ...");
            Mat<double, double> A(nodes.size());
            Vec<double> b(nodes.size());

            int cnt = -1;
            auto build_equ = [&]() -> void { ++cnt; };
            auto add = [&](int i, int j, double num) { 
                custom_assert(nodeID.count({i,j}), 
                    "Equation build failed : node [" + to_string(i) + ", " + to_string(j) + "] not exists.");
                A[cnt][nodeID[{i, j}]] = num;
            };
            auto rhs = [&](double num) -> void { b[cnt] = num; };
            auto getv = [&](const func2D& f, int i, int j) -> double {
                auto no = nodes[nodeID[{i, j}]].first;
                return f(no.x, no.y);
            };
            auto Count = [&](int i, int j) -> bool { return nodeID.count({i, j}); };

            for(int i = -1; i <= N + 1; ++i) for(int j = -1; j <= N + 1; ++j) {
                if(!nodeID.count({i, j})) continue;
                if(i > 0 && i < N && j > 0 && j < N) {
                    build_equ();
                    add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                    rhs(p.h*p.h*getv(p.F, i, j));
                } else {
                    if((i == 0 || i == N) && (j == 0 || j == N)) {
                        build_equ();
                        if(i == 0 && j == 0 && allNeumann) add(i, j, 1), rhs(1);
                        else {
                        if(Count(i-1,j)&&Count(i,j-1)&&Count(i+1,j)&&Count(i,j+1)) {
                            add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                            rhs(p.h*p.h*getv(p.F, i, j));
                        } else {
                            add(i,j,1);
                            if(!isn[lef] && i == 0) rhs(getv(p.G[lef], i, j));
                            else if(!isn[rig] && i == N) rhs(getv(p.G[rig], i, j));
                            else if(!isn[up] && j == N) rhs(getv(p.G[up], i, j));
                            else if(!isn[down] && j == 0) rhs(getv(p.G[down], i, j));
                        }
                        }
                    } else if ((i == 0 || i == N || j == 0 || j == N) && (i != -1 && i != N+1 && j != -1 && j != N+1)) {
                        build_equ();
                        if((i == 0 && isn[lef]) || (i == N && isn[rig]) || (j == 0 && isn[down]) || (j == N && isn[up])) {
                            add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                            rhs(p.h*p.h*getv(p.F, i, j));
                        } else {
                            add(i,j,1), rhs(getv(p.G[i==0?lef:(i==N?rig:(j==0?down:up))],i,j));
                        }
                    } else {
                        build_equ();
                        if(i ==  -1) add(i,j,1),add(i+2,j,-1),rhs(2*p.h*getv(p.G[lef],i+1,j));
                        if(i == N+1) add(i,j,1),add(i-2,j,-1),rhs(2*p.h*getv(p.G[rig],i-1,j));
                        if(j ==  -1) add(i,j,1),add(i,j+2,-1),rhs(2*p.h*getv(p.G[down],i,j+1));
                        if(j == N+1) add(i,j,1),add(i,j-2,-1),rhs(2*p.h*getv(p.G[up],i,j-1));
                    }
                }
            }
            custom_assert(cnt+1 == nodes.size(), "Equation number does not fit variable number");
            // cout << A << "\n" << b << std::endl << std::endl;
            pro.updateProgress(40);
            pro.updateTip(">>> Construct linear system ... done");
            pro.addTip(">>> Solving linear system ...");
            U = Gauss_elimination(A, b);
            pro.updateProgress(99);
            pro.updateTip(">>> Solving linear system ... done");
        }
    }
    void get_results(const Square_BVP_Problem& p, RES& results) const {
        results.clear();
        for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
            double x = p.xl + p.h * i;
            double y = p.yl + p.h * j;
            double val = 0;
            if((i == 0 || i == N) && (j == 0 || j == N)) {
                if(nodeID.count({i, j})) val = U[nodeID.at({i, j})];
                else if(i == 0) val = p.G[lef](x, y);
                else if(i == N) val = p.G[rig](x, y);
                else if(j == 0) val = p.G[down](x, y);
                else if(j == N) val = p.G[up](x, y);
            } 
            else {
                int id = nodeID.at({i, j});
                val = U[id];
            }
            results.push_back({{x, y}, val});
        }
        return ;
    }
    double norm1, norm2, normi;
    void ErrorAnalysis(const Square_BVP_Problem& p, bool print = 1) {
        using namespace norm;
        vector<double> u, a;
        for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
            if((i == 0 || i == N) && (j == 0 || j == N)) continue;
            int id = nodeID[{i, j}];
            u.push_back(U[id]);
            a.push_back(p.Answer(nodes[id].first.x, nodes[id].first.y));
        }
        Vec<double> err = Vec(u) - Vec(a);
        if(allNeumann) {
            double _avg = avg(err);
            for(auto &x : err) x -= _avg;
            for(auto &x : U) x -= _avg;
        }
        norm1 = Norm1Vec(err); norm2 = Norm2Vec(err); normi = NormiVec(err);
        if(!print) return ;
        std::cerr << "Error norm-1   : " << fixed << setprecision(10) << norm1 << std::endl;
        std::cerr << "Error norm-2   : " << fixed << setprecision(10) << norm2 << std::endl;
        std::cerr << "Error norm-inf : " << fixed << setprecision(10) << normi << std::endl;
        std::cerr.unsetf(ios::floatfield);
    }
};

class Square_BVPsolver::Irregular_Square_BVPsolver {
    int N;
    vector<pair<Point, int>> nodes; /* nodes & if it is extended*/
    /*0:inner grid nodes             2:grid nodes in Circle
      1:grid nodes on Circle         3:nodes extended along sides
      4:intersection of vertical lines with Circle
      5:intersection of horizonal lines with Circle */
    Vec<double> U;
    map<pair<int,int>, int> nodeID; // the position in 'nodes'
    map<pair<pair<int,int>, pair<int,int>>, int> interID;
    bool allNeumann, isn[5];
    double cx, cy, R;
public:
    void solve(const Square_BVP_Problem& p, ProgressBar &pro) {
        N = p.Grid_n; cx = p.Center.first; cy = p.Center.second; R = p.R;
        auto inDomain = [&](int i, int j) -> bool { 
            if(i == 0 || j == 0 || i == N || j == N) return true;
            return p.inDomain(i*p.h+p.xl, j*p.h+p.yl); 
        };
        auto onCircle = [&](int i, int j) -> bool {
            return fabs(R - dis(p.Center, {i*p.h+p.xl, j*p.h+p.yl})) < 1e-12;
        };
        auto inCircle = [&](int i, int j) -> bool {
            return !onCircle(i, j) && p.inCircle(i*p.h+p.xl, j*p.h+p.yl);
        };
        { pro.addTip(">>> Adding nodes...");
            auto Count = [&](int i, int j) -> bool { // grid nodes [in] the border
                return nodeID.count({i, j}) && 
                       nodes[nodeID[{i,j}]].second <= 1; 
            };
            auto P = [&](int i, int j) -> Point { return Point(i*p.h+p.xl, j*p.h+p.yl); };
            auto Inter = [&](int i1, int j1, int i2, int j2, bool type) -> Point {
                double x, y;   
                if(i1 == i2) {
                    x = i1*p.h+p.xl;
                    y = sqrt(R*R-(x-cx)*(x-cx));
                    if(fabs(y)<1e-12) y = 0;
                    if(type) return Point(x, y);
                    if(max(j1,j2)*p.h+p.yl > cy) y = cy + y;
                    else y = cy - y;
                    // custom_assert((y <= p.yl+p.h*max(j1, j2) && y >= p.yl+p.h*min(j1, j2)), "Intersection not exists."); -> OK
                    return Point(x, y);
                } else {
                    y= j1*p.h+p.yl;
                    x = sqrt(R*R-(y-cy)*(y-cy));
                    if(fabs(x)<1e-12) x = 0;
                    if(type) return Point(x, y);
                    if(max(i1,i2)*p.h+p.xl > cx) x = cx + x;
                    else x = cx - x;
                    // custom_assert((x <= p.xl+p.h*max(i1, i2) && x >= p.xl+p.h*min(i1, i2)), "Intersection not exists."); -> OK
                    return Point(x, y);
                }
                custom_assert(0, "Calculate Intersection error.");
                return Point();
            };
            allNeumann = 0;
            // grid nodes inside border
            for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
                if((i == 0 || i == N) && (j == 0 || j == N)) continue;
                if(onCircle(i, j)) {
                    nodes.push_back({P(i, j), 1});
                    nodeID[{i, j}] = nodes.size() - 1;
                    continue;
                }
                if(!inDomain(i, j)) continue;
                nodes.push_back({P(i, j), 0});
                nodeID[{i, j}] = nodes.size() - 1;
            }
            // nodes on Circle : case 1 -> one side in circle and one side out
            for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) if(!Count(i,j)) {
                if((i == 0 || i == N) && (j == 0 || j == N)) continue;
                if(Count(i+1,j)||Count(i-1,j)||Count(i,j+1)||Count(i,j-1)) {
                    nodes.push_back({P(i, j), 2});
                    nodeID[{i, j}] = nodes.size() - 1;
                    if(Count(i+1,j)&&!onCircle(i+1,j)) { nodes.push_back({Inter(i+1,j,i,j,0), 5}); interID[{{i+1,j}, {i,j}}] = nodes.size() - 1; }
                    if(Count(i-1,j)&&!onCircle(i-1,j)) { nodes.push_back({Inter(i-1,j,i,j,0), 5}); interID[{{i-1,j}, {i,j}}] = nodes.size() - 1; }
                    if(Count(i,j+1)&&!onCircle(i,j+1)) { nodes.push_back({Inter(i,j+1,i,j,0), 4}); interID[{{i,j+1}, {i,j}}] = nodes.size() - 1; }
                    if(Count(i,j-1)&&!onCircle(i,j-1)) { nodes.push_back({Inter(i,j-1,i,j,0), 4}); interID[{{i,j-1}, {i,j}}] = nodes.size() - 1; }
                }
            }
            {
            // case 2 -> two intersections within a grid side
            int l = floor((cx - p.xl)/p.h), r = l + 1;
            int d = floor((cy - p.yl)/p.h), u = d + 1;
            int _L = floor((cx - R - p.xl)/p.h)+1, _R = floor((cx + R - p.xl)/p.h);
            int _D = floor((cy - R - p.yl)/p.h)+1, _U = floor((cy + R - p.yl)/p.h);
            // up
            if(cy+R>(p.yl+_U*p.h)&&!inCircle(l,_U)&&!inCircle(r,_U)) {
                Point dx = Inter(l,_U,r,_U,1);
                nodes.push_back({Point(cx-dx.x, dx.y), 5});
                nodes.push_back({Point(cx+dx.x, dx.y), 5});
            }
            // down
            if(cy-R<(p.yl+_D*p.h)&&!inCircle(l,_D)&&!inCircle(r,_D)) {
                Point dx = Inter(l,_D,r,_D,1);
                nodes.push_back({Point(cx-dx.x, dx.y), 5});
                nodes.push_back({Point(cx+dx.x, dx.y), 5});
            }
            // left
            if(cx-R<(p.xl+_L*p.h)&&!inCircle(_L,d)&&!inCircle(_L,u)) {
                Point dy = Inter(_L,d,_L,u,1);
                nodes.push_back({Point(dy.x, cy - dy.y), 4});
                nodes.push_back({Point(dy.x, cy + dy.y), 4});
            }
            // right
            if(cx+R>(p.yl+_R*p.h)&&!inCircle(_R,d)&&!inCircle(_R,u)) {
                Point dy = Inter(_R,d,_R,u,1);
                nodes.push_back({Point(dy.x, cy - dy.y), 4});
                nodes.push_back({Point(dy.x, cy + dy.y), 4});
            }
            }
            // for(auto [x, y] : nodeID) pro.addTip(to_string(x.first) + " " + to_string(x.second) + "\n");
            isn[0] = isn[1] = isn[2] = isn[3] = isn[4] = 0;
            if(p.BC_Type == "mixed" || p.BC_Type == "Neumann") {
                int num = 0;
                for(int i = 0; i < 5; ++i) num += (isn[i] = (p._bc_types[i] == "Neumann"));
                allNeumann = (num == 5);
                for(int i = 0; i < 4; ++i) if(isn[i]) {
                    switch (i)
                    {
                    case down: for(int j = 1; j < N; ++j)
                        nodes.push_back({Point(p.xl+p.h*j, p.yl-p.h), 3}),
                        nodeID[{j, -1}] = nodes.size() - 1;
                        break;
                    case up: for(int j = 1; j < N; ++j) 
                        nodes.push_back({Point(p.xl+p.h*j, p.yr+p.h), 3}),
                        nodeID[{j, N+1}] = nodes.size() - 1;
                        break;
                    case lef: for(int j = 1; j < N; ++j)
                        nodes.push_back({Point(p.xl-p.h, p.yl+p.h*j), 3}),
                        nodeID[{-1, j}] = nodes.size() - 1;
                        break;
                    case rig: for(int j = 1; j < N; ++j) 
                        nodes.push_back({Point(p.xr+p.h, p.yl+p.h*j), 3}),
                        nodeID[{N+1, j}] = nodes.size() - 1;
                        break;
                    }
                }
                { // corner : when one side near it is Neumann
                    if(isn[lef] || isn[down]) {
                        nodes.push_back({Point(p.xl, p.yl), 3});
                        nodeID[{0, 0}] = nodes.size() - 1;
                    }
                    if(isn[lef] || isn[up]) {
                        nodes.push_back({Point(p.xl, p.yr), 3});
                        nodeID[{0, N}] = nodes.size() - 1;
                    }
                    if(isn[rig] || isn[down]) {
                        nodes.push_back({Point(p.xr, p.yl), 3});
                        nodeID[{N, 0}] = nodes.size() - 1;
                    }
                    if(isn[rig] || isn[up]) {
                        nodes.push_back({Point(p.xr, p.yr), 3});
                        nodeID[{N, N}] = nodes.size() - 1;
                    }
                }
                { // corner : when both sides near it is Neumann
                    if(isn[lef] && isn[down]) {
                        nodes.push_back({Point(p.xl - p.h, p.yl), 3});
                        nodeID[{-1, 0}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xl, p.yl - p.h), 3});
                        nodeID[{0, -1}] = nodes.size() - 1;
                    }
                    if(isn[lef] && isn[up]) {
                        nodes.push_back({Point(p.xl - p.h, p.yr), 3});
                        nodeID[{-1, N}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xl, p.yr + p.h), 3});
                        nodeID[{0, N+1}] = nodes.size() - 1;
                    }
                    if(isn[rig] && isn[down]) {
                        nodes.push_back({Point(p.xr + p.h, p.yl), 3});
                        nodeID[{N+1, 0}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xr, p.yl - p.h), 3});
                        nodeID[{N, -1}] = nodes.size() - 1;
                    }
                    if(isn[rig] && isn[up]) {
                        nodes.push_back({Point(p.xr + p.h, p.yr), 3});
                        nodeID[{N+1, N}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xr, p.yr + p.h), 3});
                        nodeID[{N, N+1}] = nodes.size() - 1;
                    }
                }
            }
            pro.updateTip(">>> Adding nodes... done ( " + to_string(nodes.size()) + " nodes in total. )");
            pro.updateProgress(20);
        }
        { // boundary conditions
            pro.addTip(">>> Construct linear system ...");
            Mat<double, double> A(nodes.size());
            Vec<double> b(nodes.size());

            int cnt = -1;
            auto build_equ = [&]() -> void { ++cnt; };
            auto add = [&](int i, int j, double num) { 
                custom_assert(nodeID.count({i,j}), 
                    "Equation build failed : node [" + to_string(i) + ", " + to_string(j) + "] not exists.");
                A[cnt][nodeID[{i, j}]] = num;
            };
            auto Add = [&](int id, double num) { A[cnt][id] = num; };
            auto rhs = [&](double num) -> void { b[cnt] = num; };
            auto getv = [&](const func2D& f, int i, int j) -> double {
                auto no = nodes[nodeID[{i, j}]].first;
                return f(no.x, no.y);
            };
            auto Count = [&](int i, int j) -> bool { return nodeID.count({i, j}); };
            auto gtInter = [&](int i1, int j1, int i2, int j2) -> int { // （i1, j1) -> outer, (i2, j2) -> inner
                if(interID.count({{i1, j1}, {i2, j2}})) return interID[{{i1, j1}, {i2, j2}}];
                else return -1;
            };

            // Grid nodes
            for(int i = -1; i <= N + 1; ++i) for(int j = -1; j <= N + 1; ++j) {
                if(!nodeID.count({i, j})) continue;
                if(i > 0 && i < N && j > 0 && j < N) {
                    if(nodes[nodeID[{i, j}]].second == 0) {
                        build_equ();
                        add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                        rhs(p.h*p.h*getv(p.F, i, j));
                    } else if (nodes[nodeID[{i, j}]].second == 2) {
                        build_equ();
                        bool flg = 0; int _id;
                        if(!flg && (onCircle(i-1, j) || (_id = gtInter(i-1,j,i,j), _id != -1))) {
                            flg = 1;
                            if(onCircle(i-1, j)) add(i,j,1), add(i-2,j,1), add(i-1,j,-2), rhs(0);
                            else {
                                double theta = fabs(p.xl+i*p.h-nodes[_id].first.x);
                                add(i, j, p.h-theta); add(i-1, j, theta); Add(_id, -p.h); rhs(0);
                            }
                        }
                        if(!flg && (onCircle(i+1, j) || (_id = gtInter(i+1,j,i,j), _id != -1))) {
                            flg = 1;
                            if(onCircle(i+1, j)) add(i,j,1), add(i+2,j,1), add(i+1,j,-2), rhs(0);
                            else {
                                double theta = fabs(p.xl+i*p.h-nodes[_id].first.x);
                                add(i, j, p.h-theta); add(i+1, j, theta); Add(_id, -p.h); rhs(0);
                            }
                        }
                        if(!flg && (onCircle(i, j-1) || (_id = gtInter(i,j-1,i,j), _id != -1))) {
                            flg = 1;
                            if(onCircle(i, j-1)) add(i,j,1), add(i,j-2,1), add(i,j-1,-2), rhs(0);
                            else {
                                double theta = fabs(p.yl+j*p.h-nodes[_id].first.y);
                                add(i, j, p.h-theta); add(i, j-1, theta); Add(_id, -p.h); rhs(0);
                            }
                        }
                        if(!flg && (onCircle(i, j+1) || (_id = gtInter(i,j+1,i,j), _id != -1))) {
                            flg = 1;
                            if(onCircle(i, j+1)) add(i,j,1), add(i,j+2,1), add(i,j+1,-2), rhs(0);
                            else {
                                double theta = fabs(p.yl+j*p.h-nodes[_id].first.y);
                                add(i, j, p.h-theta); add(i, j+1, theta); Add(_id, -p.h); rhs(0);
                            }
                        }
                        custom_assert(flg, "Node (in circle) id : [" + to_string(i) + ", " + to_string(j) + "] cannot build its equation.");
                    } // else -> on circle
                } else {
                    if((i == 0 || i == N) && (j == 0 || j == N)) {
                        build_equ();
                        if(i == 0 && j == 0 && allNeumann) add(i, j, 1), rhs(1);
                        else {
                        if(Count(i-1,j)&&Count(i,j-1)&&Count(i+1,j)&&Count(i,j+1)) {
                            add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                            rhs(p.h*p.h*getv(p.F, i, j));
                        } else {
                            add(i,j,1);
                            if(!isn[lef] && i == 0) rhs(getv(p.G[lef], i, j));
                            else if(!isn[rig] && i == N) rhs(getv(p.G[rig], i, j));
                            else if(!isn[up] && j == N) rhs(getv(p.G[up], i, j));
                            else if(!isn[down] && j == 0) rhs(getv(p.G[down], i, j));
                            else custom_assert(0, "Node id : [" + to_string(i) + ", " + to_string(j) + "] cannot build its equation.");
                        }
                        }
                    } else if ((i == 0 || i == N || j == 0 || j == N) && (i != -1 && i != N+1 && j != -1 && j != N+1)) {
                        if((i == 0 && isn[lef]) || (i == N && isn[rig]) || (j == 0 && isn[down]) || (j == N && isn[up])) {
                            build_equ();
                            add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                            rhs(p.h*p.h*getv(p.F, i, j));
                        } else {
                            build_equ();
                            add(i,j,1), rhs(getv(p.G[i==0?lef:(i==N?rig:(j==0?down:up))],i,j));
                        }
                    } else {
                        if(i ==  -1) build_equ(), add(i,j,1),add(i+2,j,-1),rhs(2*p.h*getv(p.G[lef],i+1,j));
                        if(i == N+1) build_equ(), add(i,j,1),add(i-2,j,-1),rhs(2*p.h*getv(p.G[rig],i-1,j));
                        if(j ==  -1) build_equ(), add(i,j,1),add(i,j+2,-1),rhs(2*p.h*getv(p.G[down],i,j+1));
                        if(j == N+1) build_equ(), add(i,j,1),add(i,j-2,-1),rhs(2*p.h*getv(p.G[up],i,j-1));
                    }
                }
            }
            { // nodes on circle
            auto getup = [&](int id) -> pair<int,int> {
                return {(int)((nodes[id].first.x - p.xl)/p.h+.5), (int)((nodes[id].first.y-p.yl)/p.h+.5*(nodes[id].second == 1))+1};
            };
            auto getdown = [&](int id) -> pair<int,int> {
                return {(int)((nodes[id].first.x - p.xl)/p.h+.5), (int)((nodes[id].first.y-p.yl)/p.h-.5*(nodes[id].second == 1))};
            };
            auto getleft = [&](int id) -> pair<int,int> {
                return {(int)((nodes[id].first.x - p.xl)/p.h-.5*(nodes[id].second == 1)), (int)((nodes[id].first.y-p.yl)/p.h+.5)};
            };
            auto getright = [&](int id) -> pair<int,int> {
                return {(int)((nodes[id].first.x - p.xl)/p.h+.5*(nodes[id].second == 1))+1, (int)((nodes[id].first.y-p.yl)/p.h+.5)};
            };
            auto UP = [&](pair<int,int> x) -> pair<int,int> { return {x.first, x.second + 1}; };
            auto DOWN = [&](pair<int,int> x) -> pair<int,int> { return {x.first, x.second - 1}; };
            auto LEFT = [&](pair<int,int> x) -> pair<int,int> { return {x.first - 1, x.second}; };
            auto RIGHT = [&](pair<int,int> x) -> pair<int,int> { return {x.first + 1, x.second}; };
            #define allcount(v) (Count(v[0].first,v[0].second)&&Count(v[1].first,v[1].second) \
                               &&Count(v[2].first,v[2].second)&&Count(v[3].first,v[3].second)&&Count(v[4].first,v[4].second))
            auto gtcoef = [&](pair<int,int> _, int id) -> Vec<double> {
                int _id = nodeID[{_.first, _.second}];
                double x = nodes[_id].first.x, y = nodes[_id].first.y, x0 = nodes[id].first.x, y0 = nodes[id].first.y;
                return Vec({1, x-x0, y-y0, 0.5*(x-x0)*(x-x0), 0.5*(y-y0)*(y-y0), (x-x0)*(y-y0)});
            };
            for(int i = 0; i < nodes.size(); ++i)
            if(nodes[i].second == 1 || nodes[i].second == 4 || nodes[i].second == 5) {
                if(!isn[Cir]) { // Dirichlet
                    build_equ();
                    Add(i, 1); rhs(p.G[Cir](nodes[i].first.x, nodes[i].first.y));
                } else { // Neumann -> find 6 points
                    /*
                        case1: xxx    case2: xxx    case3: xx     case4:  xx
                                x             x             x             x
                               xx             xx           xxx           xxx
                        
                        case5: x x    case6: x      case7: x x    case8:   x
                               xxx           xxx           xxx           xxx
                               x             x x             x           x x
                    */
                    bool flg = 0; int kind = nodes[i].second;
                    build_equ();
                    double grd = p.G[Cir](nodes[i].first.x, nodes[i].first.y);
                    Vec<double> e({0, (nodes[i].first.x-cx)/R, (nodes[i].first.y-cy)/R, 0, 0, 0});
                    Mat<double> m(6, 6); m[5] = Vec<double>({1, 0, 0, 0, 0, 0});
                                                            /*u ux uy uxx uyy uxy*/
                    rhs(grd);
                    for(int j = 1; j <= 8 && !flg; ++j) {
                        vector<pair<int,int>> v(5); bool ok = 0;
                        switch (j) {
                        case 1:
                            if((kind == 1 || kind == 4) && nodes[i].first.y >= cy && nodes[i].first.x <= cx) { ok = 1;
                                v[0] = getup(i), v[1] = getdown(i); v[2] = LEFT(v[0]); v[3] = RIGHT(v[0]); v[4] = LEFT(v[1]);
                            } break;
                        case 2:
                            if((kind == 1 || kind == 4) && nodes[i].first.y >= cy && nodes[i].first.x > cx) { ok = 1;
                                v[0] = getup(i), v[1] = getdown(i); v[2] = LEFT(v[0]); v[3] = RIGHT(v[0]); v[4] = RIGHT(v[1]);
                            } break;
                        case 3:
                            if((kind == 1 || kind == 4) && nodes[i].first.y < cy && nodes[i].first.x <= cx) { ok = 1;
                                v[0] = getup(i), v[1] = getdown(i); v[2] = LEFT(v[1]); v[3] = RIGHT(v[1]); v[4] = LEFT(v[0]);
                            } break;
                        case 4:
                            if((kind == 1 || kind == 4) && nodes[i].first.y < cy && nodes[i].first.x > cx) { ok = 1;
                                v[0] = getup(i), v[1] = getdown(i); v[2] = LEFT(v[1]); v[3] = RIGHT(v[1]); v[4] = RIGHT(v[0]);
                            } break;
                        case 5:
                            if((kind == 1 || kind == 5) && nodes[i].first.x < cx && nodes[i].first.y > cy) { ok = 1;
                                v[0] = getleft(i), v[1] = getright(i); v[2] = UP(v[0]); v[3] = DOWN(v[0]); v[4] = UP(v[1]);
                            } break;
                        case 6:
                            if((kind == 1 || kind == 5) && nodes[i].first.x < cx && nodes[i].first.y <= cy) { ok = 1;
                                v[0] = getleft(i), v[1] = getright(i); v[2] = UP(v[0]); v[3] = DOWN(v[0]); v[4] = DOWN(v[1]);
                            } break;
                        case 7:
                            if((kind == 1 || kind == 5) && nodes[i].first.x >= cx && nodes[i].first.y > cy) { ok = 1;
                                v[0] = getleft(i), v[1] = getright(i); v[2] = UP(v[1]); v[3] = DOWN(v[1]); v[4] = UP(v[0]);
                            } break;
                        case 8:
                            if((kind == 1 || kind == 5) && nodes[i].first.x >= cx && nodes[i].first.y <= cy) { ok = 1;
                                v[0] = getleft(i), v[1] = getright(i); v[2] = UP(v[1]); v[3] = DOWN(v[1]); v[4] = DOWN(v[0]);
                            } break;
                        }
                        if(ok && allcount(v)) {
                            // cerr << nodes[i].first.x << " " << nodes[i].first.y << ": " << v << "\n";
                            flg = 1;
                            for(int k = 0; k < 5; ++k) m[k] = gtcoef(v[k], i);
                            // stringstream str; str << ~m; pro.addTip(str.str());
                            Vec<double> c = Gauss_elimination(~m, e);
                            for(int k = 0; k < 5; ++k) add(v[k].first, v[k].second, c[k]);
                            Add(i, c[5]);
                        }
                    }
                    custom_assert(flg, "Node (on circle) [" + to_string(nodes[i].first.x) + ", " + to_string(nodes[i].first.y) + "] cannot build its equation.");
                }
            }}
            custom_assert(cnt+1 == nodes.size(), "Equation number does not fit variable number");
            // cout << A << "\n" << b << std::endl << std::endl;
            pro.updateProgress(40);
            pro.updateTip(">>> Construct linear system ... done");
            pro.addTip(">>> Solving linear system ...");
            U = Gauss_elimination(A, b);
            pro.updateProgress(99);
            pro.updateTip(">>> Solving linear system ... done");
        }
    }
    void get_results(const Square_BVP_Problem& p, RES& results) const {
        results.clear();
        for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
            double x = p.xl + p.h * i;
            double y = p.yl + p.h * j;
            double val = 0;
            if((i == 0 || i == N) && (j == 0 || j == N)) {
                if(nodeID.count({i, j})) val = U[nodeID.at({i, j})];
                else if(i == 0) val = p.G[lef](x, y);
                else if(i == N) val = p.G[rig](x, y);
                else if(j == 0) val = p.G[down](x, y);
                else if(j == N) val = p.G[up](x, y);
            } 
            else if(!p.inCircle(x, y)) val = U[nodeID.at({i, j})];
            results.push_back({{x, y}, val});
        }
        return ;
    }
    double norm1, norm2, normi;
    void ErrorAnalysis(const Square_BVP_Problem& p, bool print = 1) {
        using namespace norm;
        vector<double> u, a;
        for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
            if((i == 0 || i == N) && (j == 0 || j == N)) continue;
            if(!nodeID.count({i, j})) continue;
            int id = nodeID[{i, j}];
            if(nodes[id].second == 2) continue;
            u.push_back(U[id]);
            a.push_back(p.Answer(nodes[id].first.x, nodes[id].first.y));
        }
        // if (p._bc_types[Cir] != "Dirichlet") {
        // for(int i = 0; i < nodes.size(); ++i) if(nodes[i].second == 4 || nodes[i].second == 5) { 
        //     u.push_back(U[i]);
        //     a.push_back(p.Answer(nodes[i].first.x, nodes[i].first.y));
        // }}
        Vec<double> err = Vec(u) - Vec(a);
        if(allNeumann) {
            double _avg = avg(err);
            for(auto &x : err) x -= _avg;
            for(auto &x : U) x -= _avg;
        }
        norm1 = Norm1Vec(err); norm2 = Norm2Vec(err); normi = NormiVec(err);
        if(!print) return ;
        std::cerr << "Error norm-1   : " << fixed << setprecision(10) << norm1 << std::endl;
        std::cerr << "Error norm-2   : " << fixed << setprecision(10) << norm2 << std::endl;
        std::cerr << "Error norm-inf : " << fixed << setprecision(10) << normi << std::endl;
        std::cerr.unsetf(ios::floatfield);
    }
};

class Square_BVPsolver::Irregular_Square_BVPsolver_2 {
    int N;
    vector<pair<Point, int>> nodes; /* nodes & if it is extended*/
    /*0:inner grid nodes             2:grid nodes in Circle
      1:grid nodes on Circle         3:nodes extended along sides
      */
    Vec<double> U;
    map<pair<int,int>, int> nodeID; // the position in 'nodes'
    bool allNeumann, isn[5];
    double cx, cy, R;
public:
    void solve(const Square_BVP_Problem& p, ProgressBar &pro) {
        N = p.Grid_n; cx = p.Center.first; cy = p.Center.second; R = p.R;
        auto inDomain = [&](int i, int j) -> bool { 
            if(i == 0 || j == 0 || i == N || j == N) return true;
            return p.inDomain(i*p.h+p.xl, j*p.h+p.yl); 
        };
        auto onCircle = [&](int i, int j) -> bool {
            return fabs(R - dis(p.Center, {i*p.h+p.xl, j*p.h+p.yl})) < 1e-12;
        };
        auto inCircle = [&](int i, int j) -> bool {
            return !onCircle(i, j) && p.inCircle(i*p.h+p.xl, j*p.h+p.yl);
        };
        { pro.addTip(">>> Adding nodes...");
            auto Count = [&](int i, int j) -> bool { // grid nodes [in] the border
                return nodeID.count({i, j}) && 
                       nodes[nodeID[{i,j}]].second == 0; 
            };
            auto P = [&](int i, int j) -> Point { return Point(i*p.h+p.xl, j*p.h+p.yl); };
            allNeumann = 0;
            // grid nodes inside border
            for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
                if((i == 0 || i == N) && (j == 0 || j == N)) continue;
                if(onCircle(i, j)) {
                    nodes.push_back({P(i, j), 1});
                    nodeID[{i, j}] = nodes.size() - 1;
                    continue;
                }
                if(!inDomain(i, j)) continue;
                nodes.push_back({P(i, j), 0});
                nodeID[{i, j}] = nodes.size() - 1;
            }
            for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) if(!Count(i,j)) {
                if((i == 0 || i == N) && (j == 0 || j == N)) continue;
                if(Count(i+1,j)||Count(i-1,j)||Count(i,j+1)||Count(i,j-1)) {
                    nodes.push_back({P(i, j), 2});
                    nodeID[{i, j}] = nodes.size() - 1;
                }
            }
            isn[0] = isn[1] = isn[2] = isn[3] = isn[4] = 0;
            if(p.BC_Type == "mixed" || p.BC_Type == "Neumann") {
                int num = 0;
                for(int i = 0; i < 5; ++i) num += (isn[i] = (p._bc_types[i] == "Neumann"));
                allNeumann = (num == 5);
                for(int i = 0; i < 4; ++i) if(isn[i]) {
                    switch (i)
                    {
                    case down: for(int j = 1; j < N; ++j)
                        nodes.push_back({Point(p.xl+p.h*j, p.yl-p.h), 3}),
                        nodeID[{j, -1}] = nodes.size() - 1;
                        break;
                    case up: for(int j = 1; j < N; ++j) 
                        nodes.push_back({Point(p.xl+p.h*j, p.yr+p.h), 3}),
                        nodeID[{j, N+1}] = nodes.size() - 1;
                        break;
                    case lef: for(int j = 1; j < N; ++j)
                        nodes.push_back({Point(p.xl-p.h, p.yl+p.h*j), 3}),
                        nodeID[{-1, j}] = nodes.size() - 1;
                        break;
                    case rig: for(int j = 1; j < N; ++j) 
                        nodes.push_back({Point(p.xr+p.h, p.yl+p.h*j), 3}),
                        nodeID[{N+1, j}] = nodes.size() - 1;
                        break;
                    }
                }
                { // corner : when one side near it is Neumann
                    if(isn[lef] || isn[down]) {
                        nodes.push_back({Point(p.xl, p.yl), 3});
                        nodeID[{0, 0}] = nodes.size() - 1;
                    }
                    if(isn[lef] || isn[up]) {
                        nodes.push_back({Point(p.xl, p.yr), 3});
                        nodeID[{0, N}] = nodes.size() - 1;
                    }
                    if(isn[rig] || isn[down]) {
                        nodes.push_back({Point(p.xr, p.yl), 3});
                        nodeID[{N, 0}] = nodes.size() - 1;
                    }
                    if(isn[rig] || isn[up]) {
                        nodes.push_back({Point(p.xr, p.yr), 3});
                        nodeID[{N, N}] = nodes.size() - 1;
                    }
                }
                { // corner : when both sides near it is Neumann
                    if(isn[lef] && isn[down]) {
                        nodes.push_back({Point(p.xl - p.h, p.yl), 3});
                        nodeID[{-1, 0}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xl, p.yl - p.h), 3});
                        nodeID[{0, -1}] = nodes.size() - 1;
                    }
                    if(isn[lef] && isn[up]) {
                        nodes.push_back({Point(p.xl - p.h, p.yr), 3});
                        nodeID[{-1, N}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xl, p.yr + p.h), 3});
                        nodeID[{0, N+1}] = nodes.size() - 1;
                    }
                    if(isn[rig] && isn[down]) {
                        nodes.push_back({Point(p.xr + p.h, p.yl), 3});
                        nodeID[{N+1, 0}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xr, p.yl - p.h), 3});
                        nodeID[{N, -1}] = nodes.size() - 1;
                    }
                    if(isn[rig] && isn[up]) {
                        nodes.push_back({Point(p.xr + p.h, p.yr), 3});
                        nodeID[{N+1, N}] = nodes.size() - 1;
                        nodes.push_back({Point(p.xr, p.yr + p.h), 3});
                        nodeID[{N, N+1}] = nodes.size() - 1;
                    }
                }
            }
            pro.updateTip(">>> Adding nodes... done ( " + to_string(nodes.size()) + " nodes in total. )");
            pro.updateProgress(20);
        }
        { // boundary conditions
            pro.addTip(">>> Construct linear system ...");
            Mat<double, double> A(nodes.size());
            Vec<double> b(nodes.size());

            int cnt = -1;
            auto build_equ = [&]() -> void { ++cnt; };
            auto add = [&](int i, int j, double num) { 
                custom_assert(nodeID.count({i,j}), 
                    "Equation build failed : node [" + to_string(i) + ", " + to_string(j) + "] not exists.");
                A[cnt][nodeID[{i, j}]] = num;
            };
            auto Add = [&](int id, double num) { A[cnt][id] = num; };
            auto rhs = [&](double num) -> void { b[cnt] = num; };
            auto getv = [&](const func2D& f, int i, int j) -> double {
                auto no = nodes[nodeID[{i, j}]].first;
                return f(no.x, no.y);
            };
            auto Count = [&](int i, int j) -> bool { return nodeID.count({i, j}); };
            auto gtInter = [&](int i1, int j1, int i2, int j2) -> double {
                double x, y;   
                if(i1 == i2) {
                    x = i1*p.h+p.xl;
                    y = sqrt(R*R-(x-cx)*(x-cx));
                    if(fabs(y)<1e-12) y = 0;
                    if(max(j1,j2)*p.h+p.yl > cy) y = cy + y;
                    else y = cy - y;
                    return y;
                    // custom_assert((y <= p.yl+p.h*max(j1, j2) && y >= p.yl+p.h*min(j1, j2)), "Intersection not exists."); -> OK
                } else {
                    y= j1*p.h+p.yl;
                    x = sqrt(R*R-(y-cy)*(y-cy));
                    if(fabs(x)<1e-12) x = 0;
                    if(max(i1,i2)*p.h+p.xl > cx) x = cx + x;
                    else x = cx - x;
                    // custom_assert((x <= p.xl+p.h*max(i1, i2) && x >= p.xl+p.h*min(i1, i2)), "Intersection not exists."); -> OK
                    return x;
                }
                custom_assert(0, "Calculate Intersection error.");
                return 0;
            };
            auto Inter = [&](int i, int j) -> Point {
                double x = p.xl+i*p.h, y = p.yl+j*p.h;
                double theta = atan2(y-cy, x-cx);
                return Point(cx+R*cos(theta), cy+R*sin(theta));
            };
            auto gtcoef = [&](int _id, Point pp) -> Vec<double> {
                double x = nodes[_id].first.x, y = nodes[_id].first.y, x0 = pp.x, y0 = pp.y;
                return Vec({1, x-x0, y-y0, 0.5*(x-x0)*(x-x0), 0.5*(y-y0)*(y-y0), (x-x0)*(y-y0)});
            };

            // Grid nodes
            for(int i = -1; i <= N + 1; ++i) for(int j = -1; j <= N + 1; ++j) {
                if(!nodeID.count({i, j})) continue;
                if(i > 0 && i < N && j > 0 && j < N) {
                    if(nodes[nodeID[{i, j}]].second == 0) {
                        build_equ();
                        add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                        rhs(p.h*p.h*getv(p.F, i, j));
                    } else if (nodes[nodeID[{i, j}]].second <= 2) {
                    if(!isn[Cir]) { // Dirichlet
                        if(nodes[nodeID[{i, j}]].second == 1) {
                            build_equ(); add(i, j, 1); rhs(p.G[Cir](p.xl+i*p.h, p.yl+j*p.h));
                        } else {
                            build_equ();
                            bool flg = 0; double _;
                            if(!flg && (onCircle(i-1, j) || !inCircle(i-1, j))) {
                                flg = 1;
                                if(onCircle(i-1, j)) add(i,j,1), add(i-2,j,1), add(i-1,j,-2), rhs(0);
                                else {
                                    double theta = fabs(p.xl+i*p.h-(_=gtInter(i-1,j,i,j)));
                                    add(i, j, p.h-theta); add(i-1, j, theta); rhs(p.h*p.G[Cir](_, p.yl+j*p.h));
                                }
                            }
                            if(!flg && (onCircle(i+1, j) || !inCircle(i+1, j))) {
                                flg = 1;
                                if(onCircle(i+1, j)) add(i,j,1), add(i+2,j,1), add(i+1,j,-2), rhs(0);
                                else {
                                    double theta = fabs(p.xl+i*p.h-(_=gtInter(i+1,j,i,j)));
                                    add(i, j, p.h-theta); add(i+1, j, theta); rhs(p.h*p.G[Cir](_, p.yl+j*p.h));
                                }
                            }
                            if(!flg && (onCircle(i, j-1) || !inCircle(i, j-1))) {
                                flg = 1;
                                if(onCircle(i, j-1)) add(i,j,1), add(i,j-2,1), add(i,j-1,-2), rhs(0);
                                else {
                                    double theta = fabs(p.yl+j*p.h-(_=gtInter(i,j-1,i,j)));
                                    add(i, j, p.h-theta); add(i, j-1, theta); rhs(p.h*p.G[Cir](p.xl+i*p.h, _));
                                }
                            }
                            if(!flg && (onCircle(i, j+1) || !inCircle(i, j+1))) {
                                flg = 1;
                                if(onCircle(i, j+1)) add(i,j,1), add(i,j+2,1), add(i,j+1,-2), rhs(0);
                                else {
                                    double theta = fabs(p.yl+j*p.h-(_=gtInter(i,j+1,i,j)));
                                    add(i, j, p.h-theta); add(i, j+1, theta); rhs(p.h*p.G[Cir](p.xl+i*p.h, _));
                                }
                            }
                            custom_assert(flg, "Node (in circle) id : [" + to_string(i) + ", " + to_string(j) + "] cannot build its equation.");
                        }
                    } else { // Neumann
                        build_equ();
                        Point inter = Inter(i, j);
                        rhs(p.G[Cir](inter.x, inter.y));
                        Mat<double, double> m(6);
                        Vec<double> e({0, (inter.x-cx)/R, (inter.y-cy)/R, 0, 0, 0});
                        vector<int> v(6); v[0] = nodeID[{i, j}];
                        double x=p.xl+i*p.h, y=p.yl+j*p.h;
                        if(x>=cx&&y>=cy) { // right, up
                            v[1]=nodeID[{i+1,j}], v[2]=nodeID[{i,j+1}], v[3]=nodeID[{i+1,j+1}];
                            v[4]=Count(i-1,j+1)?nodeID[{i-1,j+1}]:nodeID[{i+2,j+1}];
                            v[5]=Count(i+1,j-1)?nodeID[{i+1,j-1}]:nodeID[{i+1,j+2}];
                        } else if (x>=cx) { // right, down
                            v[1]=nodeID[{i+1,j}], v[2]=nodeID[{i,j-1}], v[3]=nodeID[{i+1,j-1}];
                            v[4]=Count(i-1,j-1)?nodeID[{i-1,j-1}]:nodeID[{i+2,j-1}];
                            v[5]=Count(i+1,j+1)?nodeID[{i+1,j+1}]:nodeID[{i+1,j-2}];
                        } else if(y>=cy) { // left, up
                            v[1]=nodeID[{i-1,j}], v[2]=nodeID[{i,j+1}], v[3]=nodeID[{i-1,j+1}];
                            v[4]=Count(i-1,j-1)?nodeID[{i-1,j-1}]:nodeID[{i-1,j+2}];
                            v[5]=Count(i+1,j+1)?nodeID[{i+1,j+1}]:nodeID[{i-2,j+1}];
                        } else { // left, down
                            v[1]=nodeID[{i-1,j}], v[2]=nodeID[{i,j-1}], v[3]=nodeID[{i-1,j-1}];
                            v[4]=Count(i-1,j+1)?nodeID[{i-1,j+1}]:nodeID[{i-1,j-2}];
                            v[5]=Count(i+1,j-1)?nodeID[{i+1,j-1}]:nodeID[{i-2,j-1}];
                        }
                        for(int i = 0; i < 6; ++i) m[i] = gtcoef(v[i], inter);
                        Vec<double> c = Gauss_elimination(~m, e);
                        for(int i = 0; i < 6; ++i) Add(v[i], c[i]);
                    }
                } }else {
                    if((i == 0 || i == N) && (j == 0 || j == N)) {
                        build_equ();
                        if(i == 0 && j == 0 && allNeumann) add(i, j, 1), rhs(1);
                        else {
                        if(Count(i-1,j)&&Count(i,j-1)&&Count(i+1,j)&&Count(i,j+1)) {
                            add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                            rhs(p.h*p.h*getv(p.F, i, j));
                        } else {
                            add(i,j,1);
                            if(!isn[lef] && i == 0) rhs(getv(p.G[lef], i, j));
                            else if(!isn[rig] && i == N) rhs(getv(p.G[rig], i, j));
                            else if(!isn[up] && j == N) rhs(getv(p.G[up], i, j));
                            else if(!isn[down] && j == 0) rhs(getv(p.G[down], i, j));
                            else custom_assert(0, "Node id : [" + to_string(i) + ", " + to_string(j) + "] cannot build its equation.");
                        }
                        }
                    } else if ((i == 0 || i == N || j == 0 || j == N) && (i != -1 && i != N+1 && j != -1 && j != N+1)) {
                        if((i == 0 && isn[lef]) || (i == N && isn[rig]) || (j == 0 && isn[down]) || (j == N && isn[up])) {
                            build_equ();
                            add(i-1,j,-1); add(i+1,j,-1); add(i,j-1,-1); add(i,j+1,-1); add(i,j,4);
                            rhs(p.h*p.h*getv(p.F, i, j));
                        } else {
                            build_equ();
                            add(i,j,1), rhs(getv(p.G[i==0?lef:(i==N?rig:(j==0?down:up))],i,j));
                        }
                    } else {
                        if(i ==  -1) build_equ(), add(i,j,1),add(i+2,j,-1),rhs(2*p.h*getv(p.G[lef],i+1,j));
                        if(i == N+1) build_equ(), add(i,j,1),add(i-2,j,-1),rhs(2*p.h*getv(p.G[rig],i-1,j));
                        if(j ==  -1) build_equ(), add(i,j,1),add(i,j+2,-1),rhs(2*p.h*getv(p.G[down],i,j+1));
                        if(j == N+1) build_equ(), add(i,j,1),add(i,j-2,-1),rhs(2*p.h*getv(p.G[up],i,j-1));
                    }
                }
            }
            custom_assert(cnt+1 == nodes.size(), "Equation number does not fit variable number");
            // cout << A << "\n" << b << std::endl << std::endl;
            pro.updateProgress(40);
            pro.updateTip(">>> Construct linear system ... done");
            pro.addTip(">>> Solving linear system ...");
            U = Gauss_elimination(A, b);
            pro.updateProgress(99);
            pro.updateTip(">>> Solving linear system ... done");
        }
    }
    void get_results(const Square_BVP_Problem& p, RES& results) const {
        results.clear();
        for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
            double x = p.xl + p.h * i;
            double y = p.yl + p.h * j;
            double val = 0;
            if((i == 0 || i == N) && (j == 0 || j == N)) {
                if(nodeID.count({i, j})) val = U[nodeID.at({i, j})];
                else if(i == 0) val = p.G[lef](x, y);
                else if(i == N) val = p.G[rig](x, y);
                else if(j == 0) val = p.G[down](x, y);
                else if(j == N) val = p.G[up](x, y);
            } 
            else if(!p.inCircle(x, y)) val = U[nodeID.at({i, j})];
            results.push_back({{x, y}, val});
        }
        return ;
    }
    double norm1, norm2, normi;
    void ErrorAnalysis(const Square_BVP_Problem& p, bool print = 1) {
        using namespace norm;
        vector<double> u, a;
        for(int i = 0; i <= N; ++i) for(int j = 0; j <= N; ++j) {
            if((i == 0 || i == N) && (j == 0 || j == N)) continue;
            if(!nodeID.count({i, j})) continue;
            int id = nodeID[{i, j}];
            if(nodes[id].second >= 2) continue;
            u.push_back(U[id]);
            a.push_back(p.Answer(nodes[id].first.x, nodes[id].first.y));
        }
        Vec<double> err = Vec(u) - Vec(a);
        if(allNeumann) {
            double _avg = avg(err);
            for(auto &x : err) x -= _avg;
            for(auto &x : U) x -= _avg;
        }
        norm1 = Norm1Vec(err); norm2 = Norm2Vec(err); normi = NormiVec(err);
        if(!print) return ;
        std::cerr << "Error norm-1   : " << fixed << setprecision(10) << norm1 << std::endl;
        std::cerr << "Error norm-2   : " << fixed << setprecision(10) << norm2 << std::endl;
        std::cerr << "Error norm-inf : " << fixed << setprecision(10) << normi << std::endl;
        std::cerr.unsetf(ios::floatfield);
    }
};

void Square_BVPsolver::solveProblem(bool show) {
    ProgressBar progress("BVP Problem", 1, show, show);
    if(this->prob.Domain_Type == "Regular") {
        Regular_Square_BVPsolver solver;
        solver.solve(this->prob, progress);
        progress.updateProgress(100);
        if(this->prob.Need_Error == 1) {
            solver.ErrorAnalysis(this->prob);
            norm1 = solver.norm1;
            norm2 = solver.norm2;
            normi = solver.normi;
        }
        solver.get_results(this->prob, this->results);
    } else if(this->prob.use_old) {
        Irregular_Square_BVPsolver solver;
        solver.solve(this->prob, progress);
        progress.updateProgress(100);
        if(this->prob.Need_Error == 1) {
            solver.ErrorAnalysis(this->prob);
            norm1 = solver.norm1;
            norm2 = solver.norm2;
            normi = solver.normi;
        }
        solver.get_results(this->prob, this->results);
    } else {
        Irregular_Square_BVPsolver_2 solver;
        solver.solve(this->prob, progress);
        progress.updateProgress(100);
        if(this->prob.Need_Error == 1) {
            solver.ErrorAnalysis(this->prob);
            norm1 = solver.norm1;
            norm2 = solver.norm2;
            normi = solver.normi;
        }
        solver.get_results(this->prob, this->results);
    }
}

void Square_BVPsolver::Summary() { // call after solveProblem!
    this->printProblem();
    if(this->prob.Need_Error == 1) {
        std::cerr << "Error norm-1   : " << fixed << setprecision(10) << this->norm1 << std::endl;
        std::cerr << "Error norm-2   : " << fixed << setprecision(10) << this->norm2 << std::endl;
        std::cerr << "Error norm-inf : " << fixed << setprecision(10) << this->normi << std::endl;
        std::cerr.unsetf(ios::floatfield);
    }
}

#endif