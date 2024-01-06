#include <bits/stdc++.h>
#include "ExecCode.hpp"
#include "function.hpp"
#include "calculator.hpp"
#include "Spline.hpp"
#include "linear.hpp"
#define Python_style
#include "IO.hpp"

using namespace Spline;

using namespace std;

using NUM = double;

class func : public Function<NUM> {
public:
    NUM operator () (const NUM& x) const {
        return 1/(1+x*x);
    }
}f;

int main() {
    NUM L = -5, R = 5;
    cout << "h = ";
    vector<double> _h;
    for(int i = 10; i <= 100; i += 2) _h.push_back(1.0/(i-1.0));
    cout << _h << "\n";
    vector<NUM> x, y, y0;
    vector<NUM> points = evenspace(L, R, 100000);

    cout << "# ------------------- ppForm linear -------------------\n";
    vector<NUM> pp1_i, pp1_2;
    for(int N = 10; N <= 100; N += 2) {
        x = evenspace<NUM>(L, R, N);
        y0 = get_map_list<func, NUM>(f, x);
        ppForm_Spline<NUM, 1> s(x, y0);
        s.build();
        pp1_i.push_back(s.get_error_i(f, points));
        pp1_2.push_back(s.get_error_2(f, points));
    }
    cout << "pp1_i = " << pp1_i << "\npp1_2 = " << pp1_2 << "\n";

    cout << "# ------------------- ppForm order 3 (complete) -------------------\n";
    vector<NUM> pp3_i, pp3_2;
    for(int N = 10; N <= 100; N += 2) {
        x = evenspace<NUM>(L, R, N);
        y0 = get_map_list<func, NUM>(f, x);
        ppForm_Spline<NUM, 3> s(x, y0);
        s.build(Cubic_Spline_Condition<NUM, Complete>(0.014792899408284, -0.014792899408284));
        pp3_i.push_back(s.get_error_i(f, points));
        pp3_2.push_back(s.get_error_2(f, points));
    }
    cout << "pp3_i = " << pp3_i << "\npp3_2 = " << pp3_2 << "\n";


    cout << "# ------------------- B-Form linear -------------------\n";
    vector<NUM> b1_i, b1_2;
    for(int N = 10; N <= 100; N += 2) {
        x = evenspace<NUM>(L, R, N);
        y0 = get_map_list<func, NUM>(f, x);
        B_Spline<NUM, 1> s(x, y0);
        s.build();
        b1_i.push_back(s.get_error_i(f, points));
        b1_2.push_back(s.get_error_2(f, points));
    }
    cout << "b1_i = " << b1_i << "\nb1_2 = " << b1_2 << "\n";

    cout << "# ------------------- B-Form order 2 -------------------\n";
    vector<NUM> b2_i, b2_2;
    for(int N = 10; N <= 100; N += 2) {
        x = evenspace<NUM>(L, R, N);
        y0 = get_map_list<func, NUM>(f, x);
        B_Spline<NUM, 2> s(x, y0);
        s.build({{0, 1, 0.014792899408284}});
        b2_i.push_back(s.get_error_i(f, points));
        b2_2.push_back(s.get_error_2(f, points));
    }
    cout << "b2_i = " << b2_i << "\nb2_2 = " << b2_2 << "\n";


    cout << "# ------------------- B-Form order 3 (complete) -------------------\n";
    vector<NUM> b3_i, b3_2;
    for(int N = 10; N <= 100; N += 2) {
        x = evenspace<NUM>(L, R, N);
        y0 = get_map_list<func, NUM>(f, x);
        B_Spline<NUM, 3> s(x, y0);
        s.build({{0, 1, 0.014792899408284}, {1, 1, -0.014792899408284}});
        b3_i.push_back(s.get_error_i(f, points));
        b3_2.push_back(s.get_error_2(f, points));
    }
    cout << "b3_i = " << b3_i << "\nb3_2 = " << b3_2 << "\n";

    cout << "# ------------------- B-Form order 4 -------------------\n";
    vector<NUM> b4_i, b4_2;
    for(int N = 10; N <= 100; N += 2) {
        x = evenspace<NUM>(L, R, N);
        y0 = get_map_list<func, NUM>(f, x);
        B_Spline<NUM, 4> s(x, y0);
        s.build({{0, 1, 0.014792899408284}, {1, 1, -0.014792899408284}, {0, 2, 0.008420573509330906}});
        b4_i.push_back(s.get_error_i(f, points));
        b4_2.push_back(s.get_error_2(f, points));
    }
    cout << "b4_i = " << b4_i << "\nb4_2 = " << b4_2 << "\n";

    cout << "# ------------------- B-Form order 5 -------------------\n";
    vector<NUM> b5_i, b5_2;
    for(int N = 10; N <= 100; N += 2) {
        x = evenspace<NUM>(L, R, N);
        y0 = get_map_list<func, NUM>(f, x);
        B_Spline<NUM, 5> s(x, y0);
        s.build({{0, 1, 0.014792899408284}, {1, 1, -0.014792899408284}, {0, 2, 0.008420573509330906}, {1, 2, 0.008420573509330906}});
        b5_i.push_back(s.get_error_i(f, points));
        b5_2.push_back(s.get_error_2(f, points));
    }
    cout << "b5_i = " << b5_i << "\nb5_2 = " << b5_2 << "\n";
}

/*

[[0, 1, 0.014792899408284], [1, 1, -0.014792899408284]],
[[0, 2, 0.008420573509330906], [1, 2, 0.008420573509330906]], 
[[0, 2, 0.008420573509330906], [1, 2, 0.008420573509330906]], 
[[0, 2, 0.008420573509330906], [1, 2, 0.008420573509330906], [0, 1, 0.014792899408284]], 
[[0, 1, 0.014792899408284], [0, 2, 0.008420573509330906], [1, 1, -0.014792899408284], [1, 2, 0.008420573509330906]]]


*/