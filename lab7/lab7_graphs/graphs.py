import matplotlib.pyplot as plt
import numpy as np


filenames = ['balance_shuffled.txt', 'simple_shuffled.txt', 'balance.txt', 'simple.txt']

directory = '/Users/sardorislamov/Desktop/cpp_2022_islamov/lab7/cmake-build-debug/'


def show_graph(ax, filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        num = np.array([int(line.rstrip().split()[0]) for line in lines])
        time = np.array([float(line.rstrip().split()[1]) for line in lines])
    ax.plot(num, time, label=filename[69:].replace('_', ' ').split('.')[0])


fig = plt.figure(figsize=(10, 5))

ax = fig.add_subplot(121)
show_graph(ax, directory + filenames[0])
show_graph(ax, directory + filenames[1])
ax.set_title('shuffled array')
ax.set_xlabel('size of array')
ax.set_ylabel('sort time, ms')
ax.legend()
ax.grid()

ax = fig.add_subplot(122)
show_graph(ax, directory + filenames[2])
show_graph(ax, directory + filenames[3])
ax.set_title('increasing array')
ax.set_xlabel('size of array')
ax.set_ylabel('sort time, ms')
ax.legend()
ax.grid()

plt.show()
