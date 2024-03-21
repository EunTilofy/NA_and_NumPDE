/**
 * @file test.cpp
 * @author EunTilofy (papercloud@zju.edu.cn)
 * @brief This is only a test file for execcode2.hpp, execcode2d.hpp
 * @version 0.1
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <bits/stdc++.h>
#include "ExecCode2.hpp"
#include "../function.hpp"
using namespace std;

int main() {
    REGISTER_FUNCTION_FROM_STRING2(f1, "abs(x)", double, double);
    cout << f1(0) << " " << f1(1) << " " << f1(-2) << "\n"; // 0, 1, 2
    REGISTER_FUNCTION_FROM_STRING2(f2, "pow(x, 2)", double, double);
    cout << f2(0) << " " << f2(1) << " " << f2(-2) << "\n"; // 0, 1, 4
    REGISTER_FUNCTION_FROM_STRING2(f3, "log10(x)", double, double);
    cout << f3(10) << " " << f3(100) << " " << f3(1000) << "\n"; // 1, 2, 3
    REGISTER_FUNCTION_FROM_STRING2(f4, "pow(pow(x,1.0),log10(x))", double, double);
    cout << f4(10) << " " << f4(100) << " " << f4(1000) << "\n"; // 10, 10000, 1000000000
    REGISTER_FUNCTION_FROM_STRING2(f5, "-pow(pow(x,1.0),log10(x))", double, double);
    cout << f5(10) << " " << f5(100) << " " << f5(1000) << "\n"; // -10, -10000, -1000000000
    REGISTER_FUNCTION_FROM_STRING2(f6, "pow(x*x+2*x+1, 1)/((x+1)-(x-1))", double, double);
    cout << f6(0) << " " << f6(1) << " " << f6(2) << "\n"; // 0.5, 2, 4.5
    REGISTER_FUNCTION_FROM_STRING2(f7, "pow(x*x+2*x+1, 1)/((x+1)+(x+1)/(x+1))", double, double);
    cout << f7(0) << " " << f7(1) << " " << f7(2) << "\n"; // 0.5, 1.333,  2.25
    REGISTER_FUNCTION_FROM_STRING_2d(f8, "log(1 + x*x + y * y)", double, double);
    cout << f8(0, 0) << " " << f8(0, exp(1)) << " " << f8(exp(1), exp(1)) << "\n"; // 0 2.12693 2.75862
    return 0;
}

