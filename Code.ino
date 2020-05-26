#include <SimpleTimer.h>

#define BLYNK_PRINT Serial
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11 
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
SimpleTimer timer;
WidgetLED led3(V6);

int flag = 0;
char auth[] = "cSWyAlLyI7m-ORKdnZyguv9nfl-OSr6m";
char ssid[] = "MOHAN V";
char pass[] = "9840875320";

void setup(void)
{
  // Debug console
  Serial.begin(9600);
  dht.begin();
  pinMode(A0,INPUT);
  timer.setInterval(1000L,SEN);
  Blynk.begin(auth, ssid, pass);
}

void SEN() {
    float h = dht.readHumidity();
    float t = dht.readTemperature(); 
    float isButtonPressed = analogRead(A0);
    Blynk.virtualWrite(V5,t);
    Blynk.virtualWrite(V8,h);
    Blynk.virtualWrite(V4,A0);            
    if(t>=30 && flag==0 && isButtonPressed>=16)
    {
       Blynk.notify("Alert : Fire in the House");
       led3.on();
       flag=1;
    }    
    else if(t>=30 && flag == 0 && isButtonPressed<16)
    {
       Blynk.notify("Alert : Temperature is high");
       led3.on();
       flag=1;
    }
    else
       flag=0;          

   
}

void loop()
{
  Blynk.run();
  timer.run();
}
