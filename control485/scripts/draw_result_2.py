import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

car_speed_np = np.load("m87_car_speed.npy", allow_pickle=True)
m7_current_np = np.load("m87_cb_current.npy", allow_pickle=True)
m7_speed_np = np.load("m87_cb_speed.npy", allow_pickle=True)
m8_current_np = np.load("m87_reel_current.npy", allow_pickle=True)
m8_speed_np = np.load("m87_reel_speed.npy", allow_pickle=True)
# 移除离群点

# m7_current_np = np.delete(m7_current_np, (0, 1, 2), 0)
# m7_current_np[0:100, 1] = 0

index_max = np.argmax(m7_speed_np[:, 1])
m7_speed_np = np.delete(m7_speed_np, index_max, 0)
index_max = np.argmax(m7_speed_np[:, 1])
m7_speed_np = np.delete(m7_speed_np, index_max, 0)
# m7_speed_end_np = m7_speed_np[1000:2200, :]
# index_min = np.argmin(m7_speed_end_np[:, 1])
m7_speed_np = np.delete(m7_speed_np, 2152, 0)

current_step = int((m8_current_np.size/2)/500)
speed_step = int((m8_speed_np.size/2)/50)
'''
for i in range(0, 1):
    plt.figure(i, figsize=(12, 6))
    plt.title("1stConvShaft No-load test")
    plt.subplot(211)
    plt.plot(m8_current_np[current_step*i:current_step*(i+1), 0], m8_current_np[current_step*i:current_step*(i+1), 1], color="red", label="1stConvShaft", marker=">")
    # # plt.plot(m8_current_np[i:i+100, 0], m8_current_np[i:i+100, 1], color="green", label="1stConvShaft", marker="o")
    plt.ylabel("Current /A")

    plt.subplot(212)
    plt.plot(m8_speed_np[speed_step*i:speed_step*(i+1), 0], m8_speed_np[speed_step*i:speed_step*(i+1), 1], color="green", label="1stConvShaft",marker="o")
    # plt.plot(m8_speed_np[:, 0], m8_speed_np[:, 1], color="green", label="1stConvShaft")

    plt.ylabel("Speed /rpm")

    plt.xlabel("Time /s")
    plt.grid(1)
    plt.legend()
    # plt.savefig("./result/m8_current_{}.png".format(i))
    plt.show()
'''
# save excel
car_speed_data = pd.DataFrame(car_speed_np)
m7_speed_np_data = pd.DataFrame(m7_speed_np)
m7_current_np_data = pd.DataFrame(m7_current_np)
m8_speed_np_data = pd.DataFrame(m8_speed_np)
m8_current_np_data = pd.DataFrame(m8_current_np)
writer = pd.ExcelWriter('./draw_result/20210322.xlsx')		# 写入Excel文件
car_speed_data.to_excel(writer, 'car_speed', float_format='%.6f', header=False, index=False)
m7_current_np_data.to_excel(writer, 'm7_current', float_format='%.6f', header=False, index=False)
m7_speed_np_data.to_excel(writer, 'm7_speed', float_format='%.6f', header=False, index=False)
m8_current_np_data.to_excel(writer, 'm8_current', float_format='%.6f', header=False, index=False)
m8_speed_np_data.to_excel(writer, 'm8_speed', float_format='%.6f', header=False, index=False)
writer.save()

writer.close()

print("Finished")
