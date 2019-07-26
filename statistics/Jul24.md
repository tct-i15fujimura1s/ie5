---
mathjax: true
---

{% include mathjax.html %}

# 回帰分析
データがあった時、これらのデータを一つの式で表したい

＊この授業では非線形回帰は扱わない

* 線形回帰と非線形回帰
  * 線形回帰: $y = \alpha + \beta x$
  * 非線形回帰の例： $y = \alpha \log x + \beta e^x$

* 単回帰分析と重回帰分析
  * 単回帰分析: 説明変数が１つ
  * 重回帰分析：説明変数が２つ以上、例：${\rm 消費} = f({\rm 収入, 財産, 性別, 家族の人数})$

* 母回帰方程式: 元のデータを表す方程式 $Y_i = \alpha + \beta X_i + \varepsilon_i$
  * 母集団の値のため、一般にはわからない
  * 誤差項を仮定する
    * 期待値は0: $E(\varepsilon_i) = 0$
    * 分散は一定: $E(\sigma^2) = 0$
    * 無相関
  * 期待値: $E(Y_i) = \alpha + \beta X_i + E(\varepsilon_i) = \alpha + \beta X_i$

* 標本回帰直線
  * 推定
  * $\hat{Y} = a + b X$
