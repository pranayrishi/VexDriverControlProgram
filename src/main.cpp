#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Intake               motor_group   1, 2            
// Catapult             motor         3
// LeftMotor            motor         4
// RightMotor           motor         5
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

// Define your motor ports
motor intakeMotor1 = motor(1, false);
motor intakeMotor2 = motor(2, false);
motor catapultMotor = motor(3, false);
motor_group intakeMotors = motor_group(intakeMotor1, intakeMotor2);
motor leftMotor(4, false);
motor rightMotor(5, false);
controller Controller1;

// Function prototypes
double getControllerAxis(int axis);
int mapJoystickToMotor(double joystickValue);
void setMotorSpeed(motor& motorObj, int speed);

int main() {
    // Set the velocity for the intake motor group
    intakeMotors.setVelocity(100, percent);  // Adjust the value (100) as needed

    // Set the velocity for the catapult motor
    catapultMotor.setVelocity(100, percent);  // Adjust the value (100) as needed

    while (true) {
        // Read joystick values for drive control
        double leftJoystickValue = getControllerAxis(3);  // Adjust the axis (3) as needed
        double rightJoystickValue = getControllerAxis(2); // Adjust the axis (2) as needed

        // Map joystick values to motor speeds for drive control
        int leftMotorSpeed = mapJoystickToMotor(leftJoystickValue);
        int rightMotorSpeed = mapJoystickToMotor(rightJoystickValue);

        // Set motor speeds for drive control
        setMotorSpeed(leftMotor, leftMotorSpeed);
        setMotorSpeed(rightMotor, rightMotorSpeed);

        // Read button values for intake and catapult control
        if (Controller1.ButtonUp.pressing()) {
            // Move the intake motor group forward
            intakeMotors.spin(forward);
            // Move the catapult motor forward
            catapultMotor.spin(forward);
        } else if (Controller1.ButtonDown.pressing()) {
            // Move the intake motor group backward
            intakeMotors.spin(reverse);
            // Stop the catapult motor (preventing reverse movement)
            catapultMotor.stop(brakeType::brake);
        } else {
            // If no button is pressed, stop both motor groups
            intakeMotors.stop();
            catapultMotor.stop(brakeType::brake);
        }

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }

    return 0;
}

// Function to get joystick axis value from the controller
double getControllerAxis(int axis) {
    return Controller1.AxisValue(axis);
}

// Function to map joystick values to motor speeds
int mapJoystickToMotor(double joystickValue) {
    return static_cast<int>(joystickValue); // Convert double to int if needed
}

// Function to set motor speed
void setMotorSpeed(motor& motorObj, int speed) {
    motorObj.setVelocity(speed, percent);
    motorObj.spin(forward);
}
