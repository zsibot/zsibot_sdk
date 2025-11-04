# LowLevel SDK API 定义

## 1. LowLevel 数据结构与函数说明

**lowlevel.h** 文件定义了机器人底层电机控制接口，主要通过共享内存（SHM）实现对机器人电机控制和状态的管理，同时还包括惯性测量单元（IMU）的数据共享。

---

### 1.1 数据结构

#### 1.1.1 关节控制参数

**结构体原型**
```cpp
typedef struct joint_control_def {
    float p_des; // 目标位置（单位：弧度）
    float v_des; // 目标速度（单位：弧度/秒）
    float kp;    // 比例增益
    float kd;    // 微分增益
    float t_ff;  // 前馈扭矩（单位：牛·米）
} joint_control_t;
```

**字段说明**

| 字段名 | 类型 | 说明 |
|--------|------|------|
| p_des  | float | 目标位置，单位为弧度 |
| v_des  | float | 目标速度，单位为弧度/秒 |
| kp     | float | 比例增益，用于控制器 |
| kd     | float | 微分增益，用于控制器 |
| t_ff   | float | 前馈扭矩，单位为牛·米 |

---

#### 1.1.2 腿部控制参数

**结构体原型**
```cpp
typedef struct leg_control_def {
    joint_control_t abad; // 髋关节外展/内收控制
    joint_control_t hip;  // 髋关节俯仰控制
    joint_control_t knee; // 膝关节控制
    joint_control_t foot; // 足部控制
    int32_t flags;        // 标志位，始终设置为 1
} leg_control_t;
```

**字段说明**

| 字段名 | 类型 | 说明 |
|--------|------|------|
| abad   | joint_control_t | 髋关节外展/内收控制参数 |
| hip    | joint_control_t | 髋关节俯仰控制参数 |
| knee   | joint_control_t | 膝关节控制参数 |
| foot   | joint_control_t | 足部控制参数 |
| flags  | int32_t | 标志位，始终设置为 1 |

---

#### 1.1.3 关节状态参数

**结构体原型**
```cpp
typedef struct joint_state_def {
    int32_t flags; // 状态标志位
    float p;       // 当前角度（单位：弧度）
    float v;       // 当前角速度（单位：弧度/秒）
    float t;       // 当前扭矩（单位：牛·米）
} joint_state_t;
```

**字段说明**

| 字段名 | 类型 | 说明 |
|--------|------|------|
| flags  | int32_t | 状态标志位，包含电机状态信息 |
| p      | float | 当前角度，单位为弧度 |
| v      | float | 当前角速度，单位为弧度/秒 |
| t      | float | 当前扭矩，单位为牛·米 |

**备注**

- `flags` 的每个位表示不同的状态信息，例如电压、温度、故障标志等。

---

#### 1.1.4 腿部状态参数

**结构体原型**
```cpp
typedef struct leg_state_def {
    joint_state_t abad; // 髋关节外展/内收状态
    joint_state_t hip;  // 髋关节俯仰状态
    joint_state_t knee; // 膝关节状态
    joint_state_t foot; // 足部状态
} leg_state_t;
```

**字段说明**

| 字段名 | 类型 | 说明 |
|--------|------|------|
| abad   | joint_state_t | 髋关节外展/内收状态参数 |
| hip    | joint_state_t | 髋关节俯仰状态参数 |
| knee   | joint_state_t | 膝关节状态参数 |
| foot   | joint_state_t | 足部状态参数 |

---

### 1.2 函数接口

#### 1.2.1 创建腿部控制共享内存

**函数原型**
```cpp
static inline spline_data_p create_spline_shm(void);
```

**功能概述**
创建用于腿部控制和状态的共享内存。

**返回值**

| 返回值 | 说明 |
|--------|------|
| spline_data_p | 指向共享内存的指针 |

**备注**

- 共享内存路径为 `/spline_shm`。
- 共享内存大小为 10 KB。

---

#### 1.2.2 销毁腿部控制共享内存

**函数原型**
```cpp
static inline void destroy_spline_shm(spline_data_p ptr);
```

**功能概述**
销毁腿部控制和状态的共享内存。

**参数说明**

| 参数名 | 类型 | 说明 |
|--------|------|------|
| ptr    | spline_data_p | 指向共享内存的指针 |

**备注**

- 当前实现中无需显式解除映射或删除共享内存。

---

#### 1.2.3 创建 IMU 数据共享内存

**函数原型**
```cpp
static inline nav_imu_p create_imu_shm(void);
```

**功能概述**
创建用于 IMU 数据的共享内存。

**返回值**

| 返回值 | 说明 |
|--------|------|
| nav_imu_p | 指向共享内存的指针 |

**备注**

- 共享内存路径为 `/imu_shm`。
- 共享内存大小为 1 KB。

---

#### 1.2.4 销毁 IMU 数据共享内存

**函数原型**
```cpp
static inline void destroy_imu_shm(nav_imu_p ptr);
```

**功能概述**
销毁 IMU 数据的共享内存。

**参数说明**

| 参数名 | 类型 | 说明 |
|--------|------|------|
| ptr    | nav_imu_p | 指向共享内存的指针 |

**备注**

- 当前实现中无需显式解除映射或删除共享内存。

---

### 1.3 注意事项

#### 共享内存管理
- 确保在程序退出时正确销毁共享内存。
- 多进程访问共享内存时需注意同步问题。

#### 参数范围
- `joint_control_t` 中的参数（如 `kp`、`kd`）需根据具体硬件特性设置合理范围。
- `joint_state_t` 中的状态值（如 `p`、`v`、`t`）可能受硬件限制。

#### 实时性要求
- 共享内存的更新频率为 1 ms，需确保消费者能够及时处理数据。

#### 数据读写
- CONSUMER_CONTROL为状态位，
    - 控制时由消费者将状态置为1，由生产者读取数据后将状态置为0。
    - 读取数据时由生产者将状态置为1，由消费者读取数据后将状态置为0。

---