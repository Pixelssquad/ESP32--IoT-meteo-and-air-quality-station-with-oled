/*
Stazione meteo IoT - Progetto by Diego Pellacani -
Rileva temperatura, umidità, pressione atmosferica e qualità dell'aria, rileva la presenza di ammoniaca (NH3), ossidi di azoto (NOx), alcool, vapori di benzene, fumo, anidride carbonica (CO2)
Questo programma si basa sul lavoro di:
Rui Santos & Sara Santos - Random Nerd Tutorials https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
e sulle informazioni per il sensore MQ135 prese da qui: https://wokwi.com/projects/388604029799563265
Ho usato i due progetti per prenderne spunto e farne uno solo.
*/

/*
  Adapted from Example from ThingSpeak Library (Mathworks) 
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include "ThingSpeak.h"
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>


const char* ssid = "OOZTEST";   // Nome della tua rete wifi
const char* password = "diegodiego";   //  Password della tua rete wifi

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "apikey";   // Api key from https://thingspeak.com/

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Variable to hold temperature readings
float temperatureC;
float humidity;
float pressure;
//uncomment if you want to get temperature in Fahrenheit
//float temperatureF;

//aggiunto per sensore gas
float ppm;

// Create a sensor object
Adafruit_BME280 bme; //BME280 connect to ESP32 I2C (GPIO 21 = SDA, GPIO 22 = SCL)


Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
unsigned long delayTime;


//aggiunto per sensore gas
#define PPM_PIN 35   //pin35 usato

void initBME(){
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void setup() {
  Serial.begin(115200);  //Initialize serial
  initBME();
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak


    // aggiunto x display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
   // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.print(" MINI METEOBOX  IoT\n");
  display.print(" by Diego Pellacani\n");
  display.print("-=-=-=-=-=-=-=-=-=-=\n");
  display.print("  seguimi su youtube");
  display.print("    cerca DIEGOOZ");
  display.display();
}

void loop() {

    // aggiunto x display
  display.setCursor(0,0);
  display.clearDisplay();


//aggiunto per sensore gas
   // Value after from AD convertor
   int16_t ppmValue = analogRead(PPM_PIN);
   // Map the correct value ad AD convertor expects max votage to be 3.3 V and we are sending 5 V
   int mappedppmValue = (ppmValue/4.095);

   Serial.print("PPM: ");
  //  Print maapedTdsValue
   Serial.println(mappedppmValue);
      Serial.print("PPM3.3: ");
  //  Print maapedTdsValue
   Serial.println(ppmValue);
          // aggiunto x display

            display.setCursor(0,0);
  display.clearDisplay();
       display.print("MINI METEO BOX IoT"); display.print("\n");
       display.print("By Diego Pellacani"); display.print("\n");
       display.print("------------------"); display.print("\n");
      display.print("Temperatura: "); display.print(temperatureC); display.print("\n");
      display.print("Umidita' (%): "); display.print(humidity); display.print("\n");
      display.print("Press.(hPa): "); display.print(pressure); display.print("\n");
      display.print("PPM: "); display.print(ppmValue); display.print("\n");
            display.print("DIEGOOZ su YOUTUBE"); 
      display.display();
     delay(100);

  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(4000);     
      } 
      Serial.println("\nConnected.");
    }

    // Get a new temperature reading
    temperatureC = bme.readTemperature();
    Serial.print("Temperature (ºC): ");
    Serial.println(temperatureC);
    humidity = bme.readHumidity();
    Serial.print("Humidity (%): ");
    Serial.println(humidity);
    pressure = bme.readPressure() / 100.0F;
    Serial.print("Pressure (hPa): ");
    Serial.println(pressure);
    // aggiunto x SENS GAS
    ppm = ppmValue;

    
       // aggiunto x display
       display.print("MINI METEO BOX IoT"); display.print("\n");
       display.print("By Diego Pellacani"); display.print("\n");
       display.print("------------------"); display.print("\n");
      display.print("Temperatura: "); display.print(temperatureC); display.print("\n");
      display.print("Umidita' (%): "); display.print(humidity); display.print("\n");
      display.print("Press.(hPa): "); display.print(pressure); display.print("\n");
      display.print("PPM: "); display.print(ppmValue); display.print("\n");
            display.print("DIEGOOZ su YOUTUBE"); 
      display.display();
      
    //uncomment if you want to get temperature in Fahrenheit
    /*temperatureF = 1.8 * bme.readTemperature() + 32;
    Serial.print("Temperature (ºF): ");
    Serial.println(temperatureF);*/

    // set the fields with the values
    ThingSpeak.setField(1, temperatureC);
    //ThingSpeak.setField(1, temperatureF);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(3, pressure);
    ThingSpeak.setField(4, ppmValue);
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
