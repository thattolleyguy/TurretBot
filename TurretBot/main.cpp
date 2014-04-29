#include <Arduino.h>
#include <Servo.h>
//#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

extern HardwareSerial Serial;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *panStepper = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *tiltStepper = AFMS.getStepper(200, 2);
Servo rackServo;

int pos = 0;
int tiltPin = 3;
int panPin = 2;
int style = DOUBLE;
int inputState = 0;

void tiltUp() {
    tiltStepper->onestep(FORWARD, style);
}

void tiltDown() {
    tiltStepper->onestep(BACKWARD, style);
}

void panLeft() {
    panStepper->onestep(FORWARD, style);
}

void panRight() {
    panStepper->onestep(BACKWARD, style);
}
AccelStepper panAccelStepper(panRight, panLeft);
AccelStepper tiltAccelStepper(tiltUp, tiltDown);

void setup() {
    AFMS.begin();
    //    tiltStepper->setSpeed(4);
    //    panStepper->setSpeed(4);
    rackServo.attach(10);
    rackServo.write(180);
    panAccelStepper.setMaxSpeed(130.0);
    tiltAccelStepper.setMaxSpeed(130.0);
    panAccelStepper.setAcceleration(4.0);
    tiltAccelStepper.setAcceleration(4.0);


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
        tiltAccelStepper.move(10);
        // Tilt up
    } else if ((inputState & 2) != 0) {
        Serial.println("Tilting Down");
        tiltAccelStepper.move(-10);
        // Tilt down
    } else {
        tiltAccelStepper.move(0);
    }
    if ((inputState & 4) != 0) {
        Serial.println("Panning Left");
        panAccelStepper.move(10);
        // Pan left
    } else if ((inputState & 8) != 0) {
        Serial.println("Panning Right");
        panAccelStepper.move(-10);
        // Pan right
    } else {
        panAccelStepper.move(0);
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
    panAccelStepper.run();
    tiltAccelStepper.run();
}
