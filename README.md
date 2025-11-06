**English** | [中文](README_zh.md) | [online docs](https://zsibot.github.io/zsibot_sdk/en)

# ZsiBot SDK

Welcome to the ZsiBot SDK! This repository contains the official Software Development Kit for ZsiBot robotic platforms, including the ZSL-1 model. It provides a comprehensive set of tools, libraries, and documentation to help you develop advanced applications for your robot.

## 🌟 Features

The SDK offers both high-level and low-level control interfaces, giving you flexible and powerful ways to interact with your robot.

- **High-Level Control**: Simple commands for complex actions.
  - `standUp()` / `lieDown()`: Basic stance control.
  - `move(vx, vy, yaw_rate)`: Walk in any direction.
  - `jump()` / `frontJump()` / `backflip()`: Perform acrobatic maneuvers.
  - `shakeHand()`: Execute pre-programmed social interactions.
  - `attitudeControl(...)`: Fine-tune the robot's body orientation.
- **Low-Level Control**: Direct access to individual motors.
  - `sendMotorCmd(...)`: Set joint angles, velocities, and torques.
- **Sensor Data Access**: Get real-time feedback from the robot's sensors.
  - `getQuaternion()` / `getRPY()`: Read IMU orientation data.
  - `getBodyAcc()` / `getBodyGyro()`: Get accelerometer and gyroscope readings.
  - `getMotorState()`: Access detailed joint-level data (position, velocity, torque).

## 🚀 Getting Started

Follow these steps to get your development environment set up and run the included demos.

### Prerequisites

- **OS**: Ubuntu 22.04
- **Build Tools**: CMake 3.8+, GCC 11+
- **Libraries**: Eigen3, Boost
- **Language**: Python 3

### Setup & Installation

1. **Network Configuration**: Connect your computer to the robot's network (Wi-Fi or Ethernet). The robot's default IP is `192.168.234.1` (Wi-Fi) or `192.168.168.168` (Ethernet). For detailed instructions, see the [Deployment Guide](docs/deploy.md).

2. **Robot-Side Setup**: SSH into the robot and configure it to send data to your computer's IP address. Full steps are in the [Deployment Guide](docs/deploy.md).

3. **SDK Libraries**: The required shared libraries (`.so` files) for both C++ and Python are included in the `lib/` directory, sorted by architecture (`x86_64`, `aarch64`).

### Running the Demos

The `demo/` directory contains examples for both C++ and Python.

**C++ Demo:**

```bash
# Navigate to the C++ demo directory
cd demo/zsl-1/cpp

# Create a build directory
mkdir build && cd build

# Configure and compile the project
cmake ..
make -j6

# Run the demo
./highlevel_demo
```

**Python Demo:**

```bash
# Navigate to the Python examples directory
cd demo/zsl-1/python/examples

# Run the high-level control demo
python3 highlevel_demo.py
```

## 📚 Documentation

For more in-depth information, please refer to the official documentation:

- **[API Reference](docs/api.md)**: Detailed descriptions of all SDK functions.
- **[Deployment Guide](docs/deploy.md)**: Step-by-step setup instructions.
- **[Architecture Overview](docs/architecutre.md)**: An inside look at how the SDK is designed.

## 📁 Repository Structure

```
.
├── demo/             # Demo applications (C++ and Python)
├── docs/             # Detailed documentation files
├── include/          # C++ header files for the SDK
└── lib/              # Pre-compiled library files (.so) for different architectures
```

---
