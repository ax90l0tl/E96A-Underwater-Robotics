#ifndef THRUSTER_ALLOCATOR_H
#define THRUSTER_ALLOCATOR_H
#include "Arduino.h"
#include "config.h"

#include "BasicLinearAlgebra.h"
#include "Geometry.h"

class Thruster_Allocator {
public:
  Thruster_Allocator();
private:
  BLA::Matrix<1, 3> COM;
  BLA::Matrix<MOTOR_COUNT, 3> motor_pos;
  BLA::Matrix<MOTOR_COUNT, 3> motor_orient;


};

#endif