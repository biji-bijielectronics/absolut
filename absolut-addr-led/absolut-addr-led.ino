#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    7
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    144
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          255
#define FRAMES_PER_SECOND  60

#define MOTION_SENSOR 2
#define POWER_PIN 4

#define LED_PIN 13

unsigned long motion_detected;


void setup() {

  pinMode(POWER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(POWER_PIN, HIGH);

  pinMode(MOTION_SENSOR, INPUT);

  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  motion_detected = millis();
}




void loop()
{

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  //  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  // EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically

  if (digitalRead(MOTION_SENSOR) == 1) {
    juggle();
    digitalWrite(LED_PIN, HIGH);
    motion_detected = millis();

  }
  else {
    digitalWrite(LED_PIN, LOW);
    if (millis() - motion_detected > 3000) {
      all_off();
    }
    else{
      juggle();
    }
  }


}

void all_off() {
  fadeToBlackBy( leds, NUM_LEDS, 10);

}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 10);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

