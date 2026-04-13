# --- Inställningar ---
# Namnet på slutprodukten (hamnar i source/output/)
TARGET          := source/output/gpio

# Kompilator för AVR
CC              := avr-gcc
OBJCOPY         := avr-objcopy

# Mikrokontroller (ATmega328p är standard för Arduino Uno)
MCU             := atmega328p

# Kompilatorflaggor
# -Iinclude : Säger åt kompilatorn att leta efter .h-filer i mappen "include"
CFLAGS          := -Wall -Werror -mmcu=$(MCU) -Os -Iinclude

# --- Källfiler ---
# Här letar vi i mappen "source" efter din .c-fil
SOURCE_FILES    := source/gpio.c main.c

# --- Mål (Targets) ---

# Standard: körs när du bara skriver 'make'
default: clean build

# Skapar mappen och bygger hex-filen
build:
	@mkdir -p source/output
	@$(CC) $(CFLAGS) $(SOURCE_FILES) -o $(TARGET).elf
	@$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex
	@echo "--------------------------------------"
	@echo "Bygget lyckades!"
	@echo "Hex-fil skapad: $(TARGET).hex"
	@echo "--------------------------------------"

# Laddar upp koden till Arduinon (kräver avrdude)
flash:
	@avrdude -p $(MCU) -c arduino -P /dev/ttyACM0 -b 115200 -U flash:w:$(TARGET).hex:i

# Rensar gamla byggfiler
clean:
	@rm -rf source/output
	@echo "Rensat!"