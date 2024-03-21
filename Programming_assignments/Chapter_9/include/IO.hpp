/**********************************************************************
 * Ver 2.6 updated on Jan. 4th, 2023, by EunTilofy
 * In this version, 
 * 1, add REGISTER_OUTPUT_NAME and REGISTER_OUTPUT for user defined types
 * 2, modify the output format of std::string
 *    (a) when it is is a member of other object, use '\"contant\"'
 *    (b) just output 'contant' otherwise
 * 3, add C_style & Python_style control
 * 4, add std::tuple
 * This version has been fully tested, just enjoy!
***********************************************************************/
#ifndef _IO_HPP_
#define _IO_HPP_

#include <bits/stdc++.h>

// #define C_style
#define Python_style

#ifdef Python_style

const char __io__LR__[] = {'[',']'};

#else

const char __io__LR__[] = {'{','}'};

#endif


/***************************************************
 * @TODO 0927/2023
 * 1. fix the function of input '>>';
 * 2. fix arrays and other C-type objects.
****************************************************/

/**********************************************************************
 *  format of output of STL types
***********************************************************************/

// change the format of printing a string type (when it's a member) (designed in Sep. 2023)
template<typename T>
void OUTPUT_MEMBER(std::ostream& out, const T& o);
void OUTPUT_MEMBER(std::ostream& out, const std::string& o);

// common type of STL (designed in June. 2023)
template<typename T1, typename T2>
std::ostream& operator << (std::ostream& out, const std::pair<T1, T2> &o);
template<typename T1, typename T2, typename T3>
std::ostream& operator << (std::ostream& out, const std::tuple<T1, T2, T3> &o);
template<typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T> &o);
template<typename T>
std::ostream& operator << (std::ostream& out, const std::set<T> &o);
template<typename T>
std::ostream& operator << (std::ostream& out, const std::list<T> &o);
template<typename T1, typename T2>
std::ostream& operator << (std::ostream& out, const std::map<T1, T2> &o);

template<typename T1, typename T2>
std::ostream& operator << (std::ostream& out, const std::pair<T1, T2> &o) {
  out << __io__LR__[0]; OUTPUT_MEMBER(out, o.first);
  out << ", "; OUTPUT_MEMBER(out, o.second);
  out << __io__LR__[1];
  return out;
}
template<typename T1, typename T2, typename T3>
std::ostream& operator << (std::ostream& out, const std::tuple<T1, T2, T3> &o) {
  out << __io__LR__[0];
  auto &[x, y, z] = o;
  OUTPUT_MEMBER(out, x); out << ", "; OUTPUT_MEMBER(out, y);
  out << ", "; OUTPUT_MEMBER(out, z);
  out << __io__LR__[1];
  return out;
}
template<typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T> &o) {
  out << __io__LR__[0];
  bool Flag = 0;
  for(auto & item : o) {
    if(Flag) out << ", ";
    else Flag = 1;
    OUTPUT_MEMBER(out, item);
  }
  out << __io__LR__[1];
  return out;
}
template<typename T>
std::ostream& operator << (std::ostream& out, const std::set<T> &o) {
  out << __io__LR__[0];
  bool Flag = 0;
  for(auto & item : o) {
    if(Flag) out << ", ";
    else Flag = 1;
    OUTPUT_MEMBER(out, item);
  }
  out << __io__LR__[1];
  return out;
}
template<typename T>
std::ostream& operator << (std::ostream& out, const std::list<T> &o) {
  out << __io__LR__[0];
  bool Flag = 0;
  for(auto & item : o) {
    if(Flag) out << ", ";
    else Flag = 1;
    OUTPUT_MEMBER(out, item);
  }
  out << __io__LR__[1];
  return out;
}
template<typename T1, typename T2>
std::ostream& operator << (std::ostream& out, const std::map<T1, T2> &o) {
  out << __io__LR__[0];
  bool Flag = 0;
  for(auto & [key, value] : o) {
    if(Flag) out << ", ";
    else Flag = 1;
    out << __io__LR__[0];OUTPUT_MEMBER(out, key);
    out << ": ";OUTPUT_MEMBER(out, value);
    out << __io__LR__[1];
  }
  out << __io__LR__[1];
  return out;
}

/*****************************************************************************
 * macro definition for output user defined type (designed in Sep. 2023)
 * For example:
 * struct a {
 * public:
 *     int b;
 *     string c;
 *     map<int,int> d;
 *     pair<string, double> e;
 *     REGISTER_OUTPUT_NAME(a, b, c, d, e)
 * };
 * (!IMPORTANT!) Remember to put it at the end of the class declaration 
 *               for the member after print() will be public.
 * REGISTER_OUTPUT() : do not print out the name of the member
 * REGSTER_OUTPUT_NAME() : print out the name of the member
*****************************************************************************/

#ifndef REGISTER_FUNCTION
#define REGISTER_FUNCTION

// register function for members
// const function
template <typename Func, typename... Members>
void register_const_func(const Func& func, const Members&... members) {
    (func(members), ...);
}
// normal function
template <typename Func, typename... Members>
void register_normal_func(const Func& func, Members&... members) {
    (func(members), ...);
}

#endif

template<typename T>
void OUTPUT_MEMBER(std::ostream& out, const T& o) {
    out << o;
}
void OUTPUT_MEMBER(std::ostream& out, const std::string& o) {
    out << "\"" << o << "\"";
}
#define REGISTER_OUTPUT_NAME(Type, ...) \
    void print(std::ostream& out) const { \
        string t = #__VA_ARGS__, tmp = ""; \
        std::vector<string> mem_names; \
        for(char &x : t) { \
            if(x == ',') mem_names.push_back(tmp), mem_names.push_back(", "), tmp.clear(); \
            else if(x != ' ') tmp+=x; \
        } \
        mem_names.push_back(tmp); \
        bool fl = 0; \
        reverse(mem_names.begin(), mem_names.end()); \
        if(mem_names.size() > 2) out << __io__LR__[0], fl = 1; \
        register_const_func([&](const auto& member) { \
            out << mem_names.back() << " = "; \
            OUTPUT_MEMBER(out, member); \
            mem_names.pop_back(); \
            if(mem_names.size()) { \
                out << mem_names.back(); \
                mem_names.pop_back(); \
            } \
        }, __VA_ARGS__); \
        if(fl) out << __io__LR__[1]; \
    }\
    friend std::ostream& operator << (std::ostream& out, const Type& o) { \
        o.print(out); \
        return out; \
    }
#define REGISTER_OUTPUT(Type, ...) \
    void print(std::ostream& out) const { \
        string t = #__VA_ARGS__; \
        int cnt = 1, fl = 0; \
        for(char &x : t) { \
            if(x == ',') ++ cnt;\
        } \
        if(cnt > 2) out << __io__LR__[0], fl = 1; \
        register_const_func([&](const auto& member) { \
            OUTPUT_MEMBER(out, member); \
            if(--cnt) { \
                out << ", "; \
            } \
        }, __VA_ARGS__); \
        if(fl) out << __io__LR__[1]; \
    }\
    friend std::ostream& operator << (std::ostream& out, const Type& o) { \
        o.print(out); \
        return out; \
    }

#endif