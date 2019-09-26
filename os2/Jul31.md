# ZFS
## まとめ
* 大きな主記憶、高速なCPU
* COWを用い既存のブロックを上書きしない
* COWのおかげでシステムのクラッシュでも壊れない
*

# UFS
* UNIX File System
* 多くのファイルシステムがUFSに準拠している
  * NTFS on Windows
  * HFS+, APFS on macOS
  * ext3, ext4 on Linux
  * ZFS

# 練習問題
### 用語の説明
* COW (Copy on Write)
* メタデータ
* チェックサム
* スナップショット
*
* Uberblock
* ブロックポインタ
* Dnode
* MOS

### 計算
* トランザクショングループ番号が64bit、毎秒100トランザクショングループを処理したとき、オーバーフローまで約何年か
  * 64bit -> 2^64 ~ 1.8E+19
  * 1.8E+19 / (100 * 60[s] * 60[min] * 24[h] * 365.25[days]) ~ 5.9E+9 = 58億年
* ファイルを表現するdnodeが間接レベル2のとき、最大のファイルサイズは何バイトになるか計算しなさい。
* ブロックにリンクカウントを設け、スナップショットからの参照数を管理することで、ブロックの解放を管理するアイデアの利点と問題点を挙げなさい

### 調べる
* ZFSで使用できるチェックサム計算アルゴリズムについて調べなさい


* MBRより新しい仕組みも出てきた:

# 試験範囲
* ボリューム内部の構造
  * MBR
* FAT
  * BPB (BIOS Parameter Block)
  * ディレクトリエントリ
  * FAT (File Allocation Table)
  * ディレクトリファイル (ただし、ルートディレクトリ"/"だけは特別扱い)
* UFS
  * i-node
    * 間接
  * ディレクトリファイル
  * パス名とi-nodeの対応付け (/etc/passwdを解析)