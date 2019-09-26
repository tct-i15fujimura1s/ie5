# 情報理論 学習シートのまとめ
## 第1回

* 情報源符号化 (圧縮)・・・シャノンの第一基本定理
* 通信路符号化 (冗長化)・・・シャノンの第二基本定理

| --- | アナログ情報 | デジタル情報 |
| 情報の内容 | 波形そのもの | 0か1か |
| クロック | ○不要 | ×必要 |
| 雑音に | ×弱い | 〇強い |
| 中継時の雑音 | ×相加する | 〇相加しない |
| 所要周波数幅帯域 | 〇狭くてよい | ×広い帯域が必要 |
| 信号処理 | ×困難 (A-D変換が必要) | 〇容易 |

* 2元符号 (0/1)
* 情報量の単位: ビット
* 2元符号をnビットで表せる記号: 2^n種類
  * 6ビット: 64種類

| --- | 固定長符号 | 可変長符号 |
| 符号の長さ | すべて同じ | 符号により変化 |
| 区切り符号 | 〇不要 | ×必要 |
| まとめた扱い | 〇容易 | ×困難 |
| 高能率符号化 | ×単純には不可 | 〇可能 |
| 使用例 | JIS, ASCII | モールス信号 |

* ビット誤り率 (BER)
* 情報の伝送速度 (bps)

* 周波数帯域: 高速伝送には広い帯域が必要
* 通信路容量
  * 1秒間に伝送できる最大の情報量
  * 通信路容量より低い伝送速度なら誤りをいくらでも小さくできる符号化が存在する

## 第2回
* 自己情報量 I(p) [bit]: ある事象の起きる確率がpとするとき、それが起きたという知らせの情報量はI(p)
  * I(p) = -log_2(p)
* 平均情報量 (エントロピー) H [bit/symbol]: すべての事象の自己情報量の平均
  * p_1 + … + p_N = 1のとき
  * H = -Σ_{i=1}^N p_i log_2 p_i [bit/symbol]

* エントロピーが最大になる条件: すべての事象が等確率・・・どれが起きるか一番予測しにくい
  * 最大エントロピー H_max = log_2(1/N) [bit/symbol]

* 相対エントロピー h = H / H_max
* 冗長度 r = 1 - h

## 第3回
* 2元符号の場合のエントロピー関数
  * 記号1が確率p, 記号0が確率qで発生するとき (p+q=1)
  * H_f(p) = -p log_2p - (1-p) log_2 (1-p) [bit/symbol]
* ラグランジュの未定乗数法: 拘束条件がある関数の極値を求める
  1. 変数λを導入 (ラグランジュ乗数)；変数λを導入した関数：ラグランジュ関数
  2. 以下の連立方程式の解が極値
    * ∂L(x,y,λ)/∂x = ∂L(x,y,λ)/∂y = ∂L(x,y,λ)/∂λ = 0
  * 例：制約条件x^2+y^2-4 = 0が与えられるとき、x+2y=0の極値x,yを求めよ
    1. ラグランジュ関数の設定
      * L(x,y,λ) = x+2y-λ(x^2+y^2-4)
    2. 連立方程式
      * ∂L(x,y,λ)/∂x = 1-2λx = 0
      * ∂L(x,y,λ)/∂y = 2-2λy = 0
      * ∂L(x,y,λ)/∂λ = -x^2-y^2+4 = 0
      * ∴解は(x,y)=(±2/√5, ±4/√5)

## 第4回
* 情報源符号化：冗長度を利用して平均的に符号の長さを短縮。固定長と可変長がある

* 通信や記録に用いる符号の条件:
  * 一意に復号可能
  * 瞬時符号
  * 符号長ができるだけ短い

| 一意復号性 | 〇 | 〇 | 〇 | 〇 | × |
| 瞬時性 | 〇 | 〇 | 〇 | × | × |
| 情報源記号 | C1 | C2 | C3 | C4 | C5 |
| A | 00 | 0 | 0 | 0 | 0 |
| B | 01 | 10 | 10 | 01 | 01 |
| C | 10 | 110 | 110 | 011 | 10 |
| D | 11 | 1110 | 111 | 111 | 11 |

* 瞬時符号の必要十分条件（以下の条件はどれも同じ意味）
  * すべての符号が葉に割り当てられる
  * 接頭語条件: どの符号語も他の符号語の接頭語になっていない

* クラフトの不等式: N種類の記号があり、それぞれの符号長をL_iビットとするとき
  * 2^{-L_1} + … + 2^{-L_N} ≦ 1
  * この式は瞬時符号なら必ず成り立つが、逆はそうともいえない

* 平均符号長 L = p_1 L_1 + … + p_N L_N [bit/symbol]
* 符号化の効率 e = H/L (H:エントロピー, L:平均符号長)
  * 平均符号長がエントロピーに近くなるほど効率がよくなる

* コンパクト符号 (最短符号): 一意かつ瞬時に復号可能ななかでも最も能率の高い符号
* 平均符号長の限界定理: H≦L≦H+ε
  * 平均符号長はエントロピーよりも小さくできない
  * 逆に、拡大情報源のように工夫すればエントロピーの限界までいくらでも近づけられる

* ハフマンの符号化法はネットで調べてください

* 拡大情報源: 符号をm個ずつまとめる
  * 例、1次情報源{A, B, C, D}→2次拡大情報源{AA, AB, AC, AD, BA, BB, …, DD}
  * P(A)=0.6、P(B)=0.25→P(AB)＝0.6×0.25
  * m個の記号あたりのエントロピーはm倍になる
  * 1記号あたりに換算すると元の情報源と同じ
  * 情報源の拡大次数を大きくすると効率が100%に近づく


## 第7回

| --- | 情報の損失 | 圧縮率 | 実時間性 | 誤り制御 | 対象 |
| 可逆圧縮 | なし | 低い | 遅延を許容 | 誤り検出・再送要求 | テキストやデータ |
| 非可逆圧縮 | あり | 高い | リアルタイム | 受信側で誤り訂正 | 画像や音声 |

* MH符号化
  * 長さ63まで: Terminating符号
  * 64以上: Terminating符号＋Make Up符号

* テキストのデータ圧縮
  * ハフマン符号化: 発生確率を求めてから符号化するので全文走査が2回必要という欠点がある
  * ユニバーサル符号化: 記号の発生確率を求めずに符号化を始める
    * LZ符号, スライド辞書(LZ77), 動的辞書(LZ78)など

* スライド辞書法 ※[参照辞書部｜符号化部]と表記
  1. 初期状態では、参照辞書部の記号をそのまま出力 [ABCDE｜CDX]YABXYABC → ABCDE
  2. 符号化部と同じ文字列が参照辞書部に存在(3文字前から2文字分) [ABCDE｜CDX]YABXYABC → (3,2) X
  3. 検索が終わったら次の部分にスライド ABC[DECDX｜YAB]XYABC → YAB
  4. 入力がなくなるまでスライドと検索を繰り返す ABCDEC[DXYAB｜XYA]BC → (4,3)
  * 最終出力: ABCDE (3,2) XYAB (4,3) (4,1) C

* 動的辞書法: 図が必要なので略

## 第8回
1. 誤りの発生と制御
2. 誤りの検出・訂正の原理
3. ハミング距離
4. 誤り検出・訂正能力
5. 伝送できる情報量
6. 通信路符号化定理

スライドのホチキスが外れて行方不明のため内容を略。消息いまだつかめず

## 第9回

* 符号語の間のハミング距離と誤り検出・訂正能力
  * それぞれの距離をd_H、誤りを起こしたビット数をtとすると
  * 誤り検出は d_H＞tのとき可能
  * 誤り訂正は d_H＞2tのとき可能

| ハミング距離 | 検出できるビット | 訂正できるビット |
| 1 | 0 | 0 |
| 2 | 1 | 0 |
| 3 | 2 | 1 |
| 4 | 3 | 1 |
| 5 | 4 | 2 |

* 通信路の確率モデル
  * 送信する記号の種類をn種類、受信される記号をm種類 (n≠m)とすると
  * 送信記号: X={x_1, …, x_n}, 受信記号: Y={y_1, …, y_m}
  * 通信路行列の各要素 p_ij = P(y_j｜x_i): 記号x_iを送信した場合に記号y_jが受信される確率
  * 受信記号y_jから送信記号x_iを推定
    * 記号y_jを受信したとき記号x_iが送信された確率: P(x_i｜y_j) (事後確率)
    * P(x_i): 事前確率
  * 結合確率 P(x_i,y_j) = P(x_i) P(y_j｜x_i) = P(y_j) P(x_i｜y_j)

* 2元対称通信路 (BSC: Binary Symmetric Channel)
  * 送信記号X={0,1}, 受信記号Y={0,1}
  * 誤りの確率が等しい (p_ij = p_ji)
  * 誤り確率をp、P(x=0)=r、P(x=1)=1-rとすると、P(x=0, y=0)=r×(1-p)

* 相互情報量 I(X; Y) = log_2{P(x_i｜y_j) / P(x_i)} [bit]
  * I(X; Y) = H(X) - H(X|Y) [bit/symbol]

* (n,k)符号: 全体がnビット、情報ビットがkビット (冗長ビットはn-kビット)
  * 符号化率 η = k/n
  * 冗長度 ρ = 1-η = (n-k)/n