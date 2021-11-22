import matplotlib.pyplot as plt
import numpy as np

X = ['1e3','1e4','1e5','1e6']  
X_axis = np.arange(len(X))

# Time

Y = [7.5e-07,7.14575e-07,6.51356e-07,4.83907e-07]
plt.bar(X_axis-0.2,Y,0.4,label = 'Insert') 

Y = [1.125e-06,1.04941e-06,1.15569e-06,9.8625e-07]
plt.bar(X_axis+0.2,Y,0.4,label = 'Delete') 

plt.xticks(X_axis, X)
plt.xlabel("N")
plt.ylabel("Time taken (in sec)")
plt.legend()
plt.savefig("time.png")

plt.close()
# Swaps

Y = [0.836538,1.01721,0.909337,0.982975]
plt.bar(X_axis-0.2,Y,0.4,label = 'Insert') 

Y = [8.41667,11.6907,14.8893,18.076]
plt.bar(X_axis+0.2,Y,0.4,label = 'Delete') 

plt.xticks(X_axis, X)
plt.xlabel("N")
plt.ylabel("No. of swaps")
plt.legend()
plt.savefig("swaps.png")