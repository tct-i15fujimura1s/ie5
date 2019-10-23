# オブジェクト指向プログラミング 演習3

`CurrentColor`クラスを設計し、クラス図とオブジェクト図をastahというツールを使って描く。

### `CurrentColor`クラスの概要
* 色の三原色の成分ごとに、0-255の整数の組み合わせで現在の色を記憶している
* 色成分の強さは0→128→255→0と変わる
* 受信するメッセージは次の3つ
  * Color/void changeRed()
  * Color/void changeGreen()
  * Color/void changeBlue()

### `CurrentColor`クラスの設計
astahを使い、クラス図を描く。`JButton`、`JPanel`（名前だけでもよい）もクラス図に書き加えておく。

### システムのオブジェクト図を作成
astahにクラス図 [^1] を追加、そこにオブジェクト図を描く。オブジェクトは「インスタンス仕様」ボタンでできる。`CurrentColor`、`JButton`、`JPanel`のインスタンスを配置し関連を書き加える。

### システム全体のクラス図を作成
クラス図に関連を書き加える。オブジェクト図を参考に多重度も書き加える。


## 設計
```Java
class CurrentColor {
  private int red;
  private int green;
  private int blue;

  public Color changeRed();
  public Color changeGreen();
  public Color changeBlue();
}

class JButton {
  public void addActionListener(ActionListener l);
}

class JPanel {
  private Color color;

  public void setBackground(Color c);
}
```

[1]: astahではオブジェクト図もクラス図に描く
