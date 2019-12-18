{% include mathjax.html %}
# システム数理工学 12/17

## 凸集合 convex set
    $n$次元の実数空間$R^n$の部分集合$S$($S\\subeq R^n$)は、任意の$\\boldsymbol{x},\\boldsymbol{y}\\in S$および任意の$0\\le\\lambda\\le1$に対して、$$\\lambda \\boldsymbol{x}+(1-\\lambda)\\boldsymbol{y}\\in S$$が成り立つとき、凸集合である、と呼ばれる。
* $\\boldsymbol{x},\\boldsymbol{y}$は$n$次元のベクトル
* 凸集合上の任意の２点間を結ぶ線分上の点はすべて凸集合に含まれる
* $\\text{Sが凸集合}\\equiv \\forall\\boldsymbol{x},\\boldsymbol{y} \\in S, \\forall \\lambda \\in [0,1], \\lambda \\boldsymbol{x} + (1-\\lambda) \\boldsymbol{y} \\in S$

## 凸包 convex hull
    $n$次元の実数空間$R^n$の部分集合$S$($S\\subeq R^n$)に対して、$S$を含む全ての凸集合の共通部分を凸包と呼ぶ。
    凸包を記号$Co(S)$で表す。

    集合のくぼみを埋めて均してくぼみをなくしたもの。

    $$\text{Sが凸集合}\\iff Co(S)=S$$

## 凸関数 convex function
    $S\\subeq R^n$を凸集合とする。
    $S$上で定義された実数値関数$f(\\boldsymbol{x})$は、
    任意の$\\boldsymbol{x},\\boldsymbol{y}\\in S$および任意の$0\\le\\lambda\\le1$に対して、$$f(\\lambda \\boldsymbol{x}+(1-\\lambda)\\boldsymbol{y})\\le(\\lambda f(\\boldsymbol{x})+(1-\\lambda)f(\\boldsymbol{y})$$が成り立つならば、凸関数と呼ばれる。（下に凸）


    また、$\\le$でなく$\\lt$のとき、狭義 (strictly) 凸関数とよばれる

## 凹関数 concave function
    凸関数の$\\le$を$\\ge$に変えたバージョン。狭義の場合は$\\gt$（上に凸）

    $$f(x)\\text{が凸関数}\\iff-f(x)\\text{が凹関数}$$

## 最適化における凸関数
* 定理9.1
  1. $S \\subeq R^n$を凸集合とするとき、制約のない問題$\\min_{}$
