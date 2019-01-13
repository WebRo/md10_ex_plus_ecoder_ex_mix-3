
/*******************************************************************************
 * IO DEFINITION                                                                *
 *******************************************************************************/

#include <Encoder.h>
Encoder myEnc(2,11);

// PWM is connected to pin 3.
const int pinPwm = 3;

// DIR is connected to pin 2.
const int pinDir = 8;






/*******************************************************************************
 * FUNCTIONS                                                                    *
 *******************************************************************************/

// The setup routine runs once when you press reset.
void setup() { 

  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  // Initialize the PWM and DIR pins as digital outputs.
  pinMode(pinPwm, OUTPUT);
  pinMode(pinDir, OUTPUT);

}
int a = 1;
int b = 0;
int c = 0;
int d = 0;

long oldPosition  = -999;


// The loop routine runs over and over again forever.
void loop() {

  //class Motor {
 
   //   public:
         
        //Motor(int DIR, int VAL, int SPEED){
           
           long newPosition = myEnc.read();
           if (newPosition != oldPosition) {
           oldPosition = newPosition;
           //Serial.println(newPosition);
          // Aactive = active; 
        }

                  // ----------------------  A ------------------------------

                   if(1500 >= newPosition && a == 1 && b == 0){
                    analogWrite(pinPwm, 150);
                    digitalWrite(pinDir, LOW);
                     Serial.println(newPosition);
                     //Serial.println("TEST");
                     if(newPosition >= (1500 - 8)){
                      analogWrite(pinPwm, 0);
                        Serial.println("FINISHED 1");
                        a = 0;
                        b = 1;
                        delay(3000);
                      }
                    }
              

                  // ----------------------  B ------------------------------

                   if(500 <= newPosition && a == 0 && b == 1){
                    analogWrite(pinPwm, 150);
                    digitalWrite(pinDir, HIGH);
                     Serial.println(newPosition);
                     //Serial.println("TEST");
                     if(newPosition <= (500 + 6)){
                      analogWrite(pinPwm, 0);
                        Serial.println("FINISHED 2");
                        b = 0;
                        c = 1;
                        delay(3000);
                      }
                    }
                    
                  // ----------------------  C ------------------------------

                   if(3000 >= newPosition && c == 1){
                    analogWrite(pinPwm, 255);
                    digitalWrite(pinDir, LOW);
                     Serial.println(newPosition);
                     //Serial.println("TEST");
                     if(newPosition >= (3000 - 10)){
                      analogWrite(pinPwm, 0);
                        Serial.println("FINISHED 3");
                        a = 0;
                        b = 0;
                        c = 0;
                        d = 1;
                        delay(3000);
                      }
                    }
 
                  // ----------------------  D ------------------------------
    
        
                   if(-2000 <= newPosition && d == 1){
                    analogWrite(pinPwm, 200);
                    digitalWrite(pinDir, HIGH);
                     Serial.println(newPosition);
                     //Serial.println("TEST");
                     if(newPosition <= (-2000 + 10)){
                      analogWrite(pinPwm, 0);
                        Serial.println("FINISHED 4");
                        a = 0;
                        b = 0;
                        c = 0;
                        d = 0;
                        delay(3000);
                      }
                    }
   


       


         // Motor action1(LOW, 15000, 255);
           

         
  

 
 

}
