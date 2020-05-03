import numpy as np
import matplotlib.pyplot as plt

rawdata = np.loadtxt("data/ueb4_4.dat",delimiter=";" ,dtype=float)
#print(rawdata)
fig = plt.figure()
x_fit=rawdata[:, 0]
y_fit=rawdata[:, 1]
#print(x_fit,y_fit)



plt.scatter(x_fit,y_fit,color='r')


plt.yscale("log")
plt.xscale("log")
#plt.xlim(10**(-6),10**(-2))
# fig = plt.figure()
plt.savefig("data/ueb4_4")

plt.close()
