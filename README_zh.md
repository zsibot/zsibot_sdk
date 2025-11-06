[English](README.md) | **中文** | [在线文档](https://zsibot.github.io/zsibot_sdk)

# ZsiBot SDK

欢迎使用 ZsiBot SDK！本仓库包含 ZsiBot 机器人平台（包括 ZSL-1 型号）的官方软件开发套件。它提供了一整套全面的工具、库和文档，旨在帮助您为机器人开发高级应用程序。

## 🌟 功能特性

本 SDK 提供高层和底层两种控制接口，让您能够灵活而强大地与机器人互动。

- **高层控制**：用简单的命令执行复杂动作。
  - `standUp()` / `lieDown()`: 基本姿态控制。
  - `move(vx, vy, yaw_rate)`: 向任意方向行走。
  - `jump()` / `frontJump()` / `backflip()`: 执行杂技动作。
  - `shakeHand()`: 执行预设的社交互动。
  - `attitudeControl(...)`: 微调机器人的身体姿态。
- **底层控制**：直接访问和控制单个电机。
  - `sendMotorCmd(...)`: 设置关节角度、速度和扭矩。
- **传感器数据访问**：获取机器人传感器的实时反馈。
  - `getQuaternion()` / `getRPY()`: 读取 IMU 方向数据。
  - `getBodyAcc()` / `getBodyGyro()`: 获取加速度计和陀螺仪读数。
  - `getMotorState()`: 访问详细的关节级数据（位置、速度、扭矩）。

## 🚀 快速入门

请按照以下步骤设置您的开发环境并运行附带的演示程序。

### 环境要求

- **操作系统**: Ubuntu 22.04
- **构建工具**: CMake 3.8+, GCC 11+
- **依赖库**: Eigen3, Boost
- **编程语言**: Python 3

### 安装与设置

1. **网络配置**: 将您的计算机连接到机器人的网络（Wi-Fi 或以太网）。机器人的默认 IP 地址为 `192.168.234.1` (Wi-Fi) 或 `192.168.168.168` (以太网)。详细说明请参阅[部署指南](docs/deploy.md)。

2. **机器人端设置**: 通过 SSH 登录到机器人，并将其配置为向您的计算机 IP 地址发送数据。完整步骤请参阅[部署指南](docs/deploy.md)。

3. **SDK 库**: C++ 和 Python 所需的共享库（`.so` 文件）已包含在 `lib/` 目录中，并按架构（`x86_64`, `aarch64`）分类存放。

### 运行演示程序

`demo/` 目录包含了 C++ 和 Python 的示例代码。

**C++ 演示:**

```bash
# 进入 C++ 演示目录
cd demo/zsl-1/cpp

# 创建构建目录
mkdir build && cd build

# 配置并编译项目
cmake ..
make -j6

# 运行演示程序
./highlevel_demo
```

**Python 演示:**

```bash
# 进入 Python 示例目录
cd demo/zsl-1/python/examples

# 运行高层控制演示
python3 highlevel_demo.py
```

## 📚 文档

有关更深入的信息，请参阅官方文���：

- **[API 参考](docs/api.md)**: 所有 SDK 函数的详细说明。
- **[部署指南](docs/deploy.md)**: 详尽的安装设置步骤。
- **[架构概览](docs/architecutre.md)**: 深入了解 SDK 的设计原理。

## 📁 仓库结构

```
.
├── demo/             # 演示应用程序 (C++ 和 Python)
├── docs/             # 详细的文档文件
├── include/          # SDK 的 C++ 头文件
└── lib/              # 针对不同架构的预编译库文件 (.so)
```
