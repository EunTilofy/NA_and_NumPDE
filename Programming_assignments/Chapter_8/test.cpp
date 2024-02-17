#include <bits/stdc++.h>
#include "Multigrid_BVP.hpp"
#include "linear.hpp"
#include "calculator.hpp"
#include "function.hpp"
#include "function_generator/ExecCode2.hpp"

void breakline() {
    cerr << "-------------------------------------------\n";
}

using namespace linear;

int main() {
    Multigrid_BVPsolver solver;
    // solver.solveProblem("data/1-DFlf-16.json", /*print*/ 1);
    // solver.solveProblem("data/1-DVli-16.json", /*print*/ 1);
    // solver.solveProblem("data/1-mFlf-16.json", /*print*/ 1);
    // solver.solveProblem("data/1-mVlf-16.json", /*print*/ 1);
    // solver.solveProblem("data/1-NFli-16.json", /*print*/ 1);
    // solver.solveProblem("data/1-NVli-16.json", /*print*/ 1);

    // solver.solveProblem("data/1-DFlf-32.json", /*print*/ 1);
    // solver.solveProblem("data/1-DVli-32.json", /*print*/ 1);
    // solver.solveProblem("data/1-mFlf-32.json", /*print*/ 1);
    // solver.solveProblem("data/1-mVlf-32.json", /*print*/ 1);
    // solver.solveProblem("data/1-NFli-32.json", /*print*/ 1);
    // solver.solveProblem("data/1-NVli-32.json", /*print*/ 1);

    // solver.solveProblem("data/1-mFlf-512.json", /*print*/ 1);
    // solver.solveProblem("data/1-NVqi-512.json", /*print*/ 1);

    // solver.solveProblem("data/2-DVlf-8.json", 1);
    solver.solveProblem("data/2-DVlf-512.json", 1);
    // solver.solveProblem("data/2-DVlf-32.json", 1);
    // solver.solveProblem("data/2-mFli-16.json", 1);
    // solver.solveProblem("data/2-mFli-32.json", 1);
    // solver.solveProblem("data/2-NFqf-16.json", 1);
    // solver.solveProblem("data/2-NFqf-32.json", 1);
}