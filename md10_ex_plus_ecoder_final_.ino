/*******************************************************************************
 * IO DEFINITION                                                                *
 *******************************************************************************/
#include <Encoder.h>

Encoder myEnc(2, 11); // Encoder pin

const int IN1 = 7;
const int IN2 = 6;
const int ENA = 9;

long int receivedChar; // The number of the new position by serial monitor

long oldPosition = -999;

int DIR1; // direction - LOW or HIGH if statement

int DIR2; // direction - LOW or HIGH if statement

boolean l_Dir = false; // LOW if statement

boolean h_Dir = false; // HIGH if statement

int aSpeed = 0;   //Aceleration start value

int dSpeed = 255; //Dceleration start value

boolean gDown = false; // Deceleration if statement

/*******************************************************************************
 * FUNCTIONS                                                                    *
 *******************************************************************************/

// The setup routine runs once when you press reset.
void setup()
{

    Serial.begin(9600);
    Serial.setTimeout(10);
    // Initialize the PWM and DIR pins as digital outputs.
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
}

class MotorCounter { // OOP Class you could use it in many different places.
public:
    long oldPosition = -999;
    long newPosition = myEnc.read();
    counter()
    {

        if (newPosition != oldPosition) {
            oldPosition = newPosition;
        }
        return 0;
    }
}; //End of MotorCounter OOP 

void runMotor()
{

    MotorCounter counter; // First use of MotorCounter

    // ----------------------  LOW DIR ------------------------------
       //Aeceleration if statement
    if (receivedChar && l_Dir == true && counter.newPosition < receivedChar) {

        DIR1 = HIGH;
        DIR2 = LOW;
        digitalWrite(IN1, DIR1);
        digitalWrite(IN2, DIR2);

        accFubc();
    }

    //Deceleration if statement
    if (counter.newPosition >= (receivedChar) && gDown == true && l_Dir == true) {

        dccFubc();

        Serial.println("stop low");
        Serial.println(counter.newPosition);

        h_Dir = false;
    }

Serial.println(receivedChar);

    // ----------------------  HIGH DIR ------------------------------

       //Aeceleration if statement
    if (receivedChar && h_Dir == true && counter.newPosition > receivedChar) {
        DIR1 = LOW;
        DIR2 = HIGH;
        digitalWrite(IN1, DIR1);
        digitalWrite(IN2, DIR2);

        accFubc();
    }

    //Deceleration if statement
    if (counter.newPosition <= (receivedChar) && h_Dir == true && gDown == true) {

        dccFubc();

        Serial.println("stop high");
        Serial.println(counter.newPosition);
        l_Dir = false;
    }
}

// The loop routine runs over and over again forever.
void loop()
{

    recvOneChar();
    runMotor();
}

void recvOneChar()
{
    if (Serial.available() > 0) {
        int c = Serial.parseInt();
        if(c != 0){
          receivedChar = c;
          }
        MotorCounter counter2; // 2nd use of MotorCounter
        
        if (counter2.newPosition < receivedChar) { // LOW DIR
            l_Dir = true;
            h_Dir = false;
        }
        else if (counter2.newPosition > receivedChar) {  // HIGH DIR
            l_Dir = false;
            h_Dir = true;
        }
    }
}



void accFubc() //Aceleration start function
{
    while(aSpeed <= 254){
       analogWrite(ENA, aSpeed);
       Serial.println();
       Serial.println();
    aSpeed = aSpeed + 1;
    }
    gDown = true;
    dSpeed = 255;
}

void dccFubc()  //Deceleration start function
{

    while(dSpeed > 0){
       analogWrite(ENA, dSpeed);
       Serial.println();
      Serial.println();
     dSpeed = dSpeed -5;
    }
    gDown = false;
    aSpeed = 0;
}
