/******************************************************
 * Ver 1.0 updated on Jan. 3rd, 2024, by EunTilofy
 * execute code from a string, only support one param as input.
 * make sure the input param has only one character, like, a, A, x, y.
 * ex. REGISTER_FUNTION_FROM_STRING(f, "x + x", double, double)
 *                                 name function XType  YType
 * usage. f(1) -> 2, f(2) -> 4
 * 
 * !!IMPORTANT!! : this method may be dangerous since it use dynamic linking.
 * !!POSSIBLE WAY TO IMPROVE!! : write a string parser to solve 
 *                              number function, using latex style. (TO BE CONTINUED)
*******************************************************/

#ifndef __EXEC_CODE__
#define __EXEC_CODE__

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <dlfcn.h>
using namespace std;

int cnt = 0;

template<class XType, class Ytype = XType>
Ytype (*executeCode(const std::string& code))(XType) {
    // cerr << "Parse code : " << code << "\n";
    std::ofstream codeFile("tmp/temp_code" + to_string(cnt) + ".cpp");
    codeFile << code;
    codeFile.close();
    std::system(("g++ -shared -fPIC -o tmp/temp_code" + to_string(cnt) + ".so tmp/temp_code" + to_string(cnt) + ".cpp").c_str());
    void* libraryHandle = dlopen(("./tmp/temp_code" + to_string(cnt) + ".so").c_str(), RTLD_LAZY);
    if (!libraryHandle) {
        std::cerr << "Error loading the library: " << dlerror() << std::endl;
        return nullptr;
    }
    typedef Ytype (*FunctionType)(XType);
    FunctionType getvalue = reinterpret_cast<FunctionType>(dlsym(libraryHandle, ("__tmpfunction"+to_string(cnt)).c_str()));
    if (!getvalue) {
        std::cerr << "Error loading the function: " << dlerror() << std::endl;
        return nullptr;
    }
    return getvalue;
    // dlclose(libraryHandle);
}

template<class XType, class YType = XType>
YType (*preexecuteCode(const std::string& code, const std::string x, const std::string y))(XType) {
    ++cnt;
    std::string var = "x";
    for(int i = 0; i < code.size(); ++i) {
        if(isalpha(code[i])) { 
            if (i + 2 < code.size() && (code.substr(i, 3) == "sin"
                                     || code.substr(i, 3) == "cos"
                                     || code.substr(i, 3) == "exp"
                                     || code.substr(i, 3) == "tan"
                                     || code.substr(i, 3) == "abs"
                                     || code.substr(i, 3) == "pow")) {
                                        i += 2;
                                     } else {var = code[i]; break; }
        }
    }
    return executeCode<XType, YType>("#include<bits/stdc++.h>\nextern \"C\" " + y + " __tmpfunction" 
        + to_string(cnt) + "(" + y + " " + var +") { return (" + y + ")(" + code + "); }");
}

#define REGISTER_FUNCTION_FROM_STRING(name, str, Xtype, Ytype) \
    Ytype (*getvalue_##name)(Xtype); \
    getvalue_##name = preexecuteCode<Xtype, Ytype>(str, #Xtype, #Ytype); \
    class _fUnCtIoN_##name : public Function<Xtype, Ytype> { \
        function<Ytype(Xtype)> opt; \
    public: \
        _fUnCtIoN_##name(Ytype (*getvalue)(Xtype)) : opt(getvalue) {} \
        Ytype operator() (const Xtype &x) const { \
            Xtype xx = x; return opt(xx); \
        } \
    }; \
    _fUnCtIoN_##name name(getvalue_##name); \

#endif