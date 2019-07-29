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

### 問題: 誤差分散の不偏推定量と標準誤差

| 番号 | X | Y |
| --- | --- | --- |
| 1 | 2.5 | 400 |
| 2 | 2.7 | 600 |
| 3 | 2.7 | 500 |
| 4 | 2.5 | 300 |
| 5 | 2.3 | 400 |
| 6 | 2.3 | 200 |

```JavaScript
data = [
[2.5, 400],
[2.7, 600],
[2.7, 500],
[2.5, 300],
[2.3, 400],
[2.3, 200]
];

// y=a+bx
Ex = data.reduce((e,[x,y])=>e+x, 0)/data.length;
Ey = data.reduce((e,[x,y])=>e+y, 0)/data.length;
b1 = data.reduce((e,[x,y])=>e+(x-Ex)*(y-Ey),0)
b2 = data.reduce((e,[x,y])=>e+(x-Ex)**2,0)
b = b1/b2;
a = Ey-b*Ex;
console.log("y = %f + %f x", a, b);
hatYs = data.map(([x, y]) => a + b * x);
hatEs = data.map(([x, y]) => y - (a + b * x));
hatEV = 1/(hatEs.length-2) * hatEs.reduce((s, e) => s + e**2, 0);
hatEE = 1/(hatEs.length) * hatEs.reduce((s, e) => s + e);
```

## 決定係数
* 全変動: $\bar y - y_i$
  * 実際のデータとデータ全体の平均の差
* 残差変動: $\bar y - \hat y_i$
  * 実際のデータと推定された回帰式から得られた予測値との差
  * 回帰によって説明されない被説明変数の変動
* **回帰変動**: $\hat y_i - y_i$
  * 推定された回帰式から得られた予測式とデータ全体の平均値の差
  * 回帰によって説明される被説明変数の変動

$$ \text{全変動} = \text{残差変動} + \text{回帰変動} $$

* 決定係数 $r^2$: [0, 1]
  * $r^2 = \frac{\rm 回帰変動}{\rm 全変動} = \frac{\sum(\hat y_i - \bar y)^2}{\sum(y_i - \bar y)^2} = 1 - \frac{\sum(y_i - \hat y_i)^2}{\sum(y_i - \bar y)^2}$

### 問題: 上のデータにおける決定係数を求めよ
```JavaScript
data = [
[2.5, 400],
[2.7, 600],
[2.7, 500],
[2.5, 300],
[2.3, 400],
[2.3, 200]
];

xs = data.map(([x, y]) => x);
ys = data.map(([x, y]) => y);

mean = xs => xs.reduce((s, x) => s + x) / xs.length;

Ex = mean(xs);
Ey = mean(ys);
b1 = data.reduce((e,[x,y])=>e+(x-Ex)*(y-Ey),0)
b2 = data.reduce((e,[x,y])=>e+(x-Ex)**2,0)
b = b1/b2;
a = Ey-b*Ex;

console.log("y = %f + %f x", a, b);

hatYs = data.map(([x, y]) => a + b * x);

全変動 = ys.reduce((s, y) => s + (Ey - y)**2, 0);
回帰変動 = hatYs.reduce((s, hatY) => s + (hatY - Ey)**2, 0);
決定係数 = 回帰変動 / 全変動;
```

$r^2 = 0.625$
