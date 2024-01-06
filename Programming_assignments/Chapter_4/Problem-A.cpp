#include<bits/stdc++.h>
#include "function.hpp"

using namespace std;

class func_F : public Function<double> {
public:
	virtual double operator()(const double& x) const{
		return x*x*x*x*x*x*x*x-8*x*x*x*x*x*x*x+28*x*x*x*x*x*x
        -56*x*x*x*x*x+70*x*x*x*x-56*x*x*x+28*x*x-8*x+1;
	}
}f;

class func_G : public Function<double> {
public:
	virtual double operator()(const double& x) const{
		return (((((((x-8)*x+28)*x-56)*x+70)*x-56)*x+28)*x-8)*x+1;
	}
}g;

class func_H : public Function<double> {
public:
	virtual double operator()(const double& x) const{
		return (x-1)*(x-1)*(x-1)*(x-1)*(x-1)*(x-1)*(x-1)*(x-1);
	}
}h;

int main() {
	ofstream OUT("Output_A.csv");
	OUT << "x,f,g,h\n";
    double STEP = 0.0002, x = 0.99;
    for(int i = 0; i <= 100; ++i, x += STEP) {
        OUT << x << "," << f(x) << "," << g(x) << "," << h(x) << "\n";
    }
	return 0;
}