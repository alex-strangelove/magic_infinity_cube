#include <FastLED.h>
#define LED_PIN     22
#define NUM_LEDS    10
CRGB leds[NUM_LEDS];

void onesnake(int duration);
void fadeFromCenter(int duration);
void fill_red(void);
void fill_blue(void);
void fill_green(void);
void fill_cross_fade(void);
void reset_strip(void);


void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    pinMode(LED_PIN, OUTPUT);   
}

void loop(void) {
  onesnake(1000);
  fadeFromCenter(1000);
  fill_red();
  fill_blue();
  fill_green();
  fill_cross_fade();
  reset_strip();
}

void fill_red(void){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB(255, 0, 0);
  FastLED.show();
  delay(500);
  }
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB(0, 0, 0);
  FastLED.show();
  delay(500);
  }
 }
void fill_blue(void){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB(0, 0, 255);
  FastLED.show();
  delay(5);
  }
 }
void fill_green(void){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB(0, 255, 0);
  FastLED.show();
  delay(5);
  }
 }
 void fill_cross_fade(void){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB(178, 0, 255);
  FastLED.show();
  delay(5);
  }
 }
void reset_strip(void){
  for(int i=NUM_LEDS; i>0; i--){
  leds[i] = CRGB(0, 0, 0);
  FastLED.show();
  delay(2);
  }
 }
 void onesnake(int duration){
  unsigned long startTime;
  startTime=millis();
  int location=1;
  int nextpath =1;
  int corners[8][3] = {{-7,8,1},{-1,2,3},{-3,4,5},{-5,6,7},{-8,-12,9},{-2,-9,10},{-4,-10,11},{-6,-11,12}};
  int ledsInSnake[48];
  int color=0;
  for (int i=0;i<48;i++){
    ledsInSnake[i]=0;
  }
  while(startTime+duration>millis()){
    if (location>0){
      for(int i=0;i<12;i++){
        color=(color+5)%2550;
        leds[ledsInSnake[0]]=CHSV(255, 255, 0);
        for(int j = 0; j < 48; j++){
          if (j!=0){
            leds[ledsInSnake[j]]=CHSV(color/10,255, (j*255)/48);
            ledsInSnake[j-1]=ledsInSnake[j];
          }
        }
        ledsInSnake[47]=(location-1)*12+i;
        leds[ledsInSnake[47]]=CHSV(color/10,255, 255);
        FastLED.show();
        delay(20); 
      }
    }
    if (location<0){
      for(int i=0;i<12;i++){
        color=(color+5)%2550;
        leds[ledsInSnake[0]]=CHSV(255, 255, 0);
        for(int j = 0; j < 48; j++){
          if (j!=0){
            leds[ledsInSnake[j]]=CHSV(color/10,255, (j*255)/48);
            ledsInSnake[j-1]=ledsInSnake[j];
          }
        }
        ledsInSnake[47]=(location+1)*-12+11-i;
        leds[ledsInSnake[47]]=CHSV(color/10,255, 255);
        FastLED.show();
        delay(20); 
      }      
    }
    nextpath=random(0,2);
    for (int i=0; i<8;i++){//differen 8
      if (corners[i][0]==-location || corners[i][1]==-location || corners[i][2]==-location){
        if (corners[i][nextpath]!=-location){
          location=corners[i][nextpath];
        }else{
          location=corners[i][nextpath+1];
        }
        break;
      }
    }
    FastLED.show();
    delay(20); 
  }
}
void fadeFromCenter(int duration){
  unsigned long startTime;
  startTime=millis();
  int counter = 0;
  while(startTime+duration>millis()){
    counter=(counter+1)%255;
    for (int i=0;i<12;i++){
      for (int j=0;j<6;j++){
        leds[i*12+j]=CHSV((counter+j*15)%255,255,255);
        leds[i*12+11-j]=CHSV((counter+j*15)%255,255,255);
      }
    }
    FastLED.show();
    delay(20); 
  }
}
