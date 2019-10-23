# オブジェクト指向プログラミング 10/23

## Eclipse が生成する Java コード

## `main`メソッド
```Java
public static void main(String[] args) {
  EventQueue.invokeLater(new Runnable() {
    public void run() {
      try {
        Ex2 window = new Ex2();
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
  });
}
```


* `EventQueue.invokeLater`
  * EDT (Event Dispatch Thread) に処理を追加する
  * **クラスメソッド**
    * クラスから直接生えてるメソッド
    * インスタンスを作らなくても呼び出せる
* `new Runnable() {`
  * `run()` メソッドを渡したいとき
  * **無名クラス**
    * クラスを継承する新しいクラスを作って、そのインスタンスを作る
    * 実質、`Runnable`を改造しているようなもの

### EDT
Swingは非スレッドセーフ [^1] なので、複数のスレッドから操作することはできない。なので、他のスレッドは、EDTという特別なスレッドに処理をさせる。

## ボタンのアクションリスナ

```Java
btnRed.addActionListener(new ActionListener() {
  public void actionPerformed(ActionEvent e) {
    colorPanel.setBackground(Color.RED);
  }
});
```

* 無名クラスからインスタンス化している

### 無名クラス
```Java
class 無名 implements ActionListener {
  public void actionPerformed(ActionEvent e) {
    colorPanel.setBackground(Color.RED);
  }
}
btnRed.addActionListener(new 無名());
```

## UML
* クラス図: クラスの関係を静的に示す
* オブジェクト図: システムのある時点でのオブジェクトの関係を表す
* コメントも重要

### クラス図
* クラス名、属性 (プロパティ、データ)、操作 (メソッド、メッセージ) を持つ
* 四角を上中下に区分し、上にクラス名、中に属性、下に操作を書く
* クラスの属性や操作の前に「可視性」を表す記号を書く
  * `+`: public
  * `-`: private
  * `#`: protected
  * `~`: package


[1]: 処理を軽くするため。
