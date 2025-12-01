# === Project Configuration ===
MCU = atmega328p
F_CPU = 16000000UL
BAUD = 115200

PROGRAMMER = arduino
PORT = /dev/ttyACM0

SRC = src/main.cpp
TARGET = main

# === Compiler and Flags ===
CXX = avr-g++
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -std=c++17 -Wall -fno-exceptions -fno-rtti
LDFLAGS = -mmcu=$(MCU)

# === Build Rules ===
all: $(TARGET).hex

$(TARGET).elf: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET).elf $(LDFLAGS)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i

clean:
	rm -f *.elf *.hex
