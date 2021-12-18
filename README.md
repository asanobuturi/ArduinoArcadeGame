# ArduinoArcadeGame
Arduinoで作ったアーケードゲームのソースファイル  

## 電子工作

### 必要なもの
- Arduino Uno x 1
- 5VACアダプター(4A以上推奨) x 1
- ACアダプターのコネクタ x 1
- ON-OFFスイッチ x 1
- XL6009ブーストコンバーター
- 32x16 RGB LED MATRIX(Adafruit) x 1
- ボタン(アーケードゲーム用) x 5(ボタン1つ目を上、2つ目を左、3つ目を真ん中、4つ目を右、5つ目を下の十字状に設置しています。)
- ボタン(小さいボタン) x 1
- 74HC165 x 1
- 8Ω2Wスピーカー または パッシブブザー x 1
- 可変抵抗 x 1
- 導線、抵抗 必要な量

### 回路の組み方
1. ACアダプタのコネクタから電源スイッチを挟んで次の2つに並列で給電する  
    1. - ブーストコンバーターを5Vからおよそ9Vに昇圧するようにしておく
        - プラスをXL6009ブーストコンバーターの`IN+`、マイナスをブーストコンバーターの`IN-`につなげる
        - ブーストコンバーターの`OUT+`をArduinoの`Vin`に、ブーストコンバーターの`OUT-`をArduinoの`GND`につなげる
    2. プラスをLEDマトリクスパネルの`VCC`に、マイナスをLEDマトリクスパネルの`GND`につなげる
2. 次のようにLEDマトリクスとArduinoをつなげる
    - LEDマトリクスの`INPUT`(裏側から見て左)の16ピン(2x8)のうちの左側の上から2番目〈以下`[左,2]GND`〉、`[左,4]GND`、`[左,6]D`、`[左,8]GND`をArduinoの`GND`につなげる
    - `[右,1]R1`,`[左,1]G1`,`[右,2]B1`をそれぞれArduinoの`2`,`3`,`4`ピンにつなげる
    - `[右,3]R2`,`[左,3]G2`,`[左,4]B2`をそれぞれArduinoの`5`,`6`,`7`ピンにつなげる
    - `[右,5]A`,`[左,5]B`,`[右,6]C`をそれぞれArduinoの`A0`,`A1`,`A2`につなげる
    - `[左,7]LAT`をArduinoの`10`ピンにつなげる
    - `[右,8]OE`をArduinoの`9`につなげる
    - `[右,7]CLK`をArduinoの`8`につなげる
3. アーケードゲーム用のボタン5つと小さいボタン1つを74HC165のボタンのつなげ方でつなげる(それぞれ74HC165の`A`,`B`,`C`,`D`,`E`,`F`につなげる)  
また、`G`,`H`にはArduinoの`5V`ピンから抵抗を介してつなげる。
4. 74HC165の`SH/LD`を`A3`、`CLK`を`A4`、`QH`を`A5`につなげる
5. スピーカーまたはパッシブブザーをArduinoの`12`ピンに可変抵抗を介してつなげる
    
## コミットについて
☑の絵文字のついたコミットメッセージは、動作確認済みということを意味します。  