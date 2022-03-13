import matplotlib.pyplot as plt
import numpy as np
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.plot_surface(np.array(list(range(0, 10))), np.array(list(range(0, 10))), np.array(list(range(0, 10))))
plt.show(fig)