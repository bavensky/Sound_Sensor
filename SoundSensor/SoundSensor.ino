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
  File myFile;
  const int chipSelect = 4;
  RTC_DS1307 rtc;
  int i=0;
  int year0,month0,day0;
  int hour0,minute0,second0;
  
  void setup()
  {
    Serial.begin(9600);  
    while (!Serial) {;}
    Wire.begin(); 
    rtc.begin();
    pinMode(4, OUTPUT); 
    if (!SD.begin(chipSelect)) 
    { Serial.println("initialization failed!"); return; }
    
    myFile = SD.open("Datalog.csv", FILE_WRITE);
    if (myFile) 
    {
      myFile.print("Date");
      myFile.print(",");
      myFile.print("Time");
      myFile.print(",");
      myFile.println("Woof");
      myFile.close();
    } 
  }
  
  void loop()
  {
    int man = analogRead(0);
    Serial.println(man);
    if(man < 500)
    {
      sdcard();
      Serial.println("Writing");
    }
  }
  
  void time()
  {
    DateTime now = rtc.now(); 
    year0 = now.year(); 
    month0 = now.month();   
    day0 = now.day();
    hour0 = now.hour(); 
    minute0 = now.minute(); 
    second0 = now.second();
    DateTime future (now.unixtime() + 7 * 86400L + 30); 
  }
  
  void sdcard()
  {
    time();
    //myFile = SD.open("Time.txt", FILE_WRITE);
    myFile = SD.open("Datalog.csv", FILE_WRITE);
    if (myFile) 
    {
      Serial.print("Writing to Datalog");
          
      myFile.print(day0);
      myFile.print("/");
      myFile.print(month0);
      myFile.print("/");
      myFile.print(year0);
      myFile.print(",");
      
      myFile.print(hour0);
      myFile.print(":");
      myFile.print(minute0);
      myFile.print(":");
      myFile.print(second0);
      myFile.print(",");
      
      i++;
      myFile.println(i);
      myFile.close();
    } 
    else 
    {
      Serial.println("error opening");
    }
    delay(1000);
  }


