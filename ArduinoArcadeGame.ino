#include "ArduinoArcadeGame.h"

int16_t frame = 0;
void setup() {
  initialize();
}

void loop() {
  frame = 0;
  while(1){
    frame++;//フレームを1つ増やす
    matrix.fillScreen(BLACK);//フレームを黒に塗る
    if(bPressed(0)){
      matrix.fillCircle(7,9,2,RED);
      sound(NOTE_C6);
      }
    if(bPressed(1)){
      matrix.fillCircle(2,14,2,RED);
      sound(NOTE_D6);
      }
    if(bPressed(2)){
      matrix.fillCircle(7,14,2,YELLOW);
      sound(NOTE_E6);
      }
    if(bPressed(3)){
      matrix.fillCircle(12,14,2,RED);
      sound(NOTE_F6);
      }
    if(bPressed(4)){
      matrix.fillCircle(7,19,2,RED);
      sound(NOTE_G6);
      }
    if(bPressed(5)){
      matrix.fillCircle(14,7,1,MAGENTA);
      sound(NOTE_A6);
      }
    delay(1000 / FPS);//フレームを変えるまで待つ
  }
}
