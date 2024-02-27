#include <Arduino.h>
#include "StepperController.h"

// 定义步进电机连接的引脚
#define STEP_PIN 2
#define DIR_PIN 3
#define ACCELERATE_PIN 9  // 来自Arduino A的高速引脚
#define DECELERATE_PIN 10 // 来自Arduino A的低速引脚
#define ENABLE_PIN 13     // 来自Arduino 使能引脚

const unsigned int resolution = 3200;
const double rEncoder = 0.05;

StepperController stepperController(STEP_PIN, DIR_PIN, ACCELERATE_PIN, DECELERATE_PIN); // 创建 StepperController 实例
int speedTrans(double speed);

void setup()
{
  Serial.begin(9600);
  int targetSpeed = speedTrans(0.01);
  stepperController.setup(targetSpeed); // 设置目标速度
  pinMode(ENABLE_PIN, INPUT);
}

void loop()
{
  // Serial.print("当前速度：");
  // Serial.println(speedTrans(0.01));
  // int enable_state = digitalRead(ENABLE_PIN);
  // if (!enable_state)
  //   return;
  stepperController.update(); // 更新步进电机状态
}

int speedTrans(double speed)
{
  int targetspeed = resolution * speed / 2 / PI / rEncoder;
  return targetspeed;
}