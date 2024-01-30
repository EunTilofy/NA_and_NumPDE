#include <bits/stdc++.h>
#include "BVP.hpp"
#include "linear.hpp"
#include "calculator.hpp"
#include "function.hpp"
#include "function_generator/ExecCode2.hpp"

int main() {
    Square_BVPsolver solver;
    solver.readProblem("1-mixed-irregular.json");
    solver.printProblem();

    // solver.readProblem("1-Dirichlet-regular.json");
    // solver.printProblem();
    return 0;
}