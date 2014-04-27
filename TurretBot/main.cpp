#include <Arduino.h>
#include <AFMotor.h>
#include <Servo.h>

extern HardwareSerial Serial;
//AF_Stepper panStepper(200, 2);
//AF_Stepper tiltStepper(200, 1);
//Servo rackServo;

int pos = 0;
int tiltPin = 3;
int panPin = 2;
int style = INTERLEAVE;
int inputState = 0;

void setup() {
    //    tiltStepper.setSpeed(1);
    //    panStepper.setSpeed(1);
    //    rackServo.attach(9);
    //    rackServo.write(10);


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
        //        tiltStepper.onestep(FORWARD,DOUBLE);
        // Tilt up
    }
    if ((inputState & 2) != 0) {
        Serial.println("Tilting Down");
        //        tiltStepper.onestep(BACKWARD,DOUBLE);
        // Tidelt down
    }
    if ((inputState & 4) != 0) {
        Serial.println("Panning Left");
        //        panStepper.onestep(FORWARD,DOUBLE);
        // Pan left
    }
    if ((inputState & 8) != 0) {
        Serial.println("Panning Right");
        //        panStepper.onestep(BACKWARD,DOUBLE);
        // Pan right
    }
    if ((inputState & 16) != 0) {
        Serial.println("Toggling Flywheel");
        // Toggle flywheel
    }
    if ((inputState & 32) != 0) {
        Serial.println("Firing");
        //        rackServo.write(160);
        //        rackServo.write(10);
        // Fire
    }

    delay(500);
}
