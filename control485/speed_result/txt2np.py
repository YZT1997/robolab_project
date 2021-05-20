import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

input_txt_07 = "[2021-1-15 14:1:27:765]m7_3000.txt"
input_txt_01 = "[2021-1-15 14:26:54:005]m1_3000.txt"
input_txt_08 = "[2021-1-15 14:43:29:621]m8_3000.txt"

speed_01 = []
current_01 = []
speed_07 = []
current_07 = []
speed_08 = []
current_08 = []

file_01 = open(input_txt_01)
for line in file_01:
    line = line.strip('\n')
    line = line.split(' ')

    speed_01.append(float(line[-4]))
    current_01.append(float(line[-1]))

file_07 = open(input_txt_07)
for line in file_07:
    line = line.strip('\n')
    line = line.split(' ')

    speed_07.append(float(line[-4]))
    current_07.append(float(line[-1]))

file_08 = open(input_txt_08)
for line in file_08:
    line = line.strip('\n')
    line = line.split(' ')

    speed_08.append(float(line[-4]))
    current_08.append(float(line[-1]))

speed_01_np = np.array(speed_01)
current_01_np = np.array(current_01)

speed_07_np = np.array(speed_07)
current_07_np = np.array(current_07)

speed_08_np = np.array(speed_08)
current_08_np = np.array(current_08)

time_01 = np.linspace(0, 5 * 60 + 52, len(speed_01_np))
time_07 = np.linspace(0, 3 * 60 + 21, len(speed_07_np))
time_08 = np.linspace(0, 5 * 60 + 52, len(speed_08_np))

# Draw, Mind the num
step = 50
num_page = int(len(time_01)/step)
print(num_page)

for i in range(0, 1):
    plt.figure(i, figsize=(12, 6))
    plt.subplot(211)
    plt.title("M1 Feeder House Test")
    # m7
    # if i <= 1:
    #     plt.ylim(0, 35)
    # else:
    #     plt.ylim(0, 20)
    plt.ylim(0, 35)   # m1
    plt.plot(time_01[step*i:step*(i+1)], current_01_np[step*i:step*(i+1)], color="red", label="Current", marker=">")
    plt.legend()
    plt.grid(1)
    plt.ylabel("Current /A")

    plt.subplot(212)
    plt.ylim(0, 3500)
    plt.plot(time_01[step*i:step*(i+1)], speed_01_np[step*i:step*(i+1)], color="green", label="Speed", marker="o")
    plt.ylabel("Speed /rpm")

    plt.xlabel("Time /s")
    plt.grid(1)
    plt.legend()
    # plt.savefig("./result/M1_test_{}.png".format(i+1))
    plt.show()
    # plt.close()

# excel
# current_08_np = current_08_np[:, np.newaxis]
# speed_08_np = speed_08_np[:, np.newaxis]
# time_08 = time_08[:, np.newaxis]
# m7_np = np.concatenate((time_08, current_08_np, speed_08_np), axis=1)
# m7_data = pd.DataFrame(m7_np)
#
# m7_writer = pd.ExcelWriter('./result/m8_test.xlsx')		# 写入Excel文件
# m7_data.to_excel(m7_writer, 'page_1', float_format='%.5f')		# ‘page_1’是写入excel的sheet名
# m7_writer.save()
#
# m7_writer.close()
#
# print("Finished")


