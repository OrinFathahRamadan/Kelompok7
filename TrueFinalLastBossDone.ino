#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define waterl A0
int level = 0;
#define Usuck 3
#define Heater 5
bool Memory = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Usuck, OUTPUT);
  sensors.begin();
  pinMode(Heater, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly
  int level = analogRead(waterl);
  Serial.print("Water level: ");
  Serial.println(level);
  delay(500);
  digitalWrite(Usuck, 0);
  
  if(level > 100){
    digitalWrite(Usuck, 1);
  }
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
  
  if(tempC <= 30){
    digitalWrite(Heater, 1);
    Memory = 1;
  }else if(tempC > 30 && tempC < 35 && Memory == 1){
    digitalWrite(Heater, 1);
  }else if(tempC >= 35 && Memory == 1){
    digitalWrite(Heater, 0);
    Memory = 0;
  }

}
