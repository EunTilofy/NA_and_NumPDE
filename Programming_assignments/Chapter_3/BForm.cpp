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
    vector<vector<double>> X;
    vector<int> Order;
    vector<vector<vector<double>>> BC;
    REGISTER_SERIALIZATION_JSON(function, X, Order, BC);
    REGISTER_OUTPUT_NAME(Problem, function, X, Order, BC);
} prob;

int main() {
    // Read from json file
    deserialize_Json(prob, "data/BForm.json");
    // parse function from string
    REGISTER_FUNCTION_FROM_STRING(func, prob.function, double, double);
    // test -> func(1) = 0.5 (OK)
    // cerr << func(1) << "\n";
    
    for(int i = 0; i < prob.Order.size(); ++i) {
        int order = prob.Order[i];
        vector<double> x = prob.X[i];
        vector<double> y = get_map_list(func, x);
        vector<tuple<bool, int, double>> bc;
        for(int j = 0; j < prob.BC[i].size(); ++j)
            bc.push_back({prob.BC[i][j][0], prob.BC[i][j][1], prob.BC[i][j][2]});
        if(order == 1) {
            B_Spline<double, 1> s(x, y);
            s.build();

            /***** test : points (OK) ******/
            // auto XX = evenspace<double>(-5, 5, 100);
            // auto YY = get_map_list(s, XX);
            // cout << "XX = " << XX << "\nYY = " << YY << "\n";

            cout << "s1 = " << s.to_python() << "\n\n";
        } if(order == 2) {
            B_Spline<double, 2> s(x, y);
            s.build(bc);
            cout << "s2 = " << s.to_python() << "\n\n";
        }
        if(order == 3) {
            B_Spline<double, 3> s(x, y);
            s.build(bc);

            /***** test : points (OK) ******/
            // auto XX = evenspace<double>(-5, 5, 100);
            // auto YY = get_map_list(s, XX);
            // cerr << "XX = " << XX << "\nYY = " << YY << "\n";

            cout << "s3 = " << s.to_python() << "\n\n";
        } if(order == 4) {
            B_Spline<double, 4> s(x, y);
            s.build(bc);
            cout << "s4 = " << s.to_python() << "\n\n";
        } if(order == 5) {
            B_Spline<double, 5> s(x, y);
            s.build(bc);
            cout << "s5 = " << s.to_python() << "\n\n";
        } if(order == 7) {
            B_Spline<double, 7> s(x, y);
            s.build(bc);
            cout << "s7 = " << s.to_python() << "\n\n";
        } if(order == 9) {
            B_Spline<double, 9> s(x, y);
            s.build(bc);
            cout << "s9 = " << s.to_python() << "\n\n";
        }

    }
    return 0;
}