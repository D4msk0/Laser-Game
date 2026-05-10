# Laser-Game
Little Game for Dots

ESP32 Lasergame Controller — A modular, non-blocking ESP32 controller designed for a lasergame installation.
The system manages autonomous servo and stepper motor movements, a physical timer interface, and a wireless web monitor.

## 🚀 Features
- **Modular Architecture:** Logic is strictly separated into reusable classes (NetworkManager, ServoMotor, StepperMotor, Controller).
- **Non-blocking Logic:** Zero use of delay(), ensuring the system remains responsive to inputs at all times.
- **Wireless Debugging:** Real-time monitoring and remote control via WebSerial (accessible through any browser).
- **Robust Physical Interface:** Push-button control with software debouncing and state change detection.
- **Auto-stop Timer:** Programmable runtime (default: 15 min) with real-time status reporting.
- **Granular Logging:** Runtime-configurable log levels (0 = Silent, 1 = Browser monitoring, 2 = Full debug).
- **Centralized Config:** All hardware pins and parameters defined in config.h — no digging through code.

## 🛠 Hardware Setup
- **Microcontroller:** ESP32 (DevKit V1)
- **Servo:** Connected to GPIO 18 (Calibrated safe range: 12° - 170°)
- **Stepper Motor:** 28BYJ-48 via ULN2003 driver, connected to GPIO 19, 21, 22, 23
- **Push Button:** GPIO 4 (Connected to GND, utilizes internal Pull-up)
- **Power:** External 5V supply recommended for servo and stepper stability

## 📂 Project Structure
- `src/main.cpp`: Central orchestrator and application entry point
- `include/config.h`: All hardware pins, parameters, and default debug level
- `include/secrets.h`: WiFi credentials (excluded from version control)
- `lib/NetworkManager`: Handles WiFi connectivity and WebSerial initialization
- `lib/ServoMotor`: Manages random, jitter-free servo positioning within safe limits
- `lib/StepperMotor`: Manages organic random sweep movements within a configurable range
- `lib/Controller`: Manages global state (Start/Stop), physical button logic, and the countdown timer

## 📡 Web Commands (via WebSerial)
| Command | Description |
|---|---|
| `start` | Start the session |
| `stop` | Stop the session |
| `status` | Show remaining session time |
| `debug status` | Show current debug level |
| `debug 0` | Silent — no logging |
| `debug 1` | Browser monitoring (WebSerial only) |
| `debug 2` | Full debug (WebSerial + Serial + hardware logs) |
| `help` | Show all available commands |

## 📅 Roadmap & Planning

### Phase 1: Foundation (Completed ✅)
- Servo calibration and custom library development
- WiFi & WebSerial integration for remote debugging
- Modular Object-Oriented (OOP) refactor
- Physical button implementation with 15-minute countdown logic

### Phase 2: Motion Expansion (Current Focus 🏗️)
- ✅ Stepper Motor Integration: 28BYJ-48 with organic random sweep behavior
- Dual-Axis Movement: Add a second servo for 2D motion patterns
- Dynamic Speed Control: Implement variable transition speeds for more organic movement

### Phase 3: Hardware Interface
- OLED Display: Add physical countdown visualization on the device
- Status LEDs: Visual indicators for 'Standby', 'Active', and 'Time-out' states
- WiFi Captive Portal: Configurable WiFi settings without reflashing secrets.h