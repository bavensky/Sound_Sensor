  /*******************************************************************************
   * Project  : Woof woof                                                        *
   * Compiler : Arduino 1.0.2                                                    *
   * Board    : Arduino UNO                                                      *
   * Shield   : Adafruit Data Logger Shield                                      *
   * Module   : Sound sensor                                                     *
   *          :                                                                  *
   * Author   : Bavensky :3                                                      *
   * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
   * Date     : 20/04/2014 [dd/mm/yyyy]                                          *
   *******************************************************************************/
  #include <Wire.h>
  #include "RTClib.h"
  #include <SD.h>
  
  #define ANALOG_IN 0
  #define DEBUG 0
  #define LIMIT 500
  #define TIME 3000
  #define OUTPUT_FILE "Datalog.csv"
  
  File myFile;
  const int chipSelect = 10; // pin 10 using adafruit
  RTC_DS1307 rtc;
  
  int i=0, a=0, w=0;
  
  char line[50];
   
  void setup()
  {
    Serial.begin(9600);  
    Wire.begin(); 
    rtc.begin();
    pinMode(10, OUTPUT); 
     
    while (!SD.begin(chipSelect)) 
    { 
      Serial.println("initialization failed!");
      delay(TIME); 
    }
    
  }
  
  void loop()
  { 
    int sound_input = analogRead(ANALOG_IN);    
    if(sound_input < LIMIT)
    {
      writing(sound_input); 
      delay(TIME);
    }
  }
  
  void writing(int volume)
  {
    myFile = SD.open(OUTPUT_FILE, FILE_WRITE);    
    if (myFile) 
    {
      DateTime now = rtc.now();
      sprintf(line, "%d/%d/%d,%d:%d:%d,%d", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second(), volume);
      myFile.println(line);
      Serial.println(line);
      delay(TIME);
      myFile.close();
    }
  }
  

