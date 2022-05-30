# Chinese-Chess

## 前言

由於我們的前端架構做的太複雜了，在我的電腦上也不容易建置，僅能在開發的同學的 Mac 上測試執行，因此如果助教想要測試我們程式的正確性，可以透過以下提供的資訊來開啟 Visual Studio 用 CLI 來測試。

### Script 流程

```text
show 顯示目前棋盤的布置

對局流程 setNew | setFile -> getRound -> getMove -> move -> (回到 getRound -> getMove ....)

giveUp 投降，直接顯示勝負結果

logs 顯示目前對戰紀錄的所有資訊

getTime 取得當時時間，供前端使用

save 回傳儲存的內容，供前端使用
```

### 示範

```text
setNew hash
{"bTime":600,"chess":[{"color":2,"id":1,"name":"將","uni":1,"x":4,"y":0},{"color":2,"id":2,"name":"士","uni":2,"x":3,"y":0},{"color":2,"id":2,"name":"士","uni":3,"x":5,"y":0},{"color":2,"id":3,"name":"象","uni":4,"x":2,"y":0},{"color":2,"id":3,"name":"象","uni":5,"x":6,"y":0},{"color":2,"id":4,"name":"馬","uni":6,"x":1,"y":0},{"color":2,"id":4,"name":"馬","uni":7,"x":7,"y":0},{"color":2,"id":5,"name":"車","uni":8,"x":0,"y":0},{"color":2,"id":5,"name":"車","uni":9,"x":8,"y":0},{"color":2,"id":6,"name":"砲","uni":10,"x":1,"y":2},{"color":2,"id":6,"name":"砲","uni":11,"x":7,"y":2},{"color":2,"id":7,"name":"卒","uni":12,"x":0,"y":3},{"color":2,"id":7,"name":"卒","uni":13,"x":2,"y":3},{"color":2,"id":7,"name":"卒","uni":14,"x":4,"y":3},{"color":2,"id":7,"name":"卒","uni":15,"x":6,"y":3},{"color":2,"id":7,"name":"卒","uni":16,"x":8,"y":3},{"color":1,"id":1,"name":"帥","uni":17,"x":4,"y":9},{"color":1,"id":2,"name":"仕","uni":18,"x":3,"y":9},{"color":1,"id":2,"name":"仕","uni":19,"x":5,"y":9},{"color":1,"id":3,"name":"相","uni":20,"x":2,"y":9},{"color":1,"id":3,"name":" 相","uni":21,"x":6,"y":9},{"color":1,"id":4,"name":"傌","uni":22,"x":1,"y":9},{"color":1,"id":4,"name":"傌","uni":23,"x":7,"y":9},{"color":1,"id":5,"name":"俥","uni":24,"x":0,"y":9},{"color":1,"id":5,"name":"俥","uni":25,"x":8,"y":9},{"color":1,"id":6,"name":"炮","uni":26,"x":1,"y":7},{"color":1,"id":6,"name":"炮","uni":27,"x":7,"y":7},{"color":1,"id":7,"name":"兵","uni":28,"x":0,"y":6},{"color":1,"id":7,"name":"兵","uni":29,"x":2,"y":6},{"color":1,"id":7,"name":"兵","uni":30,"x":4,"y":6},{"color":1,"id":7,"name":"兵","uni":31,"x":6,"y":6},{"color":1,"id":7,"name":"兵","uni":32,"x":8,"y":6}],"hash":"hash","rTime":600}

show
-5 -4 -3 -2 -1 -2 -3 -4 -5
 0  0  0  0  0  0  0  0  0
 0 -6  0  0  0  0  0 -6  0
-7  0 -7  0 -7  0 -7  0 -7
 0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0
 7  0  7  0  7  0  7  0  7
 0  6  0  0  0  0  0  6  0
 0  0  0  0  0  0  0  0  0
 5  4  3  2  1  2  3  4  5

getRound hash
{"checkmate":0,"color":1,"delete":null,"hash":"hash","modal":"","move":null,"winner":0}

getMove hash 22
{"canEat":[],"canMove":[{"x":2,"y":7},{"x":0,"y":7}],"hash":"hash","uni":22,"x":1,"y":9}

move hash 1 9 2 7
{"action":"move","hash":"hash"}

getRound hash
{"checkmate":0,"color":2,"delete":null,"hash":"hash","modal":"","move":{"fromX":1,"fromY":9,"id":4,"toX":2,"toY":7,"uni":22},"winner":0}

getMove hash 10
{"canEat":[],"canMove":[{"x":1,"y":1},{"x":2,"y":2},{"x":3,"y":2},{"x":4,"y":2},{"x":5,"y":2},{"x":6,"y":2},{"x":1,"y":3},{"x":1,"y":4},{"x":1,"y":5},{"x":1,"y":6},{"x":0,"y":2}],"hash":"hash","uni":10,"x":1,"y":2}

move hash 1 2 1 1
{"action":"move","hash":"hash"}

show
-5 -4 -3 -2 -1 -2 -3 -4 -5
 0 -6  0  0  0  0  0  0  0
 0  0  0  0  0  0  0 -6  0
-7  0 -7  0 -7  0 -7  0 -7
 0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0
 7  0  7  0  7  0  7  0  7
 0  6  4  0  0  0  0  6  0
 0  0  0  0  0  0  0  0  0
 5  0  3  2  1  2  3  4  5

```

## 定義

### 棋的名稱

* 將/帥 - general - 1
* 士/仕 - advisor - 2
* 象/相 - elephant - 3
* 馬/傌 - horse - 4
* 車/俥 - chariot - 5
* 砲/炮 - cannon - 6
* 卒/兵 - soldier - 7

### ID

每個棋子會有一個 ID，如果需要知道棋子的 ID，可以到 GameManager.h 中的建構子查看(最後一個參數即為 uni id)

```cpp
// 黑方
onBoard.push_back(new General(Position(4, 0), ColorEnum::Black, 1));
onBoard.push_back(new Advisor(Position(3, 0), ColorEnum::Black, 2));
onBoard.push_back(new Advisor(Position(5, 0), ColorEnum::Black, 3));
onBoard.push_back(new Elephant(Position(2, 0), ColorEnum::Black, 4));
onBoard.push_back(new Elephant(Position(6, 0), ColorEnum::Black, 5));
onBoard.push_back(new Horse(Position(1, 0), ColorEnum::Black, 6));
onBoard.push_back(new Horse(Position(7, 0), ColorEnum::Black, 7));
onBoard.push_back(new Chariot(Position(0, 0), ColorEnum::Black, 8));
onBoard.push_back(new Chariot(Position(8, 0), ColorEnum::Black, 9));
onBoard.push_back(new Cannon(Position(1, 2), ColorEnum::Black, 10));
onBoard.push_back(new Cannon(Position(7, 2), ColorEnum::Black, 11));
onBoard.push_back(new Soldier(Position(0, 3), ColorEnum::Black, 12));
onBoard.push_back(new Soldier(Position(2, 3), ColorEnum::Black, 13));
onBoard.push_back(new Soldier(Position(4, 3), ColorEnum::Black, 14));
onBoard.push_back(new Soldier(Position(6, 3), ColorEnum::Black, 15));
onBoard.push_back(new Soldier(Position(8, 3), ColorEnum::Black, 16));
// 紅方
onBoard.push_back(new General(Position(4, 9), ColorEnum::Red, 17));
onBoard.push_back(new Advisor(Position(3, 9), ColorEnum::Red, 18));
onBoard.push_back(new Advisor(Position(5, 9), ColorEnum::Red, 19));
onBoard.push_back(new Elephant(Position(2, 9), ColorEnum::Red, 20));
onBoard.push_back(new Elephant(Position(6, 9), ColorEnum::Red, 21));
onBoard.push_back(new Horse(Position(1, 9), ColorEnum::Red, 22));
onBoard.push_back(new Horse(Position(7, 9), ColorEnum::Red, 23));
onBoard.push_back(new Chariot(Position(0, 9), ColorEnum::Red, 24));
onBoard.push_back(new Chariot(Position(8, 9), ColorEnum::Red, 25));
onBoard.push_back(new Cannon(Position(1, 7), ColorEnum::Red, 26));
onBoard.push_back(new Cannon(Position(7, 7), ColorEnum::Red, 27));
onBoard.push_back(new Soldier(Position(0, 6), ColorEnum::Red, 28));
onBoard.push_back(new Soldier(Position(2, 6), ColorEnum::Red, 29));
onBoard.push_back(new Soldier(Position(4, 6), ColorEnum::Red, 30));
onBoard.push_back(new Soldier(Position(6, 6), ColorEnum::Red, 31));
onBoard.push_back(new Soldier(Position(8, 6), ColorEnum::Red, 32));
```

### 顏色

* 紅 - 1
* 黑 - 2

### hash

提供前端交換資料時辨識的雜湊碼，測試時隨意輸入即可

## API

### 設定讀取的遊戲(需要在資料最末端加上特殊符號 "\n@~!~@")

setFile {hash} {rows} {fileContent}@\~!\~@

```json
{
    "chess": [
        {
            "name": "將",
            "uni": 2,
            "color": 1|2,
            "id": 1,
            "x": 4,
            "y": 0
        },
        {
            "name": "士",
            "uni": 2,
            "color": 1|2,
            "id": 2,
            "x": 3,
            "y": 0
        },
    ],
    "rTime": 600,
    "bTime": 600,
    "hash": "hash"
}
```

### 設定新的遊戲

setNew {hash}

```json
{
    "chess": [
        {
            "name": "將",
            "uni": 2,
            "color": 1|2,
            "id": 1,
            "x": 4,
            "y": 0
        },
        {
            "name": "士",
            "uni": 2,
            "color": 1|2,
            "id": 2,
            "x": 3,
            "y": 0
        },
    ],
    "rTime": 600,
    "bTime": 600
    "hash": "hash"
}
```

### 取得回合狀態

getRound {hash}

```json
{
    "color": 1|2|0,
    "checkmate": 1|2|0, //將軍
    "winner": 0|1|2,
    "modal": ""|"將軍"|"勝利",
    "move": {
        "id": 2,
        "uni": 2,
        "fromX": 0,
        "fromY": 0,
        "toX": 1,
        "toY": 1
    },
    "delete": {
        "id": 2,
        "uni": 2,
        "x": 3,
        "y": 0
    },
    "hash": "hash"
}
```

### 投降

giveUp {hash} {color}

```json
{
    "modal": "勝利",
    "winner": 1|2
    "hash": "hash"
}
```

### 取得可以移動的位置(僅能選擇當局的棋子，並且是還存在的棋子，否則報錯)

getMove {hash} {uni}

```json
{
    "canMove": [ //可以移動的位置
        {
            "x": 1,
            "y": 1
        },
        {
            "x": 2,
            "y": 2
        }
    ],
    "canEat": [ //可以吃的子的位置
        {
            "x": 1,
            "y": 1,
        },
        {
            "x": 2,
            "y": 2
        }
    ],
    "hash": "hash"
}
```

### 取得兩方剩餘時間

getTime {hash}

```json
{
    "rTime": 600,
    "bTime": 600,
    "winner": 1|2|0,
    "modal": "勝利"
    "hash": "hash"
}
```

### 移動棋子(fromXY 不能選擇空的位子)

move {hash} {fromX} {fromY} {toX} {toY}

```json
{
    "action": "move" | "replace", // 由c++端判斷是吃棋還是單純移動,
    "hash": "hash"
}

```

### 儲存

save {hash}

```json
{
    "content": "...",
    "hash": "hash"
}
```

### 取得完整日誌（日誌回放）

logs {hash}

```json
{
    "logs": [
        {
            "rTime": 580,
            "bTime": 600,
            "chess": [
                {
                    "name": "將",
                    "color": 1|2,
                    "id": 1,
                    "x": 4,
                    "y": 0
                },
                {
                    "name": "士",
                    "color": 1|2,
                    "id": 2,
                    "x": 3,
                    "y": 0
                },
                // ...
            ]
        },
        {
            "rTime": 580,
            "bTime": 560,
            "chess": [
                {
                    "name": "將",
                    "color": 1|2,
                    "id": 1,
                    "x": 4,
                    "y": 0
                },
                {
                    "name": "士",
                    "color": 1|2,
                    "id": 2,
                    "x": 3,
                    "y": 0
                },
                // ...
            ],
            // ...
        },
    ],
    "hash": "hash"
}
```

### 顯示棋盤(command 測試用)

show

```text
-5 -4 -3 -2 -1 -2 -3 -4 -5
 0  0  0  0  0  0  0  0  0
 0 -6  0  0  0  0  0 -6  0
-7  0 -7  0 -7  0 -7  0 -7
 0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0
 7  0  7  0  7  0  7  0  7
 0  6  0  0  0  0  0  6  0
 0  0  0  0  0  0  0  0  0
 5  4  3  2  1  2  3  4  5
```

## 流程

![Alternate text](https://i.imgur.com/ir2ztYt.jpg)
