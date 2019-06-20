# 代表的な画像伝達方式
1. テレビジョン（アナログ方式）←PAL, SECAM, NTSC
2. JPEG
3. H.261
4. MPEG1, MPEG2, MPEG4
5. ハイビジョンとMUSE
6. DVB
7. GⅢ

MPEG1にはテレビ方式に合わせて2種類の画像フォーマットがある

| | | SIF525(NTSC用) | SIF625(PAL,SECAM用) |
| --- | --- | --- | --- |
| 画像サイズ | 輝度信号 Y | 360×240 | 360×288 |
| | 色信号 C | 180×240 | 180×144 |
| フレーム周波数［Hz］ | | 29.97 | 25.00 |


## MPEG2
前提：伝送速度 5～30Mbps
DVDで採用されている。
放送、通信など幅広い応用を想定、MPEG1よりも高画質(HDまで)を目指した。

### MPEG1からの拡張
* 高精度な動き保障（半画素単位の動きベクトル検出など）
* 階層的画像の扱い（スケーラビリティなど）
* 異なる解像度への対応（色解像度の高い4:2:2プロファイルなど）
* インタレース走査への対応

種々のメディアで扱うために、種々のフォーマットが規定されている。

### MPEG2のプロファイルとレベル
<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:black;}
.tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:black;}
.tg .tg-baqh{text-align:center;vertical-align:top}
</style>
<table class="tg">
  <tr>
    <th class="tg-baqh" colspan="2" rowspan="2"></th>
    <th class="tg-baqh" colspan="6">プロファイル</th>
  </tr>
  <tr>
    <td class="tg-baqh">SP<br>シンプル<br>I.Pのみ</td>
    <td class="tg-baqh">MP<br>メイン</td>
    <td class="tg-baqh">SNP<br>SNRスケーラブル<br>画質階層化</td>
    <td class="tg-baqh">SSP<br>空間スケーラブル<br>階層的符号化</td>
    <td class="tg-baqh">HP<br>ハイ</td>
    <td class="tg-baqh">4:2:2P<br>4:2:2</td>
  </tr>
  <tr>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">HL<br>1920×1080×30<br>1920×1152×25<br></td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">MP@HL</td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">HP@HL</td>
    <td class="tg-baqh"></td>
  </tr>
  <tr>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">H 1440<br>1440×1080×30<br>1440×1152×25<br></td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">MP@H 1440</td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">SSP@H 1440</td>
    <td class="tg-baqh">HP@H 1440</td>
    <td class="tg-baqh"></td>
  </tr>
  <tr>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">ML<br>720×480×30<br>720×576×25</td>
    <td class="tg-baqh">SP@ML</td>
    <td class="tg-baqh">MP@ML</td>
    <td class="tg-baqh">SNP@ML</td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">HP@ML</td>
    <td class="tg-baqh">4:2:2P@ML</td>
  </tr>
  <tr>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">LL<br>952×288×30</td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh">MP@LL</td>
    <td class="tg-baqh">SNP@LL</td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh"></td>
    <td class="tg-baqh"></td>
  </tr>
</table>

## MPEG4
想定：伝送速度 ≦64Kbps
高画質な動画像、超低レート

## ハイビジョンとMUSE

### ハイビジョン
* 日本が世界に先駆けて開発したHDTV方式の1つ
* 走査線数1125本、フィールド周波数60Hz、2:1インターレス走査のテレビ方式

### MUSE (Multiple sub-nyquist sampling encoding)
* ハイビジョンの伝送方式の1つ
* 日本のBS放送で使用されていた
* オフセット標本化を基本としたサンプル値伝送方式（ハイビジョンの信号帯域をNTSCの信号帯域に圧縮するため）

#### オフセット標本化
x点を捨てて、o点のみを残す
<pre>
  --o--x--o--x--
  --x--o--x--o--
  --o--x--o--x--
  --x--o--x--o--
</pre>

#### サンプル値伝送
標本点を並び替えてサンプル値として伝送

* 圧縮による画質の劣化を抑えるために、次のようなディジタル処理を使用している
  * 斜めの解像度を落とす
  * 静止領域と動領域を別で処理
  * 動きベクトルを検出しボケを防ぐ

## DVB (Digital Video Broadcasting)
ヨーロッパの標準テレビ放送用のディジタル伝送方式
画像圧縮: MPEG2 (MP@ML)
誤り訂正: リードソロモン符号と畳込み符号
変調:
　衛星放送: QPSK
　ケーブルテレビ: QAM (64値など)
　地上放送　: OFDM

日本のCS(通信衛星)ディジタル放送も、若干の違いはあるが、DVB方式に準じている

## GⅢ
FAXの伝送方式
2値の画像信号をランレングス＋ハフマン符号化で圧縮、8PSKかQAMで変調して伝送
