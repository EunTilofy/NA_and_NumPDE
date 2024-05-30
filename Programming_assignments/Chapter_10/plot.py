import sys
import numpy as np
import matplotlib.pyplot as plt

def plot_surface_from_csv(filename):
    data = np.genfromtxt(filename + '.csv', delimiter=',')

    x = data[:, 0]
    y = data[:, 1]
    
    if data.shape[1] == 3:  # Check if the data has three columns
        z = data[:, 2]
        
        fig = plt.figure(figsize=(5, 5))
        ax = fig.add_subplot(111, projection='3d')

        ax.plot_trisurf(x, y, z, cmap='viridis', edgecolor='none', alpha=1.0)

        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
    
        ax.invert_xaxis()

    else:  # If only two columns are present, plot in 2D
        fig = plt.figure(figsize=(5, 5))
        plt.plot(x, y)
        plt.xlabel('u1')
        plt.ylabel('u2')

    plt.savefig(filename + '.png')
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage : python plot.py [<filename> ]")
    else:
        for i in range(1, len(sys.argv)):
            filename = sys.argv[i].split('.')[0]
            plot_surface_from_csv(filename)