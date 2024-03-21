import sys
import numpy as np
import matplotlib.pyplot as plt

def plot_surface_from_csv(filename):
    data = np.genfromtxt(filename + '.csv', delimiter=',')

    x = data[:, 0]
    y = data[:, 1]
    z = data[:, 2]

    fig = plt.figure()
    fig = plt.figure(figsize=(5, 5))
    ax = fig.add_subplot(111, projection='3d')

    ax.plot_trisurf(x, y, z, cmap='viridis', edgecolor='none', alpha = 1.0)
    
    # ax.scatter(x, y, z, color='black', s=5)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    
    ax.invert_xaxis()

    plt.savefig(filename + '.png')

    plt.close()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage : python plot.py [<filename> ]")
    else:
        for i in range(1, len(sys.argv)):
            filename = sys.argv[i].split('.')[0]
            plot_surface_from_csv(filename)