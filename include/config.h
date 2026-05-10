#ifndef CONFIG_H
#define CONFIG_H

// Debug levels:
// 0 = Off
// 1 = System / Timer logs
// 2 = Detailed hardware logs (Servo positions, Stepper steps, etc.)
#define DEBUG_LEVEL 2

// Controller
#define BUTTON_PIN 4
#define RUNTIME_MINUTES 15

// Servo
#define SERVO_PIN 18
#define SERVO_MIN_ANGLE 12
#define SERVO_MAX_ANGLE 170
#define SERVO_MIN_WAIT 200
#define SERVO_MAX_WAIT 2000

// Stepper Motor (28BYJ-48 via ULN2003)
#define STEPPER_PIN1 19
#define STEPPER_PIN2 21
#define STEPPER_PIN3 22
#define STEPPER_PIN4 23
#define STEPPER_SPEED 500
#define STEPPER_MAX_STEPS 2048 // Full rotation = 2048 steps for 28BYJ-48
#define STEPPER_SWEEP 1024     // Sweep range in steps (half rotation)

#endif