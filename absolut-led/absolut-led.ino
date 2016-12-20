#include "bb_LED.h"

bb_LED led1(3);
bb_LED led2(5);
bb_LED led3(6);
bb_LED led4(9);
bb_LED led5(10);
bb_LED led6(11);


int delay_time = 4000;

int fade_time = 1000;


int active = 0;

void setup() {
  Serial.begin(9600);
  led1.setMaxBrightness(125);
  led2.setMaxBrightness(125);
  led3.setMaxBrightness(125);
  led4.setMaxBrightness(125);
  led5.setMaxBrightness(125);
  led6.setMaxBrightness(125);


  led1.on();
  delay(500);
  led2.on();
  delay(500);
  led3.on();
  delay(500);
  led4.on();
  delay(500);
  led5.on();
  delay(500);
  led6.on();
  delay(500);

  led1.off();
  led2.off();
  led3.off();
  led4.off();
  led5.off();
  led6.off();

}

void run_leds() {
  led1.run();
  led2.run();
  led3.run();
  led4.run();
  led5.run();
  led6.run();

}

void wait(int mills) {
  unsigned long start_time = millis();
  while (millis() - start_time < mills) {
    run_leds();
  }
}
/*
  void wait_for_motion() {

  int current_state = sensor.detectMotion();
  Serial.print(millis());
  Serial.print("\t");

  Serial.println(current_state);
  while (current_state) {
    current_state = sensor.detectMotion();

    run_leds();
  }

  Serial.print(millis());
  Serial.print("\t");
  Serial.println(current_state);

  while (!current_state ) {
    if (sensor.detectMotion()) {
      current_state = 1;

    }
    run_leds();
  }
  }
*/

void loop() {
  led1.fadeOn(fade_time);
  led2.fadeOff(fade_time);
  led3.fadeOn(fade_time);
  led4.fadeOff(fade_time);
  led5.fadeOn(fade_time);
  led6.fadeOff(fade_time);

  wait(delay_time);

  led1.fadeOff(fade_time);
  led2.fadeOn(fade_time);
  led3.fadeOff(fade_time);
  led4.fadeOn(fade_time);
  led5.fadeOff(fade_time);
  led6.fadeOn(fade_time);

  wait(delay_time);

  //wait_for_motion();


}
