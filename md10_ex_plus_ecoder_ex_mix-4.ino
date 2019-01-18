
/*******************************************************************************
 * IO DEFINITION                                                                *
 *******************************************************************************/

#include <Encoder.h>
Encoder myEnc(2, 11);

// PWM is connected to pin 3.
const int pinPwm = 3;

// DIR is connected to pin 2.
const int pinDir = 8;

int receivedChar;
boolean newData = false;

/*******************************************************************************
 * FUNCTIONS                                                                    *
 *******************************************************************************/

// The setup routine runs once when you press reset.
void setup()
{

    Serial.begin(9600);
    Serial.setTimeout(10);
    //Serial.println("Basic Encoder Test:");
    // Initialize the PWM and DIR pins as digital outputs.
    pinMode(pinPwm, OUTPUT);
    pinMode(pinDir, OUTPUT);

    //Serial.println("<Enter the the steps Nr.>");
}

long oldPosition = -999;

int DIR;

boolean active = false;

void runMotor()
{

    long newPosition = myEnc.read();
    if (newPosition != oldPosition) {
        oldPosition = newPosition;
    }

    // ----------------------  A ------------------------------

    if (receivedChar && active == true && newPosition < receivedChar) {

        DIR = LOW;

        analogWrite(pinPwm, 150);
        digitalWrite(pinDir, DIR);
        Serial.println(newPosition);
        Serial.println(receivedChar);
        if (newPosition >= (receivedChar - 8)) {
            analogWrite(pinPwm, 0);
            Serial.println("FINISHED A");
            active = false;
            //delay(3000);
        }
    }

    // ----------------------  B ------------------------------

    if (receivedChar && active == true && newPosition > receivedChar) {

        DIR = HIGH;

        analogWrite(pinPwm, 150);
        digitalWrite(pinDir, DIR);
        Serial.println(newPosition);
        Serial.println(receivedChar);
        if (newPosition <= (receivedChar + 8)) {
            analogWrite(pinPwm, 0);
            Serial.println("FINISHED B");
            active = false;
            //delay(3000);
        }
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
        active = true;
    }
}

void showNewData()
{
    if (newData == true) {

        newData = false;
    }
}

