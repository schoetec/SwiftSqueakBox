
/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>
 
 ***************************************************
 This example shows the basic function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

 /*** Version 2 **/

// Port to attiny85/45 Kris Schoeters

// ATMEL ATTINY84 / ARDUINO
//
//                           +-\/-+
//                     VCC  1|    |14  GND
//             (D 10)  PB0  2|    |13  AREF (D  0)
//             (D  9)  PB1  3|    |12  PA1  (D  1) 
//                     PB3  4|    |11  PA2  (D  2) 
//  PWM  INT0  (D  8)  PB2  5|    |10  PA3  (D  3) 
//  PWM        (D  7)  PA7  6|    |9   PA4  (D  4) 
//  PWM        (D  6)  PA6  7|    |8   PA5  (D  5)        PWM
//                           +----+

// ATMEL ATTINY85/45 / ARDUINO
//
//                           +-\/-+
//   (D 5)(RESET,ADC0) PB5  1|    |8  VCC
//   (D 3)      (ADC3) PB3  2|    |7  PB2 (ADC1)  (D 2)
//   (D 4)      (ADC2) PB4  3|    |6  PB1 (MISO)  (D 1)
//                     GND  4|    |5  PB0 (MOSI)  (D 0)
//                           +----+


#include "Arduino.h"
//#include "SoftwareSerial.h"
#include "DFPlayer.h"
#include <SoftwareSerial.h>

// mp3 RX , TX : 2 , 3
// atu RX , TX : 10, 11
// att RX , TX :  7, 6

// Arduino uno - attiny84
// pin 11 MOSI - 11 TX
// pin 10 PWM  - 10 RX

// Arduino uno - attiny85/45
// pin 11 MOSI - 0 TX
// pin 10 PWM  - 1 RX

#define MP3_RX_PIN              0     //GPIO4/D2 to DFPlayer Mini TX
#define MP3_TX_PIN              1     //GPIO5/D1 to DFPlayer Mini RX
#define MP3_SERIAL_SPEED        9600  //DFPlayer Mini suport only 9600-baud
#define MP3_SERIAL_BUFFER_SIZE  32    //software serial buffer size in bytes, to send 8-bytes you need 11-bytes buffer (start byte+8-data bytes+parity-byte+stop-byte=11-bytes)
#define MP3_SERIAL_TIMEOUT      200   //average DFPlayer response timeout for YX5200, YX5300, JL AAxxxx chip 100msec..200msec

// Arduino uno pin A0=23 - ATtiny A0=0 [13]
int VolumeButton=1; // Volume
// Arduino uno pin 7 - attiny pin 2 [11]
//const int BUTTON_PIN = 2; // the number of the pushbutton pin
// Busy signal input
int BUSY = 3;
// Boot signal output
int BOOT = 4;
//
int delayLoop = 0; //Delays status check
int retryLoop = 0; //Ensure reboot is triggered after number of retry failures exceed.

boolean startFlag=false;

SoftwareSerial mySoftwareSerial =  SoftwareSerial(MP3_RX_PIN,MP3_TX_PIN); // RX, TX
DFPlayer myDFPlayer;

int startPlayerInLoopAll(bool reset) {
  int analogValue = analogRead(VolumeButton);
  // Rescale to potentiometer's voltage (from 0V to 5V):
  int volume = map(analogValue, 0, 1023, 5, 25);
  if(true == reset) {
    for(int i =0 ; i < volume ; i=i+1) {
        digitalWrite(BOOT, HIGH);
        delay(50);
        digitalWrite(BOOT, LOW);
        delay(70);
    }
  }
  myDFPlayer.setEQ(0);
  myDFPlayer.setVolume(volume);  //Set volume value. From 0 to 30
  myDFPlayer.repeatAll(true); 
  myDFPlayer.resume(); 
}

void setup()
{ 
  startFlag=false;
  pinMode(MP3_RX_PIN, INPUT);
  pinMode(MP3_TX_PIN, OUTPUT);
  
  mySoftwareSerial.begin(MP3_SERIAL_SPEED);
 
  pinMode(BUSY,INPUT);
  pinMode(BOOT,OUTPUT);
  digitalWrite(BOOT, LOW);

  //delay startup to prevent DFPlayer lockup 
  for(int i =0 ; i < 10 ; i=i+1) {
        digitalWrite(BOOT, HIGH);
        delay(20);
        digitalWrite(BOOT, LOW);
        delay(50);
  } 
  
  delay(500);
  //
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.stop();                             //if player was runing during ESP8266 reboot
  myDFPlayer.reset();                            //reset all setting to default
  myDFPlayer.setModel(DFPLAYER_MINI);
  myDFPlayer.setEQ(0); 
  myDFPlayer.setSource(2);  //1=USB-Disk, 2=TF-Card, 3=Aux, 4=Sleep, 5=NOR Flash
  startFlag = true; 
}

void loop()
{  
  
  if(startFlag) {
    startFlag=false;
    startPlayerInLoopAll(true);
  }
  
  // Reboot the mp3 player if busy signal is gone unexpected.
  delayLoop = delayLoop + 1;
  if(delayLoop == 1000) {
    int status = digitalRead(BUSY);
    if(status == HIGH) {
      retryLoop = retryLoop + 1;
      if(retryLoop == 2) { //BOOT
        digitalWrite(BOOT, HIGH);
        myDFPlayer.pause();
        delay(200);
        myDFPlayer.reset();
        delay(200);
        startPlayerInLoopAll(false);
        retryLoop=0;    
        delayLoop=0;
      }
    } else {
      retryLoop=0;    
    }
    delayLoop=0; 
  }   
  
  delay(10); 
}
