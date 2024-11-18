#include "Arduino.h"
#include "Keyboard.h"

#define inPin6   6
#define inPin7   7

int counter = 0;
int timer[1001];
byte status[1001];
unsigned long startTime;
int maxcount = 1000; 
void setup() {
  delay(1000);
  pinMode(inPin6, INPUT_PULLUP);
  pinMode(inPin7, INPUT_PULLUP);
  Keyboard.begin();

  while (digitalRead(inPin6) == HIGH && digitalRead(inPin7)== HIGH) {
      //key is not Pressed
  }
  startTime     = micros();
  timer[counter]= micros() - startTime;   
  status[counter]=1;
  counter++;
}

void loop(){
   int pinState6 = digitalRead(inPin6);
   int pinState7 = digitalRead(inPin7);
   timer[counter]=micros()  - startTime;      
   if(counter < maxcount) {
     if(pinState6 == LOW || pinState7 == LOW)  {  //pin==LOW  => is closed (activated )
       status[counter]=1;
     } else {                                      //pin==HIGH => is open ( deactived )
       status[counter]=0; 
     }
   } else {
   //    Keyboard.println("Start");
         for(int x=0;x < maxcount; x++) {
            String message = String(timer[x])+";"+String(status[x]);
            Keyboard.println(message);                    
            delay(30);
         }
   //    Keyboard.println("Done"); 
         Keyboard.releaseAll();
         exit(0);
   }
   counter++;
}
