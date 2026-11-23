

\# Adaptive Streetlight Automation



An embedded system project developed using the LPC2148 ARM7 microcontroller to automate streetlight operation based on ambient light intensity and predefined RTC schedules.



\## Project Overview



The system controls streetlight operation using:

\- LPC2148 microcontroller

\- LDR sensor for ambient light detection

\- ADC for analog sensor measurement

\- RTC for time-based scheduling

\- LCD for displaying time, date, and system information

\- Keypad for schedule configuration

\- External interrupt for user interaction



\## Features



\- Automatic streetlight control based on ambient light intensity

\- RTC-based ON/OFF scheduling

\- Support for schedules that cross midnight

\- LCD-based time and date display

\- Keypad-based schedule configuration

\- External interrupt-based menu access



\## Hardware and Software



\### Microcontroller

\- LPC2148 (ARM7)



\### Peripherals and Components

\- LDR sensor

\- ADC

\- RTC

\- LCD

\- Matrix keypad

\- LED output



\### Development Tools

\- Keil µVision

\- Proteus ISIS (simulation)



\## Project Structure



```text

Adaptive-Streetlight-Automation/

├── Adaptive-Streetlight-Automation\_with folders/

├── MINI\_PROJECT.uvproj

├── Startup.s

├── Hardware/

├── Simulation/

├── Documentation/

├── Images/

├── .gitignore

└── README.md

```



\## Working Principle



1\. The RTC provides the current time and date.

2\. The system checks whether the current time is within the configured operating schedule.

3\. When the schedule is active, the ADC reads the LDR sensor value.

4\. The measured light intensity is used to determine whether the streetlight should turn ON or OFF.

5\. The LCD displays the current time, date, and system status.

6\. The keypad and external interrupt allow the user to access schedule configuration.



\## RTC Battery Backup



The LPC2148 RTC supports battery-backed operation.



With an appropriate RTC backup supply or battery connected and operating correctly, the RTC can retain time while the main power supply is unavailable.



For normal battery-backed operation, startup code that resets the RTC to fixed testing values must be disabled after initial testing.



\## Build Verification



Firmware was rebuilt using Keil µVision.



\- Target microcontroller: LPC2148

\- Build errors: 0

\- Build warnings: 0

\- HEX file generation: Successful



\## Simulation and Hardware Results



Two separate output environments are maintained:



\### Proteus Simulation

Proteus ISIS simulation files and output screenshots will be added here.



\### Real Hardware Implementation

Photographs and output observations from the physical LPC2148 development kit will be added here.



\## Future Improvements



\- Improve LDR calibration

\- Add additional sensor-based control

\- Improve schedule configuration and validation

\- Enhance power efficiency



\## Author



Embedded Systems Project - Adaptive Streetlight Automation



