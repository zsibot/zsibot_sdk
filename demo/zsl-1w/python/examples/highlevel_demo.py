import os
import platform
import sys
arch = platform.machine().replace('amd64', 'x86_64').replace('arm64', 'aarch64')
lib_path = os.path.abspath(f'{os.path.dirname(__file__)}/../../../../lib/zsl-1w/{arch}')

sys.path.insert(0, lib_path)
import mc_sdk_zsl_1w_py
import time

app=mc_sdk_zsl_1w_py.HighLevel()
app.initRobot("127.0.0.1",43988, "127.0.0.1") #local_ip, local_port, dog_ip
app.standUp()
time.sleep(4)
app.move(0.1, 0, 0)
time.sleep(5)
app.standUp()
time.sleep(4)
app.attitudeControl(0.1,0.1,0.1,0.1)
time.sleep(4)
app.crawl(1.0, 0.0, 0.0)
time.sleep(5)
while True:
    time.sleep(2)
