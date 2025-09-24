BOARD = digistump:avr:digispark-tiny
SKETCH = main
BUILD_DIR = build

all: build

build:
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD_DIR) $(SKETCH)

flash:
	micronucleus --run $(BUILD_DIR)/$(SKETCH).ino.hex
