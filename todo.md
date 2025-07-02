# TODO

Here’s **exactly what your project (covering Chapters 1–11 of *Make: AVR Programming*) should be able to do** — not as a toy, but as a serious embedded training ground.

---

## 🎯 Project Title: **AVR Multi-Function Analog Control Station**

> Designed to **practice and demonstrate** all skills from Chapters 1–11 in one project — without needing sensors.

---

## ✅ Core Features (Mapped to Book Chapters)

| Feature                           | Description                                          | Book Chapter               |
| --------------------------------- | ---------------------------------------------------- | -------------------------- |
| 🟢 **LED Control**                | Basic on/off + dimming via PWM                       | Ch 2, 3, 9                 |
| 🧠 **Menu via USART**             | User interface for selecting modes                   | Ch 4                       |
| 🔘 **Button Input**               | Switch modes or confirm actions                      | Ch 5                       |
| 📈 **Analog Read + Oversampling** | Potentiometer as analog input                        | Ch 6, 11                   |
| ⚡ **Interrupts**                  | Buttons or ADC triggers using INT0                   | Ch 7                       |
| ⏱ **Timer-based LED Blink**       | Software-controlled blinking LED                     | Ch 8                       |
| 🎚 **Servo Control**              | Use PWM (Timer1) to move servo                       | Ch 10                      |
| 🌡 **ADC-Based Voltage Meter**    | Show current voltage via oversampled ADC             | Ch 6, 11                   |
| 💤 **Sleep Mode**                 | Idle in low power while waiting for input (optional) | Ch 11 (power-saving intro) |

---

## 🛠 What It Should Be Able to Do (Functions)

### 1. 🔲 **Show Menu via Serial**

* Output:

  ```
  === AVR Multi Control Station ===
  1) Set LED Brightness
  2) Blink LED
  3) Servo Control
  4) Read Analog Voltage
  5) Sleep Mode
  Choose option:
  ```
* Select using a button + potentiometer or USART input.

---

### 2. 💡 **LED Brightness Control**

* Potentiometer input → control LED brightness via PWM (Timer0 or Timer2).
* Print duty cycle and voltage used over USART.

---

### 3. 🔁 **Timer-Based Blinking**

* Use **Timer1 overflow interrupt** to blink an LED at user-defined intervals.
* Blink frequency set by potentiometer.

---

### 4. 🧭 **Servo Control**

* Move servo based on analog value (using Timer1 PWM).
* 0–180° mapping via ADC input (use oversampling for smoothness).

---

### 5. 🔍 **Voltage Meter**

* Use 16× oversampling to read voltage accurately from potentiometer.
* Print raw ADC, oversampled value, and calculated voltage via USART.

---

### 6. 🔔 **Interrupt Reaction**

* Use a button interrupt (INT0) to:

  * Wake from sleep
  * Trigger emergency stop
  * Or jump back to menu

---

### 7. 💤 **Sleep Mode (optional)**

* Enter ADC sleep mode or idle.
* Wake on button press or ADC complete interrupt.
* Print “Woke up!” when coming back to active mode.

---

## 🎯 Goals

| Objective                         | Status        |
| --------------------------------- | ------------- |
| Practice full **GPIO** control    | ✅             |
| Understand **PWM** (LED, servo)   | ✅             |
| Implement **USART** communication | ✅             |
| Apply **timers** effectively      | ✅             |
| Use **ADC** with oversampling     | ✅             |
| Handle **external interrupts**    | ✅             |
| Build state machine / menu logic  | ✅             |
| Optionally test **sleep & wake**  | ⚠️ (Optional) |

---

## ⚙️ Hardware Summary

* Potentiometer → ADC input
* LED → PWM output pin
* Servo (optional) → Timer1 PWM
* Button(s) → External Interrupt or polling
* USART (FTDI/USB-UART) → Serial monitor interface

---

## 🧱 Bonus Ideas (if you want to push further)

* Add EEPROM support to store user-selected mode (Ch 12)
* Implement automatic timeout → return to menu
* Add second LED or buzzer for feedback

---
