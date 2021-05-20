import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

m5_speed = np.load("m5_motor_speed.npy")
m5_current = np.load("m5_cm7290_current.npy")
m9_speed = np.load("m9_motor_speed.npy")
m9_current = np.load("m9_cm7290_current.npy")
m10_speed = np.load("m10_motor_speed.npy")
m10_current = np.load("m10_cm7290_current.npy")

id = ["M5 Main Fan", "M9 2ndConvShaft", "M10 Swing shaft"]

step_current = 500
step_speed = 31

id = id[2]
num_page = int(len(m10_current[:, 0]) / step_current)

# for i in range(0, num_page):
#     plt.figure(i + 1, figsize=(12, 6))
#     plt.subplot(211)
#     plt.title(id)
#     plt.plot(m10_current[step_current*i:step_current*(i + 1), 0], m10_current[step_current*i:step_current*(i + 1), 1],
#              color="red", label="Current", marker="o")
#     plt.ylabel("Current /A")
#     plt.legend()
#     plt.grid(1)
#
#     plt.subplot(212)
#     plt.plot(m10_speed[step_speed*i: step_speed*(i + 1), 0], m10_speed[step_speed*i: step_speed*(i + 1), 1],
#              color="green", label="Speed", marker=">")
#     plt.ylabel("Speed /rpm")
#     plt.xlabel("Time /s")
#     plt.legend()
#     plt.grid(1)
#     plt.savefig("./img_result/" + id + "_{}.png".format(i+1))
#     # plt.show()

# save excel

m5_speed_data = pd.DataFrame(m5_speed)
m5_current_data = pd.DataFrame(m5_current)
m9_speed_data = pd.DataFrame(m9_speed)
m9_current_data = pd.DataFrame(m9_current)
m10_speed_data = pd.DataFrame(m10_speed)
m10_current_data = pd.DataFrame(m10_current)

writer = pd.ExcelWriter('./img_result/20210418_v2.xlsx')		# 写入Excel文件
m5_speed_data.to_excel(writer, 'm5_speed', float_format='%.10f', header=False, index=False)
m5_current_data.to_excel(writer, 'm5_current', float_format='%.10f', header=False, index=False)
# m9_speed_data.to_excel(writer, 'm9_speed', float_format='%.6f', header=False, index=False)
# m9_current_data.to_excel(writer, 'm9_current', float_format='%.6f', header=False, index=False)
# m10_speed_data.to_excel(writer, 'm10_speed', float_format='%.6f', header=False, index=False)
# m10_current_data.to_excel(writer, 'm10_current', float_format='%.6f', header=False, index=False)

writer.save()

writer.close()

print("Finished")
