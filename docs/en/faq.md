# Notes and Frequently Asked Questions

## Notes
!!! danger "Device Battery"
    When controlling with SDK, the device has no protection mechanism. When the device battery is below a certain threshold, the device may shut down directly. If the device is in operation, it may cause personal injury or equipment damage. Please pay attention to the device battery.
!!! danger "WiFi Signal Interference"
    It is recommended to mount a computing board on the device and connect to the robot dog via cable when running SDK programs to avoid WiFi signal interference that causes delay in control data transmission.
## Exception Handling
### 1. Connect Time Out
After running the SDK program, there is a connection timeout with the prompt message:
```shell
client bind success
connect time out
error async receive from
```

1. Please follow the document [Modify SDK Configuration File](deploy.md#22-sdk) target_ip parameter.
2. If non-WiFi direct connection is used for communication with the device, you also need to follow the document [Modify SDK_CLIENT_IP](deploy.md#23-sdk_client_ip) parameter.
3. When using non-WiFi direct connection, there is a probability that the motion control binding SDK will fail. Please follow the document [Motion Control Binding IP Failure](#2-ip) parameter.

!!! warning "Parameters need to be restarted to take effect after configuration!"
    
### 2. Motion Control Binding IP Failure
After configuring `SDK_CLIENT_IP`, when using wlan0 network or eth0 network for SDK control, there may be cases where the device's network is not initialized after startup and the corresponding network card is not assigned an IP address, causing the motion control program to fail to bind the IP address.

Specifically manifested as the SDK program running and prompting: `connect time out`. By logging into the device controller and executing the command `sudo lsof -i -P -n -c mc_ctrl|grep 43997` to check the output content, the motion control corresponding port is not bound. And the remote controller cannot be used.

Modifying the `/etc/systemd/system/robot-launch.service` file configuration inside the device controller can fix this. Add a line `Environment="ROBOT_NET_INTERFACES=wlan0"` inside Service, where `wlan0` is the corresponding network card name. If using wired network, it can be modified to `eth0`.

Complete configuration file as follows:
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

!!! warning "Parameters need to be restarted to take effect after configuration!"
!!! danger "There is a probability that configuring this parameter will cause the robot dog program to fail to start!"
    After configuring ROBOT_NET_INTERFACES, the program will detect whether the configured network card is assigned an IP. If the network card never gets an IP, it will cause the robot dog program to fail to start.
    
### 3. Using wlan0, Device Does Not Automatically Connect After Reboot
There is a conflict between AP and wlan network card on the device. Some versions have a function to clear automatic connections. If you need to disable the automatic connection clearing function, you can execute the following commands:
```bash
sudo systemctl stop networkmanager-cleanup.service      //Stop network cleanup service
sudo systemctl disable networkmanager-cleanup.service   //Disable network cleanup service
```

### 4. Gamepad Remote Controller Cannot Control
The following situations may cause the gamepad to be unable to control, and troubleshooting is needed based on the situation

1. Motion control program not started
    - If [ROBOT_NET_INTERFACES](faq.md#2-ip) is configured, the program will detect whether the configured network card is assigned an IP when the device starts. If the network card never gets an IP, the motion control program cannot start. You need to ensure that the configured network interface is always assigned an IP.
2. SDK program is running
    - SDK control has higher priority than the gamepad program. When the SDK program is running, the gamepad remote controller will not be able to control the device.


## Frequently Asked Questions (FAQ)

**Q: Demo doesn't have zsm-1w?**  
A: The current repository does not provide official zsm-1w demos. You can quickly migrate by referring to the `zsl-1w` example: replace the library path and header file to get it working.

**Q: Python import failed?**  
A: Confirm whether the script adds `lib/<model>/<arch>` to `sys.path`; the Python version needs to match the extension module (e.g., `cp310` indicates Python 3.10).

**Q: C++ linking failed?**  
A: Confirm that there is a corresponding `.so` file in `lib/<model>/<arch>`; ensure that CMake detects the correct architecture (`x86_64` / `aarch64`).

**Q: What frequency does the device status acquisition interface support in motion control?**  
A: 500Hz for lowlevel, 50Hz for highlevel.

**Q: What frequency does the control interface in SDK support?**  
A: Control data can be sent at a maximum of 500Hz, generally 20~50Hz is sufficient to ensure stable operation of the device.

**Q: Is the SDK program thread-safe?**  
A: The SDK program is thread-safe.

**Q: Does the SDK have communication detection?**  
A: The motion control program will detect whether SDK data is continuously received. If no data is received within 3 seconds, it is considered that the SDK communication is interrupted, and the device will automatically switch to damping mode and lie down.

**Q: When starting the motion control program through service inside the machine, how to avoid the machine's own program not starting?**  
A: The After parameter in service can be configured as robot-launch. The robot-launch service will start the machine's own program.

**Q: Can gamepad remote control and SDK remote control switch simultaneously?**  
A: In the current version, SDK has higher priority than gamepad remote control, and simultaneous switching is not possible.

**Q: Is the IMU data obtained raw data?**  
A: The IMU data obtained is raw data.

**Q: The IMU data obtained seems to have errors?**  
A: The IMU data inside the device body is affected by product model, and accuracy may have errors. If higher precision IMU is required, a high-precision IMU needs to be purchased separately for use on the upper body.

**Q: After using SDK control, when using gamepad remote control to control the device, why does the device do 'push-ups' in place after sending the stand command?**  
A: If the [SDK_CLIENT_IP](deploy.md#23-sdk_client_ip) parameter is configured, the motion control will bind the corresponding IP at startup. If the IP does not exist, this phenomenon will occur.  

**Q: What is the rotation order when converting quaternions to Euler angles?**  
A: The Euler angle order is ZYX, i.e., first rotate around the Z-axis, then the Y-axis, and finally the X-axis.

**Q: Can Highlevel and Lowlevel be used simultaneously?**  
A: Highlevel and Lowlevel cannot be used simultaneously, and when switching between the two interfaces, a certain amount of time should be reserved for the device port to be released.

**Q: Why can't the device be controlled by SDK after upgrading the motion control program?**  
A: After upgrading the motion control program, the motion control related configurations will be overwritten, and the [SDK_CONFIG](deploy.md#22-sdk) and [SDK_CLIENT_IP](deploy.md#23-sdk_client_ip) parameters need to be reconfigured.

**Q: Is there a ROS interface?**  
A: There is currently no ROS interface.

**Q: When using the SDK, the program gets stuck in the initRobot function and doesn't proceed?**  
A: The SDK depends on boost 1.74.0 version. If an older version is used, there may be compatibility issues due to structural changes.