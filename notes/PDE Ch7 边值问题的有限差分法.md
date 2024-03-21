**Laplace 方程：**$\Delta u(\mathbf{x}) = 0, \Delta:= \sum\limits_{i = 1}^n \dfrac{\partial^2}{\partial x_i^2}$。

> $\Delta = \nabla \cdot \nabla$（拉普拉斯算子：梯度的散度）

**Poisson 方程：**$-\Delta u(\mathbf{x}) = f(\mathbf{x})$。

> 一维区间 $\Omega = (a, b)$ 的**边值类型**：
>
> + Dirichlet 条件：$u(a) = \alpha, u(b) = \beta$；
> + 混合条件：$u(a) = \alpha,\dfrac{\partial u}{\partial x} \bigg|_b = \beta$；
> + Neumann 条件：$\dfrac{\partial u}{\partial x}\bigg|_a = \alpha, \dfrac{\partial u}{\partial x}\bigg|_b = \beta$。

> 【**定理 7.7**】
>
> 假设 $f$ 和 $g$ 是充分光滑的函数，则方程：
>
> $$
> \Delta \phi = f \quad \text{in} \ \ \Omega \\
> \mathbf{n}\cdot \nabla \phi = g \quad \text{on} \ \ \partial \Omega
> $$
>
> 在满足额外条件（“高斯定理”）：
>
> $$
> \int_{\Omega} f \mathrm{d} V = \int_{\partial \Omega} g\mathrm{d} A.
> $$
>
> 时，有唯一解（在相差一个常数的意义下）。

**【例 7.8】**

考虑把向量场分解成无旋、无散两个部分：

$$
\begin{cases}
\mathbf{v}^* = \mathbf{v} + \nabla \phi \\
\nabla\cdot\mathbf{v} = 0, \quad \nabla \times \nabla \phi = \mathbf{0}.
\end{cases}
$$

因为无散场 $\mathbf{v}$ 满足条件 $\oint_{\partial \Omega} \mathbf{v}\cdot\mathbf{n} = 0$ ，所以可以通过求解如下 Poisson 方程 + Neumann 边值条件来求解：

$$
\Delta \phi = \nabla \cdot \mathbf{v}^* \quad \text{in}\ \  \Omega \\
\mathbf{n}\cdot \nabla \phi = \mathbf{n}\cdot (\mathbf{v}^* - \mathbf{v}) = \mathbf{n}\cdot \mathbf{v^*} \quad \text{on}\ \  \partial \Omega,
$$

下面考察这个问题解的存在唯一性（根据【定理 7.7】）：

$$
\int_{\Omega}\nabla\cdot \mathbf{v}^* \mathrm{d} V = \int_{\Omega} \nabla \cdot (\mathbf{v}^* - \mathbf{v})\mathrm{d}V \overset{\text{Gauss Law}}{=} \int_{\partial \Omega} \mathbf{n}\cdot(\mathbf{v}^* - \mathbf{v}) \mathrm{d} A.
$$

## 7.1 有限差分格式

「线性边值问题」有限差分法的步骤如下：

1. 把问题区域离散化成网格；
2. 用不同格点的函数值来近似偏导值，根据问题的约束列出线形方程组 $A\mathbf{U} = \mathbf{F}$。
3. 求解线性方程组，根据格点函数值来近似原函数。

【**例 7.10**】一维 Poisson 方程 + Dirichlet 边值条件

$$
-u''(x) = f(x), x\in \Omega:= (0, 1) \\
u(0) = \alpha, u(1) = \beta
$$

1. 建立网格：$x_j = jh, \quad h = \frac1{m+1}, \quad j = 0, 1, \ldots, m+1.$
   设 $U_0 = \alpha, U_{m+1} = \beta$，方程的未知数为 $U_1, \cdot, U_{m}$ （作为 $u(x_j)$ 的近似）。
2. 二阶导近似：

$$
u''(x_j) = \dfrac{u(x_{j-1}) - 2u(x_j) + u(x_{j+1})}{h^2} + O(h^2)
$$

3. 根据 $-\dfrac{U_{j-1} - 2U_j + U_{j+1}}{h^2} = f(x_j), j = 1, \cdots, m$，得到方程 $A\mathbf{U} = \mathbf{F}$。

## 7.2 误差和一致性

有限差分法的误差（global error） 是 $\mathbf{E} = \mathbf{U} - \hat{\mathbf{U}}$。其中 $\mathbf{U}$ 为求解方程得到的解向量，$\hat{\mathbf{U}}$ 是格点处的原函数值。

**网格函数（grid function）**：$\mathbf{g}:\mathbf{X}\to \mathbb{R}$，其中 $\mathbf{X}$ 是离散网格。

> **q-范数**
>
> 一维网格 $\mathbf{X}:= {x_1, \cdots, x_N}$。$\mathbf{g}$ 定义在 $\mathbf{X}$ 上。
>
> $$
> \| \mathbf{g}\|_q = \left(h\sum_{i = 1}^N |g_i|^q\right)^{\frac1q}
> $$
>
> 1. $1-$范数：$\|g\|_1 = h\sum_{i = 1}^N|g_i|$;
> 2. $\infty-$范数：$\| g\|_{\infty} = \max\limits_{1\le i\le N}|g_i|$。

**局部截断误差（LTE）**：导数值用有限差分替代所导致的误差（是一个理论值）。

比如：$D^2u(x_j) := \dfrac{u(x_{j-1} - 2u(x_j) + u(x_{j+1}))}{h^2}$ 的 LTE 为 $\tau_j = -D^2u(x_j) - (-u'' (x_j)) = -\dfrac{h^2}{12}u''''(x_j) + O(h^4) = O(h^2).$

> 【**引理 7.17**】
>
> 对于 $(0, 1)$ 上一维线性边值问题 $\mathcal{L}u = f(x)$，若使用有限差分方法得到 $A\mathbf{U} = \mathbf{F}$，则该方法的 LTE 为 $\tau = A\hat{\mathbf{U}} - \mathbf{F}$。其中 $\mathbf{F} = (f(x_1), \cdots, f(x_m))$。
>
> 【**证明**】以 【**例 7.10**】为例：
>
> $$
> (A\mathbf{\hat{U}} - \mathbf{F})_j = - \dfrac{u(x_{j-1}) - 2u(x_j) + u(x_{j+1})}{h^2} + \Delta u(x_j).
> $$

> 【**引理 7.18**】LTE 和 全局误差的关系为 $A\mathbf{E} = - \tau$。
>
> 【**证明**】$A\mathbf{E} = A(\mathbf{U} -\mathbf{\hat{U}}) = \mathbf{F} - (\mathbf{F} + \tau) = -\tau$。

**一致性：**称有限差分法关于边值问题一致若：

$$
\lim_{h\to 0}\|\tau^h\| = 0,
$$

其中 $\tau^h$ 是 LTE（这里 $h$ 是上标）。

## 7.3 稳定性和收敛性

**收敛性：**有限差分法收敛若 $\lim\limits_{h\to 0}\|\mathbf{E}^h\| = 0$，其中 $\mathbf{E}^h$ 是全局误差，$\|\cdot\|$ 是一种 $q-$ 范数。

**稳定性：** 有限差分法稳定，若

+ $\exists h_0 \in \mathbb{R^+}$，满足 $\forall h \in (0, h_0), \mathrm{det}(A) \neq 0$;
+ $\lim\limits_{h\to0}\|A^{-1}\| = O(1)$。

> 【**定理 7.22**】
>
> 一致且稳定的有限差分法是收敛的。
>
> 【**证明**】
>
> $$
> \lim \| \mathbf{E}^h\| \le \lim \| (A^h)^{-1}\| \lim \| \tau^h \| \le C \lim \| \tau^h\| = 0,
> $$
>
> 这里向量范数与之前定义的 $q-$范数之间的关系是： $\| \mathbf{E} \|_q = h^{\frac1q}\| \mathbf{E}\|$。

### 7.3.1 2-范数下收敛

**矩阵范数**的定义为 $\| A\| = \sup \left\{\dfrac{\| A\mathbf{x}\|}{\|\mathbf{x}\|}:\mathbf{x}\in \mathbb{R}^n, \mathbf{x}\neq 0\right\} = \sup\left\{\| A\mathbf{x}\|: \|x\| = 1\right\}.$

常见的矩阵范数如下：

$$
\begin{cases}
\| A\|_{\infty} = \max\limits_{1\le i\le n} \sum\limits_{j=1}^n |a_{ij}|, \text{(最大行)}\\
\| A\|_{1} = \max\limits_{1\le j \le n} \sum\limits_{i = 1}^n |a_{ij}|, \text{(最大列)} \\
\| A\|_{2} = \sqrt{\rho(A^T A)}, \rho(B):= \max_i|\lambda_i(B)|,  \text{(最大特征值)}
\end{cases}
$$

> 【**引理 7.25**】
>
> 【**例 7.10**】 中
>
> $$
> A = \dfrac1{h^2}\begin{bmatrix}
> 2 & -1 & & & & \\
> -1 & 2 & -1 & & & \\
> & -1 & 2 & -1 & & \\
> & & \ddots & \ddots & \ddots & \\
> & & & -1 & 2 & -1\\
> & & & & -1 & 2
> \end{bmatrix}.
> $$
>
> $$
> \lambda_k(A) = \dfrac{4}{h^2}\sin^{2}\dfrac{k\pi}{2(m+1)} \\
> w_{k,j} = \sin \dfrac{jk\pi}{m+1} \\
> j,k = 1, 2, \cdots, m
> $$
>
> 【**证明**】直接代入计算

> 【**定理 7.27**】
>
> 【**例 7.10**】中的有限差分法 2 阶收敛。
>
> 【**证明**】
>
> 根据 $A$ 的对称性
>
> $$
> \| A\|_2 = \sqrt{\rho(A^2)} = \rho(A) \le \frac{4}{h^2}
> $$
>
> 由 【**引理 7.25**】$A$ 非奇异。
>
> 并且
>
> $$
> \lim_{h\to 0}\| A^{-1}\|_2 = \lim_{h\to 0} 
> \dfrac{1}{\min |\lambda_k(A)|}=\lim_{h\to0}
> \dfrac{h^2}{4\sin^2 \frac{\pi h}{2}}
> = \dfrac{1}{\pi^2}
> $$
>
> 所以 FD 方法稳定。
>
> 因为 LTE 满足
>
> $$
> \lim_{h\to 0} |\tau_j| 
> = \left|- \frac{h^2}{12}u''''(x_j) + O(h^4)\right| = 0 \\
> \Rightarrow \lim_{h\to 0} \| \tau^h \| = 0
> $$
>
> 所以 FD 方法一致。
>
> 根据 【**定理 7.22**】，FD 方法 2 阶收敛。

### 7.3.2 Green 函数

【定义7.28】对任意给定的 $\overline{x} \in [0, 1]$，*Green* 函数 $G(x;\overline{x})$ 为 BVP $\begin{cases} u''(x) = \delta (x - \overline{x}) \\ u(0) = u(1) = 0\end{cases}$ 的解。

<img src="/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/notes/image/PDE%20Ch7%20%E8%BE%B9%E5%80%BC%E9%97%AE%E9%A2%98%E7%9A%84%E6%9C%89%E9%99%90%E5%B7%AE%E5%88%86%E6%B3%95/image-20240228232123973.png" alt="image-20240228232123973" style="zoom:50%;" />

【引理7.29】根据边值条件和脉冲函数的积分值可以得到，Green 函数的表达式为

$$
G(x; \overline{x}) = \begin{cases} (\overline{x} - 1)x, \quad x\in [0, \overline{x}]\\ \overline{x}(x - 1), \quad x\in[\overline{x}, 1] \end{cases}
$$

**证明：**

$$
\forall \epsilon, \int_{x_0 - \epsilon}^{x_0 + \epsilon} G''(x) \mathrm{d} x = \int_{x_0 - \epsilon}^{x_0 + \epsilon} \delta(x-\overline{x}) \mathrm{d} x = \begin{cases} 0, \quad \overline{x} \notin (x_0 - \epsilon, x_0 + \epsilon) \\ 1, \quad \overline{x} \in (x_0 - \epsilon , x_0 + \epsilon) \end{cases}
$$

取极限 $\epsilon \to 0$， 由微积分基本定理得

$$
\lim_{\epsilon \to 0} G'(x_0 + \epsilon) - \lim_{\epsilon \to 0} G'(x_0 - \epsilon) = \begin{cases}
	0, x_0 \in (0, \overline{x}) \cup (\overline{x}, 1) \\ 
	1, x_0 = \overline{x}
\end{cases}
$$

设 $G(x, \overline{x}) = \begin{cases} ax + b , \quad x \in [0, \overline{x}] \\ cx + d , \quad x \in [\overline{x}, 1]\end{cases}$，根据 $ c = a+1, b = 0, c+d = 0, a\overline{x} + b = c\overline{x} + d$ 得 $a = \overline{x} - 1, b = 0, c = \overline{x}, d = \overline{x}$。

【推论7.30】方程 $\begin{cases} u''(x) = c\delta (x - \overline{x}) \\ u(0) = u(1) = 0\end{cases}$ 的解为 $cG(x; \overline{x})$。

### 7.3.3 ∞范数下收敛

> 【**引理 7.31**】
>
> 对于矩阵 $A$：
>
> $$
> A = \dfrac1{h^2}\begin{bmatrix}
> 2 & -1 & & & & \\
> -1 & 2 & -1 & & & \\
> & -1 & 2 & -1 & & \\
> & & \ddots & \ddots & \ddots & \\
> & & & -1 & 2 & -1\\
> & & & & -1 & 2
> \end{bmatrix}.
> $$
>
> 其逆矩阵 $B = A^{-1}$ 为：
>
> $$
> b_{ij} = -h G(x_i; x_j)= \begin{cases}
> -h(x_j - 1)x_i, \quad i \le j, \\
> -hx_j(x_i - 1), \quad i \ge j.
> \end{cases}
> $$
>
> 即：
>
> $$
> B = -h\begin{bmatrix}
> x_1(x_1 - 1) & x_1(x_2 - 1) & \cdots & x_1(x_m - 1)\\
> x_1(x_2 - 1) & x_2(x_2 - 1) & \cdots & x_2(x_m - 1) \\
> \vdots& \vdots & \ddots & \vdots \\
> x_1(x_m - 1) & x_2(x_m - 1) & \cdots & x_m(x_m - 1)
> \end{bmatrix}
> $$
>
> 其中 $x_j = \dfrac{j}{m+1}$。
>
> 【**证明**】
>
> $A$ 的第 $i$ 行（乘 $h^2$）和 $B$ 的第 $j$ 列（乘 $-1/h$）如下：
>
> $$
> [0, \cdots, 0, -1, 2, -1, 0, \cdots, 0]
> \begin{bmatrix}
> x_1(x_j - 1) \\
> \vdots \\
> x_{j-1}(x_j-1) \\
> x_j(x_j- 1) \\
> x_j(x_{j+1}-1) \\
> \vdots \\
> x_j(x_m-1) \\
> \end{bmatrix} \\
> = \begin{cases}
> 2x_j(x_j - 1) - x_{j-1}(x_j - 1) - x_j(x_{j+1}-1) = -h & i = j \\
> (x_j - 1)(2x_i - x_{i - 1} - x_{i + 1})= 0 & i < j \\
> x_j[2(x_i - 1) - (x_{i-1} - 1) - (x_{i+1} - 1)] & i > j
> \end{cases}
> $$

> 【**定理 7.32**】
>
> 接 【**引理 7.31**】，$B = A^{-1}$ 满足
>
> $$
> \| B \|_{\infty} = \max_{1\le i \le m}\sum_{j = 1}^m |b_{ij}| \le 1.
> $$
>
> 【**证明**】
>
> $$
> \begin{aligned}
> \sum_{j = 1}^m |b_{ij}| &= \sum_{j = 1}^i hx_j|x_i - 1| + \sum_{j = i + 1}^m hx_i|x_j - 1| \\
> &\le \sum_{j = 1}^i h\left(\dfrac{m}{m + 1}\right)^2 + \sum_{j = i + 1}^m h\left(\dfrac{m}{m + 1}\right)^2 \quad [x_j \le \dfrac{m}{m+1}, |x_i - 1|\le 1]\\
> &= mh\left(\frac{m}{m+1}\right)^2 = \left(\frac{m}{m+1}\right)^3 \le 1.
> \end{aligned}
> $$

## 7.4 A solution via Green’s function

【引理7.33】设 $\mathcal{L}$ 是可逆的线性算子，满足 $\mathcal{L}u(x) = f(x)$，则有 $u(x) = \int G(x; \overline{x}) f(\overline{x})\mathrm{d}\overline{x}$，其中 $G$ 满足 $\mathcal{L}G(x;\overline{x}) = \delta(x - \overline{x})$。

**证明：**因为 $\mathcal{L}G(x; \overline{x}) = \delta(x - \overline{x})$，所以 $\int \mathcal{L}G(x; \overline{x})f(\overline{x}) \mathrm{d}\overline{x} = \int \delta(x - \overline{x})f(\overline{x}) \mathrm{d}\overline{x} = f(x)$。

根据线性性，$\mathcal{L} \int G(x; \overline{x}) f(\overline{x}) \mathrm{d} \overline{x} = f(x)$，由可逆性得到结论。

【定理7.34】Drichlet BVP $\begin{cases} u''(x) = f(x) \\ u(0) = \alpha, u(1) = \beta\end{cases}$ 的解为 $u(x) = \alpha G_0(x) + \beta G_1(x) + \hat{u}(x)$。其中，

$$
\begin{cases}
	G_0''(x) = 0, \\
	G_0(0) = 1, G_0(1) = 0 
\end{cases}
\Rightarrow G_0(x) = 1 - x,
$$

$$
\begin{cases}
	G_1''(x) = 0, \\
	G_1(0) = 0, G_1(1) = 1
\end{cases}
\Rightarrow G_0(x) = x,
$$

$$
\begin{cases}
 \hat{U}''(x) = f(x), \\
 \hat{U}(0) = 0, \hat{U}(1) = 0
\end{cases}
\Rightarrow \hat{U}(x) = \int_0^1 f(\overline{x}) G(x; \overline{x}) \mathrm{d} \overline{x}.
$$

> 【**引理7.35**】对于 $\begin{cases} u''(x) = f(x) \\ u(0) = \alpha, u(1) = \beta\end{cases}$ 这样的边值问题，一个右端项 $f$ 的 $O(\epsilon)$ 扰动带来 $O(\epsilon h)$ 的误差，对于 Dirichlet 条件的 $O(\epsilon)$ 的扰动，带来 $O(\epsilon)$ 的误差。
>
> **证明：**
>
> 离散化后得到 $A_g \mathbf{U}_g = \mathbf{F}_g$，其中，
>
> $$
> A_g = \frac{1}{h^2} 
> \begin{bmatrix}
> h^2 & 0 & & & & & \\
> 1 & -2 & 1 & & & & \\
> & 1 & -2 & 1 & & &\\
> & & \ddots & \ddots & \ddots& & \\
> & & & 1 & -2 & 1 &  \\
> & & & & 1 & -2 & 1 \\
> & & & & & 0 & h^2
> \end{bmatrix},\\
> \mathbf{U}_g = \begin{bmatrix}
> U_0 \\ \mathbf{U} \\ U_{m+1}
> \end{bmatrix},\quad
> \mathbf{F} = \begin{bmatrix}
> f(x_1) \\ f(x_2) \\ \vdots \\ f(x_{m-1}) \\ f(x_m)
> \end{bmatrix},\quad
> \mathbf{F}_g = \begin{bmatrix}
> \alpha \\ \mathbf{F} \\ \beta
> \end{bmatrix}
> $$
>
> 令 $B = A^{-1}, B_g = A_g^{-1} = \begin{bmatrix} & \mathbf{0}^T & \\ \mathbf{b}_{g,0} & B & \mathbf{b}_{g, m+1} \\  & \mathbf{0}^T & \end{bmatrix}$，则有
>
> $$
> \mathbf{U}_g = \begin{bmatrix}
>  & \mathbf{0}^T & \\
> \mathbf{b}_{g, 0} & B & \mathbf{b}_{g, m+1} \\
>  & \mathbf{0}^T & 
> \end{bmatrix}
> \begin{bmatrix}
> \alpha \\ \mathbf{F} \\ \beta
> \end{bmatrix}
> =
> \alpha \mathbf{b}_{g, 0} + \beta \mathbf{b}_{g, m+1} +
> \begin{bmatrix}
> 0 \\
> B \mathbf{F} \\
> 0
> \end{bmatrix}
> $$
>
> 因为 $\| B \| = O(h)$，所以可以得到结论1。可以证明 $\mathbf{b}_{g,0}$ 和 $\mathbf{b}_{g,m+1}$ 是常数级别的，由此得到结论2。

## 7.5 其他边值条件

【**例 7.36**】二阶边值问题+混合边值条件

$$
u''(x) = f(x) \quad \text{in}\ \ (0, 1)\\
u'(0) = \sigma, u(1) = \beta
$$

此时 $x = 0$ 处的函数值未知。

+ [方法一]

  使用 $\dfrac{U_1 - U_0}{h} = \sigma$。

  $x_0 = 0$ 处的 LTE 仅有一阶精度：

$$
\begin{aligned}
	\tau_0 &= \dfrac1{h^2}(hu(x_1) - hu(x_0)) - \sigma \\
	&= u'(x_0) + \dfrac12 hu''(x_0) + O(h^2) - \sigma \\
	&= \dfrac12 h u''(x_0) + O(h^2)
	\end{aligned}
$$

+ **[方法二]：编程使用**

  延拓一个点 $x_{-1} = -h$，使用 $\dfrac{U_1 - U_{-1}}{2h} = \sigma$，此时为二阶精度。

  为了消掉 $x_{-1}$，增加条件 $\dfrac{1}{h^2}(U_{-1} - 2U_0 + U_1) = f(x_0)$，则得到 $\dfrac{1}{h}(-U_0 + U_1) = \sigma + \dfrac{h}2f(x_0)$。
+ [方法三]

  使用 $U_0, U_1, U_2$ 来估计 $u'(0)$，$-\dfrac1h(\dfrac32 U_0 - 2U_1 + \dfrac12U_2) = \sigma + O(h^2)$。

  得到新的矩阵：

$$
A_F = \dfrac1{h^2}\begin{bmatrix}
	-\frac32h & -2h & -\frac12h& & & \\
	-1 & 2 & -1 & & & \\
	& -1 & 2 & -1 & & \\
	& & \ddots & \ddots & \ddots & \\
	& & & -1 & 2 & -1\\
	& & & & 0 & h^2
	\end{bmatrix}.
$$

【**例 7.38**】二阶边值问题+Neumann条件

$$
u''(x) = f(x) \quad \text{in}\ \  (0, 1), \\
u'(0) = \sigma_0, u'(1) = \sigma_1.
$$

为了保证解的存在性，需要满足：

$$
\int_0^1 f(x) \mathrm{d}x = \int_0^1 u''(x)\mathrm{d}x = u'(1) - u'(0) = \sigma_1 - \sigma_0.
$$

处理方法类似 【**例 7.36**】。

根据方法一：

$$
A_F\mathbf{U}_E = \mathbf{F}_F \\
A_F = \dfrac1{h^2}\begin{bmatrix}-h & h & & & & \\-1 & 2 & -1 & & & \\& -1 & 2 & -1 & & \\& & \ddots & \ddots & \ddots & \\& & & -1 & 2 & -1\\& & & & h & -h\end{bmatrix}.\\
\mathbf{F}_F = \begin{bmatrix}
\sigma_0 + \frac{h}2 f(x_0) \\
f(x_1) \\
\vdots \\
f(x_m) \\
-\sigma_1 + \frac{h}2 f(x_{m+1})
\end{bmatrix}
$$

> 【**引理 7.39**】
>
> 【**例 7.38**】 中矩阵 $A_F$ 满足 $\dim \mathcal{N}(A_F) = 1$。（$\mathcal{N}$ 即 Kernel）。
>
> 【**证明**】
>
> 显然 $\mathbf{e} = [1, 1, \cdots, 1]^T$ 属于 $A_F$ 的零空间。
>
> 如果定下了 $U_{m+1}$ 的值，则变为混合边界条件，其解唯一，所以零空间秩为1。

> 【**定理 7.40**】（可解性）
>
> 【**例 7.38**】 中方程有解，当且仅当
>
> $$
> \frac{h}2 f(x_0) + h\sum_{i = 1}^m f(x_i) + \frac{h}2f(x_{m+1}) = \sigma_1 - \sigma_0
> $$
>
> 【**证明**】
>
> 根据代数基本定理
>
>> $f:U\to V$，$A$ 是 $f$ 对应的矩阵。
>>
>> $V = \text{Im} A\oplus \text{Ker}A^T$
>>
>
> $$
> \mathbb{R}^{m+2} = \mathcal{R}(A_F) \oplus \mathcal{N}(A_F^T)
> $$
>
> 且 $\dim \mathcal{N}(A_F^T) = \dim \mathcal{N}(A_F)$（因为 $A$ 是方阵）。
>
> 可以验证 $\mathcal{N}(A_F^T) = \text{span}\{[1, h, \cdots, h,1]^T\}$。
>
> “$\Leftarrow$”：因为 $\frac{h}2 f(x_0) + h\sum_{i = 1}^m f(x_i) + \frac{h}2f(x_{m+1}) = \sigma_1 - \sigma_0$，所以 $\mathbf{F}_F$ 与 $\mathcal{N}(A_F)$ 正交，所以 $\mathbf{F}_F\in \mathcal{R}(A_F)$。则说明方程有解。
>
> "$\Rightarrow$"：$\mathbf{F}_F\in \mathcal{R}(A_F)$ 可以推出上式。

## 7.6 二维边值问题

【**例 7.41-7.42**】二维 BVP+Dirichlet条件

$$
-\dfrac{\partial^2}{\partial x^2} u(x, y) - \dfrac{\partial^2}{\partial y^2}u(x, y) = f(x, y)\quad \Omega:= (0,1)^2 \\
u(x, y)|_{\partial \Omega} = 0
$$

建立网格：

$$
x_i = ih, y_j = jh, \quad i,j = 0, 1, \cdots, m, m + 1,
\\
h = \Delta x = \Delta y = \frac1{m+1}
$$

对于 $f(x_i, y_j) = (-\dfrac{\partial^2}{\partial x^2} -\dfrac{\partial^2}{\partial y^2})u(x_i, y_j)$，作如下近似：

$$
f_{ij} = - \dfrac{U_{i - 1, j} - 2U_{i,j} + U_{i+1,j}}{h^2} - \dfrac{U_{i,j-1} - 2U_{i,j}+U_{i,j+1}}{h^2}.
$$

将 $m\times m$ 个方程组成方程组 $A_{2D}\mathbf{U} = \mathbf{F}$。

**LTE** 的计算如下：

$$
\tau_{i,j} = -\frac1{12} h^2\left(\dfrac{\partial^4u}{\partial x^4} + \dfrac{\partial^4u}{\partial y^4}\right)\bigg|_{(x_i, y_j)} + O(h^4).
$$

> 【**引理 7.44**】
>
> 【**例 7.41-7.42**】中全局误差 $\mathbf{E} = \mathbf{U} - \hat{\mathbf{U}}$。则 $A_{2D}\mathbf{E} = -\mathbf{\tau}$。

### 7.6.1 Kronecker product

【**定义7.45**】称 $A \in \mathbb{C}^{m\times n}$ 和 $B\in \mathbb{C}^{p\times q}$ 的 Kronecker 积为 $A\otimes B \in \mathbb{C}^{mn \times pq}$：

$$
A\otimes B = \begin{bmatrix}
	a_{11}B & a_{12}B & \cdots & a_{1n}B \\
	a_{21}B & a_{22}B & \cdots & a_{2n}B \\
	\vdots  & \vdots  & \ddots & \vdots  \\
	a_{n1}B & a_{n2}B & \cdots & a_{nn}B \\
\end{bmatrix}.
$$

【**定义7.47**】称 $X \in \mathbb{C}^{m \times n}$ 的拉直为 $\text{vec}(X) \in \mathbb{C}^{mn}$，为将 $X$ 的各列从上到下从左到右排列的列向量。

> 【引理7.48】任意 $A\in \mathbb{C}^{m\times m},B \in \mathbb{C}^{n \times n},X\in \mathbb{C}^{m\times n}$ 满足：
>
> $$
> \begin{aligned}
> &\text{vec}(AX) = (I_n \otimes A)\text{vec}(X), \\
> &\text{vec}(XB) = (B^T \otimes I_m) \text{vec}(X).
> \end{aligned}
> $$
>
> **证明：**
>
> $$
> \begin{aligned}
> \text{vec}(AX) &= \text{vec}([A\mathbf{X}_1, A\mathbf{X}_2, \cdots, A\mathbf{X}_n]) = [A\mathbf{X}_1, A\mathbf{X}_2, \cdots, A\mathbf{X}_n]^T \\&= \begin{bmatrix}A & & & \\ & A & &\\ & & \ddots & \\ & & & A\end{bmatrix} [A\mathbf{X}_1, A\mathbf{X}_2, \cdots, A\mathbf{X}_n]^T \\ &= (I_n \otimes A)[A\mathbf{X}_1, A\mathbf{X}_2, \cdots, A\mathbf{X}_n]^T
> \end{aligned}
> $$
>
> 令 $Y = XB$，则 $Y_j = X b_j \Rightarrow y_{kj} = \sum_{i = 1}^n x_{ki}b_{ij}$。
>
> 令 $C = B^T \otimes I_m$，则 $C_{ij} = b_{ij} I_m$。
>
> 令 $D = C \text{vec}(X)$，则 $\mathbf{D}_j = \sum_{i = 1}^n C_{ji} \mathbf{X}_i = \sum_{i = 1}^n b_{ij} I_m \mathbf{X}_i = \sum_{i = 1}^n b_{ij} \mathbf{X}_i$，$d_{(k, j)} = \sum_{i = 1}^n b_{ij} x_{ki} = \sum_{i = 1}^n x_{ki} b_{ij}$。
>
> 所以 $\text{vex}(Y) = D$，即 $\text{vec}(XB) = (B^T \otimes I_m) \text{vec}(X)$。

### 7.6.2 Convergence in the 2-norm

【引理7.49】引入中的线性方程组 $A_{2D}\mathbf{U} = \mathbf{F}$ 等价于 $AU_{m\times m} + U_{m\times m}A = F_{m\times m}$。其中 $U_{m\times m}$ 的 $(i, j)$ 个元素，是格点 $(i,j)$ 的解，$(F_{m\times m})_{ij} = f(ih, jh)$。$A = \frac1{h^2}\begin{bmatrix}2 & -1 & & & & \\ -1 & 2& -1 & & & \\ & -1 & 2 & -1 & & \\ & & \ddots & \ddots & \ddots & \\ & & & -1 & 2 -1 \\ & & & & -1  & 2\end{bmatrix}$。

**证明：**

$$
(AU_{m\times m})_{ij} = \dfrac1{h^2}(-U_{i-1, j} + 2U_{ij} - U_{i+1, j}) \\
(U_{m\times m}A)_{ij} = \dfrac1{h^2}(-U_{i, j-1} + 2U_{ij} - U_{i, j+1}) \\
\Rightarrow (AU_{m\times m}+U_{m\times m}A)_{ij} = \dfrac1{h^2}(-U_{i-1, j}-U_{i,j-1}+4U_{i,j}-U_{i+1,j}-U_{i,j+1}) \\
\Rightarrow AU_{m\times m}+U_{m\times m}A = F
$$

【引理7.50】1D 问题中的 $A$ 满足：$\text{vec}(AU+UA) = (I_m \otimes A + A\times I_m)\text{vec}(U)$。

**证明：** $\text{vec}(AU) = (I_m \times A) \text{vec}(U), \text{vec}(UA)= (A^T\otimes I_m)\text{vec}(U) = (A\otimes I_m)\text{vec}(U)$。

【定理7.51】$A_{2D} = I_m \otimes A + A \otimes I_m, \mathbf{U} = \text{vec}(U_{m\times m}), \mathbf{F} = \text{vec}(F_{m\times m})$。

【定义7.52】称 $n$ 维空间的离散拉普拉斯算子为

<center><img src="/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/notes/image/PDE%20Ch7%20%E8%BE%B9%E5%80%BC%E9%97%AE%E9%A2%98%E7%9A%84%E6%9C%89%E9%99%90%E5%B7%AE%E5%88%86%E6%B3%95/image-20240229082854745.png" style="zoom: 50%;" /></center>

**例如：**对于 $n = 3$，$A_{3D} = A\otimes I_m \otimes I_m + I_m \otimes A \otimes I_m + I_m \otimes I_m \otimes A$。

> 【定理7.54】$A_{2D}$ 的特征值为 $\lambda_{ij} = \lambda_i + \lambda_j, \mathbf{W}_{ij} = \text{vec}(\mathbf{w}_i \mathbf{w}_j^T)$ ，$i,j = 1, \cdots, m$，$$
>
> **证明：**
>
> $$
> \begin{aligned}
> A\mathbf{w}_i\mathbf{w}_j^T + \mathbf{w}_i\mathbf{w}_j^TA &= \lambda_i \mathbf{w}_i\mathbf{w}_j^T + \mathbf{w}_i \mathbf{w}_j^TA^T \\
> &= \lambda_i \mathbf{w}_i \mathbf{w}_j^T + \mathbf{w}_i(A\mathbf{w}_j)^T \\
> &= (\lambda_i + \lambda_j) \mathbf{w}_i \mathbf{w}_j^T
> \end{aligned}
> $$
>
> 所以，
>
> $$
> \begin{aligned}
> 	A_{2D}\text{vec}(\mathbf{w}_i\mathbf{w}_j^T)
> 	&= (I_m \otimes A + A\otimes I_m)\text{vec}(\mathbf{w}_i\mathbf{w}_j^T) \\
> 	&= \text{vec}(A(\mathbf{w}_i\mathbf{w}_j^T) + (\mathbf{w}_i\mathbf{w}_j^T)A) \\
> 	&= (\lambda_i + \lambda_j)\text{vec}(\mathbf{w}_i\mathbf{w}_j^T).
> \end{aligned}
> $$

> 【定理7.55】方程 $-u_{xx} - u_{yy} = f(x, y)$ 的有限差分算法在 2-范数下是 2 阶收敛的。
>
> **证明：**
>
> 因为 $A_{2D}$ 是对称的，所以 $\| A_{2D}\|_2 = \rho (A_{2D})$，根据【定理7.53】，所以
>
> $$
> \lim_{h\to 0} \| A_{2D}^{-1}\|_2 = \lim_{h\to 0} \dfrac1{\min |\lambda_{ij}|} = \lim_{h\to 0} \dfrac{h^2}{8\sin^2 \dfrac{\pi h}{2}} = \dfrac1{2\pi^2} = O(1).
> $$
>
> 所以算法是稳定的。根据【定理7.22】算法是二阶收敛的。

### 7.6.3 Convergence in the max-norm via a discrete maximum principle

> 【定理7.56】方程 $-u_{xx}-u_{yy} = f(x, y)$ 的有限差分算法在 $\infty$-范数下是 2 阶收敛的。
>
> **证明：**
>
> 令 $\mathbf{X}_I$ 为 $\mathbf{X}$ 的内点，即删去（$i = 0, m+1\vee j = 0, m +1$ 的网格点后的网格）。
>
> 定义线性映射 $\hat{A}_{2D} : \{\mathbf{X}\to \mathbb{R}\} \to \{\mathbf{X}_I \to \mathbb{R}\}$，
>
> $$
> \begin{aligned}
> 	\hat{A}_{2D} U_{i,j} &:= (\hat{A}_{2D} \mathbf{U})_{i,j} \\
> 	&= \dfrac1{h^2}(4U_{i,j} - U_{i+1,j} - U_{i-1,j} - U_{i,j+1} - U_{i,j-1})
> \end{aligned}
> $$
>
> $\hat{A}_{2D}$ 和 $A_{2D}$ 的矩阵是不相同的，（维数不同，作用效果也不同）。
>
> 定义 $\phi: \mathbb{R}^2 \to \mathbb{R}$， $\phi(x, y) = (x-\frac12)^2 + (y-\frac12)^2, \phi_{i,j} = \phi(ih, jh)$。
>
> 则 $\hat{A}_{2D} \phi_{i,j} = -4$。
>
> 令 $E, \tau: \mathbf{X} \to \mathbb{R}$ 分别为总体误差和 LTE，记 $\tau_m := \max_{i,j} |\tau_{i,j}|$，
>
> 定义网格函数 $\psi:\mathbf{X} \to \mathbb{R}, \psi_{i,j} = E_{i,j} + \frac14 \tau_m \phi_{i,j}$，又因为 $\hat{A}_{2D} E_{i,j} = -\tau_{i,j}$，
>
> 则 $\hat{A}_{2D} \psi_{i,j} = -\tau_{i,j} - \tau_m \le 0$，这说明 $\psi_{i,j}$ 一定比其四联通相邻的4个网格点之一小，因此 $\psi$ 的最大值在边界处取得。$\phi_{i,j}$ 的最大值是 $\frac12$，$E_{i,j}$ 在边界上是 $0$，所以：
>
> $$
> \exist C > 0, E_{i,j} \le \psi_{i,j} \le \frac18 \tau_m \le Ch^2
> $$
>
> 定义 $\chi:\mathbf{X} \to \mathbb{R}, \chi_{i,j} = - E_{i,j} + \frac14 \tau_m \phi_{i,j}$，则类似地有 $-E_{i,j} \le \chi_{i,j} \le \frac18\tau_m \le Ch^2$。

> **注解：**
>
> 定义 $\mathbf{X}_{\Omega}$ 为 BVP 地离散点集合，即待求值的点的集合，$\mathbf{X}_{\partial \Omega}$ 为 BVP 的边界离散点的集合，即已知值的点的集合（Dirichlet条件），以及 “ghost cell”（方便程序设计而加的 $\Omega$ 外的点）。比如 $[0, 1]^2$ 的四个角。

> 【引理7.58】（离散最大值原理）
>
> 设 BVP 的 FD 离散化为 $\forall P \in \mathbf{X}_{\Omega}, (L_h U)_P - f_P + g_P = 0$，$f_P$ 是方程的右端项，$g_P$ 是除 Dirichlet 外的边界条件（因为 Dirichlet 已包含在 $L_h$ 中）。$L_h, \mathbf{X}_{\Omega}$ 满足：
>
> **(DMP-1)**  $\forall P \in \mathbf{X}_{\Omega}, L_hU_P = c_P U_P - \sum\limits_{Q\in Q_P} c_QU_Q$，其中 $Q_P \subset \mathbf{X}_{\Omega} \cup \mathbf{X}_{\partial \Omega}, c_P > 0, c_Q > 0$，称 $\{P\}\cup Q_P$ 为 $L_h$ 上的 *P-stencil* （P-模版）；
>
> **(DMP-2)**  $\forall P \in \mathbf{X}_{\Omega}, c_P \ge \sum\limits_{Q\in Q_P} c_Q$；
>
> **(DMP-3)** $\mathbf{X}_{\Omega}$ 是联通的，即 $\forall P_0, P_m \in \mathbf{X}_{\Omega}, \exists P_1, P_2, \dots, P_{m-1},\text{ s.t.}\forall r = 1,2,\dots, m, P_r$ 在 $P_{r-1}$-模版中。
>
> **(DMP-4)**  (DMP-1) 中至少有一个方程包含了由 Dirichlet 边界条件给出的 $U_Q$。
>
> 则对于任意网格函数 $\psi: \mathbf{X} \to \mathbb{R}$，满足 $\begin{cases} \max\limits_{P\in \mathbf{X}} \psi_P \ge 0 \\ \forall P \in \mathbf{X}_{\Omega}, \quad L_h\psi_P \le 0\end{cases}$；
>
> 则有 $\max\limits_{P\in \mathbf{X}_{\Omega}} \psi _P \le \max\limits_{Q\in \mathbf{X}_{\partial\Omega}} \psi_{Q}$。
>
> **证明：**
>
> 设 $M_{\Omega} = \max\limits_{Q\in \mathbf{X}_{\Omega}} \psi_Q > M_{\partial \Omega} = \max\limits_{Q\in \mathbf{\partial \Omega}} \psi_Q$，令 $P$ 为 $\psi$ 达到 $M_{\Omega}$ 的点，则有
>
> $$
> M_{\Omega} = \psi_P \le \dfrac1{c_P} \sum_{Q\in Q_P} c_Q \psi_Q \le \dfrac1{c_P} \sum_{Q\in Q_P} c_Q M_{\Omega} \le M_{\Omega}
> $$
>
> 第二个 '=' 能取到当且仅当 $\forall Q, \psi_Q = \psi_P$，由 (DMP-3) $\psi$ 在任意离散点处都取到相同的值 $M_{\Omega}$，矛盾！

> 【定理7.60】考虑 BVP 的满足 (DMP-1,2,3,4) 的 FD 格式，则其全局误差 $E_P := U_P - u(P)$ 有界：
>
> $$
> \forall P \in \mathbf{X}, \quad |E_P| \le T_{max} \left(\max_{Q\in \mathbf{X}_{\partial \Omega}} \phi(Q)\right)
> $$
>
> 其中 $T_{max} = \max\limits_{P\in \mathbf{X}_{\Omega}} |T_P|$，$T_P$ 是 $P$ 处的 LTE，$\phi:\mathbf{X} \to \mathbb{R}$ 是一个非负函数满足 $\forall P \in \mathbf{X}_{\Omega}, L_h \phi_P \le -1$。
>
> **证明：**
>
> 根据【引理7.58】$L_hE_P = - T_P$。定义 $\psi_P := E_P + T_{max} \phi_P$，则 $L_h \psi_P \le -T_P - T_{max} \le 0$。进一步地，因为 $\phi_P \ge 0$，所以 $\max\limits_{P\in \mathbf{X}}\psi_P \ge 0$ 且 $\forall Q \in \mathbf{X}_{\partial \Omega}, E_Q = 0$。
>
> $$
> \begin{aligned}
> 	E_P &\le \max_{P \in \mathbf{X}} (E_P + T_{max} \phi_P) \\
> 	    &\le \max_{Q \in \mathbf{X}_{\partial Q}}(E_Q + T_{max} \phi_Q) = T_{max} \max_{Q\in \mathbf{X}_{\partial \Omega}} (\phi_Q).
> \end{aligned}
> $$
>
> 对 $\psi_P = -E_P + T_{max} \phi_P$ 同样处理，得 $-E_P\le T_{max} \max\limits_{Q\in \mathbf{\partial \Omega}}(\phi_Q)$。

### 7.6.4 不规则区域上的收敛性

【**例 7.61**】不规则区域二维 BVP + Dirichlet 条件

$$
-\dfrac{\partial^2}{\partial x^2} u(x, y) - \dfrac{\partial^2}{\partial y^2}u(x, y) = f(x, y)\quad
$$

网格点称作是 regular 的，当其可以使用 5 点差分法，否则是 irregular 的点。

比如对于下图中的 $P$ 点，列出的方程为：

$$
L_hU_P:= \dfrac{(1+\theta)U_P - U_A - \theta U_W}{\frac12 \theta(1+\theta)h^2} + \dfrac{(1 + \alpha)U_P - U_B - \alpha U_S}{\frac12 \alpha (1+\alpha)h^2}.
\\
L_hU_P = f_P
$$

<center><img src="https://img2024.cnblogs.com/blog/1129554/202401/1129554-20240125233234706-2137111722.png" style="zoom: 67%;" /></center>

【**练 7.62**】在 **例 7.61** 中，非正则点处的 LTE 是 $O(h)$，而正则点处的 LTE 是 $O(h^2)$。

> 【**定理 7.63**】在 **定理 7.60** 中，令 $\mathbf{X}_{\Omega} = \mathbf{X}_1 \cup \mathbf{X}_2 ,\quad\mathbf{X}_1 \cap \mathbf{X}_2 = \emptyset$，若非负函数 $\phi : \mathbf{X} \to \mathbb{R}$ 满足
>
> $$
> \forall P \in \mathbf{X}_1, \quad L_h \phi_P \le -C_1 < 0; \\
> \forall P \in \mathbf{X}_2, \quad L_h \phi_P \le -C_2 < 0,
> $$
>
> 并且 LTE 满足
>
> $$
> \forall P \in \mathbf{X}_1, \quad |T_P| < T_1; \\
> \forall P \in \mathbf{X}_2, \quad |T_P| < T_2.
> $$
>
> 则总误差 $E_P := U_P - u(P)$ 满足
>
> $$
> \forall P \in \mathbf{X}, |E_P| \le \left(\max_{Q\in \mathbf{X}_{\partial \Omega}} \phi(Q)\right) \max \left\{  \dfrac{T_1}{C_1}, \dfrac{T_2}{C_2}  \right\}.
> $$

> 【**定理7.65**】 **例 7.61** 中的 FD 格式在∞范数下二阶收敛。
>
> **证明：**
>
> 定义 $\phi(x, y) = \begin{cases}F_1[(x-p)^2 + (y - q)^2] & (x, y) \in \mathbf{X}_{\Omega} \\ F_1[(x-p)^2 + (y-q)^2] + F_2 & (x, y) \in \mathbf{X}_{\partial \Omega}\end{cases}$，其中 $(p, q)$ 是 $\Omega$ 的几何重心，$F_1, F_2 > 0$ 待定，正则点和非正则点均属于 $\mathbf{X}_{\Omega}$，不同点在于，对于正则点 $Q$，$L_h \phi_Q = -4 F_1$，对于非正则点 $P$ ，$-\frac2{\theta(1+\theta)h^2} < - \frac1{h^2} \Rightarrow L_h\phi_P < -4 F_1 - \frac1{h^2}F_2< \frac1{h^2}F_2$。根据【**练 7.62**】，有 $T_1 = K_1 h^2, T_2 = K_2 h$，所以 $|E_P| \le (F_1 R^2 + F_2)\max\left\{\frac{K_1h^2}{4F_1}, \frac{K_2h^3}{F_2}\right\}$，$R$ 是 $\Omega$ 中点到重心的最长距离，取 $\frac{F_1}{F_2} = \frac{K_1}{4K_2 h}$，有 $\forall P \in \mathbf{X}, |E_P| \le \frac14 K_1 R^2 h^2 + K_2h^3$。
>
>> 考虑**例 7.61**图中的非正则点：
>>
>> $$
>> \begin{aligned}
>> L_h\phi_P &= \dfrac{F_1[(1+\theta)(x_P - p)^2-\theta(x_P - h - p)^2 - (x_P + \theta h - p)^2]  - F_2}{\frac12 \theta(1+\theta)h^2} \\
>> &+ \dfrac{F_1[(1+\alpha)(x_P - q)^2-\alpha(x_P - h -q)^2 - (x_P + \alpha h - q)^2]  - F_2}{\frac12 \alpha(1+\alpha)h^2} \\
>> &= -8F_1 - F_2\left(\dfrac{2}{\theta(1+\theta)h^2} + \dfrac{2}{\alpha(1+\alpha)h^2}\right) \\
>> &< -8F_1 -\frac{2}{h^2}F_2 < -\frac2{h^2}F_2
>> \end{aligned}
>> $$
>>
>> 所以 $|E_P| \le (F_1 R^2 + F_2)\max\left\{\frac{K_1h^2}{4F_1}, \frac{K_2h^3}{2F_2}\right\}\Rightarrow |E_P| \le \frac14 K_1R^2h^2 + \frac12 K_2 h^3.$
>>
>> 事实上，只有一个方向的stencil不可达的非正则点的误差更大，不应该用**例 7.61**图中的非正则点来估计。
>>

## Programming 相关

二维 Poisson 方程：$-\Delta u = f \text{ in }\ \Omega$。

问题区域： $[x_l, x_r] \times [y_l, y_r]$，或者从中去掉一个圆盘：$D:(x-c_x)^2 + (y - c_y)^2 = R^2$。

+ $u(x, y) = \exp (y + \sin(x))$
+ $u(x, y) = \sin x \sin y$
+ $u(x, y) = \ln(1 + x^2 + y^2)$

**注意**

+ 纯 Neumann：有一个自由常数，可以强行左下角的点等于 $1$；
+ Regular 情况：

  + **Dirichlet**：一共 $(N+1)^2 - 4$ 个点，对于内部 $(N-1)^2$ 个点列五点差分，对于边界 $4(N-1)$ 个点直接求值；
  + **Neumann**：一共 $(N+3)^2-4$ 个点，对于已有 $(N+1)^2$ 个点列五点差分，对于延拓的 $4(N+1)$ 个点列导数条件；

    <center><img src="/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/notes/image/image-20240201025049602.png" alt="image-20240201025049602" style="zoom:25%;", width = 30% /></center>
  + **mixed**：考虑四个角，如果两侧都是 Neumann，需要把角两边的点也延拓；如果两侧都是 Dirichlet，角不需要考虑；如果两侧条件不一样，则角需要考虑，但不用延拓角两边的点，可以直接取它根据 Dirichlet 边算出来的值，具体如下：

    <center><img src="/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/notes/image/image-20240201024848821.png" alt="image-20240201024848821" style="zoom:25%;",width = 30% /></center>
+ Irregular 情况：

  [原方案——写出来2阶硬是跑成了1阶收敛]

  **限制：圆与外框不相交，不相切！圆内至少有4个格点。**

  + 边界条件如上。
  + 内部格点均可以列五点差分。
  + 圆与格线交点（可能直接就是格点），Dirichlet 直接求值，Neumann 要想满足收敛阶需要更多的点（6个）。
  + 圆内部延拓出来的点，列一个割线近似的方程。

    <center><img src="/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/notes/image/image-20240201025727047.png" alt="image-20240201025727047" style="zoom:67%;" /></center>

    [最终采纳方案⬇️]

不过点不能像下面某些取2*3的点阵，得保证一定有横纵坐标都不相同的3个才行。

![IMG_79768E0B0EC5-1](/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/notes/image/PDE%20Ch7%20%E8%BE%B9%E5%80%BC%E9%97%AE%E9%A2%98%E7%9A%84%E6%9C%89%E9%99%90%E5%B7%AE%E5%88%86%E6%B3%95/IMG_79768E0B0EC5-1.jpeg)
