import numpy as np
import matplotlib.pyplot as plt

for l in range(3):
    fig=plt.figure()
    for j in range(4):
        rawdata = np.loadtxt("data/ueb5_"+str(l)+"_"+str(j),delimiter=";" ,dtype=float)
        x_fit=rawdata[:, 0]

        y_exact=rawdata[:, 1]
        y_own=rawdata[:,2]
        a=0
        for ab in range(len(x_fit)-1):
            if (x_fit[ab]>x_fit[ab+1]):
                y=y_own[a:ab+1]
                ye=y_exact[a:ab+1]
                x=x_fit[a:ab+1]
                plt.plot(x,ye,label="exact_"+str(a),linewidth=0.1)
                plt.plot(x,y,label="own_"+str(a),linewidth=0.1)
                a=ab+1
        y=y_own[a:]
        ye=y_exact[a:]
        x=x_fit[a:]
        plt.plot(x,ye,label="exact_"+str(a),linewidth=0.1)
        plt.plot(x,y,label="own_"+str(a),linewidth=0.1)
        plt.legend(loc='best')
        plt.savefig("data/ueb5_"+str(l)+"_"+str(j)+".pdf")
        plt.close()
for l in range(3):
    fig=plt.figure()
    for j in range(4):
        rawdata = np.loadtxt("data/ueb5_"+str(l)+"_"+str(j),delimiter=";" ,dtype=float)
        x_fit=rawdata[:, 0]
        y_diff=rawdata[:,3]
        a=0
        abc=0
        for ab in range(len(x_fit)-1):
            if (x_fit[ab]>x_fit[ab+1]):
                abc=abc+1
                y=y_diff[a:ab+1]
                x=x_fit[a:ab+1]
                if(True):
                    plt.plot(x,y,label="own_"+str(a),linewidth=0.1)
                a=ab+1
        y=y_diff[a:]
        x=x_fit[a:]
        #plt.ylim(0,1)
        plt.yscale("log")
        plt.plot(x,y,label="own_"+str(a),linewidth=0.1)
        plt.legend(loc='best')
        plt.savefig("data/ueb5_"+str(l)+"_"+str(j)+"diff.pdf")
        plt.close()
#print(x_fit,y_fit)

