# How to Debug

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
2. 若与设备通讯采用非WiFi直连，还需按照文档[修改SDK_CLIENT_IP](deploy.md#23-sdk_client_ip)参数。非WiFi直连时，设备会有概率出现运控绑定SDK失败，请按照文档[运控绑定IP失败](#2-ip)参数。

!!! warning "参数配置后需进行重启设备生效！"
    
### 2. 运控绑定IP失败
在配置`SDK_CLIENT_IP`后，若使用wlan0网络或者eth0网络进行SDK控制时，会存在设备开机后网络未初始化完成，对应网卡未分配IP地址，导致运控程序绑定IP地址失败。

具体表现为SDK程序运行后提示：`connect time out`，通过登录设备主控后，执行命令`sudo lsof -i -P -n -c mc_ctrl|grep 43997`查看输出内容,运控对应端口未被绑定。

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

### 3. 使用wlan0连接环境wifi，每次重启设备都不会自动连接
设备上AP与wlan网卡存在冲突，部分版本有清除自动连接功能，若需要关闭清除自动连接功能，可执行以下命令：
```bash
sudo systemctl stop networkmanager-cleanup.service      //关闭网络清除服务
sudo systemctl disable networkmanager-cleanup.service   //禁用网络清除服务
```

## FAQ
1. Q1:运控中获取设备状态接口支持频率?
    - lowlevel 的500hz, highlevel的50hz
2. Q2: 运控中请求接口支持频率?
    - 请求数据需要以500hz发送才能保证设备稳定运行