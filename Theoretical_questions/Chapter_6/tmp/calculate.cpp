#include<bits/stdc++.h>
using namespace std;

double f(double x) {
    return exp(-x*x);
}

int main() {
    double I = 0.746824133;
    auto solveA = [&](){
        for(int N = 1; N <= 1000; ++N) {
            double h = 1.0 / N;
            double tmp = 0.5*(f(0) + f(1));
            for(int i = 1; i < N; ++i) tmp += f(i*h);
            tmp /= N;
            if(fabs(tmp-I) < 5e-7) {
                cout << "Need " << N << " subintervals.->I_N^T = " << fixed << setprecision(9) << tmp << ".\n";
                break;
            }
        }
    };
    auto solveB = [&](){
        for(int N = 1; N <= 1000; ++N) {
            double h = 1.0 / N;
            double tmp = f(0) + f(1);
            for(int i = 1; i < N; ++i) tmp += ((i&1)?4:2)*f(i*h);
            tmp/=N*3;
            if(fabs(tmp-I) < 5e-7) {
                cout << "Need " << N << " subintervals.->I_N^S = " << fixed << setprecision(9) << tmp << ".\n";
                break;
            }
        }
    };
    solveA(); solveB();
}