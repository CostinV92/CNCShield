/* 
 * Lightweight library for the Arduino CNC Shield:
 * https://blog.protoneer.co.nz/arduino-cnc-shield
 *
 * Written by Victor Gabriel Costin.
 * Licensed under the MIT license.
 */

#include "CNCShield.h"
#include "Arduino.h"

#define X_STP_PIN           2
#define Y_STP_PIN           3
#define Z_STP_PIN           4

#define X_DIR_PIN           5
#define Y_DIR_PIN           6
#define Z_DIR_PIN           7

#define SHIELD_EN_PIN       8

// #define DEBUG

CNCShield::CNCShield()
{
    motors[0].set_stp_pin(X_STP_PIN);
    motors[0].set_dir_pin(X_DIR_PIN);

    motors[1].set_stp_pin(Y_STP_PIN);
    motors[1].set_dir_pin(Y_DIR_PIN);

    motors[2].set_stp_pin(Z_STP_PIN);
    motors[2].set_dir_pin(Z_DIR_PIN);

    enable_pin = SHIELD_EN_PIN;
}

void CNCShield::begin()
{
    pinMode(enable_pin, OUTPUT);

    for (int i = 0; i < 3; i++) {
        motors[i].init();
    }
}

void CNCShield::enable()
{
    digitalWrite(SHIELD_EN_PIN, LOW);

#ifdef DEBUG
    Serial.println("CNCShield::enable()");
#endif /* DEBUG */
}

void CNCShield::disable()
{
    digitalWrite(SHIELD_EN_PIN, HIGH);

#ifdef DEBUG
    Serial.println("CNCShield::disable()");
#endif /* DEBUG */
}

StepperMotor* CNCShield::get_motor(unsigned int motor_id)
{
    StepperMotor *stepper = NULL;

    if (motor_id > 2)
        return &motors[2];

    return &motors[motor_id];
}

StepperMotor::StepperMotor(int _stp_pin, int _dir_pin):
    stp_pin(stp_pin), dir_pin(_dir_pin), dir(0) {}

void StepperMotor::init()
{
    pinMode(stp_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    was_init = true;
}

bool StepperMotor::is_init()
{
    return was_init;
}

int StepperMotor::get_stp_pin()
{
    return stp_pin;
}

void StepperMotor::set_stp_pin(int _stp_pin)
{
    stp_pin = _stp_pin;
}

int StepperMotor::get_dir_pin()
{
    return dir_pin;
}

void StepperMotor::set_dir_pin(int _dir_pin)
{
    dir_pin = _dir_pin;
}

bool StepperMotor::step()
{
    if (!is_init()) {
#ifdef DEBUG
        Serial.println("StepperMotor::step(): not init yet.");
#endif /* DEBUG */
        return false;
    }

    digitalWrite(stp_pin, HIGH);
    digitalWrite(stp_pin, LOW);

#ifdef DEBUG
    Serial.println("StepperMotor::step(): stepped.");
#endif /* DEBUG */

    return true;
}

direction_t StepperMotor::get_dir()
{
#ifdef DEBUG
    Serial.print("StepperMotor::get_dir(): dir: ");
    Serial.println(dir);
#endif /* DEBUG */

    return dir;
}

void StepperMotor::set_dir(direction_t _dir)
{
    if (_dir != dir) {
#ifdef DEBUG
        Serial.print("StepperMotor::set_dir(): dir changed from ");
        Serial.print(dir);
        Serial.print(" to ");
        Serial.println(_dir);
#endif /* DEBUG */
        dir = _dir;
        digitalWrite(dir_pin, dir);
    }
}
