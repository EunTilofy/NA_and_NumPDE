#include<bits/stdc++.h>
using namespace std;
#include"../include/BVP.hpp"
#include"../include/serialization.hpp"
using namespace Serialization_Json;

void make(Square_BVP_Problem o, string name) {
     o.Grid_n = 8;
    serialize_Json(o, name + "-a8.json");
     o.Grid_n = 16;
    serialize_Json(o, name + "-b16.json");
     o.Grid_n = 32;
    serialize_Json(o, name + "-c32.json");
     o.Grid_n = 64;
    serialize_Json(o, name + "-d64.json");
     o.Grid_n = 128;
    serialize_Json(o, name + "-e128.json");
}

Square_BVP_Problem o;

// void init() {
//     o.BC_Type = "Dirichlet";
//     o.Domain_Type = "Rregular";
//          string s = "regular";
//     o.Domain_Border = {0, 1, 0, 1};
//     o.f = "2*sin(x)*cos(y)";
//     // o.Center = {0.41, 0.55};
//     // o.R = 0.15;

//     // Dirichlet
//     o.g["all"] = "sin(x)*cos(y)";

//     // Neumann
//     // o.g["left"] = "-cos(x)*cos(y)";
//     // o.g["right"] = "cos(x)*cos(y)";
//     // o.g["up"] = "-sin(x)*sin(y)";
//     // o.g["down"] = "sin(x)*sin(y)";
//     // o.g["D"] = "(x-0.41)/0.15*cos(x)*cos(y)-(y-0.55)/0.15*sin(x)*sin(y)";

//     // mixed
//     // o.mixed_g["down"] = {"Dirichlet", "sin(x)*cos(y)"};
//     // o.mixed_g["left"] = {"Dirichlet", "sin(x)*cos(y)"};
//     // o.mixed_g["right"] = {"Neumann", "cos(x)*cos(y)"};
//     // o.mixed_g["up"] = {"Neumann", "-sin(x)*sin(y)"};
//     // o.mixed_g["D"] = {"Dirichlet", "sin(x)*cos(y)"};

//     o.Need_Error = 1;
//     o.answer = "sin(x)*cos(y)";
//     make(o, "2-"+o.BC_Type+"-"+s);
// }


void init2() {
    o.BC_Type = "mixed";
    o.Domain_Type = "Regular";
         string s = "regular";
    o.Domain_Border = {0, 1, 0, 1};
    o.f = "(4*x*x+4*y*y-4*(1+x*x+y*y))/(1+x*x+y*y)/(1+x*x+y*y)";


    // o.Center = {0.41, 0.55};
    // o.R = 0.15;

    // Dirichlet
    // o.g["all"] = "log(1+x*x+y*y)";

    // Neumann
    // o.g["left"] = "-2*x/(1+x*x+y*y)";
    // o.g["right"] = "2*x/(1+x*x+y*y)";
    // o.g["up"] = "2*y/(1+x*x+y*y)";
    // o.g["down"] = "-2*y/(1+x*x+y*y)";
    // o.g["D"] = "(x-0.41)/0.15*2*x/(1+x*x+y*y)+(y-0.55)/0.15*2*y/(1+x*x+y*y)";

    // mixed
    o.mixed_g["down"] = {"Dirichlet", "log(1+x*x+y*y)"};
    o.mixed_g["left"] = {"Neumann", "-2*x/(1+x*x+y*y)"};
    o.mixed_g["right"] = {"Neumann", "2*x/(1+x*x+y*y)"};
    o.mixed_g["up"] = {"Dirichlet", "log(1+x*x+y*y)"};
    // o.mixed_g["D"] = {"Dirichlet", "log(1+x*x+y*y)"};

    o.Need_Error = 1;
    o.answer = "log(1+x*x+y*y)";
    make(o, "3-"+o.BC_Type+"-"+s);
}

int main() {
    init2();
}