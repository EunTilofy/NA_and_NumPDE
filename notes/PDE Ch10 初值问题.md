$N$ 维常微分方程可以写为如下形式：$\mathbf{u}'(t)=\mathbf{f}(\mathbf{u}(t), t)$，其中 $\mathbf{u} \in \mathbb{R}^N, \mathbf{f}:\mathbb{R}^N \times (0, +\infty) \to \mathbb{R}^N$。若 $\texttt{RHS}$ 可以表示为 $\mathbf{f}(\mathbf{u}, t) = A(t)\mathbf{u} + \mathbf{\beta}(t)$，则称为线性的。若 $A(t) = A$ 与 $t$ 无关，称为常系数的。若 $\beta(t) = \mathbf{0}$ 且方程线性，则称为齐次的。若 $\mathbf{f}$ 与 $t$ 无关，则称为自治的。将 $t$​ 视作时间维。

> 【例10.3】
>
> <center><img src="/Users/pac/Documents/2024-sp/NumPDE/NA_and_NumPDE/notes/image/PDE%20Ch10%20%E5%88%9D%E5%80%BC%E9%97%AE%E9%A2%98/image-20240220204912572.png" alt="image-20240220204912572" style="zoom:15%;" /></center>
>
> 小球角加速度：$\theta'' = -g\sin\theta /\ell$。
>
> 初值：$\theta(0) = \theta_0, \theta'(0) = \omega_0$。
> $$
> \begin{bmatrix}\theta \\ \theta'\end{bmatrix}' = \begin{bmatrix}\theta' \\ -g\sin\theta / \ell \end{bmatrix}
> $$

**初值问题**(IVP)：$T>0, \mathbf{f}:\mathbb{R}^N \times [0, T] \to \mathbb{R}^N, \mathbf{u}_0 \in \mathbb{R}^N$，求解 $\mathbf{u}(t) \in \mathcal{C}^1$：
$$
\begin{cases}
 \mathbf{u}(0) = \mathbf{u}_0, \\
 \mathbf{u}'(t) = \mathbf{f}(\mathbf{u}(t), t), \forall t \in [0, T].
\end{cases}
$$

# 10.1 Mathematical Foundation

[暂时跳过]

# 10.2 基础数值方法

给定初值 $\mathbf{U}^0 = \mathbf{u}_0$，目标是计算近似值 $\mathbf{U}^1, \mathbf{U}^2, \cdots $使得 $\mathbf{U}^n \approx \mathbf{u}(t_n)$，$k$ 为时间步，$t_n = nk$。

【定义10.53】*(forward)Euler's Method*（欧拉折线）：$\mathbf{U}^{n+1} = \mathbf{U}^n + k\mathbf{f}(\mathbf{U}^{n}, t_{n})$。

【定义10.54】*backward Euler's Method*：$\mathbf{U}^{n+1} = \mathbf{U}^n + k\mathbf{f}(\mathbf{U}^{n+1}, t_{n+1})$。

【定义10.55】*trapezoidal method*：$\mathbf{U}^{n+1} = \mathbf{U}^n + \frac{k}2 (\mathbf{f}(\mathbf{U}^{n}, t_{n}) + \mathbf{f}(\mathbf{U}^{n}, t_{n}))$​。

【定义10.56】*midpoint(or leapfrog) method*：$\mathbf{U}^{n+1} = \mathbf{U}^{n-1} + 2k\mathbf{f}(\mathbf{U}^{n}, t_n)$。

## 10.2.1 Truncation and solution errors

【定义10.58】局部截断误差（LTE）来自将导数用有限差分来近似。

+ leapfrog 方法的 LTE 为：

$$
\begin{aligned}
\mathbf{\pmb{\tau}}^n &= \dfrac{\mathbf{u}(t_{n+1}) - \mathbf{u}(t_{n-1})}{2k} - \mathbf{f}(\mathbf{u}(t_n), t_n) \\ &= \left[ \mathbf{u}'(t_n) + \dfrac16 k^2 \mathbf{u}'''(t_n) + O(k^4) \right] - \mathbf{u}'(t_n) \\
&= \dfrac16 k^2 \mathbf{u}'''(t_n) + O(k^4).
\end{aligned}
$$

+ Euler 方法的 LTE 为：
	$$
	\pmb{\tau}^n = \dfrac{\mathbf{u}(t_{n+1} - \mathbf{u}(t_n))}{k} - \mathbf{u}'(t_n) = \dfrac12 k\mathbf{u}''(t_n) + O(k^2)
	$$

【定义10.60】对于 $\mathbf{U}^{n+1} = \phi (\mathbf{U}^{n+1}, \mathbf{U}^n, \ldots, \mathbf{U}^{n-m})$ 形式的数值方法，*one-step error* 的定义为：
$$
\mathcal{L}^n := \mathbf{u}(t_{n+1}) - \mathbf{\phi}(\mathbf{u}(t_{n+1}), \mathbf{u}(t_n), \ldots, \mathbf{u}(t_{n-m})).
$$
【例10.61】leapfrog 方法的 one-step error 为：
$$
\begin{aligned}
\mathcal{L}^n 
&= \mathbf{u}(t_{n+1}) - \mathbf{u}(t_{n-1}) - 2k \mathbf{f}(\mathbf{u}(t_n), t_n) = 2k\mathbf{\pmb{\tau}}^n \\
&= \frac13 k^3 \mathbf{u}'''(t_n)+O(k^5).
\end{aligned}
$$
【定义10.62】初值问题数值方法的 *solution error* 定义为：
$$
\mathbf{E}^N := \mathbf{U}^{T/k} - \mathbf{u}(T); \quad \mathbf{E}^n = \mathbf{U}^n - \mathbf{u}(t_n).
$$

## 10.2.2 Euler 方法的收敛性

【定义10.63】数值方法的收敛当且仅当对于所有初值问题满足 $\mathbf{f}(\mathbf{u}, t)$ 连续且关于 $\mathbf{u}$ Lipschitz 连续（满足 Picard 存在唯一性），都满足 $\forall T > 0 , \lim\limits_{k \to 0, NK = T} \mathbf{U}^N = \mathbf{u}(T)$。

> 【引理10.64】考虑线性 IVP ：$\begin{cases}\mathbf{u}'(t)=\lambda \mathbf{u}(t) + \mathbf{g}(t) \\ \mathbf{u}(0) = \mathbf{u}_0\end{cases}$，其中 $\lambda$ 是标量矩阵或对角矩阵。Euler 方法的解误差和LTE满足：$\mathbf{E}^{n+1} = (1+k\lambda)\mathbf{E}^n - k\mathbf{\pmb{\tau}}^n$​。
>
> **证明：**
> $$
> \begin{aligned}
> \pmb{\tau}^n &= \dfrac{\mathbf{u}(t_{n+1} - \mathbf{u}(t_n))}{k} - \mathbf{u}'(t_n) \\
> &= \dfrac{\mathbf{u}(t_{n+1}) - \mathbf{u}(t_n)}{k} - (\lambda\mathbf{u}(t_n) + \mathbf{g}(t_n))
> \\
> \Rightarrow &\mathbf{u}(t_{n+1}) = (1+k\lambda)\mathbf{u}(t_n) + k\mathbf{g}(t_n) + k\pmb{\tau}^n
> \end{aligned}
> $$
>
> $$
> \mathbf{U}^{n+1} = \mathbf{U}^n + k(\lambda\mathbf{U}^n + \mathbf{g}(t_n)) = (1+k\lambda)\mathbf{U}^n + k\mathbf{g}(t_n).
> $$

> 【定理10.66】Euler 方法对于线性 IVP 收敛。
>
> **证明：**
>
> 根据 $|1+k\lambda|\le 1+|k\lambda|\le e^{k|\lambda|}$，
>
> 对于 $m\le n\le T/k$，$(1+k\lambda)^{n-m} \le e^{nk|\lambda|} \le  e^{|\lambda|T}$​。
>
> 假设：$\| \mathbf{E}^0\| = O(k)$
> $$
> \begin{aligned}
> \mathbf{E}^{n} &=(1+k\lambda)^n \mathbf{E}^0 - k\sum_{k = 1}^n (1+k\lambda)^{n-m} \pmb{\tau}^{m-1} \\
> \| \mathbf{E}^{n}\| &\le e^{|\lambda|T}\left(\| \mathbf{E}^0\| + k\sum_{m=1}^n \| \pmb{\tau}^{m-1}\|\right) \\
> &\le e^{|\lambda|T} \left(\| \mathbf{E}^0\| + nk \max_{1\le m\le n} \| \pmb{\tau}^{m-1}\|\right) \\
> &\le e^{|\lambda|T}(\| \mathbf{E}^0 \| + T O(k)) = O(k). 
> \end{aligned}
> $$

> 【引理10.67】假设形式为 $\mathbf{u}'(t) = \mathbf{f} (\mathbf{u}(t), t)$ 的非线形 IVP，其中$\mathbf{f}(\mathbf{u}, t)$ 连续且关于 $\mathbf{u}$ Lipschitz 连续（常数为 $L$ ），Euler 方法满足：$\| \mathbf{E}^{n+1}\| \le (1+kL) \| \mathbf{E}^n\| + k \| \pmb{\tau}^n \|$​。
>
> **证明：**
> $$
> \pmb{\tau}^n = \dfrac{\mathbf{u}(t_{n+1}) - \mathbf{u}(t_n)}{k} - \mathbf{f}(\mathbf{u}(t_n), t_n)\\
> \mathbf{u}(t_{n+1}) = \mathbf{u}(t_n) + k\mathbf{f}(\mathbf{u}(t_n), t_n)+k\pmb{\tau}^n \\
> \Rightarrow \mathbf{E}^{n+1} = \mathbf{E}^n + k(\mathbf{f}(\mathbf{U}^n, t_n)-\mathbf{f}(\mathbf{u}(t_n), t_n)) - k\pmb{\tau}^n\\
> \Rightarrow \| \mathbf{E}^{n+1}\| \le \|\mathbf{E}^{n}\| +k\| \mathbf{f}(\mathbf{U}^n, t_n)-\mathbf{f}(\mathbf{u}(t_n), t_n)\|+k\|\tau^n\|\le(1+kL)\| \mathbf{E}^{n}\|+k\|\tau^n\|
> $$

> 【定理10.68】对于非线形 IVP（满足 10.67 条件），Euler 方法收敛。
>
> **证明：** $\| \mathbf{E}^N \|\le  (1+kL)^n\| \mathbf{E}^0\| - k\sum_{k = 1}^n (1+kL)^{n-m} \pmb{\tau}^{m-1} \le e^{LT}(\| \mathbf{E}^0 \| + LO(k)) = O(k). $

## 10.2.3 Zero stability and absolute stability

【定义10.69】数值方法的称作 *stable/zero-stable* 当且仅当对于所有初值问题满足 $\mathbf{f}(\mathbf{u}, t)$ 连续且关于 $\mathbf{u}$ Lipschitz 连续（满足 Picard 存在唯一性），都满足 $\forall T > 0, \lim\limits_{k\to 0, Nk=T}\| \mathbf{U}^N\| < \infty$​。

【定义10.71】对于 $u'(t) = \lambda u(t)$ 使用 Euler 方法  $U^{n+1} = (1+k\lambda)U^n$ 来求解是 *absolutely stable* 或说有 *eigenvalue stability* 若 $|1+k\lambda| \le 1 + O(k)$。

【定义10.72】$u'(t) = \lambda u(t)$ 的前向 Euler 方法（$U^{n+1} = (1+k\lambda)U^n$ ）的绝对稳定区域是 $\{z\in \mathbb{C} : |1+z|\le 1+O(k)\}$。对于后项 Euler 方法（$U^{n+1} = \dfrac{1}{1-k\lambda}U^n$ ）绝对稳定区域为 $\{z\in \mathbb{C} : |-1+z|\ge 1+O(k)\}$。

> 【引理10.74】对于自治齐次线性IVP，$\mathbf{u}'(t) = A\mathbf{u}$。其中 $\mathbf{u} \in \mathbb{R}^N, N>1$，并且 $A$ 是可对角化为 $\Lambda = \text{diag}(\lambda_i)$。Euler 方法是绝对稳定的若 $z_i := k\lambda_i$ 都在绝对稳定区域内。
>
> **证明：**
> $$
> \mathbf{U}^{n+1} = \mathbf{U}^{n} + k A \mathbf{U}^n = (I + kA)\mathbf{U}^n.
> $$
> 设 $AR = R\Lambda$，所以 $R^{-1}\mathbf{U}^{n+1} = R^{-1}(I+kA)RR^{-1}\mathbf{U}^n$。令 $\mathbf{V}:= R^{-1}\mathbf{U}$，则 $\mathbf{V}^{n+1}=(I+k\Lambda)\mathbf{V}^n$。

> 【公式10.79】把一个初值问题 $\mathbf{u}'(t) = \mathbf{f}(\mathbf{u}, t)$ 转化成常系数线性方程组 $w_i'(t) = \lambda_i w_i(t), \quad i = 1, 2, \cdots, n$ 的步骤如下：
>
> 1. 线性化：对于一个特定的解 $\mathbf{u}^* (t)$，记 $\mathbf{u}(t) = \mathbf{u}^*(t) + (\delta \mathbf{u}) (t)$，泰勒展开得 $\mathbf{f}(\mathbf{u}, t) = \mathbf{f}(\mathbf{u}^*, t) + J(t)\delta \mathbf{u} + o(\| \delta \mathbf{u} \|)$，（$J(t)$ 是 $\mathbf{f}$ 关于 $\mathbf{u}$ 的 Jacobi 常数）。
> 2. 冻结系数：令 $A = J(t^*)$，其中 $t^*$ 是一个特定值。
> 3. 对角化：假设 $V^{-1}AV =\Lambda$ 是一个对角阵，记 $(\delta \mathbf{u})'(t) = V(V^{-1}AV)V^{-1}(\delta \mathbf{u})$，定义 $\mathbf{w}:= V^{-1}(\delta \mathbf{u})$，则得到方程组 $\mathbf{w}'(t) = \Lambda \mathbf{w}(t)$。

# 10.3 Linear Multistep Methods

【定义10.80】初值问题 $\begin{cases} \mathbf{u}(0) = \mathbf{u}_0, \\ \mathbf{u}'(t) =\mathbf{f}(\mathbf{u}(t), t), \forall t \in [0, T].\end{cases}$ 的 *s-step linear multistep method* （LMM）形式为：
$$
\sum_{j = 0}^s  \alpha_j \mathbf{U}^{n+j} = k \sum_{j = 0}^s \beta_j \mathbf{f}(\mathbf{U}^{n+j}, t_{n+j}), (\alpha_s = 1 \quad\text{WLOG})
$$
【定义10.81】LMM 被称作是 *explicit* 的若 $\beta_s = 0$ 否则称作是 *implicit* 的。

## 10.3.1 Clasical formulas

【定义10.82】*Adams formula* 是如下形式的 LMM：（其中 $\beta_j$ 需要选择可以满足最好的收敛阶的值）
$$
\mathbf{U}^{n+s} = \mathbf{U}^{n+s-1} + k\sum_{j=0}^s \beta_j \mathbf{f}(\mathbf{U}^{n+j}, t_{n+j})
$$
【定义10.83】*Adams-Bashforth formula* 是满足 $\beta_s = 0$ 的 Adams formula。*Adams-Moulton formula* 是满足 $\beta_s \neq 0$ 的 Adams formula。

【例10.84-85】

+ Euler 方法是 1-step 的 Adams-Bashforth formula：$s = 1, \alpha_1 = 1, \alpha_0 = -1, \beta_1 = 0, \beta_0 = 1$​。
+ Trapezoidal 方法是 1-step 的 Adams-Moulton formula ：$s = 1, \alpha_1 = 1, \alpha_0 = -1, \beta_1 = \beta_0 = \dfrac12$。

【定义10.86】*Nystrom formula* 是如下形式的 LMM：（其中 $\beta_j$ 满足收敛阶达 $s$）
$$
\mathbf{U}^{n+s} = \mathbf{U}^{n+s-2} + k \sum_{j=0}^{s-1} \beta_j \mathbf{f}(\mathbf{U}^{n+j}, t_{n+j})
$$
【例10.87】中点法是 2-step 的 Nystrom formula：$s = 2, \alpha_1 = 0, \alpha_0 = -1, \beta_1 = 2, \beta_0 = \beta_1 = 0$。

【定义10.88】一个 *backward differentiation formula*（BDF）是如下形式的 LMM：（其中 $\alpha_j$'s 和 $\beta_s$ 满足收敛阶达 $s$）
$$
\mathbf{U}^{n+s} + \sum_{j=0}^{s-1} \alpha_j \mathbf{U}^{n+j} = k \beta_s \mathbf{f}(\mathbf{U}^{n+s}, t_{n+s})
$$
【例10.89】反向 Euler 算法是 1-step 的 BDF：$s=1, \alpha_1 = \beta_1 = 1, \alpha_0 = -1$。



# 10. 6 Runge-Kutta (RK) methods

【】

