# 注意事项与常见问题

## 注意事项
!!! danger "设备电量"
    使用SDK控制时设备没有保护机制，当设备电量低于一定阈值，可能会存在设备直接断电情况，若设备处于运行状态，可能会造成人员受伤或设备损坏。请关注设备电量。
!!! danger "WiFi信号干扰"
    运行SDK程序建议在设备上搭载算力板，通过网线与机器狗连接，避免WiFi信号干扰，导致控制时数据传输延迟。
## 异常处理
### 1. connect time out
运行SDK程序后存在连接超时，提示信息为：
```shell
client bind success
connect time out
error async receive from
```

1. 请按照文档[修改SDK配置文件中](deploy.md#22-sdk)target_ip参数。
2. 若与设备通讯采用非WiFi直连，还需按照文档[修改SDK_CLIENT_IP](deploy.md#23-sdk_client_ip)参数。
3. 非WiFi直连时，设备会有概率出现运控绑定SDK失败，请按照文档[运控绑定IP失败](#2-ip)参数。

!!! warning "参数配置后需进行重启设备生效！"
    
### 2. 运控绑定IP失败
在配置`SDK_CLIENT_IP`后，若使用wlan0网络或者eth0网络进行SDK控制时，会存在设备开机后网络未初始化完成，对应网卡未分配IP地址，导致运控程序绑定IP地址失败。

具体表现为SDK程序运行后提示：`connect time out`，通过登录设备主控后，执行命令`sudo lsof -i -P -n -c mc_ctrl|grep 43997`查看输出内容,运控对应端口未被绑定。且遥控器无法使用。

通过修改设备主控内`/etc/systemd/system/robot-launch.service`文件配置可修复，在Service里面添加一行`Environment="ROBOT_NET_INTERFACES=wlan0"`其中`wlan0`为对应网卡名称，若使用有线网络可修改为`eth0`。

完整配置文件如下：
```service hl_lines="13" 
[Unit]
Description=Run robot-launch at startup
After=network.target

[Service]
ExecStart=robot-launch server
ExecStop=/usr/local/bin/robot_launch_stop.sh
TimeoutStopSec=5s
Restart=always
User=root
Environment="ROBOT_HOME=/home/firefly"
Environment="ROBOT_LOG_DIR=/userdata/log"
Environment="ROBOT_NET_INTERFACES=wlan0"

[Install]
WantedBy=multi-user.target
```

!!! warning "参数配置后需进行重启设备生效！"
!!! danger "此参数配置后有概率导致机器狗程序无法启动！"
    配置ROBOT_NET_INTERFACES后程序会检测所配置网卡是否被分配IP，若网卡始终没有IP，则会导致机器狗程序无法启动。

### 3. 使用wlan0，重启设备不会自动连接
设备上AP与wlan网卡存在冲突，部分版本有清除自动连接功能，若需要关闭清除自动连接功能，可执行以下命令：
```bash
sudo systemctl stop networkmanager-cleanup.service      //关闭网络清除服务
sudo systemctl disable networkmanager-cleanup.service   //禁用网络清除服务
```

### 4. 手柄遥控器无法控制
以下几种情况都可能导致手柄无法控制，需要根据情况进行排查

1. 运控程序未启动
    - 如果配置了[ROBOT_NET_INTERFACES](faq.md#2-ip),会在设备启动时检测所配置网卡是否被分配IP，若网卡始终没有IP，则运控程序无法启动，需要保证配置的网口始终被分配IP。
2. 运行了SDK程序
    - SDK控制优先级高于手柄程序，SDK程序运行时，手柄遥控器将无法控制设备。


## 常见问题（FAQ）

<!-- **Q: Demo 里没有 zsm-1w？**   -->
<!-- A: 当前仓库未提供 zsm-1w 官方 demo。可参考 `zsl-1w` 示例快速迁移：替换库路径与头文件，即可跑通。 -->

**Q: Python 导入失败？**  
A: 确认脚本是否将 `lib/<model>/<arch>` 加入 `sys.path`；Python 版本需与扩展模块匹配（`cp310` 表示 Python 3.10）。

**Q: C++ 链接失败？**  
A: 确认 `lib/<model>/<arch>` 中存在对应 `.so` 文件；确保 CMake 检测到正确架构（`x86_64` / `aarch64`）。

**Q: 运控中获取设备状态获取接口支持频率？**  
A: lowlevel 的500hz, highlevel的50hz。

**Q: SDK中控制接口支持频率？**  
A: 控制数据最大可以支持500hz发送，一般来说20~50hz就可以保证设备稳定运行。

**Q: SDK程序是否为线程安全？**  
A: SDK程序为线程安全。

**Q: SDK是否存在通讯检测？**  
A: 运控程序会检测是否持续收到SDK数据，若3秒内未收到数据，则认为SDK通讯中断，设备会自动切换阻尼模式趴下。

**Q: 在机器内通过service启动运控程序时，如何避免机器自身程序未启动？**  
A: service中After参数可以配置为robot-launch，robot-launch服务会启动机器自身程序。

**Q: 手柄遥控和sdk遥控可以同时切换吗？**  
A: 当前版本SDK优先级高于手柄遥控，无法同时切换。

**Q: 获取到的IMU数据是否是原始数据？**  
A: 获取到的IMU数据是原始数据。

**Q: 获取到的IMU数据感觉存在误差？**  
A: 设备体内IMU数据受产品型号影响，精度存在误差，若对IMU精度有更高要求，需要单独采购高精度IMU在上身使用。

**Q: 使用过SDK控制后，再使用手柄遥控控制设备时，发送站立指令为什么设备会原地做‘俯卧撑’？**  
A: 如果配置过[SDK_CLIENT_IP](deploy.md#23-sdk_client_ip)参数，则运控启动时会绑定对应IP，若IP不存在，则会导致此现象。  

**Q: 四元数转换为欧拉角时，旋转顺序是什么？**  
A: 欧拉角顺序为ZYX，即先Z轴旋转，再Y轴旋转，最后X轴旋转。

**Q: Highlevel与Lowlevel可以同时使用吗？**  
A: Highlevel与Lowlevel不可以同时使用，且在切换两种接口时，要预留一定时间等待设备端口释放。

**Q: 为什么运控程序升级后，SDK无法控制设备？**  
A: 运控程序升级后，运控相关配置会被覆盖，需要重新配置[SDK_CONFIG](deploy.md#22-sdk)与[SDK_CLIENT_IP](deploy.md#23-sdk_client_ip)参数。

**Q: 是否有ROS接口？**  
A: 暂无ROS接口。

**Q: 使用SDK时，程序卡在initRobot函数不往下执行了？**  
A: SDK依赖boost 1.74.0版本，若使用版本过旧，可能存在结构体变化导致的兼容性问题。