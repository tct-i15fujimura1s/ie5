# ネットワークアーキテクチャ 12/25
* Ethernet (物理層)

## ケーブルの種類と規格
* 同軸ケーブル
* ツイステッドペアケーブル
  * UTP (Unshielded Twisted Pair)
  * STP (Shielded Twisted Pair)
* 光ファイバ

### 同軸ケーブル
* 伝送距離が割と長い

### ツイステッドペアケーブル
単なる平行線よりノイズの影響を受けにくい

#### UTP
* CAT3, CAT5, CAT5E, CAT6, ...
  * 建物に敷設するケーブルはできるだけ良いものを選ぶべし
    * 置換えが大変なので・・・
* エイリアンクロストーク: ケーブルを隣り合わせると、互いに影響を及ぼす
  * 電話などで、他人の声が聞こえるような場合

#### STP
* CAT6
* エイリアンクロストークの防止のため、シールドを挿入

### 光ファイバ
* 全体的にUTPより高価
  * UTPで間に合うならUTPでいい
* 接続も難しい
* 種類
  * マルチモード
  * シングルモード

#### マルチモード
* 同じ信号の光に光路差による位相の差が生じて、干渉で減衰する

#### シングルモード
* マルチモードより高価、細い
* 光の経路が一つ

#### 光ファイバを使う場合
* 100m超の長距離伝送
* UTPで規格化されない高速通信
* 建物間の電位差が大きい
* 落雷などの危険性がある
* ノイズが非常に大きな環境

## 機器間の接続（コネクタ）
* RJ-45 (UTP)
* N, BNC (同軸ケーブル)
* SC, LC, MT-RJ (光ケーブル)
  * 現在主流はSC(太い)とLC(細い)
  * すごい高価（5~10万）

### PCなど
* UTPとRJ-45

### 大規模
* パッチパネルとL2SW
* 配線はスター型が主流

### UTPの注意点
* 適切な配線
  * 正しいカテゴリー、ペア数
  * 適切な距離
  * 適切な接続
* 適切な距離
  * 規格上は100mまでだができれば、マージンを撮って80m位に抑える
  * コネクタ回り（撚りが弱い）の減衰、外乱を考慮する
  * 距離が長くなるほど減衰する（電気抵抗）
* 適切なペア
  * 正しいペアならノイズをキャンセルできる
    * 磁界のノイズ・・・打ち消す
    * 電界のノイズ・・・全体的に影響されても差動入力なので無視できる

### 無線LAN
* CSMA/CA

### 電力線ネットワーク (PLC)
* コンセントでネットワーク