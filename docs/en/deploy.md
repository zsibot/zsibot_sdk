# How to Deploy SDK

!!! tip "Current document applies to"
    zsl-1 device SDK version v0.2.6 or above, motion control version v0.2.6 or above (robot body 0.2.0 or above)  
    zsl-1w device SDK version v0.2.7 or above, motion control version v0.3.1 or above (robot body 0.3.3 or above)


**Environment Dependencies**

- Ubuntu 22.04
- CMake 3.8+
- GCC 11+
- Eigen3
- boost 1.74
- python3


## 1. Network Communication
The device is equipped with wireless and wired network interfaces, where wireless network information is located on the label on the right side of the device, indicating the device SSID and password information.

![Picture](images/net-connection.png)

Default robot IP:

| Network Interface | IP Address | DHCP |
| --- | --- | --- |
| Wireless Network | 192.168.234.1 | Yes |
| Wired Network | 192.168.168.168 | No |


The wireless network is equipped with DHCP service. After connecting to the wireless network, ensure that the operating device's wireless network is not configured with a fixed IP, and you can directly establish communication with the robot through 192.168.234.1.

The wired network does not have DHCP service. After connecting via cable, you need to configure a fixed IP on the operating device's wired network, and the IP should be in the 168 subnet to establish communication with the robot.

If the robot's IP changes, you need to configure [SDK_CLIENT_IP](#23-configure-sdk_client_ip)

---

## 2. Modify Device-side Communication Parameters Related to SDK
### 2.1 Login to Device
The device provides SSH login. After creating a connection with the device through WiFi or wireless, you can use the command:
```bash
ssh firefly@{IP}    #password: firefly
```
Modify `{IP}` according to wired/wireless, and both password and username are firefly.
### 2.2 Modify SDK Configuration File
Use vim command to modify `/opt/export/config/sdk_config.yaml` file:
```yaml
target_ip: "127.0.0.1"
target_port: 43988
```

Set `target_ip` to the IP address of the control device after connecting to the robot, and `target_port` can remain unchanged if not necessary.
By default, the device only supports WiFi network, i.e., `target_ip` is the IP address of `192.168.234.X`. If you need to communicate through cable or other subnet IPs, you need to configure `SDK_CLIENT_IP` in conjunction with step 2.4.
!!! warning "Parameters need to be restarted to take effect after configuration!"
### 2.3 Configure SDK_CLIENT_IP
If you need to use a cable or non-192.168.234.X subnet IP to control the device, you need to use the vim command to modify

For ZSL-1 (quadruped point-foot), modify `/opt/app_launch/start_motion_control.sh` file:

For ZSL-1w (quadruped wheel-legged), modify `/opt/app_launch/start_motion_control_xgw.sh` file:

```bash hl_lines="27"

#!/bin/bash

echo "start motion control"

# 共享内存文件路径
SHM_FILE="/dev/shm/spline_shm"

# 循环检查设备是否存在
while true; do
    if [ -e "$SHM_FILE" ]; then
        echo "共享内存文件 $SHM_FILE 已存在。"
        break
    else
        echo "共享内存文件 $SHM_FILE 不存在，等待 1 秒后重试..."
        sleep 1
    fi
done

# 共享内存文件存在后执行的命令
echo "共享内存文件已准备好，可以执行后续操作。"

sudo ifconfig lo multicast
sudo route add -net 224.0.0.0 netmask 240.0.0.0 dev lo

export LD_LIBRARY_PATH=/opt/export/mc/bin
export ROBOT_TYPE=P2
export SDK_CLIENT_IP="robot new ip"

cd /opt/export/mc/bin && taskset -c 7 ./mc_ctrl r
``` 


In the above code line 27, add the corresponding configuration: `export SDK_CLIENT_IP="robot new ip"`, and fill in the robot's IP address in the corresponding parameter. If using wired network, change the robot's new IP to 192.168.168.168, or modify to the corresponding IP if it's another IP.

!!! danger "The IP configured in [target_ip](#22-modify-sdk-configuration-file) and [SDK_CLIENT_IP](#23-configure-sdk_client_ip) must be in the same subnet!"

!!! warning "Parameters need to be restarted to take effect after configuration!"

!!! danger "There is a probability that configuring this parameter will cause the robot to be unable to use the remote controller!"
    After configuring SDK_CLIENT_IP, if the device's network is not initialized after booting and the corresponding network card is not assigned an IP address, causing the motion control program to fail to bind the IP address, the robot will not be able to use the remote controller. [Solution](faq.md#2-motion-control-binding-ip-failure)

---

## 3. Modify SDK Demo Configuration
    
### 3.1. Configure C++ IP and Port

Modify CLIENT_IP and CLIENT_PORT in the code:
    
```C++
constexpr int CLIENT_PORT = 43988;      // Local port  
std::string CLIENT_IP = "192.168.234.15"; // Local IP address
// Robot IP defaults to 192.168.234.1, if you need to change the robot IP, you can pass the changed robot IP through the init_robot() interface
```
### 3.2. Configure Python IP and Port
```python
app.initRobot("192.168.234.15",43988, "192.168.234.1") # (Local IP, Local Port, Robot IP)
``` 
!!! warning "The robot IP and local port in the configuration parameters must be consistent with the target_ip and target_port parameters in [sdk_config](#22-modify-sdk-configuration-file)."
    
!!! warning "Please ensure that the robot IP and port number match, otherwise communication cannot be established!"

!!! warning "If you delete or comment out the IP in sdk_config.yaml, it will cause the robot's motion control service to fail to start automatically!"

!!! warning "When the device program is updated, or the motion control program is updated, the configuration file will be reset, and the relevant configuration needs to be reconfigured!"
    
## 4. Example Running Steps


### 4.1 Compile Demo
#### ZSL-1
```Shell
cd demo/zsl-1/cpp
mkdir build
cd build
cmake ..
make -j6
```

#### ZSL-1w
```Shell
cd demo/zsl-1w/cpp
mkdir build
cd build
cmake ..
make -j6
```


### 4.2 Run C++ Demo
#### ZSL-1
```Shell
cd demo/zsl-1/cpp/build
./highlevel_demo
or
./lowlevel_demo
```


#### ZSL-1w
```Shell
cd demo/zsl-1w/cpp/build
./highlevel_demo
```
!!! note "ZSL-1w does not provide LowLevel interface, so only `highlevel_demo` is available."
    
### 4.3 Run Python Demo
#### ZSL-1
```Shell
cd demo/zsl-1/python/examples
python highlevel_demo.py
or
python lowlevel_demo.py
```


#### ZSL-1w
```Shell
cd demo/zsl-1w/python/examples
python highlevel_demo.py
```

!!! danger "If 'connect time out' appears after running, refer to the solution [connect time out](faq.md#1-connect-time-out)"

### 4.4 Using mc_sdk Based on CMake
#### ZSL-1
```cmake
cmake_minimum_required(VERSION 3.16)

project(test)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# Define architecture variable (default unknown)
set(ARCH "unknown")

# Identify x86_64 architecture (compatible with different system return values)
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
    set(ARCH "x86_64")
# Identify arm64/aarch64 architecture
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    set(ARCH "aarch64")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}, please check if there is a library for the corresponding architecture in the lib directory")
endif()

message(STATUS "Detected system architecture: ${ARCH}")

# Library file path: parent directory -> lib/zsl-1/architecture directory
set(LIB_PATH "${CMAKE_SOURCE_DIR}/../../../lib/zsl-1/${ARCH}")
message(STATUS "Library path to be linked: ${LIB_PATH}")

# Find the library for the corresponding architecture (library file name is libmc_sdk_zsl_1_${ARCH}.so)
find_library(MC_SDK_LIB 
    NAMES "mc_sdk_zsl_1_${ARCH}"  # Library name (without prefix lib and suffix .so)
    PATHS ${LIB_PATH}
    NO_DEFAULT_PATH  # Only search in specified path to avoid finding other versions
    REQUIRED
)

# Verify that the library was found
if(NOT MC_SDK_LIB)
    message(FATAL_ERROR "Library file mc_sdk_zsl_1_${ARCH}.so not found in ${LIB_PATH}, please check if the library exists")
else()
    message(STATUS "Found library file: ${MC_SDK_LIB}")
endif()

# highlevel example
add_executable(highlevel_demo highlevel_demo.cpp)
target_link_libraries(highlevel_demo ${MC_SDK_LIB})
target_include_directories(highlevel_demo PRIVATE 
    ${CMAKE_SOURCE_DIR}/../../../include  # Public headers
    ${CMAKE_SOURCE_DIR}/../../../include/zsl-1  # ZSL-1 exclusive headers
)

# lowlevel example
add_executable(lowlevel_demo lowlevel_demo.cpp)
target_link_libraries(lowlevel_demo ${MC_SDK_LIB})
target_include_directories(lowlevel_demo PRIVATE 
    ${CMAKE_SOURCE_DIR}/../../../include 
    ${CMAKE_SOURCE_DIR}/../../../include/zsl-1
)
```

---

#### ZSL-1w (CMake Path Difference)
Consistent with ZSL-1 configuration, only need to change the `<model>` in the library and header file paths to `zsl-1w`:
```cmake
# Library file path: lib/zsl-1w/${ARCH}
set(LIB_PATH "${CMAKE_SOURCE_DIR}/../../../lib/zsl-1w/${ARCH}")

# Find library: mc_sdk_zsl_1w_${ARCH}
find_library(MC_SDK_LIB 
    NAMES "mc_sdk_zsl_1w_${ARCH}"
    PATHS ${LIB_PATH}
    NO_DEFAULT_PATH
    REQUIRED
)

# Header file include paths
target_include_directories(highlevel_demo PRIVATE 
    ${CMAKE_SOURCE_DIR}/../../../include
    ${CMAKE_SOURCE_DIR}/../../../include/zsl-1w
)
```



### 4.5 Using mc_sdk Based on Python
#### ZSL-1
```python
import os
import platform
import sys
arch = platform.machine().replace('amd64', 'x86_64').replace('arm64', 'aarch64')
lib_path = os.path.abspath(f'{os.path.dirname(__file__)}/../../../../lib/zsl-1/{arch}')
sys.path.insert(0, lib_path)

import mc_sdk_zsl_1_py
```


#### ZSL-1w
```python
import os, platform, sys
arch = platform.machine().replace('amd64', 'x86_64').replace('arm64', 'aarch64')
lib_path = os.path.abspath(f'{os.path.dirname(__file__)}/../../../../lib/zsl-1w/{arch}')
sys.path.insert(0, lib_path)

import mc_sdk_zsl_1w_py
```



  
