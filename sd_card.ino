#include <SD.h> //Load SD card library
#include<SPI.h> //Load SPI Library
#include "Wire.h"    // imports the wire library for talking over I2C 
#include "Adafruit_BMP085.h"  // import the Pressure Sensor Library We are using Version one of Adafruit API for this sensor
Adafruit_BMP085 mySensor;  // create sensor object called mySensor
 
 
float tempC;  // Variable for holding temp in C
float tempF;  // Variable for holding temp in F
float pressure; //Variable for holding pressure reading
 
int chipSelect = 4; //chipSelect pin for the SD card Reader
File mySensorData; //Data object you will write your sesnor data to
 
void setup(){
Serial.begin(9600); //turn on serial monitor
mySensor.begin();   //initialize pressure sensor mySensor
 
pinMode(10, OUTPUT); //Must declare 10 an output and reserve it
SD.begin(4); //Initialize the SD card reader
}
void loop() {
tempC = mySensor.readTemperature(); //  Read Temperature from BMP180
tempF = tempC*1.8 + 32.; // Convert degrees C to F
pressure= mySensor.readPressure(); //Read Pressure
 
mySensorData = SD.open("Data.txt", FILE_WRITE);
if (mySensorData) {
Serial.print("The Temp is: "); //Print Your results
Serial.print(tempF);
Serial.println(" degrees F");
Serial.print("The Pressure is: ");
Serial.print(pressure);
Serial.println(" Pa.");
Serial.println("");
delay(250); //Pause between readings.
 
 
mySensorData.print(tempF);                             //write temperature data to card
mySensorData.print(",");                               //write a commma
mySensorData.println(pressure);                        //write pressure and end the line (println)
mySensorData.close();                                  //close the file
}
}
