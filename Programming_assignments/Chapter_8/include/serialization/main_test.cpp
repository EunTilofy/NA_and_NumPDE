#include<bits/stdc++.h>

using namespace std;

#include "serialize.hpp"
#include "serialize_xml.hpp"
#include "serialize_json.hpp"
#include "../IO.hpp"

using namespace Serialization;
using namespace Serialization_XML;
using namespace Serialization_Json;

struct UserDefinedType {
    int idx;
    std::string name;
    std::vector<double> data;
    std::list<std::pair<int, std::string>> dataa;

    bool operator == (const UserDefinedType & o) const {
        return idx == o.idx && data == o.data 
                && name == o.name && dataa == o.dataa;
    }
    REGISTER_SERIALIZATION(idx, name, data, dataa);
    REGISTER_SERIALIZATION_XML("UserDefinedType", idx, name, data, dataa);
};

struct JsonTest {
    string Name;
    int Age;
    string University;
    map<string, double> Courses;
    set<string> teammates;

    bool operator == (const JsonTest & o) const {
        return Name == o.Name && Age == o.Age && University == o.University &&
            Courses == o.Courses && teammates == o.teammates;
    }

    REGISTER_OUTPUT_NAME(JsonTest, Name, Age, University, Courses, teammates);
    REGISTER_SERIALIZATION_JSON(Name, Age, University, Courses, teammates);
};

struct JsonTest2 {
    vector<double> x;
    vector<double> y;

    bool operator == (const JsonTest2 & o) const {
        return x == o.x && y == o.y;
    }

    REGISTER_SERIALIZATION_JSON(x, y);
    REGISTER_OUTPUT_NAME(JsonTest2, x, y);
};

struct JsonTest4 {
    string Name;
    int Age;
    string University;
    map<string, double> Courses;
    set<string> teammates;

    bool operator == (const JsonTest4 & o) const {
        return Name == o.Name && Age == o.Age && University == o.University &&
            Courses == o.Courses && teammates == o.teammates;
    }

    JsonTest4 operator = (const JsonTest & o) {
        Name = o.Name; Age = o.Age; University = o.University;
        Courses = o.Courses; teammates = o.teammates;
        return *this;
    }

    REGISTER_OUTPUT_NAME(JsonTest4, Name, Age, University, Courses, teammates);
    REGISTER_SERIALIZATION_JSON_AS_LIST(Name, Age, University, Courses, teammates);
};

int main() {
    // data definition

    // std::is_arithmetic
    int xml_a1, _a1, a1 = 256;
    long long xml_a2, _a2, a2 = 256256256256256LL;
    double xml_a3, _a3, a3 = 0.654321f;
   
    // std::string
    std::string xml_str, _str, str = "Hello, world!";

    // std::vector
    std::vector<std::string> xml_strVector, _strVector, strVector = {"1", "2", "3", "4", "5"};

    // std::map
    std::map<int, std::string> xml_intStringMap, _intStringMap, intStringMap = { { 1, "one" }, { 2, "two" }, { 3, "three" } };

    // std::set
    std::set<float> xml_floatSet, _floatSet, floatSet = { 1.1f, 2.2f, 3.3f };

    // std::pair
    std::pair<std::map<std::string, int>, std::vector<float>>
        xml_myPair, _myPair, myPair = {{{ "Cindy", 100 }, { "Aaron", 97 }, { "Justin", 88 }}, {10, 9.7, 8.8}};

    // std::list
    std::list<std::pair<int, std::string>> 
        xml_pairList, _pairList, pairList = { { 1, "one" }, { 2, "two" }, { 3, "three" } };

    // User Defined Type
    UserDefinedType xml_udt, _udt, udt = { 42, "John", { 1.2, 3.4, 5.6 }, { { 1, "one" }, { 2, "two" }, { 3, "three" } }};

    // complex Type
    std::map<std::string, std::map<std::pair<int, bool>, std::set<std::vector<long long>>>>
        xml_ct, _ct, ct = {{"case1", {{{3,false}, {{11111111111,22222222222}, {-1,-2}}}, {{4,true}, {{3,3}}}}}, 
        {"case2", {{{8, true}, {{1}, {2}, {3}}}, {{10, false}, {{-1,2}, {}, {333, 444}}}}}};

    /***************************************************
     * test for binary serialization/deserialization
    ****************************************************/

   // serialize

    serialize(a1, "data_bin/1.bin");
    serialize(a2, "data_bin/2.bin");
    serialize(a3, "data_bin/3.bin");
    serialize(str, "data_bin/4.bin");
    serialize(strVector, "data_bin/5.bin");
    serialize(intStringMap, "data_bin/6.bin");
    serialize(floatSet, "data_bin/7.bin");
    serialize(myPair, "data_bin/8.bin");
    serialize(pairList, "data_bin/9.bin");
    serialize(udt, "data_bin/10.bin");
    serialize(ct, "data_bin/11.bin");

    // deserialize

    deserialize(_a1, "data_bin/1.bin");
    deserialize(_a2, "data_bin/2.bin");
    deserialize(_a3, "data_bin/3.bin");
    deserialize(_str, "data_bin/4.bin");
    deserialize(_strVector, "data_bin/5.bin");
    deserialize(_intStringMap, "data_bin/6.bin");
    deserialize(_floatSet, "data_bin/7.bin");
    deserialize(_myPair, "data_bin/8.bin");
    deserialize(_pairList, "data_bin/9.bin");
    deserialize(_udt, "data_bin/10.bin");
    deserialize(_ct, "data_bin/11.bin");

    // output the data

    std::cout << "_a1 = " << _a1 << std::endl;
    std::cout << "_a2 = " << _a2 << std::endl;
    std::cout << "_a3 = " << _a3 << std::endl;
    std::cout << "_str = " << _str << std::endl;
    std::cout << "_strVector = " << _strVector << std::endl;
    std::cout << "_intStringMap = " << _intStringMap << std::endl;
    std::cout << "_floatSet = " << _floatSet << std::endl;
    std::cout << "_myPair = " << _myPair << std::endl;
    std::cout << "_pairList = " << _pairList << std::endl;
    std::cout << "_udt.idx = " << _udt.idx 
            << "  _udx.name = " << _udt.name
            << "  _udx.data = " << _udt.data 
            << "  _udx.dataa = " << _udt.dataa << std::endl;
    std::cout << "_ct = " << _ct << std::endl;

    // verify the correctness

    assert(a1 == _a1);
    assert(a2 == _a2);
    assert(a3 == _a3);
    assert(str == _str);
    assert(strVector == _strVector);
    assert(intStringMap == _intStringMap);
    assert(floatSet == _floatSet);
    assert(myPair == _myPair);
    assert(pairList == _pairList);
    assert(udt == _udt);
    assert(ct == _ct);
    std::cout << "Passed Serialization Tests!" << std::endl;


    /*********************************************************
     * test for binary serialization_xml/deserialization_xml
    **********************************************************/

    // serialize_xml
    
    serialize_xml(a1, "data_xml/1.xml");
    serialize_xml(a2, "data_xml/2.xml");
    serialize_xml(a3, "data_xml/3.xml");
    serialize_xml(str, "data_xml/4.xml");
    serialize_xml(strVector, "data_xml/5.xml");
    serialize_xml(intStringMap, "data_xml/6.xml");
    serialize_xml(floatSet, "data_xml/7.xml");
    serialize_xml(myPair, "data_xml/8.xml");
    serialize_xml(pairList, "data_xml/9.xml");
    serialize_xml(udt, "data_xml/10.xml");
    serialize_xml(ct, "data_xml/11.xml");

    // deserialize_xml

    deserialize_xml(xml_a1, "data_xml/1.xml");
    deserialize_xml(xml_a2, "data_xml/2.xml");
    deserialize_xml(xml_a3, "data_xml/3.xml");
    deserialize_xml(xml_str, "data_xml/4.xml");
    deserialize_xml(xml_strVector, "data_xml/5.xml");
    deserialize_xml(xml_intStringMap, "data_xml/6.xml");
    deserialize_xml(xml_floatSet, "data_xml/7.xml");
    deserialize_xml(xml_myPair, "data_xml/8.xml");
    deserialize_xml(xml_pairList, "data_xml/9.xml");
    deserialize_xml(xml_udt, "data_xml/10.xml");
    deserialize_xml(xml_ct, "data_xml/11.xml");

    // output the data

    std::cout << "xml_a1 = " << xml_a1 << std::endl;
    std::cout << "xml_a2 = " << xml_a2 << std::endl;
    std::cout << "xml_a3 = " << xml_a3 << std::endl;
    std::cout << "xml_str = " << xml_str << std::endl;
    std::cout << "xml_strVector = " << xml_strVector << std::endl;
    std::cout << "xml_intStringMap = " << xml_intStringMap << std::endl;
    std::cout << "xml_floatSet = " << xml_floatSet << std::endl;
    std::cout << "xml_myPair = " << xml_myPair << std::endl;
    std::cout << "xml_pairList = " << xml_pairList << std::endl;
    std::cout << "xml_udt.idx = " << xml_udt.idx 
            << "  xml_udx.name = " << xml_udt.name
            << "  xml_udx.data = " << xml_udt.data 
            << "  xml_udx.dataa = " << xml_udt.dataa << std::endl;
    std::cout << "xml_ct = " << xml_ct << std::endl;

    // verify the correctness

    assert(a1 == xml_a1);
    assert(a2 == xml_a2);
    assert(fabs(a3 - xml_a3) < 1e-7);
    assert(str == xml_str);
    assert(strVector == xml_strVector);
    assert(intStringMap == xml_intStringMap);
    assert(floatSet == xml_floatSet);
    assert(myPair == xml_myPair);
    assert(pairList == xml_pairList);
    assert(udt == xml_udt);
    assert(ct == _ct);
    std::cout << "Passed Serialization_XML Tests!" << std::endl;


    // verify json

    JsonTest a, c;
    deserialize_Json(a, "data_json/1.json");
    cout << a << "\n";

    JsonTest2 b, d;
    deserialize_Json(b, "data_json/2.json");
    cout << b << "\n";

    serialize_Json(a, "data_json/3.json");
    deserialize_Json(c, "data_json/3.json");
    cout << c << "\n";
    assert(a == c);

    serialize_Json(b, "data_json/4.json");
    deserialize_Json(d, "data_json/4.json");
    cout << d << "\n";
    assert(b == d);

    map<int, string> e, f;
    deserialize_Json(e, "data_json/5.json");
    cout << e << "\n";
    serialize_Json(e, "data_json/6.json");
    deserialize_Json(f, "data_json/6.json");
    cout << f << "\n";
    assert(e == f);

    JsonTest4 g, h; g = a;
    serialize_Json(g, "data_json/7.json");
    deserialize_Json(h, "data_json/7.json");
    cout << g << "\n";
    assert(g == h);

    return 0;
}