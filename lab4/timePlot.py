import matplotlib.pyplot as plt
import numpy as np

Data = np.genfromtxt("data.txt", dtype=np.float64,
                     encoding=None, delimiter=",")

x = Data[:,0]
y = Data[:,1]

x1 = np.linspace(1,100000,1000)
y1 = x1*np.log(x1) 
# np.log gives natural log

y1 = y1*0.16

plt.xlabel("Number of elements in BST") 
plt.ylabel("Time taken in microseconds") 
plt.plot(x,y,color='r',label='BST') 
plt.plot(x1,y1,color='b',label='k*nlogn') 
plt.legend()
plt.savefig("plot.jpg") 

# k=0.16