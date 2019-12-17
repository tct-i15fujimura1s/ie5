{% include mathjax.html %}
# 画像工学 12/17
画像のフーリエ変換

## 離散フーリエ変換
* DFT $g(n) = \\sum_{k=0}^{N-1} G(k) e^{\frac{j2\\pi n k}{N}}$
* $G(k) = F_n[g(n)] = \frac{1}{N} g(n) e^{-\frac{j2\pi nk}{N}}

### 2次元
* $G(k,l) = F_m[F_n[g(m,n)]]$


* ftp://sugimura3.tu.tokuyama.ac.jp/pub/2D_FFT/FFT-UTF8-LF/
* ftp://sugimura3.tu.tokuyama.ac.jp/pub/2D_FFT/FFT1core-UTF8-LF/


## 課題 〆切 1/28
* cup.pgm
* source.pgm
