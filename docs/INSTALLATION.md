# Installation Guide - ARCADE DMX Controller

## Requirements

- PlatformIO Core or VS Code Extension
- Python 3.6+
- USB-TTL adapter or ESP32-S2 Mini with USB port

## Hardware Setup

### 1. Display Connection

```
TFT ILI9341 → ESP32-S2 Mini
CS   → GPIO34
DC   → GPIO35
MOSI → GPIO32
MISO → GPIO37
CLK  → GPIO36
RST  → GPIO33
VCC  → 3.3V
GND  → GND
```

### 2. Touch Screen

```
XPT2046 → ESP32-S2 Mini
CS   → GPIO39
MOSI → GPIO11
MISO → GPIO9
CLK  → GPIO10
VCC  → 3.3V
GND  → GND
```

### 3. DMX Interface (MAX485)

```
MAX485 → ESP32-S2 Mini
DI   → GPIO4  (UART1_TX)
DE   → GPIO5  (Direction)
RO   → GND
A/B  → XLR-3 Pins
```

### 4. Buttons

```
Scene Buttons → ESP32-S2 Mini (with 10k pull-up to 3.3V)
Button 1 → GPIO13
Button 2 → GPIO14
Button 3 → GPIO38
Button 4 → GPIO41
Button 5 → GPIO42
```

## Software Installation

### 1. Install PlatformIO

```bash
# Using pip
pip install platformio

# Or VS Code Extension
# Install "PlatformIO IDE" from Extensions
```

### 2. Clone Repository

```bash
git clone https://github.com/shedafoxlis/arcade-dmx-controller.git
cd arcade-dmx-controller/firmware
```

### 3. Build Project

```bash
platformio run
```

### 4. Upload Firmware

```bash
# Ensure USB cable is connected
platformio run --target upload
```

### 5. Monitor Serial Output

```bash
platformio device monitor --baud 115200
```

## Troubleshooting

### Issue: Device not recognized

```bash
# List connected devices
platformio device list

# Set port in platformio.ini
[env:esp32-s2-mini]
upload_port = /dev/ttyUSB0  # Linux
# OR
upload_port = COM5          # Windows
```

### Issue: Memory errors

- Check SPIFFS is mounted
- Reduce Web UI size
- Check for memory leaks in effects

### Issue: DMX signal not working

- Verify MAX485 connection
- Check GPIO5 (DE) switching properly
- Use oscilloscope to check signal

## Next Steps

1. Access web interface: `http://<esp32-ip>/`
2. Configure scenes in web editor
3. Set up DMX device library
4. Test light output
