#ifndef _SERIALIZE_HPP_
#define _SERIALIZE_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>

namespace Serialization {
    /*****************************************************************
     *   function declaration
    ******************************************************************/
    
    // std::is_arithmetic
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    serializeImpl(const T& data, std::ostream& stream);
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    deserializeImpl(T& data, std::istream& stream);

    // std::string
    void serializeImpl(const std::string& data, std::ostream& stream);
    void deserializeImpl(std::string& data, std::istream& stream);

    // std::pair
    template<typename T1, typename T2>
    void serializeImpl(const std::pair<T1, T2>& data, std::ostream& stream);
    template<typename T1, typename T2>
    void deserializeImpl(std::pair<T1, T2>& data, std::istream& stream);

    // std::list
    template<typename T>
    void serializeImpl(const std::list<T>& data, std::ostream& stream);
    template<typename T>
    void deserializeImpl(std::list<T>& data, std::istream& stream);

    // std::vector
    template<typename T>
    void serializeImpl(const std::vector<T>& data, std::ostream& stream);
    template<typename T>
    void deserializeImpl(std::vector<T>& data, std::istream& stream);

    // std::map
    template<typename Key, typename Value>
    void serializeImpl(const std::map<Key, Value>& data, std::ostream& stream);
    template<typename Key, typename Value>
    void deserializeImpl(std::map<Key, Value>& data, std::istream& stream);

    // std::set
    template<typename T>
    void serializeImpl(const std::set<T>& data, std::ostream& stream);
    template<typename T>
    void deserializeImpl(std::set<T>& data, std::istream& stream);

    // user_defined types
    template<typename T>
    typename std::enable_if<std::is_class<T>::value>::type
    serializeImpl(const T& data, std::ostream& stream);
    template<typename T>
    typename std::enable_if<std::is_class<T>::value>::type
    deserializeImpl(T& data, std::istream& stream);

    // main interface
    template<typename T>
    void serialize(const T obj, std::string file);
    template<typename T>
    void desrialize(T obj, std::string file);

    /*****************************************************************
     *   function definition
    ******************************************************************/
    
    // std::is_arithmetic
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    serializeImpl(const T& data, std::ostream& stream) {
        stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
    }
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    deserializeImpl(T& data, std::istream& stream) {
        stream.read(reinterpret_cast<char*>(&data), sizeof(data));
    }

    // std::string
    void serializeImpl(const std::string& data, std::ostream& stream) {
        size_t size = data.size();
        stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
        stream.write(data.c_str(), size);
    }
    void deserializeImpl(std::string& data, std::istream& stream) {
        size_t size;
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        data.resize(size);
        stream.read(&data[0], size);
    }

    // std::pair
    template<typename T1, typename T2>
    void serializeImpl(const std::pair<T1, T2>& data, std::ostream& stream) {
        serializeImpl(data.first, stream);
        serializeImpl(data.second, stream);
    }
    template<typename T1, typename T2>
    void deserializeImpl(std::pair<T1, T2>& data, std::istream& stream) {
        deserializeImpl(data.first, stream);
        deserializeImpl(data.second, stream);
    }

    // std::list
    template<typename T>
    void serializeImpl(const std::list<T>& data, std::ostream& stream) {
        size_t size = data.size();
        stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const T& item : data) {
            serializeImpl(item, stream);
        }
    }
    template<typename T>
    void deserializeImpl(std::list<T>& data, std::istream& stream) {
        size_t size;
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            T item;
            deserializeImpl(item, stream);
            data.push_back(item);
        }
    }

    // std::vector
    template<typename T>
    void serializeImpl(const std::vector<T>& data, std::ostream& stream) {
        size_t size = data.size();
        stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const T& item : data) {
            serializeImpl(item, stream);
        }
    }
    template<typename T>
    void deserializeImpl(std::vector<T>& data, std::istream& stream) {
        size_t size;
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        data.resize(size);
        for (T& item : data) {
            deserializeImpl(item, stream);
        }
    }

    // std::map
    template<typename Key, typename Value>
    void serializeImpl(const std::map<Key, Value>& data, std::ostream& stream) {
        size_t size = data.size();
        stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& pair : data) {
            serializeImpl(pair.first, stream);
            serializeImpl(pair.second, stream);
        }
    }
    template<typename Key, typename Value>
    void deserializeImpl(std::map<Key, Value>& data, std::istream& stream) {
        size_t size;
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            Key key;
            Value value;
            deserializeImpl(key, stream);
            deserializeImpl(value, stream);
            data[key] = value;
        }
    }

    // std::set
    template<typename T>
    void serializeImpl(const std::set<T>& data, std::ostream& stream) {
        size_t size = data.size();
        stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const T& item : data) {
            serializeImpl(item, stream);
        }
    }
    template<typename T>
    void deserializeImpl(std::set<T>& data, std::istream& stream) {
        size_t size;
        stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            T item;
            deserializeImpl(item, stream);
            data.insert(item);
        }
    }

    // user_defined types
    template<typename T>
    typename std::enable_if<std::is_class<T>::value>::type
    serializeImpl(const T& data, std::ostream& stream) {
        data._serializeImpl(stream);
    }
    template<typename T>
    typename std::enable_if<std::is_class<T>::value>::type
    deserializeImpl(T& data, std::istream& stream) {
        data._deserializeImpl(stream);
    }

    /******************************************************************
    * interface of serialize and deserialize
    * 1. serialize(n, "n.data")
    * 2. deserialize(n, "n.data")
    ******************************************************************/

    template <typename T>
    void serialize(const T obj, const std::string file){
        std::ofstream outFile(file, std::ios::binary);
        if(!outFile) {
            std::cerr << "open file error." << std::endl;
            return;
        }
        serializeImpl(obj, outFile);
    } 
    template <typename T>
    void deserialize(T &obj, const std::string file) {
        std::ifstream inFile(file, std::ios::binary);
        if (!inFile) {
            std::cout << "open file error." << std::endl;
            return;
        }
        deserializeImpl(obj, inFile);
    }
} // namespace Serialization

/*****************************************************************
* macro definition to register serializaion.
* e.g.
* struct UserDefinedType {
*   int idx;
*   std::string name;
*   std::vector<double> data;
*   std::list<std::pair<int, std::string>> dataa;
*
*   REGISTER_SERIALIZATION(idx, name, data, dataa);
*  };
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


#define REGISTER_SERIALIZATION(...) \
  void _serializeImpl(std::ostream& stream) const{ \
    using namespace Serialization; \
    register_const_func([&](const auto& member){serializeImpl(member, stream);}, __VA_ARGS__); \
  } \
  void _deserializeImpl(std::istream& stream) { \
    using namespace Serialization; \
    register_normal_func([&](auto& member){deserializeImpl(member, stream);}, __VA_ARGS__); \
  }

#endif