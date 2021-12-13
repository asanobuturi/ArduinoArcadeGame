#include <RGBmatrixPanel.h>
#include <misakiUTF16.h>

//ピンの諸設定
#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

//まぶしすぎるので少し暗めのRGB
#define RGB4(i,j,k)  matrix.Color333(i,j,k)

//色の諸設定
#define BLACK   RGB4(0,0,0)
#define BLUE    RGB4(0,0,4)
#define RED     RGB4(4,0,0)
#define GREEN   RGB4(0,4,0)
#define CYAN    RGB4(0,4,4)
#define MAGENTA RGB4(4,0,4)
#define YELLOW  RGB4(4,4,0)
#define WHITE   RGB4(4,4,4)

//74HC165のピンの設定
#define SL    12//SH/LD
#define CLKB  11//CLK
#define SER   13//QH

//ボタンが点灯しているかどうか
#define bPressed(i) !bitRead(buttonData,i)

//フレーム
int16_t frame = 0;
#define FPS 12

//LEDマトリクスの初期化
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int16_t n=0;
byte buf[20][8];

//全角文字を描く
void drawMisakiZenkaku ( int16_t x,int16_t y,char * text,uint16_t color )  {
  n=0;

  while(*text)
    text = getFontData(&buf[n++][0], text);
    
  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<8;k++){
        if(bitRead(buf[j][i],7-k))matrix.drawPixel(x + j * 8 + k, y + i, color);
        }
    }
  }
 }

//半角文字を描く
void drawMisakiHankaku ( int16_t x,int16_t y,char * text,uint16_t color )  {
  n=0;

  while(*text)
    text = getFontData(&buf[n++][0], text);
    
  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<4;k++){
        if(bitRead(buf[j][i],7-k))matrix.drawPixel(x + j * 4 + k, y + i,color);
        }
    }
  }
 }
 
 //全角文字のスクロール(変数frameに応じてスクロール)
 void scrollMisakiZenkaku ( int16_t x,int16_t y,int16_t w,char * text,uint16_t color,uint16_t BGColor = BLACK ){
  n=0;

  while(*text)
    text = getFontData(&buf[n++][0], text);

  int16_t loop = frame % (8 * (n + 2));


  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<8;k++){
        if(x <= x + j * 8 + k + w - loop && x + j * 8 + k + w - loop < x + w && bitRead(buf[j][i],7-k))matrix.drawPixel(x + j * 8 + k + w - loop, y + i, color);
        }
    }
  }
  } 
 
 //半角文字のスクロール(変数frameに応じてスクロール)
 void scrollMisakiHankaku ( int16_t x,int16_t y,int16_t w,char * text,uint16_t color,uint16_t BGColor = BLACK ){
  n=0;

  while(*text)
    text = getFontData(&buf[n++][0], text);

  int16_t loop = frame % (4 * (n + 4));


  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<4;k++){
        if(x <= x + j * 4 + k + w - loop && x + j * 4 + k + w - loop < x + w && bitRead(buf[j][i],7-k))matrix.drawPixel(x + j * 4 + k + w - loop, y + i, color);
        }
    }
  }
  }

byte buttonData;
//ボタンが押されているかどうか確認する
void updateButton(){
    digitalWrite(SL,LOW);
    digitalWrite(SL,HIGH);
    buttonData = digitalRead(SER);//Hを読む
    for(byte i=1; i<8; i++){
      digitalWrite(CLKB, HIGH);
      buttonData = buttonData << 1 | (digitalRead(SER));//G~Aを読む
      digitalWrite(CLKB, LOW);
      }
  }
//ボタン番号
int16_t bNum(int16_t n){
    return 8 - n;
  }

void setup() {
  matrix.begin();//マトリクスの開始
  //74HC165のピンの設定
  pinMode(CLKB,OUTPUT);
  pinMode(SL,OUTPUT);
  pinMode(SER,INPUT);
  digitalWrite(SL,HIGH);
  digitalWrite(CLKB,LOW);
  matrix.setRotation(1);//マトリクスパネルの回転を設定
  matrix.fillScreen(BLACK);//黒で埋める
}

void loop() {
  frame = 0;
  while(1){
    frame++;//フレームを1つ増やす
    matrix.fillScreen(BLACK);//フレームを黒に塗る
    updateButton();
    if(bPressed(0))matrix.fillCircle(7,9,2,RED);
    if(bPressed(1))matrix.fillCircle(2,14,2,RED);
    if(bPressed(2))matrix.fillCircle(7,14,2,YELLOW);
    if(bPressed(3))matrix.fillCircle(12,14,2,RED);
    if(bPressed(4))matrix.fillCircle(7,19,2,RED);
    if(bPressed(5))matrix.fillCircle(14,7,1,MAGENTA);
    delay(1000 / FPS);//フレームを変えるまで待つ
  }
}
