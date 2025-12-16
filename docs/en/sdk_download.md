# How to Download and Update SDK
## 📖Description

The SDK program communicates with the quadruped robot body program through a specific protocol, so there are differences in communication between different versions of SDK programs and robot body programs. Please select the corresponding version of SDK program according to the device version.

If conditions permit, it is recommended to update the robot program to the latest version for better compatibility.

When controlling with SDK, all states are designed and specified by secondary developers, and the body motion control does not perform additional intervention or state transitions.

When running SDK, please ensure that the system has sufficient resources, otherwise the motion control module may fail.

---
## 📖Version Query
Query the quadruped robot body program version:
After logging into the device, execute the following command to check the current device version:
```bash
grep -oP 'motion-control_\K[^_]+' /etc/release/*[^rootfs]*.yaml
```
If the command does not show output like: `/etc/release/602002057TCA.yaml:0.2.6`, it means the device version is too old and you need to contact customer service for an upgrade.
According to the output content number after executing the command, refer to the table below to query the corresponding version:

!!! info "Version Description"
    Some SDK versions support multiple motion control versions. When a new SDK version is released, the version number will be named after the currently supported motion control version. For example: motion control 0.2.6-0.2.9 is version 0.2.6, motion control 0.3.0 is version 0.3.0.  
    Therefore, there may not be versions 0.2.7~0.2.9 in the SDK. If the new SDK version is compatible with the old motion control, the corresponding SDK version will be incrementally named after the previous version.

### Quadruped Point-Foot (zsl-1)

| Motion Control Version Number | SDK Version |
| --- | --- |
| 0.2.6 ~ Latest | [0.2.7](https://github.com/zsibot/zsibot_sdk) |
<!-- | 0.2.6 ~ Latest | [0.2.7](https://github.com/zsibot/zsibot_sdk/tree/v0.2.7) | -->


### Quadruped Wheel-Legged (zsl-1w)

| Motion Control Version Number | SDK Version |
| --- | --- |
| 0.3.1 ~ Latest | [0.2.7](https://github.com/zsibot/zsibot_sdk) |
<!-- | 0.3.1 ~ Latest | [0.2.7](https://github.com/zsibot/zsibot_sdk/tree/v0.2.7) | -->
