import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

directory = '/Users/sardorislamov/Desktop/cpp_2022_islamov/lab1/cmake-build-debug/task1_stat'

with open(directory, 'r') as file:
    sizey = [int(line.rstrip().split()[3].split('x')[0]) for line in file.readlines()]
    file.seek(0, 0)
    sizex = [int(line.rstrip().split()[3].split('x')[1][:-1]) for line in file.readlines()]
    file.seek(0, 0)
    dislocations_amount = [int(line.rstrip().split()[5][:-1]) for line in file.readlines()]
    file.seek(0, 0)
    steps = [int(line.rstrip().split()[7]) for line in file.readlines()]

size = np.divide(np.multiply(sizex, sizey), dislocations_amount)
fig = plt.figure()
ax = fig.add_subplot(111)

plt.bar(size, steps, align='center', alpha=0.4, color=(0, 0.6, 0.7))

ax.yaxis.set_major_locator(ticker.MultipleLocator(max(steps)//5))
ax.xaxis.set_major_locator(ticker.MultipleLocator(max(size)//5))
plt.xlim(0, 1.05*max(size))
plt.ylim(0, 1.05*max(steps))
plt.xlabel('Ratio of area to dislocations amount')
plt.ylabel('Amount of steps')

plt.show()