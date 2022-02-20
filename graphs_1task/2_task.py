import matplotlib.pyplot as plt

from random import randint
import matplotlib.ticker as ticker
import numpy as np


def separate(lst, indexes):
    a = []
    for i in range(1, len(indexes)):
        a.append(lst[indexes[i-1]: indexes[i]])
    return a


def sep_indexes(lst):
    indexes = [0]
    for i in range(1, len(lst)):
        if abs(lst[i - 1] - lst[i]) > 10:
            indexes.append(i)
    indexes.append(len(lst))
    return indexes

directory = '/Users/sardorislamov/Desktop/cpp_2022_islamov/lab1/cmake-build-debug/task2_stat'

with open(directory, 'r') as file:
    sizey = [int(line.rstrip().split()[3].split('x')[0]) for line in file.readlines()]
    file.seek(0, 0)
    sizex = [int(line.rstrip().split()[3].split('x')[1][:-1]) for line in file.readlines()]
    file.seek(0, 0)
    dislocations_amount = [int(line.rstrip().split()[5][:-1]) for line in file.readlines()]
    file.seek(0, 0)
    steps = [int(line.rstrip().split()[7]) for line in file.readlines()]

ratio = np.divide(np.multiply(sizex, sizey), dislocations_amount)
# print(ratio)
# ratio = sizey

# indexes = sep_indexes(sizex)
# ratio = separate(ratio, indexes)
# steps = separate(steps, indexes)


fig = plt.figure()
ax = fig.add_subplot(111)

# max_y = [0]
# max_x = [0]

# for i in ratio:
#     max_x.append(max(i))
# for i in range(len(steps)):
#     max_y.append(max(steps[i]))
#     ax.plot(ratio[i], steps[i])
    # ax.bar(ratio[i], steps[i], width=5000, align='center', alpha=0.4, color=(0, 0.6, 0.7))
    # print(max_x)
# print(ratio)
# print(steps)
# ratio = np.arange(0, 50, 1)
# steps = [randint(0, i) for i in range(50)]
ax.bar(ratio, steps, width=5000, align='center', alpha=0.4, color=(0, 0.6, 0.7))
# maxx = max(max_x)
# maxy = max(max_y)

# plt.bar(ratio, steps, align='center', alpha=0.4, color=(0, 0.6, 0.7))

# ax.yaxis.set_major_locator(ticker.MultipleLocator(max(ratio)//5))
# ax.xaxis.set_major_locator(ticker.MultipleLocator(max(steps)//5))
plt.xlim(0, 1.05*max(ratio))
plt.ylim(0, 1.05*max(steps))
plt.xlabel('Ratio of area to dislocations amount')
plt.ylabel('Amount of steps')

plt.show()