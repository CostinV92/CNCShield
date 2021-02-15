#include <CNCShield.h>
#include <AccelStepper.h>

/*
 * Create a CNCShield object and get a pointer to motor 0 (X axis).
 */
CNCShield cnc_shield;
StepperMotor *motor = cnc_shield.get_motor(0);

/*
 * forwardstep() and backwardstep() needed by AccelStepper lib.
 */
void forwardstep()
{
  motor->step(CLOCKWISE);
}
void backwardstep()
{  
  motor->step(COUNTER);
}

/*
 * Create an AccelStepper object sending the above functions as parameters.
 */
AccelStepper stepper(forwardstep, backwardstep);

void setup()
{
  cnc_shield.begin();

  stepper.setMaxSpeed(50);  
  stepper.setSpeed(50);  
}

void loop()
{
  stepper.runSpeed();
}
