# AVR Control Console

A hands-on mini-project for understanding and experimenting with the AVR ATMEGA328P microcontroller using raw C. This project demonstrates the practical use of key peripherals such as ADC, PWM, USART, TIMER, and provides a multi-control terminal for interacting with hardware features.

## Features

- **Multi-control terminal via USART**  
  Choose between several modes using a potentiometer and a button:
  1. Set LED Brightness (PWM control)
  2. Blink LED (with adjustable speed)
  3. Servo Control (positioned by potentiometer)
  4. Read Analog Voltage (voltmeter)
  5. Sleep Mode (reduce power usage)

- **Real-time interaction:**  
  The system responds to button presses and potentiometer adjustments for seamless user experience.

- **Status Codes:**  
  - `0` – No error  
  - `1` – Error encountered

## Technologies Used

- **Language:** C
- **Microcontroller:** AVR ATMEGA328P
- **Peripherals:** ADC, PWM, USART, TIMER
- **Toolchain:** avr-gcc
- **Makefile** for build automation

## Getting Started

### Prerequisites

- AVR toolchain (e.g., avr-gcc, avr-libc)
- Programmer compatible with ATMEGA328P (e.g., Arduino as ISP)
- Serial terminal emulator (for USART interaction)
- Basic external hardware: LED, servo, potentiometer, buttons

### Build and Flash

1. **Configure Makefile**

   Set your serial port and programmer type in `Makefile`:
   ```
   PORT = /dev/ttyUSB0
   PROGRAMMER = arduino
   MCU = atmega328p
   ```

2. **Build**
   ```sh
   make
   ```

3. **Flash to AVR**
   ```sh
   make upload
   ```

### Usage

- Connect your hardware as described in the code comments (see ADC, PWM, and USART modules).
- Use a button and potentiometer to select functions from the terminal menu.
- Follow printed instructions in the USART terminal for each mode.

#### Example Modes

- **Set LED Brightness:**  
  Adjust LED brightness in real-time with the potentiometer.
- **Blink LED:**  
  Change blink speed interactively.
- **Servo Control:**  
  Move a servo based on potentiometer position.
- **Read Analog Voltage:**  
  Use the onboard voltmeter functionality (ensure reference voltage is set in code).
- **Sleep Mode:**  
  Enter low-power state for energy saving.

## Customization

- **Reference Voltage:**  
  For accurate voltage readings, adjust `REF_VCC` and `VOLTAGE_DIV_FACTOR` in `ADC/adc.h` to match your hardware.

- **Pin Assignments:**  
  Modify pin macros in header files for your setup.

## Project Structure

- `main.c` – Entry point, mode selection logic
- `ADC/` – Analog-to-digital conversion
- `PWM/` – LED dimming & servo control
- `USART/` – Serial communication and terminal UI
- `timer/` – Timing and interrupts
- `sleep/` – Sleep mode routines
- `utils/` – Utility functions

## License

This project currently does not specify a license.

---
**Author:** [Paran-oid](https://github.com/Paran-oid)
