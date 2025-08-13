import os
import platform
import sys
arch = platform.machine().replace('amd64', 'x86_64').replace('arm64', 'aarch64')
lib_path = os.path.abspath(f'{os.path.dirname(__file__)}/../../../../lib/zsl-1/{arch}')

sys.path.insert(0, lib_path)
import mc_sdk_zsl_1_py
import time

class MotorControl:
    def __init__(self):
        self.motor_func = mc_sdk_zsl_1_py.LowLevel()
        self.motor_func.initRobot("127.0.0.1",43988, "127.0.0.1") #local_ip, local_port, dog_ip
        self.init_q_abad = [0.0] * 4
        self.init_q_hip = [0.0] * 4
        self.init_q_knee = [0.0] * 4
        self.duration = 2.0
        self.default_abad_pos = 0.0
        self.default_hip_pos = 1.4
        self.default_knee_pos = -2.4
        self.stage1_progress = 0.0
        self.stage2_progress = 0.0
        self.stage = 0
        self.stage2_start = False
        self.first_trigger = False

    def run(self):
        while True:
            # 获取机器狗数据
            state = self.motor_func.getMotorState()

            if self.motor_func.haveMotorData():
                if not self.first_trigger:
                    self.first_trigger = True
                    for i in range(4):
                        self.init_q_abad[i] = state.q_abad[i]
                        self.init_q_hip[i] = state.q_hip[i]
                        self.init_q_knee[i] = state.q_knee[i]

                self.stage1_progress += 0.002
                ratio = self.stage1_progress / self.duration
                if ratio > 1.0:
                    ratio = 1.0
                    self.stage = 1
                
                if self.stage == 1:
                    self.default_abad_pos = 0.0
                    self.default_hip_pos = 0.8
                    self.default_knee_pos = -1.5
                    self.stage2_progress += 0.002
                    ratio = self.stage2_progress / self.duration
                    if ratio > 1.0:
                        ratio = 1.0
                    
                    if not self.stage2_start:
                        self.stage2_start = True
                        for i in range(4):
                            self.init_q_abad[i] = state.q_abad[i]
                            self.init_q_hip[i] = state.q_hip[i]
                            self.init_q_knee[i] = state.q_knee[i]

                cmd = mc_sdk_zsl_1_py.MotorCommand()
                for i in range(4):
                    cmd.q_des_abad[i] = ratio * self.default_abad_pos + (1.0 - ratio) * self.init_q_abad[i]
                    cmd.q_des_hip[i] = ratio * self.default_hip_pos + (1.0 - ratio) * self.init_q_hip[i]
                    cmd.q_des_knee[i] = ratio * self.default_knee_pos + (1.0 - ratio) * self.init_q_knee[i]
                    cmd.kp_abad[i] = 80
                    cmd.kp_hip[i] = 80
                    cmd.kp_knee[i] = 80
                    cmd.kd_abad[i] = 1
                    cmd.kd_hip[i] = 1
                    cmd.kd_knee[i] = 1

                ret = self.motor_func.sendMotorCmd(cmd)
                if ret < 0:
                    print("send cmd error")

            time.sleep(0.002)  # 等待 2 毫秒

    def stop(self):
        cmd = mc_sdk_zsl_1_py.MotorCommand()
        for i in range(4):
            cmd.q_des_abad[i] = 0.0
            cmd.q_des_hip[i] = 0.0
            cmd.q_des_knee[i] = -1.5
            cmd.kp_abad[i] = 0.0
            cmd.kp_hip[i] = 0.0
            cmd.kp_knee[i] = 0.0
            cmd.kd_abad[i] = 3.0
            cmd.kd_hip[i] = 3.0
            cmd.kd_knee[i] = 3.0
        flag = True
        send_msg_count = 0
        while flag:
            ret = self.motor_func.sendMotorCmd(cmd)
            if ret < 0:
                print("send cmd error")
            send_msg_count += 1
            if send_msg_count > 1500:
                flag = False
            time.sleep(0.002)  # 等待 2 毫秒

if __name__ == "__main__":
    motor_control = MotorControl()
    try:
        motor_control.run()
    except KeyboardInterrupt:
        motor_control.stop()
