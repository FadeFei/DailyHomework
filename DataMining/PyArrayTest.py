import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import csv
import math
import random

my_ma = pd.read_csv("save_train.csv", delimiter=",")
my_test = pd.read_csv("save_test.csv", delimiter=",")
data = np.array(my_ma)
testData = np.array(my_test)
rate = 0.001

# arr = [1]*385
arr = []
for i in range(385):
    # a = np.random.normal()
    a = 1
    arr.append(a)

def h(x):
    a = 0;
    for i in range(384):
        if (np.isnan(x[i+1]) or math.isnan(x[i+1])):
            continue
            # x[i+1] = 0
        a += arr[i]*x[i+1]
        # print(x[i])
    return a+arr[384]
    # _sum = [0]*385
for i in range(100000000):
    # _sum = [0]*385
    Jtheta = 0;
    # for x in data:
    #     hx = h(x)
    #     if (np.isnan(x[385]) or math.isnan(x[385])):
    #             # x[385] = 0
    #             continue
    #     for j in range(384):
    #         if (np.isnan(x[j+1]) or math.isnan(x[j+1])):
    #             continue
    #             # x[j+1] = 0
    #         _sum[j] = _sum[j] + rate*(x[385]-hx)*x[j+1]
    #     _sum[384] = _sum[384]+rate*(x[385] - hx)
    #     Jtheta = Jtheta + (hx-x[385])*(hx-x[385])
    ranNum = random.randint(0,14534)
    x = data[ranNum]
    hx = h(x)

    if (np.isnan(x[385]) or math.isnan(x[385])):
        # x[385] = 0
        continue
    for j in range(384):
        if (np.isnan(x[j+1]) or math.isnan(x[j+1])):
            continue
            # x[j+1] = 0
        arr[j] = arr[j] + rate*(x[385]-hx)*x[j+1]
    arr[384] = arr[384]+rate*(x[385] - hx)



    Jtheta = Jtheta + (hx-x[385])*(hx-x[385])
    print(Jtheta)
    # for k in range(385):
    #     arr[k] = arr[k] + _sum[k]

csvfile = open('sample_submission.csv','w+',newline='')
writer = csv.writer(csvfile)

index = 0
result = [(int(x[0]),h(x)) for x in testData]
writer.writerow(['Id','reference'])
writer.writerows(result)

# print(arr)

# for i in range(10000):
#     _sum = [0]*385
#     for x in data:
#         for j in range(384):
#             _sum[j] = _sum[j] + rate*(x[385]-h(x))*x[j+1]
#         _sum[384] = _sum[384]+rate*(x[385] - h(x))
#     for k in range(385):
#         arr[k] = arr[k] + _sum[k]