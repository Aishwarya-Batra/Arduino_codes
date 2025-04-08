#include <Arduino.h>
#include <math.h>
#include<Servo.h>


// Function to calculate theta_2(between the positive x axis and the point x,y)
double calculateTheta2(double x, double y) {
    return atan2(y, x);
}


// Function to calculate rotation matrix from theta_2
// rotation matrix 0_3
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
// (since the diagonal elements for x and y are -1, indicating a 180-degree rotation around those axes) while keeping the z-axis unchanged

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

// Function to calculate inverse matrix (simplified for this case)
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
    theta_5 = acos(rotMat[2][2]);
    theta_6 = acos(rotMat[2][0] / -sin(theta_5));
    theta_4 = acos(rotMat[1][2] / sin(theta_5));
}


void setup() {
    Serial.begin(115200);

    // pinMode(dir_pin,OUTPUT);
    // pinMode(step_pin,OUTPUT);

    // joint1.attach();
    // joint2.attach();
    // joint3.attach();

    double x = 4.0, y = 2.0;
    double theta_2 = calculateTheta2(x, y);
    Serial.print("Theta 2 = "); Serial.println(theta_2, 6);

    double rotMat_0_6[3][3] = {{-1.0, 0.0, 0.0},
                                { 0.0, -1.0, 0.0},
                                { 0.0,  0.0, 1.0}};
    
    double rotMat_0_3[3][3];
    calculateRotationMatrix(theta_2, rotMat_0_3);
    
    double invRotMat_0_3[3][3];
    inverseMatrix(rotMat_0_3, invRotMat_0_3);
    
    double rotMat_3_6[3][3];
    multiplyMatrices(invRotMat_0_3, rotMat_0_6, rotMat_3_6);
    
    Serial.println("rotMat_3_6:");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Serial.print(rotMat_3_6[i][j], 6);
            Serial.print(" ");
        }
        Serial.println();
    }
    
    double theta_5, theta_6, theta_4;
    calculateAngles(rotMat_3_6, theta_5, theta_6, theta_4);

    Serial.print("\nTheta 5 = ");
    Serial.println(theta_5, 6);
    Serial.print("Theta 6 = "); 
    Serial.println(theta_6, 6);
    Serial.print("Theta 4 = "); 
    Serial.println(theta_4, 6);
}

void loop() {
  // if (Serial.available() > 0) {  // Check if data is available
  //       String input = Serial.readStringUntil('\n');  // Read input
  //       input.trim();  // Remove any whitespace
  //       angle = input.toInt();  // Convert the entire string to an integer

  //       //Serial.print("Received value: ");
  //   } 
  // Serial.println(angle);



    
}
