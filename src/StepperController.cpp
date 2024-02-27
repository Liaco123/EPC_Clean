#include "StepperController.h"

StepperController::StepperController(int stepPin, int dirPin, int acceleratePin, int deceleratePin) : stepper(AccelStepper::DRIVER, stepPin, dirPin)
{
    this->acceleratePin = acceleratePin;
    this->deceleratePin = deceleratePin;
}

void StepperController::setup(int targetSpeed)
{
    this->targetSpeed = targetSpeed;
    pinMode(acceleratePin, INPUT);
    pinMode(deceleratePin, INPUT);

    stepper.setMaxSpeed(10000);    // 设置最大速度为 1000 steps/s
    stepper.setAcceleration(5000); // 设置加速度为 500 steps/s^2
}

void StepperController::update()
{
    unsigned long currentTime = millis();

    // 每隔一段时间检查一次引脚状态
    if (currentTime - lastCheckTime >= interval)
    {
        if (digitalRead(acceleratePin) == LOW)
        {
            stepper.setSpeed(targetSpeed++); // 加速
        }
        else if (digitalRead(deceleratePin) == HIGH)
        {
            stepper.setSpeed(targetSpeed--); // 减速
        }
        else
        {
            stepper.setSpeed(targetSpeed); // 停止
        }

        stepper.runSpeed();
        Serial.println(targetSpeed);
        lastCheckTime = currentTime;
    }
}
