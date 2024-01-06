# Programming assignments of Chapter 3

## Introduction

| 文件名                      | 介绍                                                         |
| --------------------------- | ------------------------------------------------------------ |
| `include/Spline.h`          | 多项式插值类。                                               |
| `include/calculator.hpp`    | 范数、积分等一系列简单的计算工具，更多功能仍待完善。         |
| `include/function.hpp`      | 函数类库（定义了向量函数，单变量函数，多项式函数等）。       |
| `include/IO.hpp`            | 输出库（支持各种 STL 类型和用户自定义类型的输出）。对于用户自定义类型，提供了两种输出方式：是否输出自定义类型的成员变量名。具体使用方法参考代码注释。 |
| `include/linear.hpp`        | 线形代数库 `namespace linear`（最开始写于《优化实用算法》课程，此为其第二版，对行向量和列向量都进行了更好的封装，矩阵和向量运算更加合理严谨，目前仍然在完善中）。在本次项目中，添加了 Thmos 求解三对角矩阵方法。 |
| `include/serialization.hpp` | 常用类型的序列化和反序列化方法。（最开始写于《面向对象程序设计》课程）本次项目中添加了 json 格式的序列化方法，支持文件读入到对象，对象输出到文件。具体实现在 `./include/serialization`，其中还包括了测试数据和代码。 |
| `include/ExecCode.hpp`      | 动态装载从字符串中提取的单变量函数。方便文件读入。           |
| `Problem-A.cpp`             | A题的测试代码。                                              |
| `Problem-C.cpp`             | C/D题的测试代码。                                            |
| `BForm.cpp`                 | B Form $\mathbb{S}_n^{n-1}$ 的测试代码。                     |
| `Problem-E.cpp`             | E题的测试代码。                                              |
| `Problem-E-genData.cpp`     | E题的输入数据的生成代码。                                    |
| `plot.ipynb`                | 所有画图程序。                                               |
| `res/`                      | 测试程序输出结果。                                           |
| `doc/`                      | 报告和设计文档。                                             |
| `data/`                     | 本次作业的输入数据（json 格式                                |

## Compile and Run

使用 `make` 工具进行编译：

```bash
make all # 编译所有代码
make clean # 清除make结果
make run # 运行所有代码（不包括收敛阶分析）
make analysis # 运行收敛阶分析代码，注意时间比较久，直接查看结果可以见`res/als.txt`
```

## Result

如果你想直接查看所有程序的输出结果，见目录 `/res`。
