#include "FastLED.h"
// Number of RGB LEDs in the strand
#define NUM_LEDS 50 

// Define the array of leds
CRGB leds[NUM_LEDS];
// Arduino pin used for Data
#define PIN 6 
void setup()
{
  FastLED.addLeds<WS2811, PIN,RGB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,2000); 
  randomSeed(1234);
  FastLED.setDither(1);

}

int expfilt(int x,int y,float alpha=.8){
 return  (int) (x*(1.-alpha)+y*alpha);
}


void loop() { 
  // one at a time
  memset(leds, 0, NUM_LEDS * 3);
  int i=0;
  int hue = 0;
  int val = 0;
  int dhue = 0;
  
  for (int t = 0; t<20000;t+=1){
    // wiener increment for hue, sync all leds
    dhue = random(-2,2); 
    // montecarlo over LEDS
    for(int j = NUM_LEDS ; j >0 ; j-=1 ) {
        // pick a random led
        i=random(NUM_LEDS);
        
//        // showflake?
        if (random(0,10)>9.5){
          leds[i].r=255/2.;
          leds[i].g=255/2.5;
          leds[i].b=255/2.5;
          leds[i].maximizeBrightness();
        }
//      else
        { 
          // choose hue
          if (random(0,10)<9){
            hue = random(5,20);
          }
          else{
           hue = random(-60,45); 
          }
          
          // radom walk on hue, sync all leds
          hue += dhue;
          val = random(130,255);
          
          hue = hue %255;
          val = val %255;
          leds[i]=CHSV(hue,230,val);
        }      
        FastLED.show();// serve??
        FastLED.delay(1);      
    }
  }
//  for (int t = 0;t<200;t++){
//    
//    for(int i = 0 ; i<NUM_LEDS ; i++ ) {
//      leds[i].nscale8(1);
//    }
//    FastLED.show();
//    FastLED.delay(100);      
//  }  


//  for(int j = NUM_LEDS*2 ; j >0 ; j-=1 ) {
//      i=random(NUM_LEDS);
//      leds[i].r=0.;
//      leds[i].g=0;
//      leds[i].b=0.;
//      
//      FastLED.show();
//      delay(1);      
//  }
  }
  
