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
- `include/secrets.h`: WiFi credentials (excluded from version control — copy `secrets.h.template` and fill in your credentials)
- `lib/NetworkManager`: Handles WiFi connectivity and WebSerial initialization
- `lib/ServoMotor`: Manages random, jitter-free servo positioning within safe limits
- `lib/StepperMotor`: Manages organic random sweep movements within a configurable range
- `lib/Controller`: Manages global state (Start/Stop), physical button logic, and the countdown timer

## 🗺 Architecture

The diagrams below document the system architecture and runtime behavior of the Lasergame controller. Together they tell the full story: how the system is structured, what happens at boot, how the main loop keeps everything responsive, and how a WebSerial command travels from the browser to the hardware and back. The architecture is designed around three principles — modularity, non-blocking execution, and a clean separation between hardware logic and network output.

### High-level architecture
<img width="2500" height="1200" alt="lasergame_architecture_v3" src="https://github.com/user-attachments/assets/98930114-b121-4ba7-ac87-ca3233fa02c0" />

The system is built around strict separation of concerns. Each hardware component has its own class (ServoMotor, StepperMotor, Controller) with no knowledge of the network layer. Instead of calling WebSerial directly, classes expose a log callback that main.cpp wires up at boot. This keeps every class independently reusable and testable. All hardware pins and parameters live in config.h — no magic numbers anywhere in the code.

### Boot sequence
<img width="2500" height="1200" alt="lasergame_boot_sequence" src="https://github.com/user-attachments/assets/286638d6-f575-4a4d-9c5a-654b0513e991" />

setup() runs once and order matters. WiFi must be connected before WebSerial can initialize, and the message callback must be registered before the server starts. randomSeed() uses a floating ADC pin to ensure the servo and stepper generate a unique movement pattern every session. Log callbacks are wired last, just before the hardware is initialized — guaranteeing that any log output from begin() is already routed correctly.

### Runtime loop
<img width="2500" height="1200" alt="lasergame_runtime_loop" src="https://github.com/user-attachments/assets/f1321744-f488-4230-bdc2-1edaa8c62b18" />

loop() runs thousands of times per second and nothing in it ever blocks. Controller.update() always runs — it needs to catch button presses and check the timer regardless of system state. The isRunning() check is the single gate that controls all hardware: when the system is in standby, the servo and stepper are completely idle. When active, both update() methods are called every tick — they use internal timers to decide when to actually move, keeping the loop free at all times.

### WebSerial command flow
<img width="2500" height="1200" alt="lasergame_webserial_command_flow" src="https://github.com/user-attachments/assets/0a24645d-3e27-4d0a-bfee-78bc2aa7a5c4" />

Incoming messages are handled in two layers. handleWebMsg() in main.cpp owns the debug and help commands — these need access to debugLevel which lives in main.cpp. Everything else is forwarded to Controller.handleMessage(), which owns the hardware commands. Responses never go directly to WebSerial from inside a class — they always travel back through the log callback. This means the Controller has no dependency on the network layer and the routing logic stays in one place.

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
