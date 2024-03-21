# 函数生成器

生成如下格式的函数：

```c++
template <class Xtype, class Ytype = Xtype> 
class Function{
public:
    virtual Ytype operator() (const Xtype& x) const = 0;
    virtual Ytype Diff (const Xtype& x) const {custom_assert(0, "Diff() has not be designed\n"); return Ytype();}
    virtual const std::string to_python () const {custom_assert(0, "to_python() has not be designed\n"); return "";}
};
```

主要目的是能够更方便的定义函数（不需要每次都进行派生）。

第一版：

+ `ExecCode.hpp`：使用了动态链接的方式，好处是不需要对表达式进行处理，直接把函数输出到一个文档里，然后动态链接到程序，最后利用宏直接定义一个 `Function<Xtype, Ytype> func_name`。使用起来非常方便。坏处是链接速度由于不同的运行环境差别很大，比如在 MacOs 上一个函数链接大概需要2秒，而在 Ubuntu 上只用 0.5 秒。
+ 仅支持单变量函数，变量类型可以任意（注意 include 需要的库，比如向量函数需要 `linear` ）。
+ 注意函数名不要重复，输入字符串的变量长度为1（即：x,y,z，但不能是：xx,yy,zz）。

第二版：

+ `ExecCode2.hpp`：表达式解析：尝试解析出表达式树，便于之后计算。好处是不需要动态链接，也更为安全；坏处是没有办法执行各种各样  `C++` 中自带的数值函数了。
+ 2.1 版支持：四则运算，exp，sin，cos，tan，pow，sqrt，abs，fabs，floor，ceil，min，max，log（以e为底），log10。
+ 仅支持单变量函数，因为只解析了一些数值计算函数，建议变量类型仅为数值。
+ 注意函数名不要重复，输入字符串的变量长度任意。

第三版：

+ `ExecCode2d.hpp`：表达式解析，支持2元函数。其余与第二版一样。

```c++
template <class Xtype, class Ytype = Xtype>
class Function2D {
public:
    virtual Ytype operator () (const Xtype &x, const Xtype &y) const = 0;
};
```
