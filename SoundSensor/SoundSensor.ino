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
  #define TIME 1000
  #define OUTPUT_FILE "Datalog.csv"
  
  File myFile;
  const int chipSelect = 4;
  RTC_DS1307 rtc;
  
  int i=0, a=0, w=0;
  
  char line[50];
   
  void setup()
  {
    Serial.begin(9600);  
    Wire.begin(); 
    rtc.begin();
    pinMode(4, OUTPUT); 
     
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
      a = 1;
    }
    
    while(a==1)
    {
      /*-- Loop delay 10 seconds --*/
      for(int b=0; b < TIME; b++)
      {
        int input = analogRead(ANALOG_IN);
        if(input < LIMIT)
        {      
          return;
        }
        delay(10);
      }
      
      a=2;
    }
    
    while(a==2)
    {
      w++;
      writing(w); 
      delay(TIME);
      a=0;
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
      delay(TIME);
      myFile.close();
    }
  }
  

