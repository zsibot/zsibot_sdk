# Zsibot SDK API Definition

## 1. ZsibotExecutor Class Introduction

**class ZsibotExecutor**

This class is the main interface class for communicating with Zsibot devices, providing methods to control the device and obtain device status.

---

### 1.1 Constructor

**Function Prototype**
```cpp
ZsibotExecutor(send_ip, send_port, recv_port)
```

**Function Overview**
Constructor, initialize Zsibot executor

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|----------|
| send_ip | - | IP address for sending data | Required | - |
| send_port | - | Port number for sending data | Required | - |
| recv_port | - | Port number for receiving data | Required | - |

**Return Value**
None

**Remarks**
Initialize network connection parameters

---

### 1.2 Destructor

**Function Prototype**
```cpp
~ZsibotExecutor()
```

**Function Overview**
Destructor, clean up resources

**Parameter Description**

None

**Return Value**
None

**Remarks**
Clean up network connection and other resources

---

### 1.3 Initialize Robot

**Function Prototype**
```cpp
initRobot(self_ip, self_port, robot_ip="192.168.234.1")
```

**Function Overview**
Establish communication connection with the robot

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|----------|
| self_ip | string | Local IP address | Required | - |
| self_port | int | Local port number | Required | - |
| robot_ip | string | Robot IP address | Optional | Default "192.168.234.1" |

**Return Value**
None

**Remarks**
Communication failure will output error log to terminal

---

### 1.4 Check Connection

**Function Prototype**
```cpp
checkConnect()
```

**Function Overview**
Check robot connection status

**Parameter Description**

None

**Return Value Type: bool**

| Return Value | Description |
|------|------|
| true | Connection normal |
| false | Connection failed |

**Remarks**
Can be used as heartbeat detection

---

### 1.5 Stand Up

**Function Prototype**
```cpp
standUP()
```

**Function Overview**
Control the robot to stand up

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Robot stands normally, cannot directly enter this state during movement

---

### 1.6 Lie Down

**Function Prototype**
```cpp
lieDown()
```

**Function Overview**
Control the robot to lie down

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Robot lies down with joints locked, cannot directly enter this state during movement

---

### 1.7 Passive

**Function Prototype**
```cpp
passive()
```

**Function Overview**
Control the robot to lie down in emergency

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Robot enters passive state and lies down

---

### 1.8 Move

**Function Prototype**
```cpp
move(vx, vy, yaw_rate)
```

**Function Overview**
Control robot movement

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|-----------|
| vx | float | Forward speed | Required | When not moving, 0 needs to be passed in, range (-3m/s ~ -0.05m/s; 0.05m/s ~ 3m/s) |
| vy | float | Lateral speed | Required | When not moving, 0 needs to be passed in, range (-1.0m/s ~ -0.1m/s;0.1m/s ~ 1.0m/s) |
| yaw_rate | float | Angular velocity around Z-axis | Required | When not moving, 0 needs to be passed in, range (-3.0rad/s ~ -0.02rad/s;0.02rad/s ~ 3.0rad/s) |

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Only enter when the robot is standing, control the robot to move at the specified speed.

---

### 1.9 Jump

**Function Prototype**
```cpp
jump()
```

**Function Overview**
Control the robot to jump vertically

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Only enter when standing, cannot switch state during movement

---

### 1.10 Front Jump

**Function Prototype**
```cpp
frontJump()
```

**Function Overview**
Control the robot to jump forward

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Only enter when standing, cannot switch state during movement

---

### 1.11 Backflip

**Function Prototype**
```cpp
backflip()
```

**Function Overview**
Control the robot to perform a backflip

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Only enter when standing, cannot switch state during movement
This special function is designed for special scenarios such as media presentation and product demonstration.
**Frequent use of this function will significantly accelerate the wear of core components such as motors and joints, which may cause product performance degradation or shortened service life.**
Please use with caution.

---

### 1.12 Shake Hand

**Function Prototype**
```cpp
shakeHand()
```

**Function Overview**
Control the robot to shake hands

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Only enter when standing, cannot switch state during movement
This special function is designed for special scenarios such as media presentation and product demonstration.
**Frequent use of this function will significantly accelerate the wear of core components such as motors and joints, which may cause product performance degradation or shortened service life.**
Please use with caution.

---

### 1.13 Two-Leg Stand

**Function Prototype**
```cpp
twoLegStand(vx, yaw_rate)
```

**Function Overview**
Control the robot to stand on two legs

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|---------|
| vx | float | Forward speed | Required | Pass in 0 when not moving, range (-0.5~-0.2 / 0.2~0.5m / s) |
| yaw_rate | float | Angular velocity around Z-axis | Required | Pass in 0 when not moving, range (-1~-0.2 / 0.2~1.0rad / s) |

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Only enter when standing, cannot enter this state during movement
To exit two-leg stand state, call cancelTwoLegStand(), does not respond to other interfaces
Movement can be controlled through parameters at the specified speed.
This special function is designed for special scenarios such as media presentation and product demonstration.
**Frequent use of this function will significantly accelerate the wear of core components such as motors and joints, which may cause product performance degradation or shortened service life.**
Please use with caution.

---

### 1.14 Exit Two-Leg Stand

**Function Prototype**
```cpp
cancelTwoLegStand()
```

**Function Overview**
Control the robot to exit two-leg stand

**Parameter Description**

None

**Return Value**
None

**Remarks**
Robot exits two-leg stand state, entered when robot is in two-leg stand state

---

### 1.15 Attitude Control

**Function Prototype**
```cpp
attitudeControl(roll_vel, pitch_vel, yaw_vel, height_vel)
```

**Function Overview**
Control the robot to twist in place and change body height

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|---------|
| roll_vel | float | Angular velocity around X-axis | Required | Pass in 0 when not controlling, range (-0.5rad/s~0.5rad/s) |
| pitch_vel | float | Angular velocity around Y-axis | Required | Pass in 0 when not controlling, range (-0.5rad/s~0.5rad/s) |
| yaw_vel | float | Angular velocity around Z-axis | Required | Pass in 0 when not controlling, range (-0.5rad/s~0.5rad/s) |
| height_vel | float | Vertical height velocity | Required | Pass in 0 when not controlling, range (-0.5m/s-0.5m/s) |

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Enter when robot is standing, control the robot to twist in place and change body height at the specified speed.

---

### 1.16 Get Attitude Quaternion

**Function Prototype**
```cpp
getQuaternion()
```

**Function Overview**
Get the current attitude quaternion of the robot

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [w, x, y, z] | Vector containing 4 elements, corresponding to the four components of the quaternion respectively |

**Remarks**
Robot forward is X, left is Y, vertical upward is Z

---

### 1.17 Get Attitude Euler Angles

**Function Prototype**
```cpp
getRPY()
```

**Function Overview**
Get the Euler angles (roll, pitch, yaw) of the current attitude of the robot

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [roll, pitch, yaw] | Vector containing 3 elements, unit is radians (rad), corresponding to the rotation angles around X, Y, Z axes respectively |

**Remarks**
Robot forward is X, left is Y, vertical upward is Z

---

### 1.18 Get Acceleration

**Function Prototype**
```cpp
getBodyAcc()
```

**Function Overview**
Get the acceleration data of the robot body (body coordinate system)

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [ax, ay, az] | Vector containing 3 elements, unit is m/s², corresponding to the acceleration in X, Y, Z axis directions respectively |

**Remarks**
Robot forward is X, left is Y, vertical upward is Z

---

### 1.19 Get Angular Velocity

**Function Prototype**
```cpp
getBodyGyro()
```

**Function Overview**
Get the angular velocity data of the robot body (body coordinate system)

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [gx, gy, gz] | Vector containing 3 elements, unit is rad/s, corresponding to the angular velocity in X, Y, Z axis directions respectively |

**Remarks**
Robot forward is X, left is Y, vertical upward is Z

---

### 1.20 Get Origin Coordinate Position

**Function Prototype**
```cpp
getPosition()
```

**Function Overview**
Get the position coordinates of the robot in the power-on origin coordinate system

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [x, y, z] | Vector containing 3 elements, unit is meter (m), representing the current position |

**Remarks**
Robot forward is X, left is Y, vertical upward is Z

---

### 1.21 Get Origin Coordinate Velocity

**Function Prototype**
```cpp
getWorldVelocity()
```

**Function Overview**
Get the movement speed of the robot in the power-on origin coordinate system

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [vx, vy, vz] | Vector containing 3 elements, unit is meter/second (m/s), corresponding to the speed in X, Y, Z axis directions of the power-on origin coordinate system respectively |

**Remarks**
Robot forward is X, left is Y, vertical upward is Z

---

### 1.22 Get Self-Movement Velocity

**Function Prototype**
```cpp
getBodyVelocity()
```

**Function Overview**
Get the movement speed of the robot in the body coordinate system

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [vx, vy, vz] | Vector containing 3 elements, unit is m/s, corresponding to the speed in X, Y, Z axis directions of the body coordinate system respectively |

**Remarks**
Robot forward is X, left is Y, vertical upward is Z

---

### 1.23 Get Battery Power

**Function Prototype**
```cpp
getBatteryPower()
```

**Function Overview**
Get robot battery power

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0-100 | Range: 0-100 |

**Remarks**
Return value range 0-100, 0 is no power, 100 is full power

---

### 1.24 Get Control Mode

**Function Prototype**
```cpp
getCurrentCtrlmode()
```

**Function Overview**
Get the current control mode of the robot

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Device lies down, motor enters damping state |
| 1 | Standing state/shake hand state |
| 10 | Device lies down, after a short time motor enters free state |
| 18 | Movement state |
| 21 | Action state (attitude mode, jump mode, two-leg stand, etc.) |
| 51 | Lying state |

**Remarks**
The returned state is the last state executed by the device. If an action is executed without receiving a movement command, the returned state will always be the action state.
