#include <hmi.h>
#include "SoftwareSerial.h"

/**
 *If you want to use SoftwareSerial to communicate with LCD touch screen, you need to modify the line in file hmi.h 
 * //#define HMI_SOFTWARE_SERIAL ---> #define HMI_SOFTWARE_SERIAL
 */
SoftwareSerial mySerial(3,2);
HMI myhmi(mySerial);

void setup()
{    
    Serial.begin(9600);
}
void loop()
{	
    if (myhmi.pictureEdit("p3",10) == 1)
       Serial.println("picture edit success");
    else 
       Serial.println("picture edit failure");
       
    if (myhmi.pageChange(0) == 1)
       Serial.println("page change success");
    else 
       Serial.println("page change failure");
    delay(2000);   //delaly 2 sconds ,for debug
    
    if (myhmi.cutPicture("q0",12) == 1)
       Serial.println("cut picture success");
    else 
       Serial.println("cut picture  failure");
    delay(2000);   //delaly 2 sconds ,for debug
    
    if(myhmi.textEdit("t3","13") == 1)
        Serial.println("text edit success");
    else 
        Serial.println("text edit failure");
    
    /* test progressBarEdit() */
    delay(2000);  //delaly 2 sconds ,for debug
    if (myhmi.pageChange(2) == 1)
        Serial.println("page change success");
    else 
        Serial.println("page change failure");
    if(myhmi.progressBarEdit("j0",10) == 1)
        Serial.println("progress bar edit success");
    else 
	Serial.println("progress bar edit failure");  	 
     while(1);      
}





