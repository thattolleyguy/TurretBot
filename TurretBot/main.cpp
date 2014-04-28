#include <Arduino.h>
#include <Servo.h>
//#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_PWMServoDriver.h>

extern HardwareSerial Serial;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *panStepper = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *tiltStepper = AFMS.getStepper(200, 2);
Servo rackServo;

int pos = 0;
int tiltPin = 3;
int panPin = 2;
int style = INTERLEAVE;
int inputState = 0;

void setup() {
    AFMS.begin();
    tiltStepper->setSpeed(6);
    panStepper->setSpeed(6);
    rackServo.attach(10);
    rackServo.write(180);


    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        inputState = Serial.read();
        Serial.print("Changing input state to:");
        Serial.println(inputState);
        Serial.println(inputState & 2);

    }

    //Handle input state
    if ((inputState & 1) != 0) {
        Serial.println("Tilting Up");
        tiltStepper->onestep(FORWARD, style);
        // Tilt up
    }
    if ((inputState & 2) != 0) {
        Serial.println("Tilting Down");
        tiltStepper->onestep( BACKWARD, style);
        // Tilt down
    }
    if ((inputState & 4) != 0) {
        Serial.println("Panning Left");
        panStepper->onestep(FORWARD, style);
        // Pan left
    }
    if ((inputState & 8) != 0) {
        Serial.println("Panning Right");
        panStepper->onestep(BACKWARD, style);
        // Pan right
    }
    if ((inputState & 16) != 0) {
        Serial.println("Toggling Flywheel");
        // Toggle flywheel
    }
    if ((inputState & 32) != 0) {
        // Fire
        Serial.println("Firing");
        rackServo.write(0);
        delay(1000);
        rackServo.write(180);
        delay(1000);
    }

    delay(500);
}
