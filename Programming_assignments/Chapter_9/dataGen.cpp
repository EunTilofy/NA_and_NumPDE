#include <bits/stdc++.h>
#include "serialization.hpp"
#include "Multigrid_BVP.hpp"
using namespace std;

int main() {
    cout << "----------------------------------------------------------------------------\n";
    cout << "This is a helper for generating data of BVP problems (for multigrid solver).\n";
    cout << "----------------------------------------------------------------------------\n";
    while(1) {
        cout << "A NEW BVP PROBLEM ====>\n";
        Multigrid_BVP_Problem prob;
        cout << "Boundary Condition Type: ";
        cin >> prob.BC_Type;
        if(prob.BC_Type != "mixed" && prob.BC_Type != "Dirichlet" && prob.BC_Type != "Neumann") {
            std::cout << "not defined!\n";
            continue;
        }
        
        cout << "Domain Type : ";
        cin >> prob.Domain_Type;
        if(prob.Domain_Type != "Regular" && prob.Domain_Type != "Irregular") {
            std::cout << "not defined!\n";
            continue;
        }
        cout << "Function Dimension : ";
        cin >> prob.Dimension;
        cout << "Domain Border " << (prob.Dimension == 1 ? "[l, r]" : "[xl, xr, yl, yr]") << ": ";
        prob.Domain_Border.clear();
        for(int i = 0; i < 2*prob.Dimension; ++i) {
            double x;
            cin >> x;
            prob.Domain_Border.push_back(x);
        }

        cout << "Grid_n : ";
        cin >> prob.Grid_n;
        if(prob.Grid_n < 2 || prob.Grid_n > 8192) {
            std::cout << "Not in range [2, 8192]!";
            continue;
        }
        
        cout << "Cycle Type [FMG or V] : ";
        cin >> prob.Cycle_Type;
        if(prob.Cycle_Type != "FMG" && prob.Cycle_Type != "V") {
            std::cout << "not defined!\n";
            continue;
        }
        cout << "Restriction Operator Type [injection or full_weight] : ";
        cin >> prob.Restriction_opt;
        if(prob.Restriction_opt != "injection" && prob.Restriction_opt != "full_weight") {
            std::cout << "not defined!\n";
            continue;
        }
        cout << "Interpolation Operator Type [linear or quadratic] : ";
        cin >> prob.Interpolation_opt;
        if(prob.Interpolation_opt != "linear" && prob.Interpolation_opt != "quadratic") {
            std::cout << "not defined!\n";
            continue;
        }
        cout << "Max Iteration : ";
        cin >> prob.Max_Iteration;
        cout << "Accuracy : ";
        cin >> prob.Accuracy;

        cout << "f : ";
        cin >> prob.f;

        if(prob.BC_Type == "mixed") {
            string type, func;
            if(prob.Dimension == 1) {
            for(string x : {"left", "right"}) {
                cout << x << " : ";
                cin >> type >> func;
                if(type != "Dirichlet" && type != "Neumann") {
                    std::cout << "not defined!\n";
                    continue;
                }
                prob.mixed_g[x] = {type, func};
            }  
            }
            else {
            for(string x : {"down", "left", "right", "up"}) {
                cout << x << " : ";
                cin >> type >> func;
                if(type != "Dirichlet" && type != "Neumann") {
                    std::cout << "not defined!\n";
                    continue;
                }
                prob.mixed_g[x] = {type, func};
            }
            }
        } else {
            cout << "If the function of BC are the same? [y or n] : ";
            string func;
            string sa; cin >> sa; if(sa[0] == 'y' || sa[0] == 'Y') {
                cout << "condition : ";
                cin >> func;
                prob.g["all"] = func;
            } else {
            if(prob.Dimension == 2)
            for(string x : {"down", "left", "right", "up"}) {
                cout << x << " : ";
                cin >> func;
                prob.g[x] = func;
            } else
            for(string x : {"left", "right"}) {
                cout << x << " : ";
                cin >> func;
                prob.g[x] = func;
            }
            }
        }

        cout << "Need error analysis or not? [y or n] : ";
        string er; cin >> er; if(er[0] == 'y' || er[0] == 'Y') {
            prob.Need_Error = 1;
            cout << "answer : ";
            cin >> prob.answer;
        }

        try {
            prob._self_checked();
        } catch (char const* e) {
            cout << "BVP problem not satisfiable : " << e << "\n";
            continue;
        }
        
        cout << "Load file name : ";
        std::string filename;
        cin >> filename;

        serialize_Json(prob, filename);

        cout << "Your problem has been stored in : [" << filename << "].\n";

        cout << "Quit or not? [y or n] : ";
        string qi; cin >> qi; if(qi[0] == 'Y' || qi[0] == 'y') break;
    }

}