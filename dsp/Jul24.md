---
mathjax: true
---

{% include mathjax.html %}

## 総合演習 14
### 1. 単位インパルス数列の定義式, 図の信号の式
$ \delta(n) = \lbrace 1 \quad (n=1), 0 \quad (n=0) $

$ 2\delta(n) + \delta(n+1) + 3\delta(n) - 2\delta(n-1) + 2\delta(n-2) - 3\delta(n-3) $

### 2. $X(z)=1$ の信号に $z^{-1}$ を乗ずることは、時間領域ではどのような信号となるか。また、 $X(z)=2+3z^{-1}-2z^{-1}+z^{-3}$の時間領域での信号を図示せよ。
$x(n) = \delta(n-1)$

$\lbrace x(n) \rbrace = \lbrace 2, 3, -2, 1, 0, 0 \ldots \rbrace$

### 3. 以下の式 $X(z)$ の逆z変換を求めよ。
$$ X(z) = \frac{3}{1-0.5z^{-1}} $$

等比級数の式より

$$ x(n) = 3 \cdot 0.5^n $$

### 4. 以下のシステムについて次の問いに答えよ。
$$ y(n) = \frac12 x(n) + \frac12 x(n-1) + y(n-1) $$

#### 1) 伝達関数を求めよ。
<div>$$\begin{eqnarray*}
Y(z) &=& \frac12 X(z) + \frac12 X(z) z^{-1} + Y(z) z^{-1} \\
Y(z) (1 - z^{-1}) &=& \frac12 X(z) (1 + z^{-1}) \\
H(z) &=& \frac{Y(z)}{X(z)} = \frac12 \cdot \frac{1 + z^{-1}}{1 - z^{-1}} \\
 &=& \frac12 (\frac1{1 - z^{-1}} + z^{-1}\cdot\frac1{1-z^{-1}})
\end{eqnarray*}$$
</div>

#### 2) システムに単位インパルス数列を加えた時の単位インパルス応答を求め、図示せよ。
$ h(n) = \frac12 u(n) + \frac12 u(n-1) $

または

$y(0) = \frac12 + 0 + 0 = \frac12, y(1) = 0 + \frac12 + \frac12 = 1, y(2) = 0 + 0 + 1 = 1, y(3) = 0 + 0 + 1 = 1, \cdots$
