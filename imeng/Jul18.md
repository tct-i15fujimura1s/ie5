## JPEG
* DCT 方式
* Spacial 方式

### DCT方式
```
imdct(im: int[][]) =
  blocks: int[8][8][] := imsplit(im, 8, 8)
  dctcoeffs: float[8][8][] := blocks.map dct2d _
  return dctcoeffs.map quantize _
```

## MPEG 符号化
* MPEG-1
* MPEG-2
* MPEG-3

```
I B B P B B P B B P B B I
```

* I ピクチャ: それだけで成り立つ
* P ピクチャ: 前の I ピクチャを参照する
* B ピクチャ: 前後の I, P ピクチャを参照する

### 奇数フレームと偶数フレームがあるインタレースな動画
1. 奇数フレームだけ、偶数フレームだけとそれぞれ符号化する方法
2. 奇数フレームと偶数フレームを合わせて1つのフレームにする方法

### 階層的符号化
粗く→細かく
