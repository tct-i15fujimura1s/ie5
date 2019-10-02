# オブジェクト指向プログラミング 演習1
Eclipse+WindowBuilderでウィンドウを持つアプリケーションプログラムを作成する

1. プロジェクトの作成
  * [File] → [New] → [Java Project]
  * Project name: ex1
  * Finish
2. アプリケーション（クラス）の作成
  * [File] → [New] → [Other]
  * [Window Builder] → [Swing Designer] → [Application Window]
  * Name: Ex1
  * Finish
3. ウィンドウ上にオブジェクトを配置
  1. Designタブ
  2. frameのContent Paneプロパティ
    * Layout: Border Layout
  3. JPanel panelをContentPane/Northに置く
  4. JTextArea textAreaをContentPane/Centerに置く
  5. panelのプロパティ
    * Layout: FlowLayout
  6. JButton btnClickMe, btnPushMe, btnTapMeをpanelに置く
4. オブジェクト間のメッセージ通信追加
  1. textAreaが他のオブジェクトから見えるようにする
    * textAreaに対して[Convert local to field]
  2. ボタンオブジェクトがtextAreaにメッセージを送信するようにする
    * Designer上でボタンをダブルクリックするとアクションリスナーが自動生成され、そのプログラムに切り替わる
    * アプリケーションの実行中にボタンをクリックされるとactionPerformedメソッドが呼び出される
      * actionPerformedメソッド内に「textAreaにappendメッセージを送信するプログラム」を書く
      * `textArea.append("Click!")`
  3. 全てのボタンについて`"Click!"`の部分を変更して同じことをする
5. 実行
  * Ex1.javaを選択した状態でRunボタン (緑の丸に白い三角) を押して実行する
6. 練習問題
  1. textAreaに表示される文字列が長くなりすぎた時、自動的に折り返す
  2. textAreaに文字列の追加表示ではなく、新規表示するようにする
