import matplotlib.pyplot as plt
import numpy as np


# move average function
def np_mov_avg(a, n, mode="same"):
    return np.convolve(a, np.ones((n,)) / n, mode=mode)


# rmse
def windows_rms(a, window_size):
    a2 = np.power(a, 2)
    window = np.ones((window_size, )) / window_size
    return np.sqrt(np.convolve(a2, window, mode="same"))


input_txt = '[2021-1-15 14:43:29:621]m8_3000.txt'

rev = []
motor_mVol_raw = []
motor_current_true = []

motor_current_rms = []
motor_current_cm720 = []

file = open(input_txt)

for line in file:
    line = line.strip('\n')
    line = line.split(' ')

    rev.append(float(line[-4]))
    motor_mVol_raw.append(float(line[-3]))
    motor_current_rms.append(float(line[-2]))
    motor_current_cm720.append(float(line[-1]))
# time_cost_M1_FH = 9 * 60 + 49
# time_cost_M7_FR = 6 * 60 + 44
time_cost_no_load = 5 * 60 + 52
time_axis = np.linspace(0, time_cost_no_load, len(rev))
time_axis = time_axis[-400:-1]
file.close()

# np_motor_current = np.array(motor_current)
# np_motor_current_true = np.array(motor_current_true)
# # np_motor_current = (9.9 / 820) * np_motor_current
# np_motor_current_true = np_motor_current_true / 100
# np_avg_current = np_mov_avg(np_motor_current, 50)
# np_motor_current_rms = windows_rms(np_motor_current, 50)
# np_motor_current_true_rms = windows_rms(np_motor_current_true, 50)
motor_speed_np = np.array(rev)
motor_mVol_np = np.array(motor_mVol_raw)
motor_current_raw_np = 0.01442504 * motor_mVol_np - 1.69037332
motor_current_rms_np = np.array(motor_current_rms)
motor_current_raw_avg_np = np_mov_avg(motor_current_rms_np, 100)
# motor_current_rms_np = 0.01442504 * motor_current_rms_np - 1.69037332   # ???
motor_current_cm720_np = np.array(motor_current_cm720)

print(np.argmax(motor_current_rms_np))
title = "RMS-filter result (M8)"
plt.title(title)

plt.ylim(0, 20)
plt.plot(time_axis, motor_current_raw_np[-400:-1], color="brown", label="raw", marker="o")
plt.plot(time_axis, motor_current_rms_np[-400:-1], color="blue", label="rms", marker=">")
plt.plot(time_axis, motor_current_raw_avg_np[-400:-1], color="red", label="avg", marker="x")
# plt.plot(time_axis, motor_current_cm720_np[-50:-1], color="red", label="current_cm7290", marker=">")
# plt.plot(time_axis, motor_current_rms_np, color="green", label="current_loop_rms")
# plt.plot(time_axis, motor_current_cm720_np, color="red", label="current_cm7290")
plt.ylabel('Current /A')
plt.xlabel('Time /s')
plt.legend()

# plt.subplot(122)
# plt.ylim(0, 20)
# plt.plot(time_axis, motor_current_rms_np[-100:-1], color="blue", label="current_loop_rms", marker=">")
# plt.plot(time_axis, motor_current_cm720_np[-50:-1], color="red", label="current_cm7290", marker=">")
# plt.plot(time_axis, motor_current_rms_np, color="green", label="current_loop_rms")
# plt.plot(time_axis, motor_current_cm720_np, color="red", label="current_cm7290")
# plt.ylabel('Current /A')
# plt.xlabel('Time /s')
# plt.legend()

# plt.subplot(211)
# plt.title(title)
# # plt.ylim(0, 1500)
# plt.plot(time_axis, motor_speed_np[0:2300], color="blue", label="motor_test_speed")
# plt.ylabel('Speed /rpm')
# plt.legend()

# plt.subplot(212)
# plt.ylim(0, 10)
# plt.plot(time_axis, motor_current_cm720_np[0:2300], color="red", label="current_cm7290")
# plt.ylabel('Current /A')
# plt.legend()
# plt.xlabel('time /s')

plt.tight_layout()
plt.draw()
# plt.legend()
# plt.savefig(title)
plt.show()

stable_current = np.average(motor_current_cm720_np[50:100])
stable_rev = np.average(motor_speed_np[50:100])
print("Current is {} and rev is {}".format(stable_current, stable_rev))
# time_long = len(time_axis)
# mean_motor_current = np.average(np_motor_current_rms[int(time_long/3):int(time_long/3*2)])
# mean_motor_current_true = np.average(np_motor_current_true_rms[int(time_long/3):int(time_long/3*2)])
# print("current and true current : ", mean_motor_current, " ", mean_motor_current_true)
