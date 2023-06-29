#include <SimpleDHT.h>
#include <Adafruit_Sensor.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

int soilMoisturePin = A0;

const char* ssid     = "Nimo";
const char* password = "khuchrokatha";

  
  float soilMoisture = 0;



  WiFiClient client;

  unsigned long myChannelNumber = 1749280; //Your Channel Number (Without Brackets)
  const char * myWriteAPIKey = "B7YA0B87ZY305HHL"; //Your Write API Key

  

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 

  ThingSpeak.begin(client);
  
}
void loop(){
  Serial.println(WiFi.SSID());
  
  Serial.println("+++++++++++++++++++++++++++++");
  byte temp = 0;
  byte hum = 0;

  dht11.read(&temp, &hum, NULL);
  
  
  Serial.print((float)temp); 
  Serial.print(" *C, "); 
  Serial.print((float)hum); 
  Serial.println(" H");
  
  soilMoisture = ( 100.10 - ( (analogRead(soilMoisturePin)/1023.00) * 100.00 ) );
  Serial.println(soilMoisture);
  ThingSpeak.setField(1,temp);
  ThingSpeak.setField(2,hum);
  ThingSpeak.setField(3,soilMoisture);
  
  ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey); 

  delay(1000);

  delay(500);

  Serial.println("Data Updated");
}
