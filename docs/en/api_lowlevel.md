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
    joint_control_t abad; // Hip joint abduction/adduction control
    joint_control_t hip;  // Hip joint pitch control
    joint_control_t knee; // Knee joint control
    joint_control_t foot; // Foot control
    int32_t flags;        // Flag bits, always set to 1
} leg_control_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| abad   | joint_control_t | Hip joint abduction/adduction control parameters |
| hip    | joint_control_t | Hip joint pitch control parameters |
| knee   | joint_control_t | Knee joint control parameters |
| foot   | joint_control_t | Foot control parameters |
| flags  | int32_t | Flag bits, always set to 1 |

---

#### 1.1.3 Joint State Parameters

**Structure Prototype**
```cpp
typedef struct joint_state_def {
    int32_t flags; // Status flag bits
    float p;       // Current angle (unit: radians)
    float v;       // Current angular velocity (unit: radians/second)
    float t;       // Current torque (unit: Newton·meters)
} joint_state_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| flags  | int32_t | Status flag bits, contains motor status information |
| p      | float | Current angle, unit in radians |
| v      | float | Current angular velocity, unit in radians/second |
| t      | float | Current torque, unit in Newton·meters |

**Remarks**

- Each bit of `flags` represents different status information, such as voltage, temperature, fault flags, etc.

---

#### 1.1.4 Leg State Parameters

**Structure Prototype**
```cpp
typedef struct leg_state_def {
    joint_state_t abad; // Hip joint abduction/adduction state
    joint_state_t hip;  // Hip joint pitch state
    joint_state_t knee; // Knee joint state
    joint_state_t foot; // Foot state
} leg_state_t;
```

**Field Description**

| Field Name | Type | Description |
|--------|------|------|
| abad   | joint_state_t | Hip joint abduction/adduction state parameters |
| hip    | joint_state_t | Hip joint pitch state parameters |
| knee   | joint_state_t | Knee joint state parameters |
| foot   | joint_state_t | Foot state parameters |

---

### 1.2 Function Interface

#### 1.2.1 Create Leg Control Shared Memory

**Function Prototype**
```cpp
static inline spline_data_p create_spline_shm(void);
```

**Function Overview**
Create shared memory for leg control and status.

**Return Value**

| Return Value | Description |
|--------|------|
| spline_data_p | Pointer to shared memory |

**Remarks**

- Shared memory path is `/spline_shm`.
- Shared memory size is 10 KB.

---

#### 1.2.2 Destroy Leg Control Shared Memory

**Function Prototype**
```cpp
static inline void destroy_spline_shm(spline_data_p ptr);
```

**Function Overview**
Destroy shared memory for leg control and status.

**Parameter Description**

| Parameter Name | Type | Description |
|--------|------|------|
| ptr    | spline_data_p | Pointer to shared memory |

**Remarks**

- No need to explicitly unmap or delete shared memory in current implementation.

---

#### 1.2.3 Create IMU Data Shared Memory

**Function Prototype**
```cpp
static inline nav_imu_p create_imu_shm(void);
```

**Function Overview**
Create shared memory for IMU data.

**Return Value**

| Return Value | Description |
|--------|------|
| nav_imu_p | Pointer to shared memory |

**Remarks**

- Shared memory path is `/imu_shm`.
- Shared memory size is 1 KB.

---

#### 1.2.4 Destroy IMU Data Shared Memory

**Function Prototype**
```cpp
static inline void destroy_imu_shm(nav_imu_p ptr);
```

**Function Overview**
Destroy shared memory for IMU data.

**Parameter Description**

| Parameter Name | Type | Description |
|--------|------|------|
| ptr    | nav_imu_p | Pointer to shared memory |

**Remarks**

- No need to explicitly unmap or delete shared memory in current implementation.

---

### 1.3 Notes

#### Shared Memory Management
- Ensure shared memory is properly destroyed when the program exits.
- Pay attention to synchronization issues when multiple processes access shared memory.

#### Parameter Range
- Parameters in `joint_control_t` (such as `kp`, `kd`) need to be set to reasonable ranges according to specific hardware characteristics.
- Status values in `joint_state_t` (such as `p`, `v`, `t`) may be limited by hardware.

#### Real-time Requirements
- Shared memory update frequency is 1 ms, ensure consumers can process data in time.

#### Data Read/Write
- CONSUMER_CONTROL is the status bit,
    - When controlling, the consumer sets the status to 1, and the producer reads the data and sets the status to 0.
    - When reading data, the producer sets the status to 1, and the consumer reads the data and sets the status to 0.

---