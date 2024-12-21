Project Title: IoT-Based Electrical Hazard Detection and Alert System
Introduction
Urban slum areas often face the severe risk of electrical hazards during heavy rainfall due to waterlogged streets and submerged electrical infrastructure. 
Accidental exposure to electric shocks caused by live currents in standing water poses a serious threat to life. This project presents an IoT-based solution to address this issue by creating a sensor-based device that monitors electrical voltage in water, provides real-time alerts, and ensures public safety.

Objective
To develop a low-cost, sensor-based IoT device that detects electrical hazards in waterlogged areas and alerts nearby residents in real-time, thus preventing accidents and saving lives.

System Architecture:
The proposed system consists of the following components:
1)Voltage Sensor (ZMPT101B):
The voltage sensor measures the presence of voltage/current in water. It is calibrated to detect even small electrical fluctuations and helps determine if standing water contains live currents.
2)Microcontroller (NodeMCU - ESP8266):
The NodeMCU serves as the processing unit for the system. It reads data from the voltage sensor, processes it, and triggers corresponding actions, such as alerting or sending notifications.
3)Alert Module:
The alert system consists of a buzzer module, which produces sound if hazardous voltage is detected in the water. This ensures that people nearby are instantly warned of the danger.
4)Ultrasonic Sensor (Optional):
Used to measure water depth in specific scenarios, providing additional context for when the device should activate based on the severity of waterlogging.
5)LCD Display (16x2 with I2C Module):
The display shows real-time voltage readings and hazard status. It provides a clear visual indication of whether the water is safe or not.
6)Power Supply:
The system is powered via a DC source or battery, ensuring consistent performance even during power outages.

Hardware Connections:
1. ZMPT101B Voltage Sensor
VCC → NodeMCU 3.3V
GND → NodeMCU GND
Output → NodeMCU A0 (Analog Pin)
2. LCD 16x2 with I2C Module
SDA → NodeMCU D2
SCL → NodeMCU D1
VCC → NodeMCU 3.3V
GND → NodeMCU GND
3. Buzzer
Positive Terminal → NodeMCU D5
Negative Terminal → NodeMCU GND
4. Ultrasonic Sensor (Optional)
VCC → NodeMCU 3.3V
GND → NodeMCU GND
Trigger Pin → NodeMCU D6
Echo Pin → NodeMCU D7
Software Implementation
Libraries Used:
Wire.h: For I2C communication with the LCD.
LiquidCrystal_I2C.h: To control the 16x2 LCD.
ESP8266WiFi.h: To enable Wi-Fi functionalities (if data logging or remote alerts are implemented).
Steps in Code:
Initialize all sensors and modules.
Continuously read voltage data from the ZMPT101B sensor.
Calculate RMS voltage to determine hazard levels.
Trigger alerts (buzzer + LCD display) if the voltage exceeds the safe threshold.
Log data to an IoT platform if remote monitoring is enabled.
Key Functions:
analogRead(): Reads voltage from the ZMPT101B.
lcd.print(): Displays voltage values and alerts on the LCD.
digitalWrite(): Activates the buzzer for sound alerts.
