#include <stdint.h>
#include "sensors.h"

Sensors sensors;

void send_frame() {
  Serial.write((byte*)&sensors, sizeof(Sensors));
  Serial.flush();
  sensors.frame_no++;
}


void setup() {
  Serial.begin(9600);
  sensors.frame_no=0;
  sensors.magic_number=1337;
  
  Serial.println("sensors sizeof: ");
  Serial.println(sizeof(Sensors));
}


void loop() {
  send_frame();
  delay(1000);
}
