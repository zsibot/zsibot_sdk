#pragma once
#include <memory>
#include <mutex>
#include <vector>
namespace mc_sdk {

struct alignas(4) motorCmd {
  float q_des_abad[4] = {0.0, 0.0, 0.0, 0.0};  // A关节角度指令
  float q_des_hip[4] = {0.0, 0.0, 0.0, 0.0};   // H关节角度指令
  float q_des_knee[4] = {0.0, 0.0, 0.0, 0.0};  // K关节角度指令

  float qd_des_abad[4] = {0.0, 0.0, 0.0, 0.0};  // A关节角速度指令
  float qd_des_hip[4] = {0.0, 0.0, 0.0, 0.0};   // H关节角速度指令
  float qd_des_knee[4] = {0.0, 0.0, 0.0, 0.0};  // K关节角速度指令

  float kp_abad[4] = {0.0, 0.0, 0.0, 0.0};  // A关节Kp值
  float kp_hip[4] = {0.0, 0.0, 0.0, 0.0};   // H关节Kp值
  float kp_knee[4] = {0.0, 0.0, 0.0, 0.0};  // K关节Kp值

  float kd_abad[4] = {0.0, 0.0, 0.0, 0.0};  // A关节Kd值
  float kd_hip[4] = {0.0, 0.0, 0.0, 0.0};   // H关节Kd值
  float kd_knee[4] = {0.0, 0.0, 0.0, 0.0};  // K关节Kd值

  float tau_abad_ff[4] = {0.0, 0.0, 0.0, 0.0};  // A关节扭矩指令
  float tau_hip_ff[4] = {0.0, 0.0, 0.0, 0.0};   // H关节扭矩指令
  float tau_knee_ff[4] = {0.0, 0.0, 0.0, 0.0};  // K关节扭矩指令
};

struct alignas(4) motorState {
  // 关节顺序 FL,FR,RL,RR
  float q_abad[4] = {0.0, 0.0, 0.0, 0.0};  // A关节角度
  float q_hip[4] = {0.0, 0.0, 0.0, 0.0};   // H关节角度
  float q_knee[4] = {0.0, 0.0, 0.0, 0.0};  // K关节角度

  float qd_abad[4] = {0.0, 0.0, 0.0, 0.0};  // A关节角速度
  float qd_hip[4] = {0.0, 0.0, 0.0, 0.0};   // H关节角速度
  float qd_knee[4] = {0.0, 0.0, 0.0, 0.0};  // K关节角速度

  float tau_abad_fb[4] = {0.0, 0.0, 0.0, 0.0};  // A关节扭矩反馈
  float tau_hip_fb[4] = {0.0, 0.0, 0.0, 0.0};   // H关节扭矩反馈
  float tau_knee_fb[4] = {0.0, 0.0, 0.0, 0.0};  // K关节扭矩反馈
};

class LowLevel {
 private:
  struct lowLevelFunc;
  std::shared_ptr<lowLevelFunc> impl_;

 public:
  LowLevel();
  ~LowLevel();
  void initRobot(const std::string &local_ip, const int local_port,
                 const std::string &dog_ip = "192.168.234.1");
  bool checkConnect();
  int sendMotorCmd(const motorCmd &cmd);
  std::vector<float> getQuaternion();
  std::vector<float> getRPY();
  std::vector<float> getBodyAcc();
  std::vector<float> getBodyGyro();

  motorState *getMotorState();
  bool haveMotorData();
};

}  // namespace mc_sdk