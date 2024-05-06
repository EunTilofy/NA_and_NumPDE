#include<bits/stdc++.h>
#include "include/Multigrid_BVP.hpp"
using namespace std;

int main() {
    for (string BC : {"Dirichlet", "Neumann", "mixed"})
        for (string C : {"FMG", "V"})
            for (string I : {"linear", "quadratic"})
                for (string R : {"injection", "full_weight"})
                    for (int N = 32; N <= 512; N <<= 1) {
                        Multigrid_BVP_Problem prob;
                        prob.Accuracy = 1e-8;
                        prob.Dimension = 1;
                        prob.Domain_Border = {0, 1};
                        prob.Grid_n = N;
                        prob.answer = "exp(sin(x))";
                        prob.f = "exp(sin(x)) * (sin(x) - cos(x) * cos(x))";
                        prob.BC_Type = BC;
                        prob.Interpolation_opt = I;
                        prob.Cycle_Type = C;
                        prob.Restriction_opt = R;
                        if (BC[0] == 'D') {
                            prob.g["left"] = "1";
                            prob.g["right"] = "exp(sin(1))";
                        }
                        else if (BC[0] == 'N') {
                            prob.g["left"] = "-1";
                            prob.g["right"] = "exp(sin(1)) * cos(1)";
                        }
                        else {
                            prob.mixed_g["left"] = {"Neumann", "-1"};
                            prob.mixed_g["right"] = {"Dirichlet", "exp(sin(1))"};
                        }
                        prob.Need_Error = true;
                        string file;
                        file.resize(8);
                        file[0] = '1';
                        file[1] = 'a';
                        file[2] = '-';
                        file[3] = BC[0];
                        file[4] = C[0];
                        file[5] = I[0];
                        file[6] = R[0];
                        file[7] = '-';
                        file += to_string(N);
                        serialize_Json(prob, "./data/" + file + ".json");
                    }
    
    for (string BC : {"Dirichlet", "Neumann", "mixed"})
        for (string C : {"FMG", "V"})
            for (string I : {"linear", "quadratic"})
                for (string R : {"injection", "full_weight"})
                    for (int N = 32; N <= 512; N <<= 1) {
                        Multigrid_BVP_Problem prob;
                        prob.Accuracy = 1e-12;
                        prob.Dimension = 1;
                        prob.Domain_Border = {0, 1};
                        prob.Grid_n = N;
                        prob.answer = "log(1 + x*x)";
                        prob.f = "-2 * (1 - x*x) / ((1 + x*x) * (1 + x*x))";
                        prob.BC_Type = BC;
                        prob.Interpolation_opt = I;
                        prob.Cycle_Type = C;
                        prob.Restriction_opt = R;
                        if (BC[0] == 'D') {
                            prob.g["left"] = "0";
                            prob.g["right"] = "log(2)";
                        }
                        else if (BC[0] == 'N') {
                            prob.g["left"] = "0";
                            prob.g["right"] = "1";
                        }
                        else {
                            prob.mixed_g["left"] = {"Neumann", "0"};
                            prob.mixed_g["right"] = {"Dirichlet", "log(2)"};
                        }
                        prob.Need_Error = true;
                        string file;
                        file.resize(8);
                        file[0] = '1';
                        file[1] = 'b';
                        file[2] = '-';
                        file[3] = BC[0];
                        file[4] = C[0];
                        file[5] = I[0];
                        file[6] = R[0];
                        file[7] = '-';
                        file += to_string(N);
                        serialize_Json(prob, "./data/" + file + ".json");
                    }
    for (string BC : {"Dirichlet", "Neumann", "mixed"})
        for (string C : {"FMG", "V"})
            for (string I : {"linear", "quadratic"})
                for (string R : {"injection", "full_weight"})
                    for (int N = 32; N <= 512; N <<= 1) {
                        Multigrid_BVP_Problem prob;
                        prob.Accuracy = 1e-12;
                        prob.Dimension = 1;
                        prob.Domain_Border = {0, 1};
                        prob.Grid_n = N;
                        prob.answer = "sin(x) * sin(x)";
                        prob.f = "-2 * cos(2*x)";
                        prob.BC_Type = BC;
                        prob.Interpolation_opt = I;
                        prob.Cycle_Type = C;
                        prob.Restriction_opt = R;
                        if (BC[0] == 'D') {
                            prob.g["left"] = "0";
                            prob.g["right"] = "sin(1) * sin(1)";
                        }
                        else if (BC[0] == 'N') {
                            prob.g["left"] = "0";
                            prob.g["right"] = "sin(2)";
                        }
                        else {
                            prob.mixed_g["left"] = {"Neumann", "0"};
                            prob.mixed_g["right"] = {"Dirichlet", "sin(1) * sin(1)"};
                        }
                        prob.Need_Error = true;
                        string file;
                        file.resize(8);
                        file[0] = '1';
                        file[1] = 'c';
                        file[2] = '-';
                        file[3] = BC[0];
                        file[4] = C[0];
                        file[5] = I[0];
                        file[6] = R[0];
                        file[7] = '-';
                        file += to_string(N);
                        serialize_Json(prob, "./data/" + file + ".json");
                    }
    for (string BC : {"Dirichlet", "Neumann", "mixed"})
        for (string C : {"FMG", "V"})
            for (string I : {"linear", "quadratic"})
                for (string R : {"injection", "full_weight"})
                    for (int N = 32; N <= 512; N <<= 1) {
                        Multigrid_BVP_Problem prob;
                        prob.Accuracy = 1e-12;
                        prob.Dimension = 2;
                        prob.Domain_Border = {0, 1, 0, 1};
                        prob.Grid_n = N;
                        prob.answer = "exp(sin(x) + y)";
                        prob.f = "exp(sin(x) + y) * (sin(x) - cos(x) * cos(x) - 1)";
                        prob.BC_Type = BC;
                        prob.Interpolation_opt = I;
                        prob.Cycle_Type = C;
                        prob.Restriction_opt = R;
                        if (BC[0] == 'D') {
                            prob.g["left"] = "exp(y)";
                            prob.g["right"] = "exp(sin(1) + y)";
                            prob.g["down"] = "exp(sin(x))";
                            prob.g["up"] = "exp(sin(x) + 1)";
                        }
                        else if (BC[0] == 'N') {
                            prob.g["left"] = "-exp(y)";
                            prob.g["right"] = "cos(1) * exp(sin(1) + y)";
                            prob.g["down"] = "-exp(sin(x))";
                            prob.g["up"] = "exp(sin(x) + 1)";
                        }
                        else {
                            prob.mixed_g["left"] = {"Dirichlet", "exp(y)"};
                            prob.mixed_g["right"] = {"Neumann", "cos(1) * exp(sin(1) + y)"};
                            prob.mixed_g["down"] = {"Dirichlet", "exp(sin(x))"};
                            prob.mixed_g["up"] = {"Neumann", "exp(sin(x) + 1)"};
                        }
                        prob.Need_Error = true;
                        string file;
                        file.resize(7);
                        file[0] = '2';
                        file[1] = '-';
                        file[2] = BC[0];
                        file[3] = C[0];
                        file[4] = I[0];
                        file[5] = R[0];
                        file[6] = '-';
                        file += to_string(N);
                        serialize_Json(prob, "./data/" + file + ".json");
                    }
}