#include "Motor_Driver.h"
#include "Thruster_Allocator.h"
#include "config.h"

// Make sure to download the BasicLinearAlgebra Library from the Library manager
// Change this value to the number of motors you have
Motor_Driver* motor[NUM_MOTORS];
Thruster_Allocator allocator;

void setup() {
  Serial.begin(115200);
  while(!Serial){
    delay(1);
  }
  // Initialize Motors
  // change these numbers to the appropriate pins for each motor
  uint8_t motor_pin1[NUM_MOTORS] = { 2, 3, 6, 7 };
  uint8_t motor_pin2[NUM_MOTORS] = { 2, 3, 6, 7 };
  uint8_t motor_ena[NUM_MOTORS] = { 2, 3, 6, 7 };
  for(uint8_t i; i < NUM_MOTORS; i++){
    motor[i] = new Motor_Driver(motor_pin1[i], motor_pin2[i], motor_ena[i]);
  }
  allocator = Thruster_Allocator();
  // 
  // EDIT these matrices, use whatever coordinate system you want but be consistent
  // 
  BLA::Matrix<3> COM = {0.0, 0.0, 0.0};
  BLA::Matrix<NUM_MOTORS, 3> thrusterLocations = {156,111,85,
                                                  156,-111,85,
                                                  -156,111,85,
                                                  -156,-111,85,
                                                  120,218,0,
                                                  120,-218,0,
                                                  -120,218,0,
                                                  -120,-218,0,
  };
  const float deg = 45.0;
  const float s = sin(deg * PI / 180.0);
  const float c = cos(deg * PI / 180.0);
  BLA::Matrix<NUM_MOTORS, 3> thrusterOrientations = {c,-s,0,
                                                    c,s,0,
                                                    -c,-s,0,
                                                    -c,s,0,
                                                    0,0,-1,
                                                    0,0,1,
                                                    0,0,1,
                                                    0,0,-1,
    };

  allocator.defineMatrix(COM, thrusterLocations, thrusterOrientations);
}

void loop() {
  float control_effort[6] = {1.0, 0.0, 0, 0.0, 0, 0};
  allocator.allocate(control_effort, false);
  for(uint8_t i = 0; i < NUM_MOTORS; i++){
    Serial.print(allocator.output[i], 3);
    Serial.print(" ");
    motor[i]->run(allocator.output[i]);
  }
  Serial.println();
}
