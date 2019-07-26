---
mathjax: true
---

{% include mathjax.html %}

## 最小自乗推定の性質
* $E(a) = \alpha, E(b) = \beta$ (不偏性)
* $V(a) = V(a - \alpha) = \frac{\sigma^2 \sum x_i^2}{n \sum (x_i-\bar x)^2} $ (一致性)
* $V(b) = V(b - \beta) = \frac{\sigma^2}{\sum (x_i - \bar x)^2}$ (一致性)

### 回帰残差: 説明変数で説明されずに残った分
* $ \hat y _ i = y _ i - a - b x _ i $

#### 回帰残差の平均と不偏分散
* 平均 : 0
* 分散 : $\hat \sigma ^ 2 = s^2 = \frac1{n-2} \sum \hat e_i^2$
  * 分散は不偏推定量 : $E(\hat \sigma^2) = \sigma^2$
* 標準誤差 : $s = \root{\hat \sigma^2}$
