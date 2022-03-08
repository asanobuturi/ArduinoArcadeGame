#include "ArduinoArcadeGame.h"

int16_t frame = 0;
void setup() {
  initialize();
}

void loop() {
  frame = 0;
  while(1){
    //matrix.fillScreen(BLACK);//フレームを黒に塗る
    for(int i = 0; i < 32; i++){
      matrix.drawLine(6,i,9,i,hsv(1.0f/32*((i+frame)%32),1.0f,1.0f));
      }
    delay(1000 / FPS);//フレームを変えるまで待つ
    frame++;//フレームを1つ増やす
  }
}
