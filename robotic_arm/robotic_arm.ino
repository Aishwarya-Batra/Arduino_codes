#include <Servo.h>  // Include the Servo library
#include <iostream>
#include <cmath>

using namespace std;

// Servo objects for each joint
Servo servo2, servo4, servo5, servo6; 

// Function to calculate theta_2
double calculateTheta2(double x, double y) {
    return atan2(y, x);
}

// Function to calculate rotation matrix from theta_2
void calculateRotationMatrix(double theta_2, double rotMat[3][3]) {
    rotMat[0][0] = -sin(theta_2);
    rotMat[0][1] = 0.0;
    rotMat[0][2] = cos(theta_2);
    rotMat[1][0] = cos(theta_2);
    rotMat[1][1] = 0.0;
    rotMat[1][2] = sin(theta_2);
    rotMat[2][0] = 0.0;
    rotMat[2][1] = 1.0;
    rotMat[2][2] = 0.0;
}

// Function to multiply two matrices
void multiplyMatrices(double mat1[3][3], double mat2[3][3], double result[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = 0.0;
            for (int k = 0; k < 3; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

// Function to calculate inverse of a matrix (simplified for this case)
void inverseMatrix(double mat[3][3], double invMat[3][3]) {
    invMat[0][0] = -mat[0][0];
    invMat[0][1] = 0.0;
    invMat[0][2] = mat[0][2];
    invMat[1][0] = mat[1][0];
    invMat[1][1] = 0.0;
    invMat[1][2] = mat[1][2];
    invMat[2][0] = 0.0;
    invMat[2][1] = 1.0;
    invMat[2][2] = 0.0;
}

// Function to calculate theta_5, theta_6, theta_4
void calculateAngles(double rotMat[3][3], double& theta_5, double& theta_6, double& theta_4) {
    theta_5 = acos(constrain(rotMat[2][2], -1, 1));  // Fix NaN error
    theta_6 = acos(constrain(rotMat[2][0] / -sin(theta_5), -1, 1));
    theta_4 = acos(constrain(rotMat[1][2] / sin(theta_5), -1, 1));
}

void setup() {
    Serial.begin(9600);  // Start serial communication

    // Attach servos to respective pins
    servo2.attach(9);   // Servo for theta_2
    servo4.attach(10);  // Servo for theta_4
    servo5.attach(11);  // Servo for theta_5
    servo6.attach(12);  // Servo for theta_6

    Serial.println("Enter x and y values separated by space (e.g., '4.0 2.0'):");
}

void loop() {
    if (Serial.available()) {  
        // Read user input from Serial Monitor
        double x, y;
        x = Serial.parseFloat();
        y = Serial.parseFloat();

        Serial.print("Received X = ");
        Serial.print(x);
        Serial.print(", Y = ");
        Serial.println(y);

        // Calculate theta_2
        double theta_2 = calculateTheta2(x, y);
        Serial.print("Theta 2 = ");
        Serial.println(theta_2);

        // Define target orientation matrix
        double rotMat_0_6[3][3] = {{-1.0, 0.0, 0.0},
                                   {0.0, -1.0, 0.0},
                                   {0.0, 0.0, 1.0}};

        // Calculate rotation matrix from theta_2
        double rotMat_0_3[3][3];
        calculateRotationMatrix(theta_2, rotMat_0_3);

        // Calculate inverse of rotMat_0_3
        double invRotMat_0_3[3][3];
        inverseMatrix(rotMat_0_3, invRotMat_0_3);

        // Calculate rotMat_3_6
        double rotMat_3_6[3][3];
        multiplyMatrices(invRotMat_0_3, rotMat_0_6, rotMat_3_6);

        Serial.println("rotMat_3_6:");
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                Serial.print(rotMat_3_6[i][j]);
                Serial.print(" ");
            }
            Serial.println();
        }

        // Calculate theta_5, theta_6, theta_4
        double theta_5, theta_6, theta_4;
        calculateAngles(rotMat_3_6, theta_5, theta_6, theta_4);

        Serial.print("\nTheta 5 = ");
        Serial.println(theta_5);
        Serial.print("Theta 6 = ");
        Serial.println(theta_6);
        Serial.print("Theta 4 = ");
        Serial.println(theta_4);

        // Convert radians to degrees
        int servoTheta2 = constrain(abs(theta_2 * 180.0 / M_PI), 0, 180);
        int servoTheta4 = constrain(abs(theta_4 * 180.0 / M_PI), 0, 180);
        int servoTheta5 = constrain(abs(theta_5 * 180.0 / M_PI), 0, 180);
        int servoTheta6 = constrain(abs(theta_6 * 180.0 / M_PI), 0, 180);

        // Move servos to computed positions
        servo2.write(servoTheta2);
        servo4.write(servoTheta4);
        servo5.write(servoTheta5);
        servo6.write(servoTheta6);

        Serial.println("\nServos moved to calculated angles.");
        Serial.println("Enter new x and y values:");
    }
}
