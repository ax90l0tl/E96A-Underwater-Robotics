#include "Motor_Driver.h"
#include "Thruster_Allocator.h"
#include "config.h"


// Make sure to download the BasicLinearAlgebra Library from the Library manager
// Change this value to the number of motors you have
Motor_Driver* motor[MOTOR_COUNT];

void setup() {
  // Initialize Motors
  // change these numbers to the appropriate pins for each motor
  uint8_t motor_pin1[MOTOR_COUNT] = { 2, 3, 6, 7 };
  uint8_t motor_pin2[MOTOR_COUNT] = { 2, 3, 6, 7 };
  uint8_t motor_ena[MOTOR_COUNT] = { 2, 3, 6, 7 };
  for(uint8_t i; i < MOTOR_COUNT; i++){
    motor[i] = new Motor_Driver(motor_pin1[i], motor_pin2[i], motor_ena[i]);
  }
}

void loop() {
  float speed[MOTOR_COUNT] = {};
  for(uint8_t i; i < MOTOR_COUNT; i++){
    motor[i]->run(speed[i]);
  }
}
