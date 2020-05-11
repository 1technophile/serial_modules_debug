//  SerialIn_SerialOut_HM-1X
//  Uses hardware serial to talk to the host computer and AltSoftSerial for communication with the bluetooth module
//
//  What ever is entered in the serial monitor is sent to the connected device
//  Anything received from the connected device is copied to the serial monitor
//  Does not send line endings to the HM-10
//
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  Arduino D8 (SS RX) - BT TX no need voltage divider 
//  Arduino D9 (SS TX) - BT RX through a voltage divider (5v to 3.3v)
//
//  Initial sketch from http://www.martyncurrey.com/hm-10-bluetooth-4ble-modules/
//

// with an ESP8266
#define BT_RX 13 //D7 ESP8266 RX connect HM-10 or 11 TX
#define BT_TX 12 //D6 ESP8266 TX connect HM-10 or 11 RX

#include <SoftwareSerial.h>
SoftwareSerial softserial(BT_RX, BT_TX);
 
char c=' ';
boolean NL = true;
 
void setup() 
{
    Serial.begin(115200);
    softserial.begin(115200);  
    Serial.println("softserial started at 115200");
}
 
void loop()
{
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (softserial.available())
    {
        c = softserial.read();
        Serial.write(c);
    }
 
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
 
        // do not send line end characters to the HM-10
        if (c!=10 & c!=13 ) 
        {  
             softserial.write(c);
        }
 
        // Echo the user input to the main window. 
        // If there is a new line print the ">" character.
        if (NL) { Serial.print("\r\n>");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }
}
