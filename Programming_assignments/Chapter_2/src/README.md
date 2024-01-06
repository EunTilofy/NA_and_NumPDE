# Programming assignments of Chapter 1

## Introduction

| 文件名                                                                      | 介绍                                                                                                                                                                |
| --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Interpolation.h`                                                         | 多项式插值类。                                                                                                                                                      |
| `calculator.hpp`                                                          | 范数等一系列简单的计算工具，更多功能仍待完善。                                                                                                                      |
| `function.hpp`                                                            | 函数类库（初步定义了向量函数和单变量函数的成员），本次作业添加了多项式函数类。                                                                                      |
| `IO.hpp`                                                                  | 输出库（支持各种 STL 类型和用户自定义类型的输出）。对于用户自定义类型，提供了两种输出方式：是否输出自定义类型的成员变量名。具体使用方法参考代码注释。               |
| `linear.hpp`                                                              | 线形代数库 `namespace linear`（最开始写于《优化实用算法》课程，此为其第二版，对行向量和列向量都进行了更好的封装，矩阵和向量运算更加合理严谨，目前仍然在完善中）。 |
| `Problem-B.cpp`                                                           | B题的求解代码。                                                                                                                                                     |
| `Problem-C.cpp`                                                           | C题的求解代码。                                                                                                                                                     |
| `Problem-D.cpp`                                                           | D题的求解代码。                                                                                                                                                     |
| `Problem-E.cpp`                                                           | E题的求解代码。                                                                                                                                                     |
| `tmp/result.txt`                                                          | 本次作业所有题目的求解结果（方便直接查阅）。                                                                                                                        |
| `tmp/res_latex.out`<br />`tmp/res_tikz.out`<br />`tmp/res_python.out` | 各题相关插值结果按照 latex, tikz, python 可识别的格式输出的结果，<br />其中 `tmp/res_latex.out` 和 `tmp/res_tikz.out` 的结果用于辅助报告的撰写。                |
| `tmp/test_res_python.ipynb`                                               | 使用 `tmp/res_python.out` 的输出结果，对各题相关插值结果进行绘图的代码，用于测试 python 格式的多项式输出的正确性。                                                |

## Compile and Run

手动编译请开启 `C++20`，编译示例：

```bash
g++ Problem-B.cpp -o solB --std=c++20
```

你也可以使用 `make` 工具进行编译：

```bash
make all # 编译所有代码
make clean # 清除make结果
make run # 运行所有代码（其中代码结果会在错误流中输出）
make result # 运行所有代码，并保存结果到 result.out
make tikz # 运行所有代码，将相关多项式输出为tikz可识别格式
make latex # 运行所有代码，将相关多项式输出为latex可识别格式
make python # 运行所有代码，将相关多项式输出为python可识别格式
```

## Result

如果你想直接查看各题代码的输出结果，见目录 `/tmp`。
