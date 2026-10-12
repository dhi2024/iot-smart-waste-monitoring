# IoT Smart Waste Monitoring System

A simulation-based IoT smart waste monitoring system designed to monitor bin fill levels, identify collection priority and send data to a cloud dashboard.

The project uses an ESP32 microcontroller, ultrasonic sensing, LCD output and ThingSpeak cloud monitoring to demonstrate how IoT technology can support more efficient waste collection.

## Project Overview

Traditional waste collection often relies on fixed schedules or manual inspection, which can lead to bins being collected when they are not full or overflowing before the next collection.

This project demonstrates a smart monitoring approach where each bin can report its current fill level and collection priority in real time.

## Technologies Used

- ESP32
- Wokwi
- HC-SR04 ultrasonic sensor
- 16x2 I2C LCD
- ThingSpeak
- Arduino/C++ style programming
- Wi-Fi connectivity

## Key Features

- Real-time bin fill-level monitoring
- Distance measurement using ultrasonic sensing
- Fill percentage calculation
- Bin status classification
- Collection priority assignment
- Battery-level monitoring
- Low-battery warning
- LCD status display
- Serial monitoring
- ThingSpeak cloud dashboard integration
- Office and community multi-bin simulation scenarios

## Fill-Level Logic

The simulated bin depth is 50 cm.

Fill percentage is calculated using:

Fill % = ((Bin Depth - Measured Distance) / Bin Depth) × 100

The result is restricted to a range between 0% and 100%.

### Bin Status

| Fill Level | Status |
|---|---|
| 0–49% | Available |
| 50–79% | Nearly Full |
| 80–100% | Full |

### Collection Priority

| Status | Priority |
|---|---|
| Available | LOW |
| Nearly Full | MEDIUM |
| Full | HIGH |

A low-battery warning is generated when battery level falls to 15% or below.

## Cloud Monitoring

ThingSpeak is used to store and visualise simulated IoT data.

The project currently uses the following fields:

- Field 1 – Fill Percentage
- Field 2 – Distance
- Field 3 – Battery Percentage
- Field 4 – Collection Priority

Data is transmitted approximately every 15–20 seconds during simulation.

## Simulation Scenarios

The system is designed to demonstrate multiple deployment scenarios.

### Office Environment

Example locations include:

- OFFICE-01 – Reception
- OFFICE-02 – Kitchen
- OFFICE-03 – Staff Area

### Community Environment

Multiple simulated community bins can also be monitored to demonstrate how collection teams could prioritise bins across a larger area.

## Testing

The project includes controlled testing across different simulated bin conditions including:

- Empty
- Half full
- Nearly full
- Full
- Low battery

The planned evaluation includes 30 controlled tests with a target detection accuracy of at least 90%.

## Future Improvements

Potential future development includes:

- Route optimisation
- Mobile notifications
- Predictive waste analysis
- Additional environmental sensors
- Improved battery and solar monitoring
- Multi-location dashboard integration
- Real-world hardware deployment

## Project Status

This project is currently being developed as part of a final-year Computing project.

The GitHub repository contains a portfolio version of the technical implementation and does not include the full academic submission.
