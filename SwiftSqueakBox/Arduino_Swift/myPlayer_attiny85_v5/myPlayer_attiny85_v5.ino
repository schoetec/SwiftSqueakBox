
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
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

// mp3 RX , TX : 2 , 3
// atu RX , TX : 10, 11
// att RX , TX :  7, 6

// Arduino uno - attiny84
// pin 11 MOSI - 6 TX
// pin 10 PWM  - 7 RX

// Arduino uno - attiny85/45
// pin 11 MOSI - 0 TX
// pin 10 PWM  - 1 RX

//dfplayer (red led)
int RX=0;
int TX=1;
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

SoftwareSerial mySoftwareSerial(RX, TX); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int startPlayerInLoopAll(bool reset) {
   // read the input on analog pin A0:
  int analogValue = analogRead(VolumeButton);
  // Rescale to potentiometer's voltage (from 0V to 5V):
  int volume = map(analogValue, 0, 1023, 5, 25);
  if(true == reset) {
    for(int i =0 ; i < volume ; i=i+1) {
        digitalWrite(BOOT, HIGH);
        delay(200);
        digitalWrite(BOOT, LOW);
        delay(300);
    }
  }
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
  myDFPlayer.enableLoopAll();  
}

void setup()
{

 
  //delay(1000);

  //pinMode(RX,INPUT);
  //pinMode(TX,OUTPUT);
  
  mySoftwareSerial.begin(9600);
 
  pinMode(BUSY,INPUT);
  pinMode(BOOT,OUTPUT);
  digitalWrite(BOOT, LOW);

  //delay startup to prevent DFPlayer lockup 
  for(int i =0 ; i < 10 ; i=i+1) {
        digitalWrite(BOOT, HIGH);
        delay(100);
        digitalWrite(BOOT, LOW);
        delay(400);
  } 
  
  delay(1000);
  //
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    digitalWrite(BOOT, HIGH);
    while(true){
      delay(50); // Code to compatible with ESP8266 watch dog.
    }
  }

  digitalWrite(BOOT, LOW);
  //
  startPlayerInLoopAll(true);
}

void loop()
{  
  // Reboot the mp3 player if busy signal is gone unexpected.
  delayLoop = delayLoop + 1;
  if(delayLoop == 1000) {
    int status = digitalRead(BUSY);
    if(status == HIGH) {
      retryLoop = retryLoop + 1;
      if(retryLoop == 5) { //BOOT
        digitalWrite(BOOT, HIGH);
        myDFPlayer.pause();
        delay(1000);
        myDFPlayer.reset();
        delay(1000);
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
