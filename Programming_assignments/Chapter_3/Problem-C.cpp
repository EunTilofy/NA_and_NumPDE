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

struct Problem {
    std::string function;
    pair<int,int> Interval;
    vector<int> N;
    vector<double> err_points;
    vector<std::string> Type;
    vector<vector<double>> Cond;
    REGISTER_SERIALIZATION_JSON(function, Interval, N, err_points, Type, Cond);
    REGISTER_OUTPUT_NAME(Problem, function, Interval, N, err_points, Type, Cond);
} prob;

int main() {
    // Read from json file
    deserialize_Json(prob, "data/C.json");
    // parse function from string
    REGISTER_FUNCTION_FROM_STRING(func, prob.function, double, double);
    // test -> func(1) = 0.5 (OK)

    cout << "err_points = " << prob.err_points << "\n\n";
    
    int L = prob.Interval.first;
    int R = prob.Interval.second;
    for(int i = 0; i < prob.Type.size(); ++i) {
        string type = prob.Type[i];
        vector<double> cond = prob.Cond[i];
        int n = prob.N[i];
        vector<double> X(n), Y;
        X = evenspace<double>(L, R, n);
        Y = get_map_list(func, X);
        if(type == "Linear") {
            auto s = Cardinal_B_Spline<double, 1>(L, R, n, Y);
            s.build();

            /***** test : points (OK) ******/
            // auto XX = evenspace<double>(-5, 5, 100);
            // auto YY = get_map_list(s, XX);
            // cout << "XX = " << XX << "\nYY = " << YY << "\n";

            cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";

            vector<double> err;
            for(auto x : prob.err_points) err.push_back(fabs(s(x) - func(x)));
            cout << "err_values_linear = " << err << "\n\n";
        }
        if(type == "Quadratic") {
            auto s = Quadratic_Cardinal_B_Spline_Interpolation<double>(func, L, n);

            /***** test : points (OK) ******/
            // auto XX = evenspace<double>(-5, 5, 100);
            // auto YY = get_map_list(s, XX);
            // cout << "XX = " << XX << "\nYY = " << YY << "\n";

            cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";

            vector<double> err;
            for(auto x : prob.err_points) err.push_back(fabs(s(x) - func(x)));
            cout << "err_values_Quadratic = " << err << "\n\n";
        }
        if(type == "NatureCubic") {
            auto s = Cardinal_B_Spline<double, 3>(L, R, n, Y);
            s.build(Cubic_Spline_Condition<double, Nature>());

            /***** test : points (OK) ******/
            // auto XX = evenspace<double>(-5, 5, 100);
            // auto YY = get_map_list(s, XX);
            // cout << "XX = " << XX << "\nYY = " << YY << "\n";

            cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";

            vector<double> err;
            for(auto x : prob.err_points) err.push_back(fabs(s(x) - func(x)));
            cout << "err_values_Nature = " << err << "\n\n";
        }
        if(type == "SecondDerivativesCubic") {
            auto s = Cardinal_B_Spline<double, 3>(L, R, n, Y);
            s.build(Cubic_Spline_Condition<double, Second_Derivatives>(cond[0], cond[1]));

            /***** test : points (OK) ******/
            // auto XX = evenspace<double>(-5, 5, 100);
            // auto YY = get_map_list(s, XX);
            // cout << "XX = " << XX << "\nYY = " << YY << "\n";

            cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";

            vector<double> err;
            for(auto x : prob.err_points) err.push_back(fabs(s(x) - func(x)));
            cout << "err_values_SD = " << err << "\n\n";
        }
        if(type == "CompleteCubic") {
            auto s = Cardinal_B_Spline<double, 3>(L, R, n, Y);
            s.build(Cubic_Spline_Condition<double, Complete>(cond[0], cond[1]));

            /***** test : points (OK) ******/
            // auto XX = evenspace<double>(-5, 5, 100);
            // auto YY = get_map_list(s, XX);
            // cout << "XX = " << XX << "\nYY = " << YY << "\n";

            cout << "s" + to_string(n) + type + " = " << s.to_python() << "\n\n";

            vector<double> err;
            for(auto x : prob.err_points) err.push_back(fabs(s(x) - func(x)));
            cout << "err_values_Complete = " << err << "\n\n";
        }
    }

    return 0;
}