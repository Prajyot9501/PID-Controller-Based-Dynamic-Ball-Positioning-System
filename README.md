# PID Controller Based Dynamic Ball Positioning System

A feedback control system project for MECH 208 that dynamically positions a ball within a vertical transparent tube using fan-based airflow, PID control, and ultrasonic sensing.
<p align="center">
  <img src="https://github.com/user-attachments/assets/2d584cd8-58ad-4a5a-95bc-dfa7df9c5ee6" width="200" height="200">
</p>

---

## 🛠️ Project Overview

This project implements a **closed-loop control system** to position a lightweight ball inside a transparent tube. Two **PWM-controlled fans** at each end of the tube regulate airflow to move the ball vertically. A **HC-SR04 ultrasonic sensor** monitors the ball’s position in real time. The core logic is governed by a **PID controller** running on an **Arduino Mega 2560**, which adjusts the fan speeds based on the error between the desired and actual position.

A **potentiometer** serves as a user input to set the target position (setpoint) of the ball.

---

## ⚙️ System Architecture

### Key Components

- **Transparent Tube** – Constrained environment for ball motion.
- **Ball** – The controlled element.
- **Fans (x2, Noctua NF-A8 PWM)** – Actuators that generate airflow.
- **Ultrasonic Sensor (HC-SR04)** – Measures ball position.
- **Arduino Mega 2560** – Microcontroller that executes PID control logic.
- **Potentiometer** – Interface to adjust desired ball position.

### Functional Flow

1. User adjusts setpoint via potentiometer.
2. Ultrasonic sensor measures current ball position.
3. Arduino computes PID output based on position error.
4. Fan PWM signals are updated to drive the ball toward the setpoint.
5. System stabilizes when error falls within a tolerance range.

---

## 🔢 Control System Design

- **Controller:** PID (Proportional-Integral-Derivative)
- **Measured Variable:** Ball position (via ultrasonic sensor)
- **Controlled Variable:** Airflow intensity (fan speed)
- **Actuators:** Noctua NF-A8 PWM fans
- **Sensor Model:** Linear with minor noise
- **Actuator Model:** Assumed linear PWM-force response

### PID Tuning Parameters

```cpp
double Kp = 3.0;
double Ki = 5.0;
double Kd = 4.0;
```
---

### This project demonstrates fundamental principles of:

- Feedback control systems

- Sensor-actuator integration

- PID controller tuning

- Real-time embedded system design

- Applicable to robotics, automation, and process control domains

  ---

### Author:
Prajyot Patil

