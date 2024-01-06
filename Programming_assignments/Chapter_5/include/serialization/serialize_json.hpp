#ifndef _SERIALIZE_JSON_HPP_
#define _SERIALIZE_JSON_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include "json/json.h"
#include "../IO.hpp"

namespace Serialization_Json {
    /*****************************************************************
     *   function declaration
    ******************************************************************/
   // std::is_arithmetic
    void deserialize_Json_Impl(int & data, Json::Value & e);
    void deserialize_Json_Impl(long long & data, Json::Value & e);
    void deserialize_Json_Impl(bool & data, Json::Value & e);
    void deserialize_Json_Impl(unsigned int & data, Json::Value & e);
    void deserialize_Json_Impl(unsigned long long & data, Json::Value & e);
    void deserialize_Json_Impl(double & data, Json::Value & e);
    void deserialize_Json_Impl(float& data, Json::Value & e);

    // std::string
    void deserialize_Json_Impl(std::string& data, Json::Value & e);

    // std::pair
    template<typename T1, typename T2>
    void deserialize_Json_Impl(std::pair<T1, T2>& data, Json::Value & e);

    // std::list
    template<typename T>
    void deserialize_Json_Impl(std::list<T>& data, Json::Value & e);

    // std::vector
    template<typename T>
    void deserialize_Json_Impl(std::vector<T>& data, Json::Value & e);

    // std::map
    template<typename Key, typename Value>
    void deserialize_Json_Impl(std::map<Key, Value>& data, Json::Value & e);

    // std::set
    template<typename T>
    void deserialize_Json_Impl(std::set<T>& data, Json::Value & e);

    // user_defined types
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
    void deserialize_Json_Impl(T& data, Json::Value & e);

    // main interface
    template<typename T>
    void deserialize_Json(T& obj, std::string file);
   
   /*****************************************************************
     *   function definition
    ******************************************************************/
    // std::is_arithmetic
    void deserialize_Json_Impl(int & data, Json::Value & e) {
        data = e.asInt();
    }
    void deserialize_Json_Impl(long long & data, Json::Value & e) {
        data = e.asInt64();
    }
    void deserialize_Json_Impl(bool & data, Json::Value & e) {
        data = e.asBool();
    }
    void deserialize_Json_Impl(unsigned int & data, Json::Value & e) {
        data = e.asUInt();
    }
    void deserialize_Json_Impl(unsigned long long & data, Json::Value & e) {
        data = e.asUInt64();
    }
    void deserialize_Json_Impl(double & data, Json::Value & e) {
        data = e.asDouble();
    }
    void deserialize_Json_Impl(float& data, Json::Value & e) {
        data = e.asFloat();
    }

    // std::string
    void deserialize_Json_Impl(std::string& data, Json::Value & e) {
        data = e.asString();
    }

    // std::pair
    template<typename T1, typename T2>
    void deserialize_Json_Impl(std::pair<T1, T2>& data, Json::Value & e) {
        deserialize_Json_Impl(data.first, e["first"]);
        deserialize_Json_Impl(data.second, e["second"]);
    }

    // std::list
    template<typename T>
    void deserialize_Json_Impl(std::list<T>& data, Json::Value & e) {
        data.clear();
        for(auto & eValue : e) {
            T data_ele;
            deserialize_Json_Impl(data_ele, eValue);
            data.push_back(data_ele);
        }
    }

    // std::vector
    template<typename T>
    void deserialize_Json_Impl(std::vector<T>& data, Json::Value & e) {
        data.clear();
        for(auto & eValue : e) {
            T data_ele;
            deserialize_Json_Impl(data_ele, eValue);
            data.push_back(data_ele);
        }
    }

    // std::map
    template<typename Key, typename Value>
    void deserialize_Json_Impl(std::map<Key, Value>& data, Json::Value & e) {
        data.clear();
        for (Json::ValueConstIterator it = e.begin(); it != e.end(); ++it) {
            const std::string key = it.key().asString();
            Value value;
            deserialize_Json_Impl(value, e[key]);
            data[key] = value;
        }
    }

    // std::set
    template<typename T>
    void deserialize_Json_Impl(std::set<T>& data, Json::Value & e) {
        data.clear();
         for(auto & eValue : e) {
            T data_ele;
            deserialize_Json_Impl(data_ele, eValue);
            data.insert(data_ele);
        }
    }

    // user_defined types
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type*>
    void deserialize_Json_Impl(T& data, Json::Value & e) {
        data._deserialize_Json_Impl(e);
    }
    // user defined types members
    template<typename T>
    void udt_deserialize_Json_Impl(T& data, Json::Value & e) {
        deserialize_Json_Impl(data, e);
    }

    /****************************************************************
    * interface of serialize and deserialize
    * 1. serialize_json(n, "n.json") <--- not implemented --->
    * 2. deserialize_json(n, "n.json")
    ******************************************************************/

    template<typename T>
    void deserialize_Json(T& obj, std::string file) {
        std::ifstream ifs(file);
        if (ifs.is_open()) {
            Json::Reader reader;
            Json::Value value;
            if(!reader.parse(ifs, value)) {
                // Deserialize error
                std::cerr << "Error : fail to parse" << std::endl;
            } else {
                deserialize_Json_Impl(obj, value);
            }
        } else {
            // Handle file not found or other error
            std::cerr << "Error: Unable to open file " << file << std::endl;
        }
    }

} // namespace Serialization_JSON

/*****************************************************************
* macro definition to register serialization.
* e.g.
* struct UserDefinedType {
*   int idx;
*   std::string name;
*   std::vector<double> data;
*   std::list<std::pair<int, std::string>> dataa;
*
*   REGISTER_SERIALIZATION_JSON("UserDefinedType", idx, name, data, dataa);
* };
******************************************************************/

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

#define REGISTER_SERIALIZATION_JSON(...) \
    void _deserialize_Json_Impl(Json::Value & e) { \
        using namespace Serialization_Json; \
        string t = #__VA_ARGS__, tmp = ""; \
        std::vector<string> mem_names; \
        for(char &x : t) { \
            if(x == ',') mem_names.push_back(tmp), mem_names.push_back(", "), tmp.clear(); \
            else if(x != ' ') tmp+=x; \
        } \
        mem_names.push_back(tmp); \
        reverse(mem_names.begin(), mem_names.end()); \
        register_normal_func([&](auto& member){ \
            udt_deserialize_Json_Impl(member, e[mem_names.back()]); \
            mem_names.pop_back(); \
            if(mem_names.size()) mem_names.pop_back(); \
        }, __VA_ARGS__); \
  } \

#endif