#ifndef StepperController_h
#define StepperController_h

#include <Arduino.h>
#include <AccelStepper.h>

class StepperController
{
public:
    int targetSpeed;
    StepperController(int stepPin, int dirPin, int acceleratePin, int deceleratePin);
    void setup(int targetSpeed);
    void update();

private:
    AccelStepper stepper;
    int acceleratePin;
    int deceleratePin;
    unsigned long lastCheckTime;
    const unsigned long interval = 100;
};

#endif
