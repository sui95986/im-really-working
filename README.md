# 😴 im-really-working

A little ATTiny85 sketch for a Digispark board (or compatible) that makes your computer think you're working — by occasionally nudging the mouse pointer.
Perfect for taking that mid-workday nap you deserve. 💤

---

## Features

* Emulates a USB mouse using the [DigiMouse](https://github.com/digistump/DigistumpArduino/tree/master/digistump-avr/libraries/DigisparkMouse) library.
* Randomized delay between movements (about 4 minutes ± jitter).
* Smooth mouse movements instead of robotic jumps.
* Initial "wiggle" on startup to confirm it’s alive.

---

## Requirements

### Hardware

* Digispark ATTiny85 board (or clone).
* USB port to plug it into.

### Software

Make sure you have the following installed on your system:

* [Arduino CLI](https://arduino.github.io/arduino-cli/latest/installation/)
* Digistump AVR board definitions for `arduino-cli`
* [micronucleus](https://github.com/micronucleus/micronucleus) bootloader tool

**Install examples**

On **Arch Linux**:

```bash
sudo pacman -S arduino-cli
# micronucleus from AUR
yay -S micronucleus-git
```

On **Ubuntu / Debian**:

```bash
sudo apt update
sudo apt install arduino-cli micronucleus
```

On **macOS (Homebrew)**:

```bash
brew install arduino-cli
brew tap micronucleus/micronucleus || true
brew install micronucleus
```

> If `micronucleus` isn't available in your distribution's packages, follow the project README for building from source.

---

## Setup

### 1) Install Digistump board package

```bash
arduino-cli core update-index
arduino-cli core install digistump:avr
```

### 2) Clone this repo

```bash
git clone https://github.com/yourusername/im-really-working.git
cd im-really-working
```

### 3) Build the sketch

```bash
make build
```

This compiles `main/main.ino` for the Digispark ATTiny85 and writes outputs into `./build`.

### 4) Flash the device

1. Run:

```bash
make flash
```

The Makefile invokes `micronucleus --run build/main.ino.hex` so the hex is uploaded automatically.

If permission errors occur, either run the command with `sudo` or install the udev rule described below so you can flash as a normal user.

2. Plug your Digispark into USB. (If your board's bootloader only listens briefly on plug-in, plug it in when prompted by the tool.)

---

## Optional: udev rules (Linux)

To flash without `sudo` on Debian/Ubuntu/Arch, create a udev rule file and reload rules. Create `/etc/udev/rules.d/50-micronucleus.rules` with the contents below (you'll need `sudo` to write this file):

```text
# Micronucleus / Digispark
SUBSYSTEM=="usb", ATTR{idVendor}=="16d0", ATTR{idProduct}=="0753", MODE="0666", GROUP="plugdev"
```

Then run:

```bash
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Add your user to the `plugdev` group if needed (Debian/Ubuntu):

```bash
sudo usermod -aG plugdev $USER
# then log out and back in for group membership to apply
```

> Note: vendor/product IDs above are the common Digispark/micronucleus identifiers. Some clones use other IDs — if flashing still fails, run `lsusb` while the device is plugged to see the IDs and adjust the rule.

---

## File layout

```
.
├── build/             # compiled outputs (.hex, .elf, etc.)
├── main/              # sketch sources
│   ├── arduino.json   # Arduino CLI project config
│   └── main.ino       # mouse mover logic
└── Makefile           # helper targets for build/flash
```

---

## Usage

* Plug the Digispark ATTiny85 into your computer.
* The device will enumerate as a USB HID mouse.
* Every few minutes it will move the cursor slightly.
* Close your eyes and **let the productivity flow**. 😎

---

## Troubleshooting

* **`micronucleus` cannot open device / permission denied**: either run the flash command under `sudo` or add the udev rule and reload rules as shown above.
* **Device not detected by micronucleus**: unplug and replug the Digispark; some bootloaders only listen for a short time after plug-in. Try running `micronucleus --run build/main.ino.hex` and plug the device in when the tool asks.
* **Build fails, missing board**: confirm `digistump:avr` was installed with `arduino-cli core list`.

---

## Disclaimer

This code is for **educational purposes only**. Use responsibly — don’t get yourself in trouble at work!
