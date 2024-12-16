# Project Tama_Chan
2000年頃に作成した自作ゲームを現在(2024年)の環境でビルドし直してみるプロジェクト

## 当時の開発環境
- Windows98 (32bit)
- Microsoft Visual C++5.0
- DirectX 5.0
 
## 再ビルドの環境
- Windows11 (64bit)
- VisualStudio 2022
- DirectX 12

# 珍獣ハンターTama_Chan
[![demo](https://img.youtube.com/vi/aeewvT8_F_A/0.jpg)](https://www.youtube.com/watch?v=aeewvT8_F_A)

> [!Note]
> - youtube動画にリンクしています（音声注意）。
> - タイトル画像は[Gork](https://help.x.com/ja/using-x/about-grok)で生成したものです。

## 動作環境
- OS：windows98以降
- CPU：Pentium133MHz以上
- メモリ：32MB以上
- VRAM：2MB以上
- DirectX：ver.5.0以上
- グラフィック：解像度640×480, 256色

## ゲームの目的
このゲームは、面クリア型のアクションゲームです。ステージは全部で５つあり、すべてのステージのクリアを目指します。
主人公「タマちゃん」を操って、珍獣「ブルゴン」を捕まえることが、各ステージでの目的になります。ステージ上にいるすべてのブルゴンを捕まえればクリアとなり、次のステージに進むことが出来ます。


## 操作法
### タマちゃんの操作
|ジョイパッド|キーボード|アクション|
|-|-|-|
|十字キーの左右|カーソルキー or テンキー左右|左右に移動します(横移動)|
|十字キーの上下|カーソルキー or テンキー上下|はしごの上り下りに使用|
|Bボタン	|[Z]キー|押しながら横移動でダッシュします|
|Aボタン	|[Ctrl]キー|ジャンプします。早くダッシュしている時ほど高くジャンプできます|

### その他の操作
- [F1]キー: 画面のウインドウモードと、フルスクリーンモードを切り替えます
- [F2]キー: タマちゃんの操作を、ジョイパッドで行うか、キーボードで行うかを切り替えます
- [Enter]キー: ゲームスタート及びゲームのポーズ・解除に使用
- [Esc]キー: 終了キー。[Esc]キーを押すといつでも終了できます

### ポーズ機能
プレイ中[Enter]キーで、ゲームの一時停止ができます。一時停止中は、十字キーで画面をスクロールして、ステージ全体を見渡すことができます。もう１度[Enter]キーを押せば解除できます。

## [登場キャラクタ]
### 主人公「タマちゃん」
プレイヤの操作するキャラクタ	

### 珍獣「ブルゴン」
捕まえるキャラクタ。タマちゃんを追いかけてきます。　

### お邪魔キャラ｢グリーナ｣
画面左下から出現し、タマちゃんを追いかけて邪魔をしてきます。このキャラクタを捕まえることはできません。怒ると怖い。


## 敵キャラの攻撃
「ブルゴン」、及び「グリーナ」(以下敵キャラ)は、タマちゃんを追いかけてきます。ぶつかるとタマちゃんの体力が減ってしまうので、うまく逃げてください。


## タマちゃんの体力
「タマちゃん」の体力は、画面左上のハート形のゲージで表わされます。最大ハート３つ分で、敵キャラとぶつかるごとに１つ減って行きます。回復アイテムのハートを取るとハート１つ分回復します。ハートがなくなるとゲームオ－バーです。

## ブロックの利用
「タマちゃん」は、敵キャラを直接攻撃することはできませんが、ブロックを利用して、敵キャラを気絶させたり、捕まえたりすることができます。

## ブロックの種類
「レンガブロック」と「檻ブロック」は、ジャンプして下から頭突きすると、数秒点滅した後、落下します。タイミング良く落下させて敵キャラにぶつけると..?

|ブロック|説明|
|-|-|
|ノーマルブロック|ただの足場。落下しない|
|レンガブロック|敵キャラにぶつけると、そのキャラクタを気絶させることができます。ただし、「ブルゴン」は１回当てただけで気絶しますが、「グリーナ」は２回当てなければ気絶しません|
|檻ブロック|「ブルゴン」にぶつけると、檻の中に捕らえることができます。「グリーナ」を捕らえることはできません。<br>「グリーナ」にはレンガブロックとおなじ効果です。「グリーナ」にブロックを当てると、怒ってタマちゃんを追いかけるスピードが速くなります。これは２回目を当てて気絶させるまでおさまりません。<br>また、「グリーナ」は、怒ると当時に回復アイテムのハートを出すことがあります|

> [!NOTE]
> - 気絶した敵キャラは、しばらく動けなくなり、触れてもタマちゃんの体力は減らなくなります。檻に捕らえた「ブルゴン」も同様です
> - タマちゃんも、落下中のブロックに当たると気絶してしまいます



## クリア条件
ステージ上には、「ブルゴン」と同じ数だけの檻ブロックが配置されています。この檻ブロックを使って、すべての「ブルゴン」を捕らえることができれば、ゲームクリアです。

> [!NOTE]
> 捕らえたブルゴンは、しばらく放っておくと、暴れ出して（この時、赤く点滅します）檻から逃げてしまいます。すべての「ブルゴン」が檻に捕らえられた状態となっていなければ、ステージクリアとなりませんので、逃げてしまった場合はもう一度捕まえなければなりません。

> [!NOTE]
> #### 捕らえたブルゴンを逃がさないようにする
>　捕らえた「ブルゴン」が暴れ出すと、警告音が鳴り、「ブルゴン」は赤く点滅します。
> 放っておくと逃げ出してしまいますが、この状態で檻に衝撃を与えると「ブルゴン」は大人しくなり、またしばらくは逃げ出さないようになります。
>  - 檻の真上にあるブロックを落下させて檻にぶつける
>  - 檻の足元にあるブロックを落として、檻自体を落下させる



