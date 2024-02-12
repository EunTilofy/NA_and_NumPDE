#include <bits/stdc++.h>
#include "BVP.hpp"
#include "linear.hpp"
#include "calculator.hpp"
#include "function.hpp"
#include "function_generator/ExecCode2.hpp"

void breakline() {
    cerr << "-------------------------------------------\n";
}

int main() {
    Square_BVPsolver solver;
    // solver.solveProblem("data/1-Dirichlet-regular.json", /*print*/ 1);
    // solver.solveProblem("data/1-Neumann-regular.json", /*print*/ 1);
    // solver.solveProblem("data/1-mixed-regular.json", /*print*/ 1);
    // solver.solveProblem("data/1-Dirichlet-irregular.json", /*print*/1);
    // solver.solveProblem("data/1-Neumann-irregular.json", /*print*/ 1);
    // solver.solveProblem("data/1-Neumann-irregular2.json", /*print*/ 1);
    solver.solveProblem("data/1-mixed-irregular.json", /*print*/ 1);
    // breakline();
    solver.solveProblem("data/1-mixed-irregular2.json", /*print*/ 1);
    return 0;
}