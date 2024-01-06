#include <bits/stdc++.h>
#include "serialization.hpp"
#include "function.hpp"
#include "calculator.hpp"

using namespace std;

using NUM = double;
const NUM Pi = acos(-1.), dt = 1e-8, Q = sqrt(3);

class FX : public Function<NUM> {
public :
    NUM operator () (const NUM& t) const {
        return Q * sin(t);
    }
    NUM diff (const NUM& t) const {
        return Q * cos(t);
    }
    NUM diff2 (const NUM& t) const {
        return -Q * sin(t);
    }
} fx;

class FY : public Function<NUM> {
public:
    double operator () (const NUM& t) const {
		return 2 * (Q * cos(t) + sqrt(Q * fabs(sin(t)))) / 3;
	}
	NUM diff (const NUM& t) const {
		if (sin(t) > 0) return 2 * (-Q * sin(t) + sqrt(Q) * cos(t) / 2 / sqrt(fabs(sin(t)))) / 3;
		else return 2 * (-Q * sin(t) - sqrt(Q) * cos(t) / sqrt(fabs(sin(t)))) / 3;
	}
    NUM diff2 (const NUM& t) const {
		return (diff(t) - diff(t+1e-8)) / (1e-8);
	}
} fy;

// lenght = \int_{0}^{t} dl(t)
class dlength : public Function<NUM> {
public:
    NUM operator () (const NUM& t) const {
		return sqrt(sq(fx.diff(t))+sq(fy.diff(t)));
	}
} dl;


// get even points of length

vector<NUM> Get_Knots_l(int n) {
    vector<NUM> x(n+1);
    x[0] = 0;
    NUM I;
    x[n/2] = I = Simpson<dlength, NUM>(dl, 1e-8, Pi-1e-8);
    x[n] = I * 2;
    
    for(int i = 1; i < n/2; ++i) 
        x[i] = I / (n/2) * i,
        x[n-i] = 2*I - x[i];

    return x;
}

vector<NUM> Get_Knots(int n) {
    vector<NUM> x(n+1), y(n+1);
    x[0] = 1e-8; // special point -> t = 0
    x[n/2] = Pi-1e-8; // special point -> t = pi
    NUM I = Simpson<dlength, NUM>(dl, 1e-8, Pi-1e-8) * 2;
    for(int i = 1; i < n/2; ++i) {
        NUM l = x[i-1], r = Pi*2;
        while(r-l>=1e-8) {
            NUM mid = (l+r)/2.0;
            if(Simpson<dlength, NUM>(dl, x[i-1], mid) < I/n) l = mid;
            else r = mid;
        }
        x[i] = (l+r)/2;
    }
    for(int i = 0; i < n/2; ++i) {
        x[n-i] = 2*Pi-x[i];
    }
    return x;
}

class Problem {
public:
    class subProblem {
    public:
        vector<NUM> T, X, Y; // input points
        vector<NUM> BC; // boudary conditions
        string Type; // spline type (cubic)
        REGISTER_SERIALIZATION_JSON(T, X, Y, BC, Type);
    };
    vector<subProblem> problems;
    REGISTER_SERIALIZATION_JSON(problems);
}prob;

int main() {
	prob.problems.resize(9);

    cout << "I = " << fixed << setprecision(16) << Simpson<dlength, NUM>(dl, 1e-8, Pi-1e-8) * 2 << "\n";

    prob.problems[0].T = prob.problems[1].T = prob.problems[2].T = Get_Knots_l(10);
    auto t = Get_Knots(10);
    prob.problems[0].X = prob.problems[1].X = prob.problems[2].X = get_map_list(fx, t);
    prob.problems[0].Y = prob.problems[1].Y = prob.problems[2].Y = get_map_list(fy, t);

    t = Get_Knots(40);
    prob.problems[3].T = prob.problems[4].T = prob.problems[5].T = Get_Knots_l(40);
    prob.problems[3].X = prob.problems[4].X = prob.problems[5].X = get_map_list(fx, t);
    prob.problems[3].Y = prob.problems[4].Y = prob.problems[5].Y = get_map_list(fy, t);

    t = Get_Knots(160);
    prob.problems[6].T = prob.problems[7].T = prob.problems[8].T = Get_Knots_l(160);
    prob.problems[6].X = prob.problems[7].X = prob.problems[8].X = get_map_list(fx, t);
    prob.problems[6].Y = prob.problems[7].Y = prob.problems[8].Y = get_map_list(fy, t);

    prob.problems[0].Type = prob.problems[3].Type = prob.problems[6].Type = "Nature";
    prob.problems[1].Type = prob.problems[4].Type = prob.problems[7].Type = "Complete";
    prob.problems[2].Type = prob.problems[5].Type = prob.problems[8].Type = "SecondDerivatives";

    for(int i = 1; i <= 7; i += 3)
    prob.problems[i].BC = {fx.diff(prob.problems[i].X[0]),
                           fx.diff(prob.problems[i].X.back()),
                           -fy.diff(prob.problems[i].Y[0]),
                           fy.diff(prob.problems[i].Y.back())};

    for(int i = 2; i <= 8; i += 3)
    prob.problems[i].BC = {fx.diff2(prob.problems[i].X[0]),
                           fx.diff2(prob.problems[i].X.back()),
                           fy.diff2(prob.problems[i].Y[0]),
                           fy.diff2(prob.problems[i].Y.back())};                  

    serialize_Json(prob, "data/E.json");

    return 0;
}