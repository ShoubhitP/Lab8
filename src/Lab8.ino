SYSTEM_THREAD(ENABLED);

#include "Wire.h"
#include "blynk.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "oled-wing-adafruit.h"

#define BLYNK_TEMPLATE_ID "TMPL2EKRGok8d"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "I6qMbq7oS9Qbn2gEUzw4G7kuT7kHQT-v"

OledWingAdafruit display;
VCNL4040 proximitySensor;
uint16_t proximityValue;
int lightValue;

void setup() {

display.setup();
Serial.begin(9600);
Wire.begin();


proximitySensor.begin();
proximitySensor.powerOnProximity();
proximitySensor.powerOnAmbient();
proximitySensor.enableWhiteChannel();

pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D7, OUTPUT);

refreshDisplay();
display.println("Starting data reading..");
display.display();
}
void loop() {

display.loop();

proximityValue = proximitySensor.getProximity();
lightValue = proximitySensor.getAmbient();

if(proximityValue <= 50)
{
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
}
else if(proximityValue <= 150)
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

if(display.pressedA())
{
    refreshDisplay();
    printProximity();
    
}
if(display.pressedB())
{
   refreshDisplay(); 
   printAmbientLight();
}
if(display.pressedC())
{


}

}
void refreshDisplay()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

void printProximity()
{
  display.print("Current proximity results: ");
  display.print(proximityValue);
  display.display();
}
void printAmbientLight()
{
  display.print("Current light level: ");
  display.print(lightValue);
  display.display();
}