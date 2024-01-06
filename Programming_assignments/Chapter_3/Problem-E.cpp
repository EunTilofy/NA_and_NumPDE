#include <bits/stdc++.h>
#include "serialization.hpp"
#include "ExecCode.hpp"
#include "function.hpp"
#include "calculator.hpp"
#include "Spline.hpp"
#include "linear.hpp"
#include "IO.hpp"

using namespace Spline;

using namespace std;

class Problem {
public:
    class subProblem {
    public:
        vector<double> T, X, Y; // input points
        vector<double> BC; // boudary conditions
        string Type; // spline type (cubic)
        REGISTER_SERIALIZATION_JSON(T, X, Y, BC, Type);
    };
    vector<subProblem> problems;
    REGISTER_SERIALIZATION_JSON(problems);
}prob;

int main() {
    // Read from json file
    deserialize_Json(prob, "data/E.json");
    for(auto &subprob : prob.problems) {
        Curve_fitting_Order3 s(subprob.T, subprob.X, subprob.Y);
        if(subprob.Type == "Nature") {
            s.buildNature();
            cout << "px = " << subprob.X << "\n";
            cout << "py = " << subprob.Y << "\n";
            cout << s.to_python() << "\n\n";
        }
        if(subprob.Type == "Complete") {
            auto cond = subprob.BC;
            s.buildComplete(cond[0], cond[1], cond[2], cond[3]);
            cout << "px = " << subprob.X << "\n";
            cout << "py = " << subprob.Y << "\n";
            cout << s.to_python() << "\n\n";
        }
        if(subprob.Type == "SecondDerivatives") {
            auto cond = subprob.BC;
            s.buildSecondDerivatives(cond[0], cond[1], cond[2], cond[3]);
            cout << "px = " << subprob.X << "\n";
            cout << "py = " << subprob.Y << "\n";
            cout << s.to_python() << "\n\n";
        }
    }
    return 0;
}