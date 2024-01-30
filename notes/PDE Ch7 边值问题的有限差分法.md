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
> $$
> \Delta \phi = f \quad \text{in} \ \ \Omega \\
> \mathbf{n}\cdot \nabla \phi = \quad \text{on} \ \ \partial \Omega
> $$
> 在满足额外条件（“高斯定理”）：
> $$
> \int_{\Omega} f \mathrm{d} V = \int_{\partial \Omega} g\mathrm{d} A.
> $$
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

有限差分法的全局误差（global error） 是 $\mathbf{E} = \mathbf{U} - \hat{\mathbf{U}}$。其中 $\mathbf{U}$ 为求解方程得到的解向量，$\hat{\mathbf{U}}$ 是格点处的原函数值。

**网格函数（grid function）**：$\mathbf{g}:\mathbf{X}\to \mathbb{R}$，其中 $\mathbf{X}$ 是离散网格。

>  **q-范数**
>
>  一维网格 $\mathbf{X}:= {x_1, \cdots, x_N}$。$\mathbf{g}$ 定义在 $\mathbf{X}$ 上。
>  $$
>  \| \mathbf{g}\|_q = \left(h\sum_{i = 1}^N |g_i|^q\right)^{\frac1q}
>  $$
>
>  1. $1-$范数：$\|g\|_1 = h\sum_{i = 1}^N|g_i|$;
>  2. $\infty-$范数：$\| g\|_{infty} = \max\limits_{1\le i\le N}|g_i|$。

**局部截断误差（LTE）**：导数值用有限差分替代所导致的误差（是一个理论值）。

比如：$D^2u(x_j) := \dfrac{u(x_{j-1} - 2u(x_j) + u(x_{j+1}))}{h^2}$ 的 LTE 为 $\tau_j = -D^2u(x_j) - (-u'' (x_j)) = -\dfrac{h^2}{12}u''''(x_j) + O(h^4) = O(h^2).$

> 【**引理 7.17**】
>
> 对于 $(0, 1)$ 上一维线性边值问题 $\mathcal{L}u = f(x)$，若使用有限差分方法得到 $A\mathbf{U} = \mathbf{F}$，则该方法的 LTE 为 $\tau = A\hat{\mathbf{U}} - \mathbf{F}$。其中 $\mathbf{F} = (f(x_1), \cdots, f(x_m))$。
>
> 【**证明**】以 【**例 7.10**】为例：
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
> $$
> \lim \| \mathbf{E}^h\| \le \lim \| (A^h)^{-1}\| \lim \| \tau^h \| \le C \lim \| \tau^h\| = 0,
> $$
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

> 【**定理 7.27**】
>
> 【**例 7.10**】中的有限差分法 2 阶收敛。
>
> 【**证明**】
>
> 根据 $A$ 的对称性
> $$
> \| A\|_2 = \sqrt{\rho(A^2)} = \rho(A) \le \frac{4}{h^2}
> $$
> 由 【**引理 7.25**】$A$ 非奇异。
>
> 并且
> $$
> \lim_{h\to 0}\| A^{-1}\|_2 = \lim_{h\to 0} 
> \dfrac{1}{\min |\lambda_k(A)|}=\lim_{h\to0}
> \dfrac{h^2}{4\sin^2 \frac{\pi h}{2}}
> = \dfrac{1}{\pi^2}
> $$
> 所以 FD 方法稳定。
>
> 因为 LTE 满足
> $$
> \lim_{h\to 0} |\tau_j| 
> = \left|- \frac{h^2}{12}u''''(x_j) + O(h^4)\right| = 0 \\
> \Rightarrow \lim_{h\to 0} \| \tau^h \| = 0
> $$
> 所以 FD 方法一致。
>
> 根据 【**定理 7.22**】，FD 方法 2 阶收敛。

### 7.3.2 Green 函数

[跳过]

### 7.3.3 ∞范数下收敛

> 【**引理 7.31**】
>
> 对于矩阵 $A$：
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
> 其逆矩阵 $B = A^{-1}$ 为：
> $$
> b_{ij} = -h G(x_i; x_j)= \begin{cases}
> -h(x_j - 1)x_i, \quad i \le j, \\
> -hx_j(x_i - 1), \quad i \ge j.
> \end{cases}
> $$
> 即：
> $$
> B = -h\begin{bmatrix}
> x_1(x_1 - 1) & x_1(x_2 - 1) & \cdots & x_1(x_m - 1)\\
> x_1(x_2 - 1) & x_2(x_2 - 1) & \cdots & x_2(x_m - 1) \\
> \vdots& \vdots & \ddots & \vdots \\
> x_1(x_m - 1) & x_2(x_m - 1) & \cdots & x_m(x_m - 1)
> \end{bmatrix}
> $$
> 其中 $x_j = \dfrac{j}{m+1}$。
>
> 【**证明**】
>
> $A$ 的第 $i$ 行（乘 $h^2$）和 $B$ 的第 $j$ 列（乘 $-1/h$）如下：
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
> $$
> \| B \|_{\infty} = \max_{1\le i \le m}\sum_{j = 1}^m |b_{ij}| \le 1.
> $$
> 【**证明**】
> $$
> \begin{aligned}
> \sum_{j = 1}^m |b_{ij}| &= \sum_{j = 1}^i hx_j|x_i - 1| + \sum_{j = i + 1}^m hx_i|x_j - 1| \\
> &\le \sum_{j = 1}^i h\left(\dfrac{m}{m + 1}\right)^2 + \sum_{j = i + 1}^m h\left(\dfrac{m}{m + 1}\right)^2 \quad [x_j \le \dfrac{m}{m+1}, |x_i - 1|\le 1]\\
> &= mh\left(\frac{m}{m+1}\right)^2 = \left(\frac{m}{m+1}\right)^3 \le 1.
> \end{aligned}
> $$



## 7.4 A solution via Green’s function

[跳过]

## 7.5 其他边值条件

【**例 7.35**】二阶边值问题+混合边值条件
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

+ [方法二]

	延拓一个点 $x_{-1} = -h$，使用 $\dfrac{U_1 - U_{-1}}{2h} = \sigma$，此时为二阶精度。

	为了消掉 $x_{-1}$，增加条件 $\dfrac{1}{h^2}(U_{-1} - 2U_0 + U_1) = f(x_0)$，则得到 $\dfrac{1}{h}(-U_0 + U_1) = \sigma + \dfrac{h}2f(x_0)$。

+ [方法三]（编程推荐）

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

【**例 7.37**】二阶边值问题+Neumann条件
$$
u''(x) = f(x) \quad \text{in}\ \  (0, 1), \\
u'(0) = \sigma_0, u'(1) = \sigma_1.
$$
为了保证解的存在性，需要满足：
$$
\int_0^1 f(x) \mathrm{d}x = \int_0^1 u''(x)\mathrm{d}x = u'(1) - u'(0) = \sigma_1 - \sigma_0.
$$
处理方法类似 【**例 7.35**】。

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

> 【**引理 7.38**】
>
> 【**例 7.37**】 中矩阵 $A_F$ 满足 $\dim \mathcal{N}(A_F) = 1$。（$\mathcal{N}$ 即 Kernel）。
>
> 【**证明**】
>
> 显然 $\mathbf{e} = [1, 1, \cdots, 1]^T$ 属于 $A_F$ 的零空间。
>
> 如果定下了 $U_{m+1}$ 的值，则变为混合边界条件，其解唯一，所以零空间秩为1。

> 【**定理 7.39**】（可解性）
>
> 【**例 7.37**】 中方程有解，当且仅当 
> $$
> \frac{h}2 f(x_0) + h\sum_{i = 1}^m f(x_i) + \frac{h}2f(x_{m+1}) = \sigma_1 - \sigma_0
> $$
> 【**证明**】
>
> 根据代数基本定理
>
> > $f:U\to V$，$A$ 是 $f$ 对应的矩阵。
> >
> > $V = \text{Im} A\oplus \text{Ker}A^T$
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

【**例 7.40-7.41**】二维 BVP+Dirichlet条件
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
对于 $\Delta f(x_i, y_j) = (-\dfrac{\partial^2}{\partial x^2} -\dfrac{\partial^2}{\partial y^2})(x_i, y_j)$，作如下近似：
$$
f_{ij} = - \dfrac{U_{i - 1, j} - 2U_{i,j} + U_{i+1,j}}{h^2} - \dfrac{U_{i,j-1} - 2U_{i,j}+U_{i,j+1}}{h^2}.
$$
将 $m\times m$ 个方程组成方程组 $A_{2D}\mathbf{U} = \mathbf{F}$。

**LTE** 的计算如下：
$$
\tau_{i,j} = -\frac1{12} h^2\left(\dfrac{\partial^4u}{\partial x^4} + \dfrac{\partial^4u}{\partial y^4}\right)\bigg|_{(x_i, y_j)} + O(h^4).
$$

> 【**引理 7.43**】
>
> 【**例 7.40-7.41**】中全局误差 $\mathbf{E} = \mathbf{U} - \hat{\mathbf{U}}$。则 $A_{2D}\mathbf{E} = -\mathbf{\tau}$。

### 7.6.1 Kronecker product

[跳过]

### 7.6.2 Convergence in the 2-norm

[跳过]

### 7.6.3 Convergence in the max-norm via a discrete maximum principle

[跳过]

### 7.6.4 不规则区域上的收敛性

【**例 7.60**】不规则区域二维 BVP + Dirichlet 条件
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

[7.62-64 暂时跳过]