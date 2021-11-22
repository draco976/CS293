import matplotlib.pyplot as plt 
import numpy as np

comparisons = np.genfromtxt("comparisons.txt",
                     encoding=None, delimiter=",")
swaps = np.genfromtxt("swaps.txt",
                     encoding=None, delimiter=",")
time = np.genfromtxt("time.txt",
                     encoding=None, delimiter=",")

x = np.arange(1000,10000,1000) 

plt.figure(0)
plt.xlabel("Number of elements in BST") 
plt.ylabel("Number of comparisons") 
plt.plot(x,comparisons[:,0],color='r',label='QSP1') 
plt.plot(x,comparisons[:,1],color='b',label='QSRP') 
# plt.plot(x,comparisons[:,2],color='g',label='BuSo') 
plt.legend()
plt.savefig("comparisons.jpg")

plt.figure(1)
plt.xlabel("Number of elements in BST") 
plt.ylabel("Number of swaps") 
plt.plot(x,swaps[:,0],color='r',label='QSP1') 
plt.plot(x,swaps[:,1],color='b',label='QSRP') 
# plt.plot(x,swaps[:,2],color='g',label='BuSo') 
plt.legend()
plt.savefig("swaps.jpg")

plt.figure(2)
plt.xlabel("Number of elements in BST") 
plt.ylabel("Time taken in seconds") 
plt.plot(x,time[:,0],color='r',label='QSP1') 
plt.plot(x,time[:,1],color='b',label='QSRP') 
# plt.plot(x,time[:,2],color='g',label='BuSo') 
plt.legend()
plt.savefig("time.jpg")

