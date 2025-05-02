#include <PID_v1.h>
#include <NewPing.h>


#define TRIGGER_PIN 11 // Set to your Ultrasonic sensor's trigger pin
#define ECHO_PIN 12 // Set to your Ultrasonic sensor's echo pin
#define MAX_DISTANCE 200 // Maximum distance you want to measure (in cm)
#define POTENTIOMETER_PIN A0
#define FAN1_PWM_PIN 9
#define FAN2_PWM_PIN 10


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Ultrasonic sensor setup


double Setpoint, Input, Output;
double Kp = 3.0, Ki = 5.0, Kd = 4.0; // PID parameters


double PreviousSetpoint = 0; // To store the previous setpoint
bool FansOffDueToSetpoint = false; // To control the fan state based on setpoint achievement


PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setup() {
pinMode(FAN1_PWM_PIN, OUTPUT);
pinMode(FAN2_PWM_PIN, OUTPUT);


myPID.SetMode(AUTOMATIC);
myPID.SetOutputLimits(0, 255);


Serial.begin(9600); // Start serial communication at 9600 baud rate


PreviousSetpoint = Setpoint; // Initialize with the first setpoint
}


void loop() {
int potValue = analogRead(POTENTIOMETER_PIN);
if(potValue < 171) Setpoint = 10;
else if(potValue < 341) Setpoint = 20;
else if(potValue < 512) Setpoint = 30;
else if(potValue < 682) Setpoint = 40;
else if(potValue < 853) Setpoint = 50;
else Setpoint = 60;


// Check if setpoint has changed to reset the fan control
if (Setpoint != PreviousSetpoint) {
FansOffDueToSetpoint = false; // Reset the flag if the setpoint changes
PreviousSetpoint = Setpoint; // Update PreviousSetpoint to the new value
}


unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
Input = uS / US_ROUNDTRIP_CM; // Convert time into distance


Serial.print("Sensor Reading: ");
Serial.print(Input);
Serial.print(" cm, Setpoint: ");
Serial.println(Setpoint);


// If input is within the acceptable range of the setpoint and fans were previously turned off, do nothing
if ((Input > Setpoint - 2 && Input < Setpoint + 2) && !FansOffDueToSetpoint) {
analogWrite(FAN1_PWM_PIN, 0); // Stop fans to maintain current position
analogWrite(FAN2_PWM_PIN, 0);
FansOffDueToSetpoint = true; // Indicate fans are turned off after reaching setpoint
} else if (!FansOffDueToSetpoint) { // Only control fans if they haven't been turned off due to setpoint achievement
myPID.Compute();
analogWrite(FAN1_PWM_PIN, Output);
analogWrite(FAN2_PWM_PIN, 255 - Output);
}


delay(200); // Delay to make adjustments and readings more stable
}
