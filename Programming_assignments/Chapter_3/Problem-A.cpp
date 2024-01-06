#include <bits/stdc++.h>
#include "serialization.hpp"
#include "ExecCode.hpp"
#include "function.hpp"
#include "calculator.hpp"
#include "Spline.hpp"
#include "linear.hpp"
#define Python_style
#include "IO.hpp"

using namespace Spline;

using namespace std;

struct Problem {
    std::string function;
    vector<int> N;
    pair<double,double> Interval;
    vector<std::string> Type;
    vector<vector<double>> Cond;
    REGISTER_SERIALIZATION_JSON(function, N, Interval, Type, Cond);
    REGISTER_OUTPUT_NAME(Problem, function, N, Interval, Type, Cond);
} prob;

int main() {
    // Read from json file
    deserialize_Json(prob, "data/A.json");
    // parse function from string
    REGISTER_FUNCTION_FROM_STRING(func, prob.function, double, double);
    // test -> func(0) = 1 (OK)

    cout << "N = " << prob.N << "\n";
    vector<double> err1, err2, err3, err4;
    
    for(auto n : prob.N) {
        vector<double> X(n), Y;
        X = evenspace<double>(prob.Interval.first, prob.Interval.second, n);
        Y = get_map_list(func, X);

        for(int i = 0; i < prob.Type.size(); ++i) {
            string type = prob.Type[i];
            vector<double> cond = prob.Cond[i];
            if(type == "linear") {
                ppForm_Spline<double, 1> s(X, Y);
                s.build();
                cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";
                err1.push_back(s.get_midpoint_error(func));
            }
            if(type == "CompleteCubic") {
                ppForm_Spline<double, 3> s(X, Y);
                s.build(Cubic_Spline_Condition<double, Complete>(cond[0], cond[1]));
                cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";
                err2.push_back(s.get_midpoint_error(func));
                // int _N = 100;
                // auto U = evenspace<double>(-1, 1, _N);
                // auto V = get_map_list(s, U);
                // cout<< "X = " << U << "\n Y = " << V << "\n";
            }
            if(type == "NatureCubic") {
                ppForm_Spline<double, 3> s(X, Y);
                s.build(Cubic_Spline_Condition<double, Nature>());
                cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";
                err3.push_back(s.get_midpoint_error(func));
            }
            if(type == "SecondDerivativesCubic") {
                ppForm_Spline<double, 3> s(X, Y);
                s.build(Cubic_Spline_Condition<double, Second_Derivatives>(cond[0], cond[1]));
                cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";
                err4.push_back(s.get_midpoint_error(func));
            }
        }
    }

    cout << "err_linear = " << err1 << "\n\nerr_complete = " 
    << err2 << "\n\nerr_nature = " << err3 << "\n\nerr_sd = " << err4 << "\n\n";

    return 0;
}