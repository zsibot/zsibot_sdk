# Changelog

## 2025-11-04
[v0.2.7]

- support zsl-1w product

- add lowlevel interface

- change checkconnect default value to false

---

## 2025-09-15
[v0.2.6-patch1]

- fix checkconnect bug

---

## 2025-07-19
[v0.2.6]

- Updating interface

### Highlevel

#### Removed interface

- `getRoll()`
- `getPitch()`
- `getYaw()`
- `getAccelX()`
- `getAccelY()`
- `getAccelZ()`
- `getGyroX()`
- `getGyroY()`
- `getGyroZ()`
- `getPosWorldX()`
- `getPosWorldY()`
- `getPosWorldZ()`
- `getWorldVelX()`
- `getWorldVelY()`
- `getWorldVelZ()`
- `getBodyVelX()`
- `getBodyVelY()`
- `getBodyVelZ()`

#### Added interface

- `checkConnect()`
- `shakeHand()`
- `twoLegStand()`
- `cancleTwoLegStand()`
- `getQuaternion()`
- `getRPY()`
- `getBodyAcc()`
- `getBodyGyro()`
- `getPosition()`
- `getWorldVelocity()`
- `getBodyVelocity()`
- `getLegAbadJoint()`
- `getLegHipJoint()`
- `getLegKneeJoint()`
- `getLegAbadJointVel()`
- `getLegHipJointVel()`
- `getLegKneeJointVel()`
- `getLegAbadJointTorque()`
- `getLegHipJointTorque()`
- `getLegKneeJointTorque()`

### Lowlevel

#### Removed interface

- `getRoll()`
- `getPitch()`
- `getYaw()`
- `getAccelX()`
- `getAccelY()`
- `getAccelZ()`
- `getGyroX()`
- `getGyroY()`
- `getGyroZ()`

#### Added interface

- `checkConnect()`
- `getQuaternion()`
- `getRPY()`
- `getBodyAcc()`
- `getBodyGyro()`
---
## 2025-07-18

Fix issues

---
## 2025-07-16

Initial release
