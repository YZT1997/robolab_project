#!/usr/bin/env python
# coding=utf-8

import rospy
from std_msgs.msg import Float32
from std_msgs.msg import Int64
import numpy as np
import requests
import threading


# 数据格式定义：m5: time, speed, cm7290 current

class Interpreter:
    def __init__(self):
        self.init_time = rospy.get_rostime()
        self.time = 0
        self.cm7290_current = []
        self.motor_speed = []

        # 把后边可能用到的 sub, pub 在初始化函数中定义好
        # 数据内容：time,car_speed,reel_speed,cb_speed,reel_current,cm7290_current,cb_current
        rospy.Subscriber('/current_cm7290', Float32, self.callback_cm7290_current)
        rospy.Subscriber('/motor_test_speed', Int64, self.callback_motor_speed)

        self.time_thread = threading.Thread(target=self.time_get_job)
        self.time_thread.start()
        self.callback_thread = threading.Thread(target=self.call_back_jobs)
        self.callback_thread.start()

    ## callback functions ##

    def callback_cm7290_current(self, data):
        msg = data.data
        self.cm7290_current.append(np.array([self.time, msg]))

    def callback_motor_speed(self, data):
        msg = data.data
        self.motor_speed.append(np.array([self.time, msg]))

    ## thread functions ##
    def call_back_jobs(self):
        rospy.spin()

    def time_get_job(self):
        while not rospy.is_shutdown():
            time_duration = rospy.get_rostime() - self.init_time
            self.time = time_duration.to_sec()
            # print 'time:' + str(self.time)

    ## save data ##
    def save_data_to_npy(self):
        # 数据内容：time,car_speed,reel_speed,cb_speed,reel_current,cm7290_current,cb_current
        cm7290_current_npy = np.stack(self.cm7290_current)
        np.save("m10_cm7290_current.npy", cm7290_current_npy)
        motor_speed_npy = np.stack(self.motor_speed)
        np.save("m10_motor_speed.npy", motor_speed_npy)

if __name__ == '__main__':
    rospy.init_node('interpreter')
    try:
        convertor = Interpreter()
        while not rospy.is_shutdown():
            print 'Converting...'
            rospy.sleep(1)
        convertor.save_data_to_npy()
        print 'All data have been save as npy files.'
        convertor.callback_thread.join()
        convertor.time_thread.join()
        print 'Convertor exited.'

    except rospy.ROSInterruptException:
        pass
