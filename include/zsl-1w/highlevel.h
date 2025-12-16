#pragma once
#include <memory>
#include <mutex>
#include <string>
#include <vector>
namespace mc_sdk {
namespace zsl_1w {

class HighLevel {
 private:
  struct highLevelFunc;
  std::shared_ptr<highLevelFunc> impl_;

 public:
  HighLevel();
  ~HighLevel();
  void initRobot(const std::string& local_ip, const int local_port,
                 const std::string& dog_ip = "192.168.234.1");
  bool checkConnect();
  uint32_t standUp();
  uint32_t lieDown();
  uint32_t passive();
  uint32_t move(const float vx, const float vy, const float yaw_rate);

  uint32_t crawl(const float vx, const float vy, const float yaw_rate);
  void cancelCrawl();
  uint32_t shakeHand();
  uint32_t attitudeControl(const float roll_vel, const float pitch_vel,
                           const float yaw_vel, const float height_vel);

  std::vector<float> getQuaternion();
  std::vector<float> getRPY();
  std::vector<float> getBodyAcc();
  std::vector<float> getBodyGyro();
  std::vector<float> getPosition();
  std::vector<float> getWorldVelocity();
  std::vector<float> getBodyVelocity();

  uint32_t getBatteryPower();     //获取电池电量
  uint32_t getCurrentCtrlmode();  // 获取当前机器狗控制状态

  std::vector<float> getLegAbadJoint();
  std::vector<float> getLegHipJoint();
  std::vector<float> getLegKneeJoint();
  std::vector<float> getLegFootJoint();

  std::vector<float> getLegAbadJointVel();
  std::vector<float> getLegHipJointVel();
  std::vector<float> getLegKneeJointVel();
  std::vector<float> getLegFootJointVel();

  std::vector<float> getLegAbadJointTorque();
  std::vector<float> getLegHipJointTorque();
  std::vector<float> getLegKneeJointTorque();
  std::vector<float> getLegFootJointTorque();
};

}  // namespace zsl_1w
}  // namespace mc_sdk
