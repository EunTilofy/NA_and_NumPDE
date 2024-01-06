#include<bits/stdc++.h>
#include "IO.hpp"
#include "linear.hpp"
#include "function.hpp"
#include "calculator.hpp"

using namespace std;
using namespace linear;
using namespace norm;

struct a {
public:
    int b;
    string c;
    map<int,int> d;
    pair<string, double> e;
    REGISTER_OUTPUT(a, b, c, d, e)
};

class myfunction : public Function<Vec<double>>  {
public:
    myfunction(int _d1, int _d2 = 0) :Function(_d1, _d2){}
    Vec<double> operator() (const Vec<double>& x) const{
        assert(x.size == Function<Vec<double>>::d1);
        return x;
    }
    Vec<double> Diff (const Vec<double>& x) const{
        assert(x.size == Function<Vec<double>>::d1);
        return x;
    }
};


int main() {
    a x{10, "hello", {{1,2}, {3, 4}}, {"string", 1.01}};
    cout << x << "\n";
    cout << "aaaaa" << "\n";
    Vec<double> v({1, 2, 3}), w({2,3,4});
    cout << v;

    myfunction F(3, 3);
    cout << F({1,1,3}) << F.Diff({1,2,2}) << "\n";

    Mat<double> m(3, 3, {{1,2,3},{1,2,3},{1,2,3}});
    Vec<double> vv(3);

    cout << m << "\n" << vv << "\n";
    cout << m[0][2] << " " << vv[1] << "\n";
    cout << w << " " << w + v << "\n";

    RowVec<double> rv({1, 1, 1, 2});
    Vec<double> cv({1, 1, 1, 2});
    rv = ~cv;
    cv = ~rv;
    Mat<double> test=~cv;
    Mat<double> mrv(rv);
    cout << Norm1(mrv);
    cout << " " << Normi(mrv) << "\n";
    rv = mrv;
    mrv = rv;
    mrv = Mat<double>(rv);

    cout << rv << " " << cv << "\n";
    cout << rv*cv << "\n";
    cout << cv*rv << "\n";

    for(auto &x : rv) {
        cout << x << " ";
        x += 2;
    }
    cout << "\n" << rv << "\n";
    cout << mrv << "\n";

    cout << Norm1(mrv);
    cout << " " << Normi(mrv) << "\n";
}
