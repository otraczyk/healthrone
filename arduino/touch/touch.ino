#include <CapacitiveSensor.h>
#include <stdint.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */

class WalkingAverageCapacitiveSensor:public CapacitiveSensor {
  public:
    WalkingAverageCapacitiveSensor(uint8_t sendPin, uint8_t receivePin):CapacitiveSensor(sendPin, receivePin) {
      val=0;
    }
    
    
    float val;
    int capacitiveSensorWA() {
      const float a=0.1;
      const float revA=1-a;
//        if (error < 0) return -1;                  // bad pin - this appears not to work

      val=val*revA+a*capacitiveSensorRaw(1);
      
      return (int)val;
    }

};


CapacitiveSensor   cs_3_2 = CapacitiveSensor(3,2);        // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor   cs_5_4 = CapacitiveSensor(5,4);        // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
//CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);        // 10 megohm resistor between pins 4 & 6, pin 6 is sensor pin, add wire, foil
//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil
//WalkingAverageCapacitiveSensor  cs = WalkingAverageCapacitiveSensor(2,3);        // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil

void setup()                    
{

//   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  cs_3_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_5_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
   Serial.begin(9600);

}

void loop()                    
{
    long start = millis();
    long total2 =  cs_5_4.capacitiveSensor(30);
    long total1 =  cs_3_2.capacitiveSensor(30);
//    long total21 =  cs_5_4.capacitiveSensor(30);
//    long total11 =  cs_3_2.capacitiveSensor(30);
//    long total2 =  cs_4_5.capacitiveSensor(30);
//    long total3 =  cs_4_8.capacitiveSensor(30);

    Serial.print("t=");
    Serial.print(millis() - start);        // check on performance in milliseconds

    Serial.print("\t a=");                    // tab character for debug windown spacing
    Serial.print(total1);                  // print sensor output 2
    
    Serial.print("\t b=");                  // print sensor output 2
    Serial.print(total2);                  // print sensor output 2

//    Serial.print("\t a=");                    // tab character for debug windown spacing
//    Serial.print(total11);                  // print sensor output 2
//    
//    Serial.print("\t b=");                  // print sensor output 2
//    Serial.print(total21);                  // print sensor output 2
//    
    Serial.println();                  // print sensor output 1
//    Serial.print("\t");
//    Serial.print(total2);                  // print sensor output 2
//    Serial.print("\t");
//    Serial.println(total3);                // print sensor output 3


}

