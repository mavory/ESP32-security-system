Documentation for the ESP32 RFID locking system!!

## Wiring

### RFID Reader (MFRC522)
- SDA (SS): GPIO 21
- SCK: GPIO 18
- MOSI: GPIO 23
- MISO: GPIO 19
- RST: GPIO 22
- 3.3V: 3.3V
- GND: GND

### Stepper Motor (ULN2003 Driver)
- IN1: GPIO 32
- IN2: GPIO 33
- IN3: GPIO 27
- IN4: GPIO 14
- VCC: 5V (External)
- GND: GND

### RGB LED Indicator
- Red: GPIO 25
- Green: GPIO 26
- Blue: GPIO 4
- GND: GND

### Buzzer
- Pin: GPIO 2
- GND: GND

---

## Technical Notes
- **Power:** The RFID module must be powered by 3.3V. Using 5V will damage the chip!
