/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/shoubhitsstuff/Desktop/Lab8/src/Lab8.ino"
void setup();
void loop();
void printProximity();
void printAmbientLight();
void refreshDisplay();
#line 1 "/Users/shoubhitsstuff/Desktop/Lab8/src/Lab8.ino"
SYSTEM_THREAD(ENABLED);

#define BLYNK_TEMPLATE_ID "TMPL2KmJCdE6-"
#define BLYNK_TEMPLATE_NAME "Lab8 Template"
#define BLYNK_AUTH_TOKEN "dXQKu-4RF1jdQ3i-yF09hM7qEMkICzAx"

#include "Wire.h"
#include "blynk.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "oled-wing-adafruit.h"



OledWingAdafruit display;
VCNL4040 proximitySensor;
uint16_t proximityValue;
int lightValue;
volatile bool display_message = true;

void setup()
{

  display.setup();
  Serial.begin(9600);
  Wire.begin();
  //Blynk.begin(BLYNK_AUTH_TOKEN);

  
  refreshDisplay();
  proximitySensor.begin();
  proximitySensor.powerOnProximity();
  proximitySensor.powerOnAmbient();
  proximitySensor.enableWhiteChannel();

  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}
void loop()
{
  //Blynk.run();
  display.loop();

  proximityValue = proximitySensor.getProximity();
  lightValue = proximitySensor.getAmbient();

  if (proximityValue <= 50)
  {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
  }
  else if (proximityValue <= 150)
  {

    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);
  }
  else
  {
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  }

  if (display.pressedA())
  {
    refreshDisplay();
    printProximity();
  }
  if (display.pressedB())
  {
    refreshDisplay();
    printAmbientLight();
  }
//   if (display.pressedC())
//   {
//     if (display_message)
//     {
//       refreshDisplay();
//       printProximity();
//       printAmbientLight();
//     }
//     else
//     {
//       refreshDisplay();
//       Blynk.virtualWrite(V0, 1);
//       Blynk.virtualWrite(V1, 1);
//     }
//     display_message = !display_message;
//   }
// }

// BLYNK_WRITE(V0) // When something is listening towaerds virtual pin V0
// {
//   int pinValue = param.asInt();
//   if(pinValue == 1)
//   {
//     Serial.println(proximityValue);
//     Serial.println(lightValue);
//   }
// }
// BLYNK_WRITE(V1) //When something is listening towards virtual pin v1
// {
//   int pinValue = param.asInt();
//   if(pinValue == 1)
//   {
//     Serial.println(proximityValue);
//     Serial.println(lightValue);
//   }
}
void printProximity()
{
  display.println("Current proximity: ");
  display.print(proximityValue);
  display.display();
}
void printAmbientLight()
{
  display.println("Current light: ");
  display.print(lightValue);
  display.display();
}

void refreshDisplay()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}
