# 


# これから追加したいと思っている機能
* GUI機能
  * ボタンクリックを開始／終了とする
  * 指定キー（スペースキー）押下を開始／終了とする
* 時間指定
  * 今すぐスタート／今すぐストップ
  * スタート・ストップのタイミングを時刻で指定
  * スタート・ストップのタイミングを現在からの経過時間で指定
* Debugモード
  * 詳細なログを出力
* macOS対応
* Linux対応

# std::threadで時間周期的処理を実装する理由（ChatGPT 3.5談）
`for`ループの中に`sleep`を入れる方法と`std::thread`を使用する方法にはいくつかの違いがあります。

### `for`ループに`sleep`を入れる方法:

1. **シンプルさ**:
   - `for`ループ内で`sleep`を使用する方法はシンプルで直感的です。処理の一部としての時間待ちを明確に示すことができます。

2. **単純な周期的な処理**:
   - 単純な周期的な処理を行う場合には、`for`ループと`sleep`を組み合わせることで、比較的簡単に実装できます。

### `std::thread`を使用する方法:

1. **非同期処理**:
   - `std::thread`を使用することで、処理をメインスレッドから分離し、非同期で実行できます。これにより、他の処理と並行して時間を待つことができます。

2. **柔軟性**:
   - `std::thread`を使用すると、スレッド内で処理を実行しながら、そのスレッドを停止させる時間やタイミングをより柔軟に制御できます。`sleep`は一定の時間待つだけですが、`std::thread`を使うとスレッドを動的に制御できます。

3. **複雑な処理の分離**:
   - `std::thread`を使用することで、複雑な処理をスレッド内で管理し、メインスレッドと分離することができます。これにより、処理の複雑さに応じてスレッドごとに制御できます。

4. **同時性**:
   - `std::thread`を使うことで、複数の処理を同時に実行し、マルチタスクを実現できます。これにより、システム全体のレスポンスが向上する場合があります。

ただし、`std::thread`を使う際には、マルチスレッドプログラミングに伴う注意が必要です。同期、競合条件、デッドロックなど、スレッドセーフなコードを書くことが重要です。また、スレッドの管理やオーバーヘッドについても考慮する必要があります。