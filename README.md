# Smart Home Control System

A C++ console application for managing smart home devices with user authentication, room management, energy tracking, and automation support.

---

## Features

- **Multi-device support** — Smart Lights, Thermostats, Security Cameras, Smart Locks, Smart Speakers
- **User authentication** — Login system with role-based access (admin / user / guest)
- **Room management** — Organize devices by room and view per-room status
- **Energy dashboard** — Track and log energy usage per device
- **Automation rules** — Create time/condition-based automation routines
- **Scheduling** — Schedule actions on supported devices
- **Session management** — Logout returns to login screen; data persists across sessions

---

## Project Structure

```
├── main.cpp          # Entry point, menus, and user interaction logic
├── SmartHome.h       # All class declarations
├── SmartHome.cpp     # Class implementations (if separate)
```

---

## Classes Overview

| Class | Description |
|---|---|
| `SmartHome` | Central hub managing all devices, rooms, users, energy logs, and automations |
| `SmartDevice` | Base class for all devices (toggle, restart, status) |
| `SmartLight` | Extends SmartDevice — brightness, color temp, hex color, sunset mode |
| `Thermostat` | Extends SmartDevice — temperature control, heat/cool/auto modes |
| `SecurityCamera` | Extends SmartDevice — recording, resolution settings |
| `SmartLock` | Extends SmartDevice — lock/unlock with code, access history |
| `SmartSpeaker` | Extends SmartDevice — volume, music, skills, connected services |
| `User` | Authentication, roles, password management |
| `Room` | Groups devices by location |
| `EnergyLog` | Records energy consumption per device |
| `Automation` | Condition-based rules that trigger device actions |
| `Schedulable` | Interface for devices that support scheduled actions |

---

## Default Devices on Startup

| ID | Device | Location |
|---|---|---|
| 1 | Living Room Light | Living Room |
| 2 | Kitchen Light | Kitchen |
| 3 | Bedroom Light | Bedroom |
| 4 | Main Thermostat | Living Room |
| 5 | Bedroom Thermostat | Bedroom |
| 6 | Front Door Camera | Entrance |
| 7 | Backyard Camera | Backyard |
| 8 | Front Door Lock | Entrance |
| 9 | Back Door Lock | Backyard |
| 10 | Living Room Speaker | Living Room |
| 11 | Kitchen Speaker | Kitchen |

---

## Default Users

| Username | Password | Role |
|---|---|---|
| `admin` | `Admin@123` | admin |
| `user` | `User@123` | user |

---

## Build & Run

### Compile

```bash
g++ -o app.exe *.cpp
```

With a separate include folder:

```bash
g++ -o app.exe *.cpp -I./include
```

### Run

```bash
./app.exe         # Linux / macOS
app.exe           # Windows
```

---

## Usage

### Login
The system prompts for a username and password on startup. After 3 failed attempts, you can choose to retry or exit. Logging out returns you to the login screen — all device data is preserved.

### Main Menu Options

```
1. View All Devices Status
2. Control a Device          ← enter device ID (1–11)
3. View All Rooms
4. View Energy Dashboard
5. Automations Panel
6. Turn ON/OFF All Devices
7. Restart a Device
8. Schedule an Action
9. User Management           ← admin only
0. Exit / Logout
```

### Controlling a Device
Select option `2` and enter the device ID. The system detects the device type and opens the appropriate sub-menu.

**SmartLight actions:** `setBrightness`, `setColor`, `dimToSunset`, `turn_on`, `turn_off`

**Thermostat actions:** `heat`, `cool`, `auto`, `turn_on`, `turn_off`

### Scheduling
Select option `8`, enter a device ID, provide a time in `HH:MM` format, and choose a valid action for that device type.

### Automations
Automations trigger based on conditions like `time`, `motion_detected`, `device_state`, or `temperature`. The default automation (`nightRoutine`) dims the living room light and sets the thermostat to auto at 22:00.

---

## Role Permissions

| Action | guest | user | admin |
|---|---|---|---|
| View device status | ✅ | ✅ | ✅ |
| Control devices | ❌ | ✅ | ✅ |
| Turn all ON/OFF | ❌ | ✅ | ✅ |
| Restart devices | ❌ | ✅ | ✅ |
| User management | ❌ | ❌ | ✅ |

---

## Requirements

- C++11 or later
- Any standard C++ compiler (g++, clang++, MSVC)
