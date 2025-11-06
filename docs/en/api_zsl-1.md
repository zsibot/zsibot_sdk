# ZSL-1 SDK API Definition

## 1. HighLevel Function Introduction

**class HighLevel**

This class contains methods for controlling the quadruped robot application functions, and users can use these methods for high-level control and data acquisition.

---

### 1.1 Initialization

**Function Prototype**

```cpp
initRobot(const std::string& local_ip, const int local_port, const std::string& dog_ip = "192.168.234.1")
```

**Function Overview**
Establish communication with the robot dog. The robot dog's IP defaults to "192.168.234.1". If the robot's IP is changed, the new IP needs to be passed through this interface.

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
checkConnection()
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
standUP()
```

**Function Overview**
Control the robot dog to stand up

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
Robot dog stands normally, cannot directly enter this state during movement

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
| 0 | Enter state normal |
| 0x3012 | Motor data lost |
| 0x3010 | Motor disabled |
| 0x3011 | Motor fault |
| 0x3009 | Motor angle limit exceeded |
| 0x3007 | State machine switching failed |
| 0x3013 | Speed command too large |

**Remarks**
Robot dog lies down with joints locked, cannot directly enter this state during movement

---

### 1.5 Passive

**Function Prototype**

```cpp
passive()
```

**Function Overview**
Control the robot dog to lie down in emergency

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
Robot dog enters passive state and lies down

---

### 1.6 Move

**Function Prototype**

```cpp
move(float vx, float vy, float yaw_rate)
```

**Function Overview**
Control the robot dog movement

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
Only enter when the robot dog is standing, control the dog to move at the specified speed.

---

### 1.7 Jump

**Function Prototype**

```cpp
jump()
```

**Function Overview**
Control the robot dog to jump vertically

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

### 1.8 Front Jump

**Function Prototype**

```cpp
frontJump()
```

**Function Overview**
Control the robot dog to jump forward

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

### 1.9 Backflip

**Function Prototype**

```cpp
backflip()
```

**Function Overview**
Control the robot dog to perform a backflip

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

### 1.10 Shake Hand

**Function Prototype**

```cpp
shakeHand()
```

**Function Overview**
Control the robot dog to shake hands

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

### 1.11 Two-Leg Stand

**Function Prototype**

```cpp
twoLegStand(float vx, float yaw_rate)
```

**Function Overview**
Control the robot dog to stand on two legs

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|---------|
| vx | float | Forward speed | Required | Pass in 0 when not moving, range (-0.5~-0.2 / 0.2~0.5m / s) |
| yaw_rate | float | Angular velocity around Z-axis | Required | Pass in 0 when not moving, range (-1~-0.2 / 0.2~1.0rad / s)

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

### 1.12 Exit Two-Leg Stand

**Function Prototype**

```cpp
cancelTwoLegStand()
```

**Function Overview**
Control the robot dog to exit two-leg stand

**Parameter Description**

None

**Return Value**
None

**Remarks**
Robot dog exits two-leg stand state, entered when robot dog is in two-leg stand state

---

### 1.13 Attitude Control

**Function Prototype**

```cpp
attitudeControl(float roll_vel, float pitch_vel, float yaw_vel, float height_vel)
```

**Function Overview**
Control the robot dog to twist in place and change body height

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
Enter when robot dog is standing, control the dog to twist in place and change body height at the specified speed.

---

### 1.14 Get Attitude Quaternion

**Function Prototype**

```cpp
getQuaternion()
```

**Function Overview**
Get the current attitude quaternion of the robot dog

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [w, x, y, z] | Vector containing 4 elements, corresponding to the four components of the quaternion respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 1.15 Get Attitude Euler Angles

**Function Prototype**

```cpp
getRPY()
```

**Function Overview**
Get the Euler angles (roll, pitch, yaw) of the current attitude of the robot dog

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [roll, pitch, yaw] | Vector containing 3 elements, unit is radians (rad), corresponding to the rotation angles around X, Y, Z axes respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 1.16 Get Acceleration

**Function Prototype**

```cpp
getBodyAcc()
```

**Function Overview**
Get the acceleration data of the robot dog body (body coordinate system)

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [ax, ay, az] | Vector containing 3 elements, unit is m/s², corresponding to the acceleration in X, Y, Z axis directions respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 1.17 Get Angular Velocity

**Function Prototype**

```cpp
getBodyGyro()
```

**Function Overview**
Get the angular velocity data of the robot dog body (body coordinate system)

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [gx, gy, gz] | Vector containing 3 elements, unit is rad/s, corresponding to the angular velocity in X, Y, Z axis directions respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 1.18 Get Origin Coordinate Position

**Function Prototype**

```cpp
getPosition()
```

**Function Overview**
Get the position coordinates of the robot dog in the power-on origin coordinate system

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [x, y, z] | Vector containing 3 elements, unit is meter (m), representing the current position |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 1.19 Get Origin Coordinate Velocity

**Function Prototype**

```cpp
getWorldVelocity()
```

**Function Overview**
Get the movement speed of the robot dog in the power-on origin coordinate system

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [vx, vy, vz] | Vector containing 3 elements, unit is meter/second (m/s), corresponding to the speed in X, Y, Z axis directions of the power-on origin coordinate system respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 1.20 Get Self-Movement Velocity

**Function Prototype**

```cpp
getBodyVelocity()
```

**Function Overview**
Get the movement speed of the robot dog in the body coordinate system

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [vx, vy, vz] | Vector containing 3 elements, unit is m/s, corresponding to the speed in X, Y, Z axis directions of the body coordinate system respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 1.21 Get Battery Power

**Function Prototype**

```cpp
getBatteryPower()
```

**Function Overview**
Get robot dog battery power

**Parameter Description**

None

**Return Value Type: uint32_t**

| Return Value | Description |
|------|------|
| 0-100 | Range: 0-100 |

**Remarks**
Return value range 0-100, 0 is no power, 100 is full power

---

### 1.22 Get Control Mode

**Function Prototype**

```cpp
getCurrentCtrlmode()
```

**Function Overview**
Get the current control mode of the robot dog

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

---

### 1.23 Get Abad Joint Angles

**Function Prototype**

```cpp
getLegAbadJoint()
```

**Function Overview**
Get the current angles of the hip abduction/adduction joints (Abad Joint) of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, corresponding to the Abad joint angles of right front, left front, right rear, left rear respectively (unit: rad) |

**Remarks**
Unit rad, robot dog body forward is X, left is Y, vertical upward is Z

---

### 1.24 Get Hip Joint Angles

**Function Prototype**

```cpp
getLegHipJoint()
```

**Function Overview**
Get the current angles of the hip pitch joints (Hip Joint) of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, corresponding to the Hip joint angles of right front, left front, right rear, left rear respectively (unit: rad) |

**Remarks**
Unit rad, robot dog body forward is X, left is Y, vertical upward is Z

---

### 1.25 Get Knee Joint Angles

**Function Prototype**

```cpp
getLegKneeJoint()
```

**Function Overview**
Get the current angles of the knee joints (Knee Joint) of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, corresponding to the Knee joint angles of right front, left front, right rear, left rear respectively (unit: rad) |

**Remarks**
Unit rad, robot dog body forward is X, left is Y, vertical upward is Z

---

### 1.26 Get Angular Velocity of Abad Joints

**Function Prototype**

```cpp
getLegAbadJointVel()
```

**Function Overview**
Get the current angular velocity of Abad joints of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, unit is rad/s, corresponding to the joint angles of right front, left front, right rear, left rear respectively |

**Remarks**
Unit rad/s, robot dog body forward is X, left is Y, vertical upward is Z

---

### 1.27 Get Hip Joint Angular Velocity

**Function Prototype**

```cpp
getLegHipJointVel()
```

**Function Overview**
Get the current angular velocity of Hip joints of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, unit is rad/s, corresponding to the joint angles of right front, left front, right rear, left rear respectively |

**Remarks**
Unit rad/s, robot dog body forward is X, left is Y, vertical upward is Z

---

### 1.28 Get Knee Joint Angular Velocity

**Function Prototype**

```cpp
getLegKneeJointVel()
```

**Function Overview**
Get the current angular velocity of Knee joints of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, unit is rad/s, corresponding to the joint angles of right front, left front, right rear, left rear respectively |

**Remarks**
Unit rad/s, robot dog body forward is X, left is Y, vertical upward is Z

---

### 1.29 Get Abad Joint Torque

**Function Prototype**

```cpp
getLegAbadJointTorque()
```

**Function Overview**
Get the current output torque of Abad joints of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, unit usually N・m, corresponding order same as joint torque |

**Remarks**
Unit usually N・m, corresponding to the Abad joint torque of right front, left front, right rear, left rear respectively

---

### 1.30 Get Hip Joint Torque

**Function Prototype**

```cpp
getLegHipJointTorque()
```

**Function Overview**
Get the current output torque of Hip joints of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, unit usually N・m, corresponding order same as joint torque |

**Remarks**
Unit usually N・m, corresponding to the Hip joint torque of right front, left front, right rear, left rear respectively

---

### 1.31 Get Knee Joint Torque

**Function Prototype**

```cpp
getLegKneeJointTorque()
```

**Function Overview**
Get the current output torque of Knee joints of each leg

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [FR, FL, RR, RL] | Vector containing 4 elements, unit usually N・m, corresponding order same as joint torque |

**Remarks**
Unit usually N・m, corresponding to the Knee joint torque of right front, left front, right rear, left rear respectively

---

## 2. LowLevel Function Introduction

**class lowlevel**

This class is used to interact with the motors, including sending motor commands and obtaining motor status.

---

### 2.1 Create Connection

**Function Prototype**

```cpp
initRobot(const std::string &local_ip, const int local_port, const std::string &dog_ip = "192.168.234.1")
```

**Function Overview**
Establish communication with the robot dog. The robot dog's IP defaults to "192.168.234.1". If the robot's IP is changed, the new IP needs to be passed through this interface.

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|---------|
| local_ip | string& | User host IP address | Required | - |
| local_port | int | User host port | Required | - |
| dog_ip | string& | Robot dog IP address | Optional | Default "192.168.234.1" |

**Return Value**
None

**Remarks**
When communication establishment fails, failure logs are output to the terminal

---

### 2.2 Check Communication Status

**Function Prototype**

```cpp
checkConnection()
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

### 2.3 Send Motor Command

**Function Prototype**

```cpp
sendMotorCmd(motorCmd& cmd)
```

**Function Overview**
Publish motor control command

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|-------|
| cmd | motorCmd | Motor control command structure | Required | - |

**Return Value Type: int**

| Return Value | Description |
|------|------|
| 0 | Send success |
| -1 | Send failure |

**Remarks**
Leg order: Right front leg is leg 1, left front leg is leg 2, right rear leg is leg 3, left rear leg is leg 4; Control command coordinate system is robot dog forward is X, left is Y, vertical upward is Z

**Cmd Data Protocol**

```C++
struct alignas(4) motorCmd  {

  float q_des_abad[4] = {0.0, 0.0, 0.0, 0.0}; // A joint angle command
  float q_des_hip[4] = {0.0, 0.0, 0.0, 0.0};  // H joint angle command
  float q_des_knee[4] = {0.0, 0.0, 0.0, 0.0}; // K joint angle command

  float qd_des_abad[4] = {0.0, 0.0, 0.0, 0.0}; // A joint angular velocity command
  float qd_des_hip[4] = {0.0, 0.0, 0.0, 0.0};  // H joint angular velocity command
  float qd_des_knee[4] = {0.0, 0.0, 0.0, 0.0}; // K joint angular velocity command

  float kp_abad[4] = {0.0, 0.0, 0.0, 0.0}; // A joint Kp value
  float kp_hip[4] = {0.0, 0.0, 0.0, 0.0};  // H joint Kp value
  float kp_knee[4] = {0.0, 0.0, 0.0, 0.0}; // K joint Kp value

  float kd_abad[4] = {0.0, 0.0, 0.0, 0.0}; // A joint Kd value
  float kd_hip[4] = {0.0, 0.0, 0.0, 0.0};  // H joint Kd value
  float kd_knee[4] = {0.0, 0.0, 0.0, 0.0}; // K joint Kd value

  float tau_abad_ff[4] = {0.0, 0.0, 0.0, 0.0}; // A joint torque command
  float tau_hip_ff[4] = {0.0, 0.0, 0.0, 0.0};  // H joint torque command
  float tau_knee_ff[4] = {0.0, 0.0, 0.0, 0.0}; // K joint torque command

};
```

---

### 2.4 Get Attitude Quaternion

**Function Prototype**

```cpp
getQuaternion()
```

**Function Overview**
Get the current attitude quaternion of the robot dog

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [w, x, y, z] | Vector containing 4 elements, corresponding to the four components of the quaternion respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 2.5 Get Attitude Euler Angles

**Function Prototype**

```cpp
getRPY()
```

**Function Overview**
Get the Euler angles (roll, pitch, yaw) of the current attitude of the robot dog

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [roll, pitch, yaw] | Vector containing 3 elements, unit is radians (rad), corresponding to the rotation angles around X, Y, Z axes respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 2.6 Get Acceleration

**Function Prototype**

```cpp
getBodyAcc()
```

**Function Overview**
Get the acceleration data of the robot dog body (body coordinate system)

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [ax, ay, az] | Vector containing 3 elements, unit is m/s², corresponding to the acceleration in X, Y, Z axis directions respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 2.7 Get Angular Velocity

**Function Prototype**

```cpp
getBodyGyro()
```

**Function Overview**
Get the angular velocity data of the robot dog body (body coordinate system)

**Parameter Description**

None

**Return Value Type: vector**

| Return Value | Description |
|------|------|
| [gx, gy, gz] | Vector containing 3 elements, unit is rad/s, corresponding to the angular velocity in X, Y, Z axis directions respectively |

**Remarks**
Robot dog forward is X, left is Y, vertical upward is Z

---

### 2.8 Get Motor Data

**Function Prototype**

```cpp
getMotorState()
```

**Function Overview**
Get the robot dog motor data

**Parameter Description**

None

**Return Value Type: motorState**

| Return Value | Description |
|------|------|
| motorState | Returns motor data |

**Remarks**
Unit rad

**MotorState Data Protocol**

```C++
struct alignas(4) motorState {
  // Joint order FR,FL,RR,RL 
  float q_abad[4] = {0.0, 0.0, 0.0, 0.0}; // A joint angle
  float q_hip[4] = {0.0, 0.0, 0.0, 0.0};  // H joint angle
  float q_knee[4] = {0.0, 0.0, 0.0, 0.0}; // K joint angle

  float qd_abad[4] = {0.0, 0.0, 0.0, 0.0}; // A joint angular velocity
  float qd_hip[4] = {0.0, 0.0, 0.0, 0.0};  // H joint angular velocity
  float qd_knee[4] = {0.0, 0.0, 0.0, 0.0}; // K joint angular velocity

  float tau_abad_fb[4] = {0.0, 0.0, 0.0, 0.0};// A joint torque feedback
  float tau_hip_fb[4] = {0.0, 0.0, 0.0, 0.0};  // H joint torque feedback
  float tau_knee_fb[4] = {0.0, 0.0, 0.0, 0.0}; // K joint torque feedback
};
```

---

### 2.9 Motor Data Existence

**Function Prototype**

```cpp
haveMotorData()
```

**Function Overview**
Determine whether motor data is obtained

**Parameter Description**

None

**Return Value Type: bool**

| Return Value | Description |
|------|------|
| true | Motor data exists |
| false | Motor data does not exist |

**Remarks**

Check whether motor data is received before sending motor commands