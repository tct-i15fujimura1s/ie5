演習 3-*
deadline: 9/30 (Mon)


評価 = 0.3(中間 + 期末) + 0.1課題 + 0.3演習


RE -> NFA -> DFA -> 最簡DFA/プログラム


# コード生成
省略
教科書

# 最適化
* Peepehole最適化 ・・・ マシン依存の局所的最適化
  - 高速な命令への置換
  - 共通項（冗長な演算の削除）
* 論理式の最適化
* 不変計算のループ外への移動

## Peepehole最適化
### 高速な命令への置換 (例)

<div class="row">
<pre class="col-6">
PUSHA 1
PUSHA 1
MULA
</pre>
<pre class="col-6">
PUSHA 1
DUPA 1
MULA
</pre>
</div>

### 冗長なコードの削除
<div class="row">
<pre class="col-6">
a = b + c * d
e = b + c * d
</pre>
<pre class="col-6">
a = b + c * d
a = e
</pre>
</div>

## 論理式の最適化
<div class="row">
<pre class="col-6">
if(a || b || c) {
  P
} else {
  Q
}
</pre>
<pre class="col-6">
if(!a) {
  if(!b) {
    if(!c) goto q;
    P;
    goto end;
  }
}
q: Q
end:
</pre>
</div>


# 期末試験
* CFG/BNF/構文図 ・・・ 配布資料
* 決定性変換 ・・・ 課題4,5
* LL(1)文法の判定 (First, Follow, Director) ・・・ 課題6,7
* 簡単のtop-downの構文解析プログラム
