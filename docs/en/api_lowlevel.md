# LowLevel SDK API Definition

## 1. LowLevel Data Structures and Function Descriptions

**lowlevel.h** file defines the robot's low-level motor control interface, mainly implemented through shared memory (SHM) to manage robot motor control and status, as well as inertial measurement unit (IMU) data sharing.

---

### 1.1 Data Structures

#### 1.1.1 Joint Control Parameters

**Structure Prototype**
```cpp
typedef struct joint_control_def {
    float p_des; // Target position (unit: radians)
    float v_des; // Target velocity (unit: radians/second)
    float kp;    // Proportional gain
    float kd;    // Derivative gain
    float t_ff;  // Feedforward torque (unit: Newton·meters)
} joint_control_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| p_des  | float | Target position, unit in radians |
| v_des  | float | Target velocity, unit in radians/second |
| kp     | float | Proportional gain, used in controller |
| kd     | float | Derivative gain, used in controller |
| t_ff   | float | Feedforward torque, unit in Newton·meters |

---

#### 1.1.2 Leg Control Parameters

**Structure Prototype**
```cpp
typedef struct leg_control_def {
    joint_control_t abad; // Hip abduction/adduction control
    joint_control_t hip;  // Hip pitch control
    joint_control_t knee; // Knee control
    joint_control_t foot; // Foot control
    int32_t flags;        // Flag bits, always set to 1
} leg_control_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| abad   | joint_control_t | Hip abduction/adduction joint control |
| hip    | joint_control_t | Hip pitch joint control |
| knee   | joint_control_t | Knee joint control |
| foot   | joint_control_t | Foot control |
| flags  | int32_t | Flag bits, always set to 1 |

---

#### 1.1.3 Robot Control Command

**Structure Prototype**
```cpp
typedef struct robot_cmd_def {
    leg_control_t legs[4];  // Leg control commands for four legs
    uint32_t crc;           // CRC checksum
    uint32_t counter;       // Command counter
} robot_cmd_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| legs   | leg_control_t[4] | Leg control commands for four legs (FR, FL, RR, RL) |
| crc    | uint32_t | CRC checksum |
| counter| uint32_t | Command counter |

---

#### 1.1.4 IMU Data

**Structure Prototype**
```cpp
typedef struct imu_data_def {
    float quaternion[4];   // Quaternion (w, x, y, z)
    float angular_velocity[3]; // Angular velocity (x, y, z) (rad/s)
    float linear_acceleration[3]; // Linear acceleration (x, y, z) (m/s^2)
    float temperature;     // Temperature (°C)
} imu_data_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| quaternion | float[4] | Quaternion (w, x, y, z) |
| angular_velocity | float[3] | Angular velocity (x, y, z), unit rad/s |
| linear_acceleration | float[3] | Linear acceleration (x, y, z), unit m/s^2 |
| temperature | float | Temperature, unit °C |

---

#### 1.1.5 Joint State

**Structure Prototype**
```cpp
typedef struct joint_state_def {
    float pos;    // Current position (rad)
    float vel;    // Current velocity (rad/s)
    float torque; // Current torque (N·m)
} joint_state_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| pos    | float | Current position, unit rad |
| vel    | float | Current velocity, unit rad/s |
| torque | float | Current torque, unit N·m |

---

#### 1.1.6 Leg State

**Structure Prototype**
```cpp
typedef struct leg_state_def {
    joint_state_t abad;  // Hip abduction/adduction joint state
    joint_state_t hip;   // Hip pitch joint state
    joint_state_t knee;  // Knee joint state
    joint_state_t foot;  // Foot state
} leg_state_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| abad   | joint_state_t | Hip abduction/adduction joint state |
| hip    | joint_state_t | Hip pitch joint state |
| knee   | joint_state_t | Knee joint state |
| foot   | joint_state_t | Foot state |

---

#### 1.1.7 Robot State

**Structure Prototype**
```cpp
typedef struct robot_state_def {
    leg_state_t legs[4];  // Leg states for four legs
    imu_data_t imu;       // IMU data
    uint32_t crc;         // CRC checksum
    uint32_t counter;     // State counter
} robot_state_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| legs   | leg_state_t[4] | Leg states for four legs (FR, FL, RR, RL) |
| imu    | imu_data_t | IMU data |
| crc    | uint32_t | CRC checksum |
| counter| uint32_t | State counter |

---

### 1.2 Shared Memory Operations

#### 1.2.1 Initialize Shared Memory

**Function Prototype**
```cpp
int lowlevel_init(void);
```

**Function Overview**
Initialize shared memory for communication with the robot

**Parameter Description**

None

**Return Value**

| Return Value | Description |
|------|------|
| 0    | Initialization successful |
| -1   | Initialization failed |

**Remarks**
Must be called before any other lowlevel functions

---

#### 1.2.2 Send Control Command

**Function Prototype**
```cpp
int lowlevel_send_cmd(const robot_cmd_t* cmd);
```

**Function Overview**
Send control command to the robot

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|------|
| cmd    | const robot_cmd_t* | Robot control command | Required | - |

**Return Value**

| Return Value | Description |
|------|------|
| 0    | Send successful |
| -1   | Send failed |

**Remarks**
Control command coordinate system: robot forward is X, left is Y, vertical upward is Z

---

#### 1.2.3 Receive Robot State

**Function Prototype**
```cpp
int lowlevel_recv_state(robot_state_t* state);
```

**Function Overview**
Receive robot state data

**Parameter Description**

| Parameter Name | Type | Description | Option | Remarks |
|--------|------|------|---------|------|
| state  | robot_state_t* | Robot state data | Required | - |

**Return Value**

| Return Value | Description |
|------|------|
| 0    | Receive successful |
| -1   | Receive failed |

**Remarks**
Leg order: Right front leg is leg 0, left front leg is leg 1, right rear leg is leg 2, left rear leg is leg 3

---

#### 1.2.4 Close Shared Memory

**Function Prototype**
```cpp
int lowlevel_close(void);
```

**Function Overview**
Close shared memory connection

**Parameter Description**

None

**Return Value**

| Return Value | Description |
|------|------|
| 0    | Close successful |
| -1   | Close failed |

**Remarks**
Should be called when the program exits to release resources