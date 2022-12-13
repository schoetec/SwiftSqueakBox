/*
MIT License

Copyright (c) 2022 schoetec

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/***************************************************
 * Swift Squeak Box
 * Code as used for version 2
 * ATTiny84-20PU
 * 
 * Author : Schoeters Kris
 * 
 */

/***************************************************
  DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html> 
 ***************************************************
 Used library for DFPlayer.
 
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

/*** Version 3 **/

// Port to attiny85/45 by Kris Schoeters

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

// ATMEL ATTINY85 / ARDUINO
//
//                           +-\/-+
//   (D 5)(RESET,ADC0) PB5  1|    |8  VCC
//   (D 3)      (ADC3) PB3  2|    |7  PB2 (ADC1)  (D 2)
//   (D 4)      (ADC2) PB4  3|    |6  PB1 (MISO)  (D 1)
//                     GND  4|    |5  PB0 (MOSI)  (D 0)
//                           +----+


#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

// mp3 RX , TX : 2 , 3
// atu RX , TX : 10, 11
// att RX , TX :  7, 6

// Arduino uno - attiny84
// pin 11 MOSI - 6 TX
// pin 10 PWM  - 7 RX

// Arduino uno - attiny85
// pin 11 MOSI - 0 TX
// pin 10 PWM  - 1 RX

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
int boot_happened = 0;

SoftwareSerial mySoftwareSerial(RX, TX); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
// constants won't change. They're used here to set pin numbers:
// Variables will change:
int currentState;    // the current reading from the input pin
bool pauseToggle = false;
int lastState = HIGH;
bool _blink = true;

int startPlayerInLoopAll() {
   // read the input on analog pin A0:
  int analogValue = analogRead(VolumeButton);
  // Rescale to potentiometer's voltage (from 0V to 5V):
  int volume = map(analogValue, 0, 1023, 0, 25);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
  myDFPlayer.enableLoopAll();  
}

void setup()
{

 
  delay(1000);

  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
  
  mySoftwareSerial.begin(9600);
 
  pinMode(BUSY,INPUT);
  pinMode(BOOT,OUTPUT);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true){
      delay(100); // Code to compatible with ESP8266 watch dog.
    }
  }
  //
  startPlayerInLoopAll();
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
        startPlayerInLoopAll();
        retryLoop=0;    
        delayLoop=0;
        boot_happened=1;
      }
    } else {
      retryLoop=0;    
    }
    delayLoop=0; 
  }   
  
  delay(10); 
}
