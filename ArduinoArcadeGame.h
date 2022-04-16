/*
ArduinoArcadeGame.h
独自の関数一覧
  void initialize();
    初期化
  void sound(uint16_t note);
    音を鳴らす
  void drawMisakiZenkaku ( int16_t x,int16_t y,char * text,uint16_t color );
    全角文字を描く
  void drawMisakiHankaku ( int16_t x,int16_t y,char * text,uint16_t color );
    半角文字を描く
  void scrollMisakiZenkaku ( int16_t x,int16_t y,int16_t w,char * text,uint16_t color,uint32_t frame );
    全角文字のスクロール
  void scrollMisakiHankaku ( int16_t x,int16_t y,int16_t w,char * text,uint16_t color,uint32_t frame );
    半角文字のスクロール
  bool bPressed(int16_t num)
    ボタンが押されているかどうか確認する

  RGB4(r,g,b)
    matrix.color333と全く同じ
    RGBをそれぞれ0~3(本来は0~7だがまぶしすぎるため)で調整する

matrix.[Adafruit GFX Libraryの関数]
  Adafruit GFX Libraryの関数を実行
*/

#include <RGBmatrixPanel.h>
#include <misakiUTF16.h>
#include "pitches.h"

//LEDマトリクスのピンの諸設定
#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

//まぶしすぎるので少し暗めのRGB
#define RGB4(r,g,b)  matrix.Color333(r,g,b)

//色の諸設定
#define BLACK   RGB4(0,0,0)
#define BLUE    RGB4(0,0,3)
#define RED     RGB4(3,0,0)
#define GREEN   RGB4(0,3,0)
#define CYAN    RGB4(0,3,3)
#define MAGENTA RGB4(3,0,3)
#define YELLOW  RGB4(3,3,0)
#define WHITE   RGB4(3,3,3)

//74HC165のピンの設定
#define SL    A3//SH/LD
#define CLKB  A4//CLK
#define SER   A5//QH

//パッシブブザーのピン
#define BUZ 12


//フレーム
#define FPS 18

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
 
 //全角文字のスクロール
 void scrollMisakiZenkaku ( int16_t x,int16_t y,int16_t w,char * text,uint16_t color,uint32_t frame ){
  n=0;

  while(*text)
    text = getFontData(&buf[n++][0], text);

  int16_t scrollLoop = frame % (8 * (n + 2));


  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<8;k++){
        if(x <= x + j * 8 + k + w - scrollLoop && x + j * 8 + k + w - scrollLoop < x + w && bitRead(buf[j][i],7-k))matrix.drawPixel(x + j * 8 + k + w - scrollLoop, y + i, color);
        }
    }
  }
  } 
 
 //半角文字のスクロール
 void scrollMisakiHankaku ( int16_t x,int16_t y,int16_t w,char * text,uint16_t color,uint32_t frame ){
  n=0;

  while(*text)
    text = getFontData(&buf[n++][0], text);

  int16_t scrollLoop = frame % (4 * (n + 4));


  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<4;k++){
        if(x <= x + j * 4 + k + w - scrollLoop && x + j * 4 + k + w - scrollLoop < x + w && bitRead(buf[j][i],7-k))matrix.drawPixel(x + j * 4 + k + w - scrollLoop, y + i, color);
        }
    }
  }
  }

//ボタンが押されているかどうか確認する
//0 <= num <= 7
byte buttonData;
bool bPressed(int16_t num){
    digitalWrite(SL,LOW);
    digitalWrite(SL,HIGH);
    buttonData = digitalRead(SER);//Hを読む
    for(byte i=1; i<8; i++){
      digitalWrite(CLKB, HIGH);
      buttonData = buttonData << 1 | (digitalRead(SER));//G~Aを読む
      digitalWrite(CLKB, LOW);
      }
    return !bitRead(buttonData,num);
  }

//音を鳴らす
void sound(uint16_t note){
  tone(BUZ,note,1200 / FPS);
  }

//初期化
void initialize(){
  matrix.begin();//マトリクスの開始
  //74HC165のピンの設定
  pinMode(CLKB,OUTPUT);
  pinMode(SL,OUTPUT);
  pinMode(SER,INPUT);
  digitalWrite(SL,HIGH);
  digitalWrite(CLKB,LOW);
  pinMode(BUZ,OUTPUT);//スピーカーのピン
  matrix.setRotation(1);//マトリクスパネルの回転を設定
  matrix.fillScreen(BLACK);//黒で埋める
  }

//HSVをRGBに変換
//一部改造 https://ja.wikipedia.org/wiki/HSV%E8%89%B2%E7%A9%BA%E9%96%93#%E3%82%BD%E3%83%95%E3%83%88%E3%82%A6%E3%82%A7%E3%82%A2%E3%81%A7%E3%81%AE%E5%A4%89%E6%8F%9B%E5%87%A6%E7%90%86_2
uint16_t hsv(float h, float s, float v){
  float r = v;
  float g = v;
  float b = v;
  if (s > 0.0f) {
      h *= 6.0f;
      int16_t i = (int16_t) h;
      float f = h - (float) i;
      switch (i) {
          default:
          case 0:
              g *= 1 - s * (1 - f);
              b *= 1 - s;
              break;
          case 1:
              r *= 1 - s * f;
              b *= 1 - s;
              break;
          case 2:
              r *= 1 - s;
              b *= 1 - s * (1 - f);
              break;
          case 3:
              r *= 1 - s;
              g *= 1 - s * f;
              break;
          case 4:
              r *= 1 - s * (1 - f);
              g *= 1 - s;
              break;
          case 5:
              g *= 1 - s;
              b *= 1 - s * f;
              break;
      }
  }
  return RGB4(r*4,g*4,b*4);
}
