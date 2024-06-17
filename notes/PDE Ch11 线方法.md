# 11.1 热方程 MOL 方法

【定义11.1】称二阶常系数线性 PDE ：$Au_{xx} + B u_{xy} + C u_{yy} + D u_x + E u_y + F = 0$，是抛物型 PDE，如果 $B^2 - 4 AC = 0$​。

> Remark：若 $B^2 - 4A C < 0$，称 PDE 为椭圆型；若 $B^2 - 4 AC >0$​，称 PDE 为双曲型。  
>
> 参考二次曲线 $A x^2 + B xy + C y^2 + Dx + Ey + F = 0$ 的分类。
>
> 若用 $x$ 表示空间，$y$ 表示时间，则 PDE 成为初边值问题。

【定义11.2】一维热方程是如下形式的抛物型 PDE：
$$
\begin{cases}
	u_t = \nu u_{xx} ~~\text{in}~~\Omega:=(0, 1)\times (0, T) \\
	u(x, 0) = \eta(x) ~~\text{on}~~ (0, 1)\times\{0\}
\end{cases}
$$
其中 $x\in (0, 1)$ 为空间位置，$t \in (0, T)$ 为时间，$\nu > 0$ 为动态粘度，方程还需加上在 $\{0, 1\} \times (0, T)$​ 的适当边值条件：$u(0, t) = g_0(t), u(1, t) = g_1(t), t \in (0, T)$​。

> Remark：若 $L$ 是椭圆算子（算子矩阵负定，例如 Laplace ｜ $L= -\nabla \cdot A \nabla u + B \nabla u + C \cdot u$），则方程 $u_t = Lu - f$ 是抛物型 PDE。
>
> Remark：称系统的稳定状态是 $u_t = 0$ 的状态。

【定义11.3】初始边界值问题是确定具有初始条件和边界条件的微分方程的解的问题。

【定理11.5】热方程的精确解在 Dirichlet 边界条件 $g_0(t) = g_1(t) = 0$ 下是
$$
u(x, t) = \sum_{j=0}^{\infty} \hat{u}_j(t) \sin (\pi j x), \hat{u}_j(t) = \exp (-j^2 \pi^2 \nu t) \hat{u}_j(0),
$$
$\hat{u}_j(0)$ 是 $u(x, 0) = \sum_{j=0}^{\infty} \hat{u}_j(0) \sin (\pi j x) = \eta(x)$ 的第 $j$ 项（$\sin (\pi j x)$） Fourier mode 的系数。

## 11.1.1 FTCS 和 Crank-Nicolson

> 记 $x_i = i h, t_n = nk$，其中 $h = \frac1{m+1}$ 是均匀网格边长，$k = \Delta t$ 是时间步长，未知数 $U_i^n \approx u(x_i, t_n)$。
>
> <img src="/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/notes/image/PDE%20Ch11%20%E7%BA%BF%E6%96%B9%E6%B3%95/image-20240612114411643.png" alt="image-20240612114411643" style="zoom:50%;" />

【定义11.6】线方法（MOL）按如下方法求解 PDE：

1. 对空间 $x$ 离散，保持时间 $t$ 连续（半离散）；
2. 用 IVP 数值解法求解离散得到的 ODE。

【例子11.7】对热方程 $u_t = \nu u_{xx}$：
$$
U_i'(t) = \frac{\nu}{h^2}(U_{i-1}(t) - 2U_i(t) + U_{i+1}(t)), U_i(t) \approx u(x_i, t), i = 1, 2, \cdots, m
$$
对于 Dirichlet 边值条件 $u(0, t) = g_0(t), u(1, t) = g_1(t)$，半离散结果为：
$$
\mathbf{U}'(t) = A\mathbf{U}(t) + \mathbf{g}(t),
$$

$$
A = \frac{\nu}{h^2}\begin{bmatrix}
-2 & +1 & & & & \\
+1 & -2 & +1 & & &  \\
& +1 & -2 & +1 &  & \\
& & \ddots & \ddots & \ddots & \\
& & & +1 & -2 & +1 \\
& & & & +1 & -2
\end{bmatrix}, 
\mathbf{U}(t):=\begin{bmatrix}
U_1(t) \\ U_2(t) \\ U_3(t) \\ \vdots \\U_{m-1}(t) \\ U_m(t)
\end{bmatrix},
\mathbf{g}(t) = \frac{\nu}{h^2} \begin{bmatrix}
g_0(t) \\ 0 \\ 0 \\ \vdots \\ 0 \\ g_1(t)
\end{bmatrix}
$$

由于 $A$ 负定，定义10.224，例子10.225，该 ODE 方程是耗散的。

> 记 $r := \frac{k \nu}{h^2}$

> 【定义11.8】FTCS（*forward in time,centered in space*）
>
> 直接用 $U'(t_i) = \frac{U(t_{i+1})-U(t_i)}{k}$​，得
> $$
> \frac{U_i^{n+1} - U_i^{n}}{k} = \frac{\nu}{h^2} (U_{i-1}^n - 2 U_i^n + U_{i+1}^n),\\
> \Leftrightarrow U_i^{n+1} = U_i^n + r(U_{i-1}^n - 2U_i^n + U_{i+1}^n)
> $$

【例子11.9】对奇次 Dirichlet 边界条件，FTCS 方法可重写为 $\mathbf{U}^{n+1} = (I + kA)\mathbf{U}^n$。

【定义11.10】Crank-Nicolson 方法：
$$
\begin{aligned}
\frac{U_i^{n+1} - U_i^k}{k} &= \frac12 \left(f(U_i^n, t_n), f(U_i^{n+1}, t_{n+1})\right) \\
&= \frac{\nu}{2h^2} (U_{i-1}^n - 2U_i^n + U_{i+1}^n + U_{i-1}^{n+1} - 2U_i^{n+1} + U_{i+1}^{n+1}),
\end{aligned}
$$

$$
\Leftrightarrow -rU_{i-1}^{n+1} + 2(1+r) U_i^{n+1} - r U_{i+1}^{n+1} = rU_{i-1}^n - 2(1-r)U_i^n + rU_{i+1}^n
$$

【定义11.12】$\theta$-方法（$\theta \in [0, 1]$）：
$$
\begin{aligned}
\frac{U_i^{n+1}-U_i^{n}}{k} = \frac{\nu}{h^2}[\theta (U_{i-1}^{n+1} - 2U_i^{n+1} + U_{i+1}^{n+1}) + (1-\theta )(U_{i-1}^n - 2U_i^n + U_{i+1}^n)],\\
\Leftrightarrow -\theta r U_{i-1}^{n+1} + (1 + 2 \theta r) U_i^{n+1} - \theta r U_{i+1}^{n+1} = (1 - \theta) r U_{i-1}^n + [1 - 2(1 - \theta)r]U_i^n + (1- \theta)r U_{i+1}^n.
\end{aligned}
$$
【例子11.13】$\theta = 0$ 时的 $\theta$-方法是 FTCS 方法，$\theta = \frac12$ 时是 Crank-Nicolson 方法，$\theta = 1$ 是 BTCS（*backward in time and centered in space*）其中 ODE 求解器是反向欧拉方法。

## 11.1.2 准确性和一致性(Accuracy and consistency)

【定义11.14】MOL 求解 PDE 的局部截断误差（LTE）$\tau$​ 来自将连续的导数替换为有限差分形式。

【定义11.15】MOL 被称作一致的，如果 $\lim_{k,h\to 0} \tau(x, t) = 0$。

【定义11.16】MOL 被称作时间上 $p$-th 阶精确、空间上 $q$-th 阶精确当且仅当 $\tau(x, t) = O(k^p + h^q)$。

【例子11.17】FTCS 的 LTE 为
$$
\begin{aligned}
\tau(x, t) &= \frac{u(x, t+k) - u(x, t)}{k} - \frac{\nu}{h^2}(u(x-h, t)-2u(x, t)+u(x+h,t)) \\
&= (u_t + \frac12 k u_{tt} + \frac16 k^2 u_{ttt} + \cdots) - \nu (u_{xx} + \frac1{12}h^2 u_{xxxx} + \cdots) \\
&= (\frac12 k\nu^2 - \frac{\nu}{12}h^2)u_{xxxx} + O(k^2 + h^4)
\end{aligned}
$$
其中：$u_t = \nu u_{xx}, u_{tt} = \nu u_{xxt} = \nu u_{txx} = \nu^2 u_{xxxx}$。

所以 FTCS 在空间上2阶精确，在时间上1阶精确。

【引理11.18】$\theta$-方法的 LTE 为
$$
\begin{aligned}
\tau_i^{n+\frac12} =& \frac{u(x_i, t_n+k) - u(x_i, t_n)}{k} - \frac{\nu}{h^2}\theta [u(x_i - h, t_n + k) - 2u(x_i, t_n + k) + u(x_i + h, t_n + k)] \\
& -\frac{\nu}{h^2} (1-\theta)[u(x_i-h, t_n) - 2u(x_i, t_n) + u(x_i+h, t_n)]\\
= &\text{(根据} (x_i, t_{n+\frac12}) \text{处的 Taylor 展开以及} u_t = \nu u_{xx}\text{)} \\
& (\frac12 - \theta)k\nu u_{xxt} - \frac1{12} h^2 \nu u_{xxxx} + \frac1{12} (\frac12 - \theta)k h^2 \nu u_{xxxxt} + O(k^2+h^4)
\end{aligned}
$$
【推论11.19】Crank-Nicolson 方法的时间和空间都是2阶精确的。

【例子11.20】置 $\theta = \frac12 - \frac{h^2}{12 k\nu}$ 则得到 LTE 为 $O(k^2 + h^4)$。注意这里需要 $h^2 \leq 6 k\nu$ 以保证 $\theta \geq 0$。

## 11.1.3 绝对稳定性(Absolute stability)

【引理11.21】矩阵 $A$ 的特征值和特征向量
$$
\begin{aligned}
&\lambda_p = - \frac{4\nu}{h^2} \sin^2 \left(\frac{p \pi h}{2}\right) \\
&w_j^p = \sin (p \pi j h)\\
& p,j = 1, 2, \cdots, m, h = \frac{1}{m+1}
\end{aligned}
$$
【例子11.22】对 FTCS 方法，要绝对稳定，需要 $\forall \lambda_p, \text{s.t.~~}|1+k\lambda| \leq 1 + O(k)$，即 $-2 - O(k) \leq -4 \nu k / h^2 \leq 0$，因为 $k = o(k/h^2)$，所以 $k \leq \frac{h^2}{2\nu}(\Leftrightarrow r \leq \frac12)$​。

> Remark：由 Lem11.21，有
> $$
> \lambda_1 \approx - \frac{4\nu}{h^2} \frac{\pi^2 h^2}{2^2} = - \nu \pi^2, \lambda_m \approx - \frac{4\nu}{h^2} \\
> \frac{|\lambda|_{\text{max}}}{|\lambda|_{\text{min}}} = \frac{4}{\pi^2 h^2} \to \infty, h\to 0
> $$
> 因此热方程是刚性的。

【定义11.23】称 MOL 是无条件稳定的(*unconditionally stable*)，如果对于 $\forall k > 0$，其半离散化 ODE 都是绝对稳定的。

【引理11.24】设 MOL 所使用的 ODE 求解器对半离散化 ODE 是 $A(\alpha)$-稳定的，则对热方程，MOL 是无条件稳定的。

**证明：** $A(\alpha)$-稳定的 ODE 求解器包含整个负实轴，热方程的所有特征值全为负，所以 $\forall k > 0, k$ 均在 RAS 上。

【引理11.25】当 $\theta \in [\frac12, 1]$ 时，$\theta$-方法是无条件稳定的；当 $\theta \in [0,\frac12)$ 是稳定的当且仅当 $k \leq \frac{h^2}{2(1-2\theta)\nu}$。

【推论12.27】Crank-Nicolson 方法对热方程是无条件稳定的。

## 11.1.4 Lax-Richtmyer 稳定性

【定义11.28】称线性 MOL $\mathbf{U}^{n+1} = B_h (k) \mathbf{U}^n + \mathbf{b}_h^n (k)$ 是 Lax-Richtmyer 稳定的，当且仅当
$$
\forall T > 0, \exists h_0, k_0, C_T > 0, \text{s.t.~~}\\
\forall k \in (0, k_0], \forall h \in (0, h_0], \forall n \in \mathbb{N}^+, \\
nk \leq T \Rightarrow \| B_h(k)^n \| \leq C_T
$$
其中，$B_h$ 是边长为 $h$ 的网格的迭代矩阵，$C_T$ 与 $k$  和 $h$ 无关。进一步的，MOL 在限制 $\mathbf{g}(k, h) \leq \mathbf{0}$ （$\forall i = 1, 2, \cdots, m, g_i(k, h) \leq 0 \text{~or~} g_i(k, h) < 0$）下 Lax-Richtmyer 稳定，如果
$$
\forall T > 0, \exist h_0, k_0, C_T > 0, \text{s.t.~~}\\
\forall k \in (0, k_0], \forall h \in (0, h_0], \forall n \in \mathbb{N}^+, \\
\mathbf{g}(k, h) \leq \mathbf{0} \Rightarrow \| B_h(k)^n\| \leq C_T
$$
【定义11.29】称线性 MOL $\mathbf{U}^{n+1} = B_h (k) \mathbf{U}^{n} + \mathbf{b}_h^n(k)$ 是强稳定的，当且仅当 $\exist k_0 > 0, \text{s.t.~~} \forall k \in (0, k_0], \forall h \in \mathbb{R}^+, \| B_h(k)\|_2 \leq 1$。

【推论11.30】Crank-Nicolson 方法是强稳定的，$B = (I - \frac{k}2 A)^{-1}(I+\frac{k}2 A).$

**证明：**因为 $A$ 对称，所以 $B$ 对称，所以 $\|B\|_2 = \rho(B) = \max\left|\frac{1+k\lambda_p / 2}{1 - k \lambda_p / 2}\right| \leq 1$。

## 11.1.5 收敛性

【定义11.31】MOL 的整体误差为 $E_i^n = U_i^n - u(x_i, t_n)$。

【定义11.32】称 MOL 是收敛的，如果 $\forall T > 0, \lim\limits_{k\to 0, h\to 0; KN = T}\|E^N\| = 0$。

【引理11.33】设 $\{E_i\}_{i=1}^{\infty}$ 是一列 Banach 空间，定义空间 $E$ 和投影算子 $P_j : E \to E_j$，嵌入算子 $I_j : E_j \to E$ 如下：
$$
E := \bigoplus_{j=1}^{\infty} E_j = \bigg\{(x_i)_{i\in \mathbb{N^+}} : x_i \in E_i, \sum_{i=1}^{\infty} \| x_i \| < + \infty \bigg\} \\
\begin{cases}
	\forall (x_i) \in E, &P_j((x_i)) = x_j, \\
	\forall x \in E_j, & I_j(x) = \overline{x_j} := (0, \cdots, 0, x_j, 0, \cdots).
\end{cases}
$$
则成立：

1. $(E, \| \cdot \|) $ 是 Banach 空间，$\forall (x_i)_{i\in \mathbb{N}^+} \in E, \|(x_i)_{i\in \mathbb{N}^+}\| := \sum\limits_{i=1}^{\infty}\|x_i\|$;
2. $\forall j \in \mathbb{N}^+$，$P_j$  和 $I_j$ 都是连续线性映射，即 $P_j \in \mathcal{CL}(E, E_j), I_j \in \mathcal{CL}(E_j, E)$；
3. $\|P_j\| = \|I_j\| = 1, P_jI_j = \text{Id}_{E_j}$；
4. $\forall T \in \mathcal{CL}(E_j, E_j)$，线性算子 $\overline{T} := I_jTP_j$ 是保长延拓，即 $\overline{T} \in \mathcal{CL}(E, E), \forall n \in \mathbb{N}^+ , \left\| \overline{T}^n\right\| = \| T^n\|$。

**证明：**4. $\forall (x_i) \in E, \left\| \overline{T}^n((x_i))\right\| = \| I_j T^n P_j((x_i))\| = \| I_j T^n (x_j)\| = \| (0, \ldots, 0, T^n(x_j), 0, \ldots, 0)\| = \| T^n (x_j)\|$。

> 【定理11.34】（Lax equivalenc theorem）一致线性 MOL 方法收敛当且仅当它 Lax-Richtmyer 稳定。
>
> **证明：**暂略。

【推论11.35】用 $\theta$-方法求解热方程时，对一切 $\theta\in [0, 1]$，$\theta$ 方法均收敛。

**证明：**$B = (1-\theta k A)^{-1}[I + (1-\theta )k A], \rho(B) = \max \left|\frac{1+(1-\theta)k \lambda_p}{1 - \theta k \lambda_p}\right| \leq 1, k\to 0^+$。

## 11.1.6 离散最大值原理

【定理11.36】
