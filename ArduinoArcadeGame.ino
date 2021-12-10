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
 void scrollMisakiZenkaku ( int16_t x,int16_t y,int16_t w,char * text,uint16_t color ){
  n=0;

  while(*text)
    text = getFontData(&buf[n++][0], text);

  int16_t loop = frame % (8 * (n + 2));

  matrix.fillRect(x,y,w,7,BLACK);

  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<8;k++){
        if(x <= x + j * 8 + k + w - loop && x + j * 8 + k + w - loop < x + w && bitRead(buf[j][i],7-k))matrix.drawPixel(x + j * 8 + k + w - loop, y + i, color);
        }
    }
  }
  } 
 
 //半角文字のスクロール(変数frameに応じてスクロール)
 void scrollMisakiHankaku ( int16_t x,int16_t y,int16_t w,char * text,uint16_t color ){
  n=0;

  while(*text)
    text = getFontData(&buf[n++][0], text);

  int16_t loop = frame % (4 * (n + 4));

  matrix.fillRect(x,y,w,7,BLACK);

  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<4;k++){
        if(x <= x + j * 4 + k + w - loop && x + j * 4 + k + w - loop < x + w && bitRead(buf[j][i],7-k))matrix.drawPixel(x + j * 4 + k + w - loop, y + i, color);
        }
    }
  }
  }

void setup() {
  Serial.begin(9600);
  matrix.begin();//マトリクスの開始
  matrix.setRotation(1);//マトリクスパネルの回転を設定
  matrix.fillScreen(BLACK);//黒で埋める
}

void loop() {
  frame = 0;
  while(1){
    frame++;//フレームを1つ増やす
    scrollMisakiZenkaku(1,1,14,"全角文字のスクロール",MAGENTA);
    scrollMisakiHankaku(1,17,14,"3.14159265358979",YELLOW);
    delay(1000 / FPS);//フレームを変えるまで待つ
  }
}
