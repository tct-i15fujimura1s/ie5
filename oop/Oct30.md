# オブジェクト指向プログラミング 10/30

## 演習3の解答

### 案1
* JButtonがCurrentColorとJPanel1の両方にメッセージを送る設計

### 案2
* JButtonがCurrentColorへ、CurrentColorがJPanelへメッセージを送る

### 案3
* 案1に加え
* CurrentColorは配列 `vals: int[] = {0, 128, 255}` を持ち、`red, green, blue` は0〜2とする
