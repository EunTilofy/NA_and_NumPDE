# Object Serialization

原地址：https://github.com/EunTilofy

修改于 Dec. 21st, 2023，在原来的基础上加上了 json 反序列化方法（序列化方法还没有制定准则，所以留待将来实现）。

以下为原先项目的介绍：

## Introduction

该项目为本人 OOP 的 Final Project。

在本项目中，本人实现了对不同对象的二进制序列化和 XML 格式序列化（调用 [tinyxml2](https://github.com/leethomason/tinyxml2) 库）。

序列化支持的对象包括：

+ 所有算术类型，即 `std::is_arithmetic` 下的所有类型；
+ 各种 STL 容器，包括：

  + `std::pair`
  + `std::vector`
  + `std::list`
  + `std::set`
  + `std::map`
+ 用户自定义类型，比如：

  ```c++
  struct UserDefinedType {
      int idx;
      std::string name;
      std::vector<double> data;
      std::list<std::pair<int, std::string>> dataa;

      bool operator == (const UserDefinedType & o) const {
          return idx == o.idx && data == o.data 
                  && name == o.name && dataa == o.dataa;
      }
  };
  ```
+ 上述不同类型的各种复杂嵌套，比如：

  ```c++
  td::map<std::string, std::map<std::pair<int, bool>, std::set<std::vector<long long>>>>
  ```

## Using Method

1. 二进制序列化（`serialize.hpp`）

   调用接口示例：

   ```c++
   using namespace Serialization;
   int n0 = 256, n1;
   // serialize object n0 to a binary file n.data
   serialize(n0, "n.data");
   // reconstruct object n1 from the content of n.data
   deserialize(n1, "n.data");
   // now n0 == n1 should be true.
   ```

   对于用户自定义类型的结构体，需要在类型定义中加上如下代码，其功能是通过宏定义自动加入相关序列化和反序列化成员函数，（以上述结构体为例）：

   ```c++
   REGISTER_SERIALIZATION(idx, name, data, dataa);
   ```
2. XML 序列化

   调用接口示例：

   ```c++
   using namespace Serialization_XML;
   std::pair<int, double> pair0 = {2, 3.1}, pair1;
   // serialize object pair0 to an XML file pair.xml with the name std_pair
   serialize_xml(pair0, "std_pair", "pair.xml");
   // reconstruct object pair1 from the content of pair.xml
   deserialize_xml(pair1, "std_pair", "pair.xml");
   // now pair0 == pair1 should be true.
   ```

   对于用户自定义类型的结构体，需要在类型定义中加上如下代码，其功能是通过宏定义自动加入相关序列化和反序列化成员函数，（以上述结构体为例）：

   ```c++
   REGISTER_SERIALIZATION_XML("UserDefinedType", idx, name, data, dataa);
   ```

## Tests

测试主程序代码为 `./main_test.cpp`

测试方法为：

```
make
./main
```

或者：

```
g++ main_test.cpp include/tinyxml2.cpp -o main --std=c++20
./main
```

测试程序对各种可能的情况进行了充分的测试，并对正确性做了检验。

需要注意的是，在正确性检验的时候，由于浮点数类型比较运算有可能会出现精度误差，而出现不可测结果。

测试类型包括：

```c++
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

```

测试输出目录为 `/data_xml` 和 `/data_bin`。

比如对于 `UserDefinedType udt = { 42, "John", { 1.2, 3.4, 5.6 }, { { 1, "one" }, { 2, "two" }, { 3, "three" } }};` 的 XML 格式序列化结果为：

```plaintext
<serialization>
    <UserDefinedType>
        <i>42</i>
        <std_string>John</std_string>
        <std_vector>
            <Element0>
                <d>1.200000</d>
            </Element0>
            <Element1>
                <d>3.400000</d>
            </Element1>
            <Element2>
                <d>5.600000</d>
            </Element2>
        </std_vector>
        <std_list>
            <Element0>
                <std_pair>
                    <first>
                        <i>1</i>
                    </first>
                    <second>
                        <std_string>one</std_string>
                    </second>
                </std_pair>
            </Element0>
            <Element1>
                <std_pair>
                    <first>
                        <i>2</i>
                    </first>
                    <second>
                        <std_string>two</std_string>
                    </second>
                </std_pair>
            </Element1>
            <Element2>
                <std_pair>
                    <first>
                        <i>3</i>
                    </first>
                    <second>
                        <std_string>three</std_string>
                    </second>
                </std_pair>
            </Element2>
        </std_list>
    </UserDefinedType>
</serialization>

```

测试输出如下：

```plaintext
_a1 = 256
_a2 = 256256256256256
_a3 = 0.654321
_str = Hello, world!
_strVector = { 1, 2, 3, 4, 5 }
_intStringMap = { { 1: one }, { 2: two }, { 3: three } }
_floatSet = { 1.1, 2.2, 3.3 }
_myPair = { { { Aaron: 97 }, { Cindy: 100 }, { Justin: 88 } }, { 10, 9.7, 8.8 } }
_pairList = { { 1, one }, { 2, two }, { 3, three } }
_udt.idx = 42  _udx.name = John  _udx.data = { 1.2, 3.4, 5.6 }  _udx.dataa = { { 1, one }, { 2, two }, { 3, three } }
_ct = { { case1: { { { 3, 0 }: { { -1, -2 }, { 11111111111, 22222222222 } } }, { { 4, 1 }: { { 3, 3 } } } } }, { case2: { { { 8, 1 }: { { 1 }, { 2 }, { 3 } } }, { { 10, 0 }: { {  }, { -1, 2 }, { 333, 444 } } } } } }
Passed Serialization Tests!
xml_a1 = 256
xml_a2 = 256256256256256
xml_a3 = 0.654321
xml_str = Hello, world!
xml_strVector = { 1, 2, 3, 4, 5 }
xml_intStringMap = { { 1: one }, { 2: two }, { 3: three } }
xml_floatSet = { 1.1, 2.2, 3.3 }
xml_myPair = { { { Aaron: 97 }, { Cindy: 100 }, { Justin: 88 } }, { 10, 9.7, 8.8 } }
xml_pairList = { { 1, one }, { 2, two }, { 3, three } }
xml_udt.idx = 42  xml_udx.name = John  xml_udx.data = { 1.2, 3.4, 5.6 }  xml_udx.dataa = { { 1, one }, { 2, two }, { 3, three } }
xml_ct = { { case1: { { { 3, 0 }: { { -1, -2 }, { 11111111111, 22222222222 } } }, { { 4, 1 }: { { 3, 3 } } } } }, { case2: { { { 8, 1 }: { { 1 }, { 2 }, { 3 } } }, { { 10, 0 }: { {  }, { -1, 2 }, { 333, 444 } } } } } }
Passed Serialization_XML Tests!
```

功能性测试和正确性测试全部通过。
