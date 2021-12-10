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

//LEDマトリクスの初期化
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

//半角文字を描く
void drawMisakiHankaku ( int16_t x,int16_t y,char * text,uint16_t color )  {
  int n=0;
  byte buf[20][8];

  while(*text)
    text = getFontData(&buf[n++][0], text);
    
  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<4;k++){
        matrix.drawPixel(x + j * 4 + k, y + i, bitRead(buf[j][i],7-k) ? color: BLACK);
        }
    }
  }
 }
 
//全角文字を描く
void drawMisakiZenkaku ( int16_t x,int16_t y,char * text,uint16_t color )  {
  int n=0;
  byte buf[20][8];

  while(*text)
    text = getFontData(&buf[n++][0], text);
    
  for (byte i=0; i < 8; i++) {
    for (byte j=0; j < n; j++){
      for (byte k=0; k<8;k++){
        matrix.drawPixel(x + j * 8 + k, y + i, bitRead(buf[j][i],7-k) ? color: BLACK);
        }
    }
  }
 }

void setup() {
  matrix.begin();//マトリクスの開始
  matrix.setRotation(1);//マトリクスパネルの回転を設定
  matrix.fillScreen(BLACK);//黒で埋める
  drawMisakiHankaku(0,0,"ｱｻﾉ",RED);//ｱｻﾉ
  drawMisakiHankaku(0,8,"ﾌﾞﾂﾘ",GREEN);//ﾌﾞﾂﾘ
  drawMisakiZenkaku(0,16,"浅野",YELLOW);//浅野
  drawMisakiZenkaku(0,24,"物理",MAGENTA);//物理
}

void loop() {
  
}
