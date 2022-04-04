import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111)

# file_names = ['float_sum', 'sum_with_near_numbers', 'forward_kahan_sum',
#               'forward_kahan_sum_with_using_fma', 'standard_sum_in_double_type', 'recurrent_sum']
file_names = ['float_sum', 'sum_with_near_numbers', 'forward_kahan_sum',
              'forward_kahan_sum_with_using_fma', 'standard_sum_in_double_type']

directory = '/Users/sardorislamov/Desktop/cpp_2022_islamov/lab2/cmake-build-debug/'


def graphs(ax, directory, T):
    with open(directory, 'r') as file:
        lines = file.readlines()
        segmentations_ = [int(line.rstrip().split()[2]) for line in lines]
        error_values_ = [float(line.rstrip().split()[11]) for line in lines]
        temperatures_ = [float(line.rstrip().split()[5]) for line in lines]
        temperatures = []
        for t in temperatures_:
            idx = temperatures_.index(t)
            if t not in temperatures:
                temperatures.append(t)
                temperatures.append([idx])
            else:
                idx1 = temperatures.index(t) + 1
                temperatures[idx1].append(idx)
            temperatures_[idx] = -1

    idx = temperatures.index(T) + 1
    error_values = []
    segmentations = []
    for i in range(len(temperatures[idx])):
        error_values.append(error_values_[temperatures[idx][i]])
        segmentations.append(segmentations_[temperatures[idx][i]])

    arg_sort = sorted(range(len(segmentations)), key=lambda i: segmentations[i])
    segmentations = [segmentations[i] for i in arg_sort]
    error_values = [error_values[i] for i in arg_sort]

    ax.plot(segmentations, error_values, label=directory[69:].replace('_', ' '))
    # ax.scatter(segmentations, error_values, s=2, label=directory[69:].replace('_', ' '))
    # print(temperatures)
    # print(error_values)
    # print(segmentations)


T = 100.0

for file_name in file_names:
    graphs(ax, directory + file_name, T)

plt.grid(linestyle='--')
plt.xlabel('Segmentation')
plt.ylabel('Error value')
plt.title('T = ' + str(T) + 'K')
plt.legend()
plt.show()
