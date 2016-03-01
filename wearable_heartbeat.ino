#include "LedControlMS.h"
LedControl lc=LedControl(12,11,10,1);
unsigned long delaytime=100;


//  VARIABLES
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
int speaker = 2;                  // speaker on pin2 makes a beep with heartbeat


// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, must be seeded! 
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.


void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void heart_shape(char status)
{
    lc.setLed(0,3,5,status);
    lc.setLed(0,4,5,status);
    
    lc.setLed(0,5,6,status);
    lc.setLed(0,2,6,status);
    
    lc.setLed(0,6,6,status);
    lc.setLed(0,1,6,status);

    lc.setLed(0,7,5,status);    
    lc.setLed(0,0,5,status);    
    
    lc.setLed(0,7,4,status);    
    lc.setLed(0,0,4,status);   

    lc.setLed(0,6,3,status);    
    lc.setLed(0,1,3,status);     

    lc.setLed(0,5,2,status);    
    lc.setLed(0,2,2,status);  

    lc.setLed(0,3,1,status);
    lc.setLed(0,4,1,status);
}


void loop(){
  if (QS == true){                       // Quantified Self flag is true when arduino finds a heartbeat
        QS = false;                      // reset the Quantified Self flag for next time    
          heart_shape(true);
          Serial.println("heartbeat detected");
     }
  
  heart_shape(false);
  delay(10);
}







