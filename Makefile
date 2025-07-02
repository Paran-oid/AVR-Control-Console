MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
BAUD = 115200

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

# Source and target

TARGET = out/main
SRC = main.c USART/usart.c USART/output/output.c USART/input/input.c ADC/adc.c PWM/pwm.c utils/utils.c timer/timer.c sleep/sleep.c
INCLUDE = -IUSART -IUSART/input -IUSART/output -IADC -IPWM -Iutils -Itimer -Isleep -lm

#$@ = target file (main.elf), 
#$^ = all prerequisites (source files).
#$< = first prerequisite (main.elf)

# everything after : means it depends on x file/s

all: $(TARGET).hex

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload:
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex

clean:
	rm -rf *.o *.elf *.hex