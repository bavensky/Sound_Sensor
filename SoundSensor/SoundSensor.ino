  /*******************************************************************************
   * Project  : Woof woof                                                        *
   * Compiler : Arduino 1.0.2                                                    *
   * Board    : Arduino duemilanove                                              *
   * Shield   : Ethernet Shield                                                  *
   *          : DFRduino I/O Expansion Shield                                    *
   * Module   : Sound sensor                                                     *
   *          : RealTimeClock Module                                             *
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
  #define OUTPUT_FILE "Datalog.csv"
  
  File myFile;
  const int chipSelect = 4;
  RTC_DS1307 rtc;
  int i=0, a=0;
  int year0, month0, day0;
  int hour0, minute0, second0;
  
  char line[50];
   
  void setup()
  {
    Serial.begin(9600);  
    Wire.begin(); 
    rtc.begin();
    pinMode(4, OUTPUT); 
    
    if (!SD.begin(chipSelect)) 
    { 
      Serial.println("initialization failed!");
      return; 
    }
  }
  
  void loop()
  { 
    int sound_input = analogRead(ANALOG_IN);
    if(sound_input < LIMIT)
    {
      writing(sound_input);
    }
  }
  
  void writing(int input)
  {
    myFile = SD.open(OUTPUT_FILE, FILE_WRITE);
    
    if (myFile) 
    {
      DateTime now = rtc.now();
      sprintf(line, "%d/%d/%d,%d:%d:%d,%d", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second(), input);
      myFile.println(line);
      Serial.println(line);
      myFile.close();
    }
  }
  

