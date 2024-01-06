#include <bits/stdc++.h>
#include "serialization.hpp"
#include "DLS.hpp"

using namespace std;

int main(int argc, char** argv) {
    struct problem {
        vector<double> x;
        vector<double> y;
        REGISTER_SERIALIZATION_JSON(x, y);
    } prob;

    if(argc == 1) {
        std::cerr << "No input file!" << std::endl;
        return 0;
    }

    deserialize_Json(prob, argv[1]);

    auto SolA = [&] (problem & prob) {
        cerr << "--------------- results of Problem A ---------------\n";
        vector<double> rho(prob.x.size(), 1.0);
        DLS dls_solver;
        auto res = dls_solver.solveNormal(prob.x, prob.y, rho);
        cerr << Poly_n(res) << "\n";
    };

	auto SolB = [&] (problem & prob) {
        cerr << "--------------- results of Problem B ---------------\n";
        DLS dls_solver;
        auto res = dls_solver.solveQR(prob.x, prob.y);
        cerr << Poly_n(res) << "\n";
    };


	SolA(prob);
	SolB(prob);
}