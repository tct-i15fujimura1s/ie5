---
mathjax: true
---

{% include mathjax.html %}

# z変換
ラプラス変換の離散時間版

```
連続時間
信号 → フーリエ変換 → 周波数領域
システム → ラプラス変換 → s領域

離散時間
信号 → 離散フーリエ変換(DFT), FFT → 周波数領域
システム → z変換 → z領域
```

因果性のサンプル値信号 $x_s(t) = x(t) \delta_T(t) = \sum_{n=0}^\infty x(t) \delta(t + nT)$

$x_s(t)$ をラプラス変換したものを $X_s(s)$ とすると、定義式より

<div>
  \[X_s(s) = \int_0^\infty x_s(t) e^{-st} dt = \int_0^\infty \{ x(t) \delta(t) + x(t) \delta(t+T) + \cdots \} dt\]
</div>

インパルス関数の性質より

<div>
  \[X_s(s) = x(0) + x(T) e^{-Ts} + x(2T) e^{-2Ts} + \cdots = \sum_{n=0}^\infty x(nT) e^{-nTs}\]
</div>

ここで、複素変数 $z=e^s$ と定義する。また、 $X(z) = X_s(s)$ とすると、片側z変換の式になる。

<div>
  \[X(z) = \sum_{n=0}^\infty x(n) z^{-n}\]
</div>


非因果性の場合は、両側z変換。

<div>
  \[X(z) = \sum_{n=-\infty}^\infty x(n) z^{-n}\]
</div>

## 信号の遅れ

単位インパルス数列について考える。

$$\delta(n) = \left\{\begin{eqnarray*}
  1 && (n = 0) \\
  0 && ({\text{otherwise})
\end{eqnarray*}\right~$$

$x(n) = \delta(n)$ とした時

$$X(z) \\ = \sum_{n=0}^\infty \delta(n) z^{-n} \\ = \delta(0) z^0 = 1$$

$x(n) = \delta(n-1)$ とした時

$$X(z) = \delta(1) z^{-1} = z^{-1}$$

信号が1遅れている ($\delta(n) \to \delta(n-1)$) ことを、$z^{-1}$で表せる

$x(n) = \delta(n-d)$ とした時

$$X(z) = \delta(d) z^{-d} = z^{-d}$$

__信号がd遅れていることを $z^{-d}$で表せる__

##

単位ステップ数列について考える

$$\u(n) = \left\{\begin{eqnarray*}
  1 && (n \le 0 \vee n\in\mathbb N) \\
  0 && (\text{otherwise})
\end{eqnarray*}\right~$$

$$X(z) = \sum_{n=0}^\infty u(n) z^{-n} \\ = 1 + z^{-1} + z^{-2} + \cdots = \frac1{1 - z^{-1}}$$

等比級数の公式より、 $\left|z^{-1}\right| < 1$ で収束 (収束領域は単位円の外側)

##

## z変換の性質
1. 線型性
  * $y(n) = c_1 x_1(n) + c_2 x_2(n)$
  * $Y(z) = c_1 X_1(z) + c_2 X_2(z)$
2. 推移定理
  * $y(n) = x(n-k)$
  * $Y(z) = z^{-k} X(z)$
3. 畳み込み定理
  * $y(n) = x_1(n) * x_2(n)$
  * $Y(z) = X_1(z) X_2(z)$

## 逆z変換

$X(z)$ から $x(n)$ を求める。

式は $x(n) = \frac1{2\pi j} \oint_C X(z) z^{n-1} dz$ (C: 収束領域内での原点を内部に含む反時計方向の円周路) だが、通常は使わない。

留数定理、冪級数法、部分分数展開法を使う。

### 留数定理

$X(z) = \frac{z}{3z^2 - 4z + 1}$ の逆z変換

<div>
$$\begin{eqnarray*}
X(z) &=& \frac{z}{(z-1)(3z-1)} \\
X(z) z^{n-1} &=& \frac{z^n}{(z-1)(3z-1)} = \frac{z^n}{3(z-1)(z-\frac13)} \\
Res\left[X(z)z^{n-1}, z=\frac13\right] = \left~ \frac{z^n}{3(z-1)}\right|_{z=1} = \frac12 \\
Res\left[X(z)z^{n-1}, z=\frac13\right] = \left~ \frac{z^n}{3(z-1)}\right|_{z=\frac13} = - \frac12 3^{-n} \\
x(n) &=& \frac12 (1 - 3^{-n})
\end{eqnarray*}$$
</div>
