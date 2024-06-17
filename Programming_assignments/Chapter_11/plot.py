import sys
import numpy as np
import matplotlib.pyplot as plt

def plot_surface_from_csv(filename):
    data = np.genfromtxt(filename + '.csv', delimiter=',')

    x = data[:, 0]
    y = data[:, 1]
    
    if data.shape[1] == 3:  # Check if the data has three columns
        z = data[:, 2]
        plt.figure(figsize=(5, 5))
        plt.plot(x, y, linewidth = 1.2, color = 'black')
        plt.plot(x, z, linewidth = 0.6, color = 'black')

        # plt.set_xlabel('x')
        # plt.set_ylabel('f(x, t)')

    # else:  # If only two columns are present, plot in 2D
    #     fig = plt.figure(figsize=(5, 5))
    #     plt.plot(x, y)
    #     plt.xlabel('u1')
    #     plt.ylabel('u2')

    plt.savefig(filename + '.png')
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage : python plot.py [<filename> ]")
    else:
        for i in range(1, len(sys.argv)):
            filename = sys.argv[i][:-4]
            plot_surface_from_csv(filename)