// Constants/Macros
#define MOTOR_STEPS 3200
#define RPM 30
#define MICROSTEPS 1
#define STEPS_FOR_90 1397

// Basic Pin Definitions for sensors and drivers
#define STEP 14
#define MOTOR_DIR_1 12
#define MOTOR_DIR_2 27
#define STEP1 26
#define WHITELED 25
#define RIGHTSENS 33
#define FRONTSENS 32
#define LEFTSENS 35
#define SCL 22
#define SDA 21
#define SERVOPWM 13

#define MOTOR_MAX_SPEED 5000
#define MOTOR_ACCELERATION 500

enum initOptions
{
    ACCELERATION,
    MAX_SPEED
};