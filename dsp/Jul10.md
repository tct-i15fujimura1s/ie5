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

## 

$x(n) = \delta(n)$ とした時

$$X(z) \\ = \sum_{n=0}^\infty \delta(n) z^{-n} \\ = \delta(0) z^0 = 1$$

$x(n) = \delta(n-1)$ とした時

$$X(z) = \delta(1) z^{-1} = z^{-1}$$

信号が1遅れている ($\delta(n) \to \delta(n-1)$) ことを、$z^{-1}$で表せる

$x(n) = \delta(n-d)$ とした時

$$X(z) = \delta(d) z^{-d} = z^{-d}$$

__信号がd遅れていることを $z^{-d}$で表せる__
