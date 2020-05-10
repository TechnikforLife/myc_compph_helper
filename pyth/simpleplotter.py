import numpy as np
import matplotlib.pyplot as plt

rawdata = np.loadtxt("data/ueb5_2_d.dat",delimiter=";" ,dtype=float)
x_fit=rawdata[:, 0]

y_exact=rawdata[:, 1]
#y_own=rawdata[:,2]
plt.plot(x_fit,y_exact,label="exact",linewidth=0.1)
#plt.plot(x_fit,y_own,label="own",linewidth=0.1)
#plt.axvline(x=4.68570,ymin=0,ymax=2.)
plt.legend(loc='best')
plt.savefig("data/ueb5_2_d.pdf")
plt.close()

#print(x_fit,y_fit)

