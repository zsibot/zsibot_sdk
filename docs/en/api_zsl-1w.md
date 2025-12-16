# ZSL-1w SDK API Definition

## 1. HighLevel Function Introduction

**class HighLevel**

This class contains methods for controlling the ZSL-1w robot dog application functions, and users can use these methods for high-level control and data acquisition.

---

### 1.1 Initialization

**Function Prototype**

```cpp
initRobot(local_ip, local_port, dog_ip)
```

**Function Overview**
Establish communication with the robot dog. The default IP is "192.168.234.1". If the robot IP is changed, the new IP needs to be passed in.

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|----------|
| local_ip | string& | User host IP address | Required | - |
| local_port | int | User host port | Required | - |
| dog_ip | string& | Robot dog IP address | Optional | Default "192.168.234.1" |

**Return Value**
None

**Remarks**
When communication establishment fails, failure logs are output to the terminal

---

### 1.2 Check Communication Status

**Function Prototype**

```cpp
checkConnect()
```

**Function Overview**
Check robot communication status

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

### 1.3 Stand Up

**Function Prototype**

```cpp
standUp()
```

**Function Overview**
Control the robot dog to stand up

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Normal |
| Others | Other error codes same as ZSL-1 |

**Remarks**
Cannot directly enter during movement

---

### 1.4 Lie Down

**Function Prototype**

```cpp
lieDown()
```

**Function Overview**
Control the robot dog to lie down

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Normal |
| Others | Other error codes same as ZSL-1 |

**Remarks**
Cannot directly enter during movement

---

### 1.5 Passive

**Function Prototype**

```cpp
passive()
```

**Function Overview**
Control the robot dog to enter passive mode

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Normal |
| Others | Other error codes same as ZSL-1 |

**Remarks**
For emergency stop

---

### 1.6 Move

**Function Prototype**

```cpp
move(float vx, float vy, float yaw_rate)
```

**Function Overview**
Control the robot dog to move at speed

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|----------|
| vx | float | Forward speed m/s | Required | When not moving, 0 needs to be passed in, range (-3.7 ~ -0.05/0.05 ~ 3.7m/s) |
| vy | float | Lateral speed m/s | Required | When not moving, 0 needs to be passed in, range (-1 ~ -0.1/0.1 ~ 1.0m/s) |
| yaw_rate | float | Angular velocity around Z-axis rad/s | Required | When not moving, 0 needs to be passed in, range (-3 ~ -0.1/0.1 ~ 3.0 rad/s) |

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Normal |
| Others | Other error codes same as ZSL-1 |

**Remarks**
Must be called in standing state

---

### 1.7 Crawl

**Function Prototype**

```cpp
crawl(float vx, float vy, float yaw_rate)
```

**Function Overview**
Control the robot dog to crawl in low posture

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|----------|
| vx | float | Forward speed m/s | Required | When not moving, 0 needs to be passed in, range (-3 ~ -0.1/0.1 ~ 3.0m/s) |
| vy | float | Lateral speed m/s | Required | When not moving, 0 needs to be passed in, range (-0.5 ~ -0.1/0.1 ~ 0.5m/s) |
| yaw_rate | float | Angular velocity around Z-axis rad/s | Required | When not moving, 0 needs to be passed in, range (-1 ~ -0.1/0.1 ~ 1.0 rad/s) |

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Normal |
| Others | Other error codes same as ZSL-1 |

**Remarks**
Similar to move, but uses crawling gait. Cannot enter this state during high-speed movement.

---

### 1.8 Cancel Crawl

**Function Prototype**

```cpp
cancelCrawl()
```

**Function Overview**
Exit crawl mode

**Parameter Description**

None

**Return Value**
None

**Remarks**
None

---

### 1.9 Attitude Control

**Function Prototype**

```cpp
attitudeControl(float roll_vel, float pitch_vel, float yaw_vel, float height_vel)
```

**Function Overview**
Control body twisting and height changes

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|----------|
| roll_vel | float | Angular velocity around X-axis | Required | When not controlling, pass in 0, range (-0.5rad/s~0.5rad/s) |
| pitch_vel | float | Angular velocity around Y-axis | Required | When not controlling, pass in 0, range (-0.5rad/s~0.5rad/s) |
| yaw_vel | float | Angular velocity around Z-axis | Required | When not controlling, pass in 0, range (-0.5rad/s~0.5rad/s) |
| height_vel | float | Vertical height velocity | Required | When not controlling, pass in 0, range (-0.5m/s-0.5m/s) |

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Normal |

**Remarks**
Must be called in standing state

---

### 1.10 Get Attitude/Velocity/Position

**Function Prototype**

```cpp
getQuaternion()
```

**Function Overview**
Get attitude quaternion

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [w, x, y, z] | Quaternion |

**Remarks**
None

---

**Function Prototype**

```cpp
getRPY()
```

**Function Overview**
Get Euler angles

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [roll, pitch, yaw] | Euler angles, unit rad |

**Remarks**
None

---

**Function Prototype**

```cpp
getBodyAcc()
```

**Function Overview**
Get body acceleration

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [ax, ay, az] | Unit m/s² |

**Remarks**
None

---

**Function Prototype**

```cpp
getBodyGyro()
```

**Function Overview**
Get body angular velocity

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [gx, gy, gz] | Unit rad/s |

**Remarks**
None

---

**Function Prototype**

```cpp
getPosition()
```

**Function Overview**
Get body position

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [x, y, z] | Body position, unit m |

**Remarks**
None

---

**Function Prototype**

```cpp
getWorldVelocity()
```

**Function Overview**
Get body velocity in world coordinate system

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [vx, vy, vz] | Body linear velocity, unit m/s |

**Remarks**
None

---

**Function Prototype**

```cpp
getBodyVelocity()
```

**Function Overview**
Get body velocity in body coordinate system

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [vx, vy, vz] | Body linear velocity, unit m/s |

**Remarks**
None

---

### 1.11 Get Battery Power

**Function Prototype**

```cpp
getBatteryPower()
```

**Function Overview**
Get battery power

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0-100 | Battery power percentage |

**Remarks**
None

---

### 1.12 Get Control Mode

**Function Prototype**

```cpp
getCurrentCtrlmode()
```

**Function Overview**
Get current robot dog control state

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0 | Damping mode |
| 1 | Standing mode |
| 3 | Movement mode |

**Remarks**
None

---

### 1.13 Joint Information Acquisition

#### 1.13.1 Get Joint Angles

**Function Prototype**

```cpp
getLegAbadJoint()
getLegHipJoint()
getLegKneeJoint()
getLegFootJoint()
```

**Function Overview**
Get joint angle values

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Joint angles of each leg, unit rad |

**Remarks**
- LegAbadJoint corresponds to hip joint abduction/adduction direction
- LegHipJoint corresponds to hip joint hip direction  
- LegKneeJoint corresponds to knee joint
- LegFootJoint corresponds to foot joint

---

#### 1.13.2 Get Joint Velocities

**Function Prototype**

```cpp
getLegAbadJointVel()
getLegHipJointVel()
getLegKneeJointVel()
getLegFootJointVel()
```

**Function Overview**
Get joint velocity values

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Joint velocities of each leg, unit rad/s |

**Remarks**
- LegAbadJointVel corresponds to hip joint abduction/adduction direction
- LegHipJointVel corresponds to hip joint hip direction  
- LegKneeJointVel corresponds to knee joint
- LegFootJointVel corresponds to foot joint

---

#### 1.13.3 Get Joint Torques

**Function Prototype**

```cpp
getLegAbadJointTorque()
getLegHipJointTorque()
getLegKneeJointTorque()
getLegFootJointTorque()
```

**Function Overview**
Get joint torque values

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Joint torques of each leg, unit N·m |

**Remarks**

- LegAbadJointTorque corresponds to hip joint abduction/adduction direction
- LegHipJointTorque corresponds to hip joint hip direction  
- LegKneeJointTorque corresponds to knee joint
- LegFootJointTorque corresponds to foot joint
