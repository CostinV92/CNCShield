#include <CNCShield.h>

#define NO_OF_STEPS               200
#define SLEEP_BETWEEN_STEPS_MS    15

CNCShield cnc_shield;
StepperMotor *motor = cnc_shield.get_motor(0);

void setup()
{
  cnc_shield.begin();
  cnc_shield.enable();

  motor->set_dir(CLOCKWISE);
  for (int i = 0; i < NO_OF_STEPS; i++) {
    motor->step();
    delay(SLEEP_BETWEEN_STEPS_MS);
  }

  motor->set_dir(COUNTER);
  for (int i = 0; i < NO_OF_STEPS; i++) {
    motor->step();
    delay(SLEEP_BETWEEN_STEPS_MS);
  }

  cnc_shield.disable();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
