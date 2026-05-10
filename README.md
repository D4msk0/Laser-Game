# Laser-Game
Little Game for Dots

ESP32 Lasergame ControllerA modular, non-blocking ESP32 controller designed for a lasergame installation. 
The system manages autonomous servo movements, a physical timer interface, and a wireless web monitor.

🚀 Features
- Modular Architecture: Logic is strictly separated into reusable classes (NetworkManager, RandomServo, Controller).
- Non-blocking Logic: Zero use of delay(), ensuring the system remains responsive to inputs at all times.
- Wireless Debugging: Real-time monitoring and remote control via WebSerial (accessible through any browser).
- Robust Physical Interface: Push-button control with software debouncing and state change detection.
- Auto-stop Timer: Programmable runtime (default: 15 min) with real-time status reporting.
- Granular Logging: Centralized Log Levels (0 = Off, 1 = System/Timer, 2 = Detailed Hardware Logs).

🛠 Hardware Setup
- Microcontroller: ESP32 (DevKit V1)
- Servo: Connected to GPIO 18 (Calibrated safe range: 12° - 170°).
- Push Button: GPIO 4 (Connected to GND, utilizes internal Pull-up).
- Power: External 5V supply recommended for servo stability.

📂 Project Structure
- src/main.cpp: Central orchestrator and application entry point.
- lib/NetworkManager: Handles WiFi connectivity and WebSerial initialization.
- lib/RandomServo: Manages random, jitter-free servo positioning within safe limits.
- lib/Controller: Manages global state (Start/Stop), physical button logic, and the countdown timer.
- include/secrets.h: Stores WiFi credentials (excluded from version control).

📡 Web Commands (via WebSerial)
- start: Manually trigger the 15-minute runtime.
- stop: Immediately halt the system and reset the timer.
- status: Returns the remaining time of the active session.

📅 Roadmap & Planning
Phase 1: Foundation (Completed ✅)
- Servo calibration and custom library development.
- WiFi & WebSerial integration for remote debugging.
- Modular Object-Oriented (OOP) refactor.
- Physical button implementation with 15-minute countdown logic.

Phase 2: Motion Expansion (Current Focus 🏗️)
- Stepper Motor Integration: Implement a slow-rotating axis (e.g., for a rotating target platform).
- Dual-Axis Movement: Add a second servo for 2D motion patterns.
- Dynamic Speed Control: Implement variable transition speeds for more organic movement.

Phase 3: Hardware Interface
- OLED Display: Add physical countdown visualization on the device.
- Status LEDs: Visual indicators for 'Standby', 'Active', and 'Time-out' states.
- WiFi Captive Portal: Configurable WiFi settings without reflashing secrets.h.