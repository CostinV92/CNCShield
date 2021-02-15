/* 
 * Lightweight library for the Arduino CNC Shield:
 * https://blog.protoneer.co.nz/arduino-cnc-shield
 *
 * Written by Victor Gabriel Costin.
 * Licensed under the MIT license.
 */

#ifndef __CNCSHIELD_H__
#define __CNCSHIELD_H__

typedef enum {
    COUNTER = 0,
    CLOCKWISE
} direction_t;

class CNCShield;

class StepperMotor {
private:
    direction_t     dir = COUNTER;
    int             speed = 0; /* steps per second */
    double          delay_between_steps = 0; /* ms */
    int             stp_pin;
    int             dir_pin;
    bool            was_init = false;

    StepperMotor(int _stp_pin = 0, int _dir_pin = 0);

    void            init();
    bool            is_init();

    int             get_stp_pin();
    void            set_stp_pin(int _stp_pin);

    int             get_dir_pin();
    void            set_dir_pin(int _dir_pin);

    void            _step();

public:
    bool            step();
    bool            step(direction_t _dir);
    bool            step(int no_of_steps);
    bool            step(int no_of_steps, direction_t _dir);

    direction_t     get_dir();
    void            set_dir(direction_t _dir);

    double          get_speed();
    void            set_speed(double _speed);

    friend class CNCShield;
};

class CNCShield {
private:
    int             enable_pin;
    StepperMotor    motors[3];

public:
    CNCShield();

    void            begin();
    void            enable();
    void            disable();

    StepperMotor*   get_motor(unsigned int motor_id);
};

#endif /* __CNCSHIELD_H__ */
