/************************************************************************
 * Ver 2.0, Dec. 22nd, 2023.
 * 1. Add serialization method.
 * 2. Offer two different kind of methods to serialize map<string, *>.
 * 3. Offer two different kind of methods to serialize UDT.
***********************************************************************/
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

using namespace std;

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

    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    Json::Value serialize_Json_Impl(const T& data);

    // std::string
    void deserialize_Json_Impl(std::string& data, Json::Value & e);
    Json::Value serialize_Json_Impl(const std::string& data);

    // std::pair
    template<typename T1, typename T2>
    void deserialize_Json_Impl(std::pair<T1, T2>& data, Json::Value & e);
    template<typename T1, typename T2>
    Json::Value serialize_Json_Impl(const std::pair<T1, T2>& data);

    // std::list
    template<typename T>
    void deserialize_Json_Impl(std::list<T>& data, Json::Value & e);
    template<typename T>
    Json::Value serialize_Json_Impl(const std::list<T>& data);

    // std::vector
    template<typename T>
    void deserialize_Json_Impl(std::vector<T>& data, Json::Value & e);
    template<typename T>
    Json::Value serialize_Json_Impl(const std::vector<T>& data);

    // std::map
    template<typename Key, typename Value>
    void deserialize_Json_Impl(std::map<Key, Value>& data, Json::Value & e);
    template<typename Key, typename Value>
    Json::Value serialize_Json_Impl(const std::map<Key, Value>& data);
    #ifndef STRING_MAP_NORMAL
        template<typename Value>
        void deserialize_Json_Impl(std::map<std::string, Value>& data, Json::Value & e);
        template<typename Value>
        Json::Value serialize_Json_Impl(const std::map<std::string, Value>& data);
    #endif

    // std::set
    template<typename T>
    void deserialize_Json_Impl(std::set<T>& data, Json::Value & e);
    template<typename T>
    Json::Value serialize_Json_Impl(const std::set<T>& data);

    // user_defined types
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
    void deserialize_Json_Impl(T& data, Json::Value & e);
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
    Json::Value serialize_Json_Impl(const T& data);

    // main interface
    template<typename T>
    void deserialize_Json(T& obj, std::string file);
    template<typename T>
    void serialize_Json(const T obj, std::string file);
   
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
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type*>
    Json::Value serialize_Json_Impl(const T& data) {
        return Json::Value(data);
    }

    // std::string
    void deserialize_Json_Impl(std::string& data, Json::Value & e) {
        data = e.asString();
    }
    Json::Value serialize_Json_Impl(const std::string& data) {
        return Json::Value(data);
    }

    // std::pair
    template<typename T1, typename T2>
    void deserialize_Json_Impl(std::pair<T1, T2>& data, Json::Value & e) {
        bool _1 = 0;
        for(auto x : e) {
            if(!_1) deserialize_Json_Impl(data.first, x), _1 = 1;
             else {
                deserialize_Json_Impl(data.second, x);
                break;
            }
        }
    }
    template<typename T1, typename T2>
    Json::Value serialize_Json_Impl(const std::pair<T1, T2>& data) {
        Json::Value e;
        e.append(serialize_Json_Impl(data.first));
        e.append(serialize_Json_Impl(data.second));
        return e;
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
    template<typename T>
    Json::Value serialize_Json_Impl(const std::list<T>& data) {
        Json::Value e;
        for(auto &x : data) {
            e.append(serialize_Json_Impl(x));
        }
        return e;
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
    template<typename T>
    Json::Value serialize_Json_Impl(const std::vector<T>& data) {
        Json::Value e;
        for(auto &x : data) {
            e.append(serialize_Json_Impl(x));
        }
        return e;
    }

    // std::map
    #ifndef STRING_MAP_NORMAL
    template<typename Value>
    void deserialize_Json_Impl(std::map<std::string, Value>& data, Json::Value & e) {
        data.clear();
        for (Json::ValueConstIterator it = e.begin(); it != e.end(); ++it) {
            std::string key = it.key().asString();
            Value value;
            deserialize_Json_Impl(value, e[it.key().asString()]);
            data[key] = value;
        }
    }
    template<typename Value>
    Json::Value serialize_Json_Impl(const std::map<std::string, Value>& data) {
        Json::Value e;
        for(auto &x : data) {
            e[serialize_Json_Impl(x.first).asString()] = serialize_Json_Impl(x.second);
        }
        return e;
    }
    #endif
    template<typename Key, typename Value>
    void deserialize_Json_Impl(std::map<Key, Value>& data, Json::Value & e) {
        data.clear();
        for (auto it : e) {
            Key key; Value value;
            bool _1 = 0;
            for(auto x : it) {
                if(!_1) deserialize_Json_Impl(key, x), _1 = 1;
                else {
                    deserialize_Json_Impl(value, x);
                    break;
                }
            }
            data.insert({key, value});
        }
    }
    template<typename Key, typename Value>
    Json::Value serialize_Json_Impl(const std::map<Key, Value>& data) {
        Json::Value e;
        for(auto &x : data) {
            Json::Value ee;
            ee.append(serialize_Json_Impl(x.first));
            ee.append(serialize_Json_Impl(x.second));
            e.append(ee);
        }
        return e;
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
    template<typename T>
    Json::Value serialize_Json_Impl(const std::set<T>& data) {
        Json::Value e;
        for(auto &x : data) {
            e.append(serialize_Json_Impl(x));
        }
        return e;
    }

    // user_defined types
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type*>
    void deserialize_Json_Impl(T& data, Json::Value & e) {
        data._deserialize_Json_Impl(e);
    }
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type*>
    Json::Value serialize_Json_Impl(const T& data) {
        return data._serialize_Json_Impl();
    }

    // user defined types members
    template<typename T>
    void udt_deserialize_Json_Impl(T& data, Json::Value & e) {
        deserialize_Json_Impl(data, e);
    }
    template<typename T>
    Json::Value udt_serialize_Json_Impl(const T& data) {
        return serialize_Json_Impl(data);
    }
    

    /****************************************************************
    * interface of serialize and deserialize
    * 1. serialize_json(n, "n.json")
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
    template<typename T>
    void serialize_Json(const T obj, std::string file) {
        Json::Value e = serialize_Json_Impl(obj);
        ofstream ofs(file);
        if(ofs.is_open()) {
            Json::StyledWriter sw;
            ofs << sw.write(e);
            ofs.close();
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
            if(e.isMember(mem_names.back())) { \
                udt_deserialize_Json_Impl(member, e[mem_names.back()]); \
                /* cerr << mem_names.back() << "\n";*/ \
            }\
            mem_names.pop_back(); \
            if(mem_names.size()) mem_names.pop_back(); \
        }, __VA_ARGS__); \
    } \
    Json::Value _serialize_Json_Impl() const { \
        using namespace Serialization_Json; \
        Json::Value root; \
        string t = #__VA_ARGS__, tmp = ""; \
        std::vector<string> mem_names; \
        for(char &x : t) { \
            if(x == ',') mem_names.push_back(tmp), mem_names.push_back(", "), tmp.clear(); \
            else if(x != ' ') tmp+=x; \
        } \
        mem_names.push_back(tmp); \
        reverse(mem_names.begin(), mem_names.end()); \
        register_const_func([&](const auto& member){ \
            root[mem_names.back()] = udt_serialize_Json_Impl(member); \
            mem_names.pop_back(); \
            if(mem_names.size()) mem_names.pop_back(); \
        }, __VA_ARGS__); \
        return root; \
    } \

#define REGISTER_SERIALIZATION_JSON_AS_LIST(...) \
    void _deserialize_Json_Impl(Json::Value & e) { \
        using namespace Serialization_Json; \
        std::vector<Json::Value> v; \
        for(auto x : e) v.push_back(x); \
        reverse(v.begin(), v.end()); \
        register_normal_func([&](auto& member){ \
            if(v.size() == 0) { std::cerr << "Parse error : too short member list. \n"; return; } \
            udt_deserialize_Json_Impl(member, v.back()); \
            v.pop_back(); \
        }, __VA_ARGS__); \
    } \
    Json::Value _serialize_Json_Impl() const { \
        using namespace Serialization_Json; \
        Json::Value root; \
        register_const_func([&](const auto& member){ \
            root.append(udt_serialize_Json_Impl(member)); \
        }, __VA_ARGS__); \
        return root; \
    } \


#endif