import matplotlib.pyplot as plt
import matplotlib.ticker as ticker


def separate(lst, indexes):
    a = []
    for i in range(1, len(indexes)):
        a.append(lst[indexes[i-1]: indexes[i]])
    return a


def sep_indexes(lst):
    indexes = [0]
    for i in range(1, len(lst)):
        if abs(lst[i - 1] - lst[i]) > 50:
            indexes.append(i)
    indexes.append(len(lst))
    return indexes


directory = '/Users/sardorislamov/Desktop/cpp_2022_islamov/lab1/cmake-build-debug/task1_stat'

with open(directory, 'r') as file:
    size = [int(line.rstrip().split()[3].split('x')[1][:-1]) for line in file.readlines()]
    file.seek(0, 0)
    steps = [int(line.rstrip().split()[7]) for line in file.readlines()]

indexes = sep_indexes(size)
size = separate(size, indexes)
steps = separate(steps, indexes)

figure = plt.Figure(facecolor="None")

fig = plt.figure()
ax = fig.add_subplot(111)

max_y = [0]
max_x = [0]
for i in size:
    max_x.append(max(i))
for i in range(len(steps)):
    max_y.append(max(steps[i]))
    ax.plot(size[i], steps[i])
maxx = max(max_x)
maxy = max(max_y)
ax.yaxis.set_major_locator(ticker.MultipleLocator(maxy//5))
ax.xaxis.set_major_locator(ticker.MultipleLocator(maxx//5))
plt.xlim(0, 1.05*maxx)
plt.ylim(0, 1.05*maxy)
plt.xlabel('Field size')
plt.ylabel('Amount of steps')
plt.show()
