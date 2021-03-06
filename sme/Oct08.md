---
mathjax: true
---

{% include mathjax.html %}

# システム数理工学 10/8

## 例題1.1
* 次の最適化問題を解け（ただし、$a$は定数である）
  * 目的関数 $max.\ -x_1 x_2,$
  * 制約 $s.t.\ x_1-x_2-a=0.$

  * 最大化問題なので、偏微分して0になるときを考える
    * $f(x_1, x_2) = -x_1 x_2$
    * $\frac\partial{\partial x_1} f(x_1, x_2) = -2x_1+a = 0 \to x_1 = \frac a 2$
    * $\frac a 2 - x_2 - a = 0 \to x_2 = -\frac a 2$

## 最適化問題 _(optimization problem)_
* 最大化問題 _(maximization problem)_
* 最小化問題 _(minimization problem)_

## 線形計画法
* $n$個の変数$x_1, x_2, \ldots x_n$はすべて **非負**
* $m$個の制約条件は変数$x_1, x_2, \ldots x_n$の **1次式の不等式** (制約不等式)
* 目的関数$f$は変数$x_1, x_2, \ldots x_n$の **1次関数**

### 線形計画法の標準形

<div>$$\begin{eqnarray*}
a_{11} x_1 + a_{12} x_2 + \cdots + a_{1n} x_n &\le& b_1 \\
a_{21} x_1 + a_{22} x_2 + \cdots + a_{2n} x_n &\le& b_1 \\
\vdots&\ &\\
a_{m1} x_1 + a_{m2} x_2 + \cdots + a_{mn} x_n &\le& b_m
\end{eqnarray*}$$</div>

$$ max.\quad f = c_1 x_1 + c_2 x_2 + \cdots + c_n x_n \ge 0, \\\ \ s.t. \quad x_1, x_2, \ldots x_n \ge 0. $$

または、ベクトルで表すと

$$\begin{eqnarray*}\boldsymbol{A x} &\le& \boldsymbol b \\ max. \quad &f = \boldsymbol{c}\cdot\boldsymbol{x} \ge 0, \\\ \ s.t. \quad &\boldsymbol{x} \ge \boldsymbol{0}. \end{eqnarray*}$$

## 例題2.1

* $m$種類の原料$M_1,\ldots,M_m$を用いて$n$種類の製品$A_1,\ldots,A_n$をつくる
* 製品$A_j$一つにつき原料$M_i$を$a_{ij}\ \text{[kg]}$必要とする
* 工場には原料$M_i$がそれぞれ$b_i\ \text{[kg]}$ある ($i = 1,\ldots,m$)
* 製品$A_j$はそれぞれ一つ$c_j\text{[円]}$で売れる ($j = 1,\ldots,n$)
* 売上高を最大にするように製品$A_j$を製造するための計画は？

### 定式化
* $x_j$: 生産する$A_j$の個数
* $x_j a_{ij} \le b_i$
* $M_i$は最大でも$b_i$[kg]まで
* $f = \sum_j x_j c_j$


<div>$$\begin{eqnarray*}
& \sum_j a_{ij} x_j \le b_i \\
max. & f = \sum_j x_j c_j \\
s.t. & x_j \ge 0
\end{eqnarray*}$$</div>

## 例題2.2
* 2台の機械$M_1,M_2$を使って2種類の容器$A,B$を生産する
* 容器$A$には機械$M_1$を2分、$M_2$を4分使う
* 容器$B$には機械$M_1$を8分、$M_2$を4分使う
* 容器$A$は29円、$B$は45円で売れる
* 1時間あたりの利益を最大にするにはどのように計画する？


* $x_1, x_2$: それぞれ1時間のうちに$A, B$を生産する個数
* 機械$M_1,M_2$を使用する時間は、それぞれ1時間=60分以内でないといけない

<div>$$\begin{eqnarray*}
2x_1+4x_2 &\le& 60 \\
8x_1+4x_2 &\le& 60
\end{eqnarray*}$$</div>

$$max. f = 29x_1 + 45x_2, \\\ s.t. x_1 \ge 0, x_2 \ge 0 $$

## 例題2.3
* $A, B$を用いて$M_1, M_2$をつくる
* $A, B$はそれぞれ$30\,000, 25\,000$の利益
* $A$は$M_1:M_2=1:1$の割合
* $B$は$M_1:M_2=1:3$の割合
* $M_1\le10, M_2\le15$
* 1日あたりの利益を最大にする計画は？


* $x_1, x_2$: それぞれ1日に$A,B$を生産する量
* $c_1, c_2$: それぞれ$30\,000, 25\,000$
<div>$$\begin{eqnarray*}
0.5x_1+0.5x_2 &\le& 10 \\
0.25x_1+0.75x_2 &\le& 15
\end{eqnarray*}$$</div>

$$max. f = 30\,000 x_1 + 25\,000 x_2, \\\ s.t. x_1 \ge 0, x_2 \ge 0 $$

## 注意
* $x_i$が整数でないといけない場合もあるが、整数問題を解くのは難しいので、実数として計算してから四捨五入する

## (実行)可能領域
* n次元空間内で不等式を満たす点の集合を可能領域or許容領域という
* 可能領域に属する点を可能解or許容解という
* 可能界の中で目的関数を最大にする点を最適解という

## 定理2.1
* 問題P0の可能領域は$n$次元空間内の凸多面体である
* 凸とは、図形の中の2点を結ぶ線上の点が、すべて図形の内部にあること

## 最適解が存在しない場合
* 可能領域が有界でない or
* 可能領域が空集合

## 等式の制約条件
* {2x + 8y <= 60, 4x + 4y <= 60} (x, y >= 0)
* 非負の変数 (スラック変数) を追加
* {2x + 8y + λ1 = 60, 4x + 4y + λ2 <= 60} (x, y, λ1, λ2 >= 0)
* もっと変数や式が多くても同じ

## 定理3.1
最適解($x_1^\*, \ldots, x_n^\*, λ_1^\*, \ldots, λ_m^\*$)のうちn個は0

このn個の変数を基底でないという

p. 28 まで教科書を読んでください
