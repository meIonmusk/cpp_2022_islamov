import matplotlib.pyplot as plt
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

# directory = '/Users/sardorislamov/Desktop/cpp_2022_islamov/lab1/cmake-build-debug/task2_stat' # width = 5000
directory = '/Users/sardorislamov/Desktop/cpp_2022_islamov/lab1/cmake-build-debug/task3_stat_2' # width = 12

with open(directory, 'r') as file:
    sizey = [int(line.rstrip().split()[3].split('x')[0]) for line in file.readlines()]
    file.seek(0, 0)
    sizex = [int(line.rstrip().split()[3].split('x')[1][:-1]) for line in file.readlines()]
    file.seek(0, 0)
    dislocations_amount = [int(line.rstrip().split()[5][:-1]) for line in file.readlines()]
    file.seek(0, 0)
    steps = [int(line.rstrip().split()[7]) for line in file.readlines()]

ratio = np.divide(np.multiply(sizex, sizey), dislocations_amount)

indexes = sep_indexes(ratio)
ratio = separate(ratio, indexes)
steps = separate(steps, indexes)


fig = plt.figure()
ax = fig.add_subplot(111)

max_y = [0]
max_x = [0]

for i in ratio:
    max_x.append(max(i))
for i in range(len(steps)):
    max_y.append(max(steps[i]))
    ax.bar(ratio[i], steps[i], width=12, align='center', alpha=0.4)

maxx = max(max_x)
maxy = max(max_y)

plt.xlim(0, 1.05*maxx)
plt.ylim(0, 1.05*maxy)
plt.xlabel('Ratio of area to dislocations amount')
plt.ylabel('Amount of steps')

plt.show()
