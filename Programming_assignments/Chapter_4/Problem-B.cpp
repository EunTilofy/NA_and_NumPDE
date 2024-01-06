#include<bits/stdc++.h>
using namespace std;

const int Beta = 2, L = -1, U = 1, p = 3;

int main() {

    cerr << "Beta = 2, p = 3, L = -1, U = 1\n";
    cerr << "UFL = " << pow(Beta, L) << "\n";
    cerr << "OFL = " << pow(Beta, U) * (Beta - pow(Beta, 1-p)) << endl;
    vector<double> num, subnum;
    num.push_back(0);
    double eps = pow(Beta, 1-p);
    for(int e = L; e <= U; ++e) {
        for(int M = 1; M < pow(Beta, p); ++M) {
            if(M>=pow(Beta, p-1)) {
                num.push_back(M * eps * pow(Beta, e));
                num.push_back(-M * eps * pow(Beta, e));
            }
            else if(e == -1) {
                subnum.push_back(M * eps * pow(Beta, e));
                subnum.push_back(-M * eps * pow(Beta, e));
            }
        }
    }
    sort(num.begin(), num.end());
    sort(subnum.begin(), subnum.end());
    cerr << num.size() << " numbers in F : ";
    for(auto x : num) cerr << x << ",\n"[x == num.back()];
    cerr << subnum.size() << " subnumbers in F : ";
    for(auto x : subnum) cerr << x << ",\n"[x == subnum.back()];
    
    return 0;
}