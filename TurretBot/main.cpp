#include <Arduino.h>
#include <AFMotor.h>

extern HardwareSerial Serial;
AF_Stepper panStepper(200, 2);
int direction=FORWARD;

void setup() {
    panStepper.setSpeed(30);
    Serial.begin(9600);

}
char input;
void loop() {
    panStepper.step(15,direction, SINGLE);
    if(Serial.available()>0)
    {
        input = Serial.read();
        if(input=='f')
        {
            Serial.write("Changing direction to forward");
            direction=FORWARD;
        }
        if(input=='r')
        {
            Serial.write("Changing direction to backward");
            direction=BACKWARD;
        }
    }
}