入力1: 文法規則 `S → aBd` (_文形式_: まだ非終端記号が含まれている)

出力: 構文木

入力: `abcd` (_文_: 全て終端記号; ソースプログラム)

### 構文解析
1. _文_ の先頭が`a`か?
2. _文_ の次の文字列が`B`の形か?
3. _文_ の最後が`d`か?

これをプログラムの形で表すと

```C
main() {
  getSym();   // 1記号先読み
  S();        // 開始記号の解析モジュールを呼び出し
}

S() {
  check_a();
  getSym();
  B();        // この中でgetSym()は呼ばれている
  check_d();
}
```

### 課題1: backtrack がおこる
`B → b` | `B → bc`
* 対策: くくりだし
  `B -> b(ε|c)` どちらを選ぶか先延ばし
### 課題2
* 例: `E → E + T`
下向きの構文解析法は左再帰性のある文法に適用できない
* 対策: 文法を修正する
  * `A → Aα|β` ⇒ <code>A → β{α}</code>


<pre>
〈S〉 → <u>if</u> 〈P〉 <u>then</u> 〈S〉
〈S〉 → <u>if</u> 〈P〉 <u>then</u> 〈S〉 <u>else</u> 〈S〉
</pre>
<div>↓</div>
<pre>
〈S〉 → <u>if</u> 〈P〉 <u>then</u> 〈S〉<strong>〈S’〉</strong>
〈S’〉 → <u>else</u> 〈S〉 |　ε
</pre>

<style>u { text-decoration: underline }</style>
