{% include mathjax.html %}
* 文と文形式
* 構造図式
* LL(1)文法

# 文と形式
* 文形式: S（開始記号）から生成される記号列、非終端記号を含むかも $x\text{が文} \equiv x\in(V_N \cup V_T)^* \wedge S \overset*\Rightarrow x$
* 文: 終端記号のみの文形式 $x\text{が文形式} \equiv x\in V_T^* \wedge S \overset*\Rightarrow x$
* 言語 (文の集合) $L(G) = \{x | x \in V_T^* \wedge S \overset*\Rightarrow x\}$

# 構造図式
![構造図式の例](files/Jul2/structure-diagram.svg)

等価なBNF:
```
<A> ::= <B>c
<B> ::= <A>a|b
```

等価なプログラム:
```
main() =
  getSym()
  A()

A() =
  B()
  check 'c'
  getSym()

B() =
  if check 'b'
    getSym()
  else
    A()
    check 'a'
    getSym()
```

# LL(k) 文法
* CFGのサブセット
* k は先読みする記号の数
* 入力の先読みによって、バックトラックを排除

## 関数
* $First(\alpha) = \{a \in V_T | \alpha \overset*\Rightarrow \beta; \beta = abc\ldots\}$
* $Follow(\alpha) = \{z \in V_T | S \overset*\Rightarrow xy \alpha zw\ldots\}$
* $Director(A, \alpha) = V_T \cap (First(\alpha) \cup (\{a | a \overset*\Rightarrow \varepsilon\} \cap Follow(A)))

