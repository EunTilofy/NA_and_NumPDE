#ifndef _SERIALIZE_XML_HPP_
#define _SERIALIZE_XML_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include "xml/tinyxml2.h"

using namespace tinyxml2;

namespace Serialization_XML {
    /*****************************************************************
     *   function declaration
    ******************************************************************/
   // std::is_arithmetic
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    XMLElement * serialize_xml_Impl(const T& data, XMLDocument &doc);
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    void deserialize_xml_Impl(T& data, XMLElement * e);

    // std::string
    XMLElement * serialize_xml_Impl(const std::string& data, XMLDocument &doc);
    void deserialize_xml_Impl(std::string& data, XMLElement * e);

    // std::pair
    template<typename T1, typename T2>
    XMLElement * serialize_xml_Impl(const std::pair<T1, T2>& data, XMLDocument &doc);
    template<typename T1, typename T2>
    void deserialize_xml_Impl(std::pair<T1, T2>& data, XMLElement * e);

    // std::list
    template<typename T>
    XMLElement * serialize_xml_Impl(const std::list<T>& data, XMLDocument &doc);
    template<typename T>
    void deserialize_xml_Impl(std::list<T>& data, XMLElement * e);

    // std::vector
    template<typename T>
    XMLElement * serialize_xml_Impl(const std::vector<T>& data, XMLDocument &doc);
    template<typename T>
    void deserialize_xml_Impl(std::vector<T>& data, XMLElement * e);

    // std::map
    template<typename Key, typename Value>
    XMLElement * serialize_xml_Impl(const std::map<Key, Value>& data, XMLDocument &doc);
    template<typename Key, typename Value>
    void deserialize_xml_Impl(std::map<Key, Value>& data, XMLElement * e);

    // std::set
    template<typename T>
    XMLElement * serialize_xml_Impl(const std::set<T>& data, XMLDocument &doc);
    template<typename T>
    void deserialize_xml_Impl(std::set<T>& data, XMLElement * e);

    // user_defined types
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
    XMLElement * serialize_xml_Impl(const T& data, XMLDocument &doc);
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
    void deserialize_xml_Impl(T& data, XMLElement * e);

    // main interface
    template<typename T>
    void serialize_xml(const T obj, std::string file);
    template<typename T>
    void deserialize_xml(T& obj, std::string file);
   
   /*****************************************************************
     *   function definition
    ******************************************************************/
   // std::is_arithmetic
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type*>
    XMLElement * serialize_xml_Impl(const T& data, XMLDocument &doc) {
        XMLElement * e = doc.NewElement(typeid(T).name());
        e->SetText(std::to_string(data).c_str());
        return e;
    }
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type*>
    void deserialize_xml_Impl(T& data, XMLElement * e) {
        std::string s = e->GetText();
        data = static_cast<T>(std::stod(e->GetText()));
    }

    // std::string
    XMLElement * serialize_xml_Impl(const std::string& data, XMLDocument &doc) {
        XMLElement * e = doc.NewElement("std_string");
        e->SetText(data.c_str());
        return e;
    }
    void deserialize_xml_Impl(std::string& data, XMLElement * e) {
        data = std::string(e->GetText());
    }

    // std::pair
    template<typename T1, typename T2>
    XMLElement * serialize_xml_Impl(const std::pair<T1, T2>& data, XMLDocument &doc) {
        XMLElement * e = doc.NewElement("std_pair");
        XMLElement * first = doc.NewElement("first");
        XMLElement * second = doc.NewElement("second");

        first->InsertEndChild(serialize_xml_Impl(data.first, doc));
        second->InsertEndChild(serialize_xml_Impl(data.second, doc));
        e->InsertFirstChild(first);
        e->InsertEndChild(second);

        return e;
    }
    template<typename T1, typename T2>
    void deserialize_xml_Impl(std::pair<T1, T2>& data, XMLElement * e) {
        deserialize_xml_Impl(data.first, e->FirstChildElement("first")->FirstChildElement());
        deserialize_xml_Impl(data.second, e->FirstChildElement("second")->FirstChildElement());
    }

    // std::list
    template<typename T>
    XMLElement * serialize_xml_Impl(const std::list<T>& data, XMLDocument &doc) {
        int index = 0;
        XMLElement * e = doc.NewElement("std_list");

        for(auto &x : data) {
            XMLElement * ele = doc.NewElement(("Element"+std::to_string(index)).c_str());
            ele->InsertFirstChild(serialize_xml_Impl(x, doc));
            e->InsertEndChild(ele);
            index ++;
        }

        return e;
    }
    template<typename T>
    void deserialize_xml_Impl(std::list<T>& data, XMLElement * e) {
        data.clear();

        for (XMLElement* ele = e->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement()) {
            T data_ele;
            deserialize_xml_Impl(data_ele, ele->FirstChildElement());
            data.push_back(data_ele);
        }
    }

    // std::vector
    template<typename T>
    XMLElement * serialize_xml_Impl(const std::vector<T>& data, XMLDocument &doc) {
        int index = 0;
        XMLElement * e = doc.NewElement("std_vector");

        for(auto &x : data) {
            XMLElement * ele = doc.NewElement(("Element"+std::to_string(index)).c_str());
            ele->InsertFirstChild(serialize_xml_Impl(x, doc));
            e->InsertEndChild(ele);
            index ++;
        }

        return e;
    }
    template<typename T>
    void deserialize_xml_Impl(std::vector<T>& data, XMLElement * e) {
        data.clear();

        for (XMLElement* ele = e->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement()) {
            T data_ele;
            deserialize_xml_Impl(data_ele, ele->FirstChildElement());
            data.push_back(data_ele);
        }
    }

    // std::map
    template<typename Key, typename Value>
    XMLElement * serialize_xml_Impl(const std::map<Key, Value>& data, XMLDocument &doc) {
        int index = 0;

        XMLElement * e = doc.NewElement("std_map");

        for(auto &x : data) {
            XMLElement * ele = doc.NewElement(("Element"+std::to_string(index)).c_str());
            XMLElement * first = doc.NewElement("key");
            XMLElement * second = doc.NewElement("value");

            first->InsertEndChild(serialize_xml_Impl(x.first, doc));
            second->InsertEndChild(serialize_xml_Impl(x.second, doc));
            ele->InsertFirstChild(first);
            ele->InsertEndChild(second);
            e->InsertEndChild(ele);
            index ++;
        }

        return e;
    }
    template<typename Key, typename Value>
    void deserialize_xml_Impl(std::map<Key, Value>& data, XMLElement * e) {
        data.clear();

        for (XMLElement* ele = e->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement()) {
            Key data_ele_key;
            Value data_ele_value;

            deserialize_xml_Impl(data_ele_key, ele->FirstChildElement("key")->FirstChildElement());
            deserialize_xml_Impl(data_ele_value, ele->FirstChildElement("value")->FirstChildElement());
            data.insert(std::make_pair(data_ele_key, data_ele_value));
        }
    }

    // std::set
    template<typename T>
    XMLElement * serialize_xml_Impl(const std::set<T>& data, XMLDocument &doc) {
        int index = 0;
        XMLElement * e = doc.NewElement("std_set");

        for(auto &x : data) {
            XMLElement * ele = doc.NewElement(("Element"+std::to_string(index)).c_str());
            ele->InsertFirstChild(serialize_xml_Impl(x, doc));
            e->InsertEndChild(ele);
            index ++;
        }

        return e;
    }
    template<typename T>
    void deserialize_xml_Impl(std::set<T>& data, XMLElement * e) {
        data.clear();

        for (XMLElement* ele = e->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement()) {
            T data_ele;
            deserialize_xml_Impl(data_ele, ele->FirstChildElement());
            data.insert(data_ele);
        }
    }

    // user_defined types
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type*>
    XMLElement * serialize_xml_Impl(const T& data, XMLDocument &doc) {
        return data._serialize_xml_Impl(doc);
    }
    template<typename T, typename std::enable_if<std::is_class<T>::value>::type*>
    void deserialize_xml_Impl(T& data, XMLElement * e) {
        data._deserialize_xml_Impl(e);
    }
    // user defined types members
    template<typename T>
    void udt_serialize_xml_Impl(const T& data, XMLDocument &doc, XMLElement * e) {
        e->InsertEndChild(serialize_xml_Impl(data, doc));
    }
    template<typename T>
    void udt_deserialize_xml_Impl(T& data, XMLElement *& e) {
        deserialize_xml_Impl(data, e);
        e = e->NextSiblingElement();
    }

    /******************************************************************
    * interface of serialize and deserialize
    * 1. serialize_xml(n, "n.data")
    * 2. deserialize_xml(n, "n.data")
    ******************************************************************/

    template<typename T>
    void serialize_xml(const T obj, std::string file) {
        XMLDocument doc("serialization");
        XMLElement* root = doc.NewElement("serialization");
        root->InsertEndChild(serialize_xml_Impl(obj, doc));
        doc.InsertEndChild(root);
        doc.SaveFile(file.c_str());
    }
    template<typename T>
    void deserialize_xml(T& obj, std::string file) {
        XMLDocument doc;
        doc.LoadFile(file.c_str());
        XMLElement * root = doc.FirstChildElement("serialization")->FirstChildElement();
        deserialize_xml_Impl(obj, root);
    }
} // namespace Serialization_XML

/*****************************************************************
* macro definition to register serializaion.
* e.g.
* struct UserDefinedType {
*   int idx;
*   std::string name;
*   std::vector<double> data;
*   std::list<std::pair<int, std::string>> dataa;
*
*   REGISTER_SERIALIZATION_XML("UserDefinedType", idx, name, data, dataa);
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


#define REGISTER_SERIALIZATION_XML(TYPE, ...) \
  XMLElement * _serialize_xml_Impl(XMLDocument &doc) const{ \
    using namespace Serialization_XML; \
    XMLElement * e = doc.NewElement(TYPE); \
    register_const_func([&](const auto& member){udt_serialize_xml_Impl(member, doc, e);}, __VA_ARGS__); \
    return e; \
  } \
  void _deserialize_xml_Impl(XMLElement * e) { \
    using namespace Serialization_XML; \
    XMLElement * ele = e->FirstChildElement(); \
    register_normal_func([&](auto& member){udt_deserialize_xml_Impl(member, ele);}, __VA_ARGS__); \
  }

#endif