/*******************************************************************************
 * IO DEFINITION                                                                *
 *******************************************************************************/
#include <Encoder.h>

Encoder myEnc(2, 11); // Encoder pin

// PWM is connected to pin 3. /////
const int pinPwm = 3;         ///////
                              //////// ---->  Cytron Shild pins
// DIR is connected to pin 2. //////
const int pinDir = 8;         /////

int receivedChar; // The number of the new position by serial monitor

boolean newData = false; // It used for showNewData Function to send new data once you click send 

long oldPosition = -999;

int DIR; // direction - LOW or HIGH if statement

//boolean active = false;

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
    pinMode(pinPwm, OUTPUT);
    pinMode(pinDir, OUTPUT);
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

        DIR = LOW;
        digitalWrite(pinDir, DIR);
        Serial.println();

        accFubc();
    }

    //Deceleration if statement
    if (counter.newPosition >= (receivedChar - 8) && gDown == true && l_Dir == true) {

        dccFubc();

        Serial.println();

        h_Dir = false;
    }

    // ----------------------  HIGH DIR ------------------------------

       //Aeceleration if statement
    if (receivedChar && h_Dir == true && counter.newPosition > receivedChar) {

        DIR = HIGH;

        digitalWrite(pinDir, DIR);
        Serial.println();

        accFubc();
    }

    //Deceleration if statement
    if (counter.newPosition <= (receivedChar + 1) && h_Dir == true && gDown == true) {

        dccFubc();

        Serial.println();
        l_Dir = false;
    }
}

// The loop routine runs over and over again forever.
void loop()
{

    recvOneChar();
    showNewData();
    runMotor();
}

void recvOneChar()
{
    if (Serial.available() > 0) {
        receivedChar = Serial.parseInt();
        newData = true;
    }
}

void showNewData()
{
    if (newData == true) {

        newData = false;

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
    if (aSpeed >= 0) {
        aSpeed = aSpeed + 1;
        if (aSpeed >= 254) {
            aSpeed = 255;
            dSpeed = 255;
            gDown = true;
        }
        analogWrite(pinPwm, aSpeed);
    }
}

void dccFubc()  //Deceleration start function
{

    if (dSpeed >= 0) {
        dSpeed = dSpeed - 1;
        if (dSpeed <= 0) {
            dSpeed = 0;
            aSpeed = 0;
        }
        analogWrite(pinPwm, dSpeed);
    }
}

