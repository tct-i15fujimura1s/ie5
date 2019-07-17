---
mathjax: true
---

{% include mathjax.html %}

1. 線形システムの確認
2. 畳込み和の確認
3. 伝達関数と差分方程式

## 1. 離散時間システム
離散時間信号を入出力とするシステム

入力 $x(n)$ と 出力 $y(n)$ とし線形演算子 $L$ を用いて

$$ L\\{x(n)\\} = y(n) $$

### システムの特性
* 線形システム: $$L\\{a_1 x_1(n) + a_2 x_2(n)\\} = a_1 L\\{x_1(n)\\} + a_2 L\\{x_2(n)\\}$$
* 時不変システム: $$L\\{x(n-k)\\} = y(n-k)$$
* 因果性システム: $$h(n) = 0 \quad t \lt 0$$

単位インパルス数列 $\delta(n)$ を加えた時の出力

$$L\\{\delta(n)\\} = h(n)$$

時不変なので両辺の $n$ の代わりに $n-k$ としてもいい

## 2. 離散畳込み和
任意の離散時間信号 $x(n)$

$$x(n) = \sum_{k = -\infty}^\infty x(k) \delta(n-k)$$

$x(n)$ を離散時間システムに入力した時の応答 $y(n)$

$$y(n) = \sum_{k = -\infty}^\infty x(k) h(n-k)$$

システムが因果性で $x(n \lt 0) = 0$ なら

$$y(n) = \sum_{k = 0}^\infty x(k) h(n-k)$$

$y(n) = x(n) * h(n)$ とも書ける

## 3. 伝達関数と差分方程式
### 伝達関数
上の式の両辺を z 変換すると

<p>$$\begin{eqnarray*}
Y(z) &=& H(z) X(z) \\
H(z) &=& \frac{Y(z)}{X(z)}
\end{eqnarray*}$$</p>

$H(z)$ を離散時間システムの伝達関数という。

### 差分方程式
| 連続時間システム | 微分方程式 |
| 離散時間システム | 差分方程式 |

$$y(n) = \sum_{k = 0}^M a_k x(n-k) - \sum_{k=1} ^N b_k y(n-k)$$

現在の出力は、{現在の入力, 過去の M 個の入力, 過去の N 個の出力} の線型結合で決まることを表している

## 4. 離散時間システムの周波数応答
正弦波入力 $x(n) = e^{j \Omega n}$ に対する応答

システムは因果性とする

<p>$$
y(n) = \sum_{k = 0}^\infty h(k) e^{j \Omega (n-k)} = \left(\sum_{k = 0}^\infty h(k) e^{j \Omega k}\right) e^{j \Omega n} = H(\Omega) e^{j \Omega n} \\
H(\Omega) = \sum_{k = 0}^\infty h(k) e^{-j \Omega k}
$$</p>

$H(\Omega)$ は、連続時間系システムの周波数特性に対応する。一般に複素数。

大きさを **振幅特性** 、位相を **位相特性** 、両方合わせて **周波数特性** と呼ぶ。

<p>$$
H(\Omega) = R(\Omega) + j I(\Omega) = |H(\Omega)| e^{j \angle H(\Omega)} \\
|H(\Omega)| = \sqrt{R^2(\Omega) + I^2(\Omega)} \\
\angle H(\Omega) = \tan^{-1} \frac{I(\Omega)}{R(\Omega)}
$$</p>

----

<p>$$\begin{eqnarray*}

y(n) &=& x(n) + b y(n-1) \\

Y(z) &=& X(z) + b y(z) z^{-1} \\

\therefore H(z) = \frac1{1 - bz^{-1}} \\

&\quad (z = e^{j \Omega}) \\

H(z) &=& \frac1{1 ^ be^{-j\Omega}} = \frac1{1 - b\cos\Omega + jb\sin\Omega} \\

|H(\Omega)| &=& \frac1{\sqrt{(1 - b\cos\Omega)^2 + (b\sin\Omega)^2}} \\

\angle H(\Omega) &=& \tan^{-1} \frac{-b\sin\Omega}{1-b\cos\Omega}

\end{eqnarray*}$$</p>

----

因果性システムを考え、簡単な次の差分方程式を考える

<p>$$\begin{eqnarray*}
y(n) &=& x(n) + by(n-1) \\
Y(z) &=& X(z) + bY(z) z^{-1} \\
\therefore H(z) = \frac1{1 - bz^{-1}}
\end{eqnarray*}$$</p>

----

## 第8回レポート
### 演習1
システムの差分方程式を表す式で、 $M=N=2$ の時伝達関数を求めよ。

----
システムの差分方程式は

$$y(n) = \sum_{k = 0}^M a_k x(n-k) - \sum_{k=1} ^N b_k y(n-k)$$

と表せるので、この式に $M=N=2$ を代入して展開すると

$$y(n) = a_0 x(n) + a_1 x(n-1) + a_2 x(n-2) - \\{b_1 y(n-1) + b_2 y(n-2)\\}$$

両辺を z 変換して

<p>$$\begin{eqnarray*}
Y(z) &=& (a_0 + a_1 z^{-1} + a_2 z^{-2}) X(z) - (b_1 z^{-1} + b_2 z^{-2}) Y(z) \\
(1 + b_1 z^{-1} + b_2 z^{-2}) Y(z) &=& (a_0 + a_1 z^{-1} + a_2 z^{-2}) X(z) \\
H(z) = \frac{Y(z)}{X(z)} &=& \frac{a_1 z^{-1} + a_2 z^{-2}}{1 + b_1 z^{-1} + b_2 z^{-2}}
\end{eqnarray*}$$</p>

### 演習2
次の式で表されるシステムの、伝達関数 $H(z)$ とインパルス応答 $h(n)$ を求めよ。
$$y(n) - y(n-1) + 0.24y(n-2) = x(n)$$

----
z 変換して、

$$(1 - z^{-1} + 0.24z^{-2}) Y(z) = X(z)$$

伝達関数は

<p>$$\begin{eqnarray*}
H(z) &=& \frac{Y(z)}{X(z)} = \frac1{1 - z^{-1} + 0.24z^{-2}} \\
&=& \frac3{1 - 0.6z^{-1}} - \frac2{1 - 0.4z^{-1}}
\end{eqnarray*}$$</p>

逆 z 変換して、

$$h(n) = 3 \cdot {0.6}^n \cdot u(t) - 2 \cdot {0.4}^n \cdot u(t)$$

### 演習3
差分方程式が次式で与えられるシステムのインパルス応答および振幅応答と位相応答を求めよ。
$$y(n) = x(n) + x(n-1)$$

----
z 変換して伝達関数を求める。

<p>$$\begin{eqnarray*}
Y(z) &=& (1 + z^{-1}) X(z) \\
H(z) &=& 1 + z^{-1}
\end{eqnarray*}$$</p>

伝達関数を逆 z 変換してインパルス応答を求める。

$$ h(n) = \delta(n) + \delta(n-1) $$

また、 $H(z)$ に $z = e^{j\Omega}$ を代入して、

<p>$$\begin{eqnarray*}
H(z) &=& 1 + e^{-j\Omega} = 1 + \cos\Omega - j\sin\Omega \\

|H(\Omega)| &=& \sqrt{(1+\cos\Omega)^2+\sin^2\Omega} \\
&=& \sqrt{2+2\cos\Omega} \\

\angle H(\Omega) &=& \tan^{-1}\frac{-\sin\Omega}{1+\cos\Omega}
\end{eqnarray*}$$</p>
