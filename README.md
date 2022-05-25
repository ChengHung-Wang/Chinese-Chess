# Chinese-Chess

## 定義
### 棋的名稱
* 將/帥 - general - 1
* 士/仕 - advisor - 2
* 象/相 - elephant - 3
* 馬/傌 - horse - 4
* 車/俥 - chariot - 5
* 砲/炮 - cannon - 6
* 卒/兵 - soldier - 7

### 顏色
* 紅 - 1
* 黑 - 2

## API

### 設定讀取的遊戲

setFile {hash} {rows} {fileContent}@\~!\~@
```json=
{
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
    ],
    "rTime": 600,
    "bTime": 600,
    "hash": "hash"
}
```
### 設定新的遊戲
setNew {hash}
```json=
{
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
    ],
    "rTime": 600,
    "bTime": 600
    "hash": "hash"
}
```

### 取得回合狀態
getRound {hash}
```json=
{
    "color": 1|2|0,
    "checkmate": 1|2|0, //將軍
    "winner": 0|1|2,
    "modal": ""|"將軍"|"勝利",
    "move": {
        "id": 2,
        "fromX": 0,
        "fromY": 0,
        "toX": 1,
        "toY": 1
    },
    "delete": {
        "id": 2,
        "x": 3,
        "y": 0
    },
    "hash": "hash"
}
```

### 投降
giveUp {hash} {color}
```json=
{
    "modal": "勝利",
    "winner": 1|2
    "hash": "hash"
}
```

### 取得可以移動的位置
getMove {hash} {x} {y}
```json=
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
```json=
{
    "rTime": 600,
    "bTime": 600,
    "winner": 1|2|0,
    "modal": "勝利"
    "hash": "hash"
}
```
### 移動棋子
move {hash} {fromX} {fromY} {toX} {toY}
```json=
{
    "action": "move" | "replace", // 由c++端判斷是吃棋還是單純移動,
    "hash": "hash"
}

```
### 儲存
save {hash}
```json=
{
    "content": "...",
    "hash": "hash"
}
```
### 取得完整日誌（日誌回放）

logs {hash}
```json=
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
```
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
![](https://i.imgur.com/ir2ztYt.jpg)
