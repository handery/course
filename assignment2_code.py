import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

#2 dimension guassian
def gaussian(x,mean,cov):
    return 1./(2*np.pi*np.linalg.det(cov)**0.5 ) * np.exp(-0.5*(x-mean).T.dot(np.linalg.inv(cov)).dot(x-mean))

#EM algorithm
def EM(data, mean, cov, k, step=10):
    n = len(k)
    datanum=int(data.size/2)
    gama=np.zeros((n,datanum))
    for s in range(step):
        for i in range (n):
            for j in range(datanum):
                total=sum(k[t]*gaussian(data[j],mean[t],cov[t]) for t in range(n))
                gama[i][j]=k[i]*gaussian(data[j],mean[i],cov[i])/float(total)
        for i in range(n):
            mean[i]=np.sum(gama[i][j]*data[j] for j in range(datanum))/np.sum(gama[i])
        for i in range(n):
            cov[i]= np.sum((gama[i][j]*np.mat((data[j]-mean[i])).T.dot(np.mat((data[j]-mean[i]))) for j in range(datanum)) )/ np.sum(gama[i]) 
        for i in range(n):
            k[i]=np.sum(gama[i])/datanum       
        print("Round "+str(s)+" finished.")
    return k,mean,cov

def classify(data,mean,cov,k):
    n=len(k)
    datanum=int(data.size/2)
    gama=np.zeros((n,datanum))
    c=np.zeros(datanum)
    for i in range(n):
        for j in range(datanum):
            total=sum(k[t]*gaussian(data[j],mean[t],cov[t]) for t in range(n))
            gama[i][j]=k[i]*gaussian(data[j],mean[i],cov[i])/float(total)
    c=np.argmax(gama,axis=0)
    return c

def plotfig(data,color):
    datanum=c.size;
    colors=['r','g','b','y']
#    print(data)
    for i in range(datanum):
        plt.scatter(data[i][0],data[i][1],c=colors[color[i]],marker='.')
    return 

#import data
data=pd.read_csv("TrainingData_GMM.csv",header=None)
sets=data.sample(1000)
data=data.values
sets=sets.values

#initialization
mean=np.array([[-0.5,-0.5],[-0.3,0.5],[0.3,0.3],[1.3,-1.]])
cov = np.array([[[0.1,0.],[0.,0.05]],[[0.1,0.],[0.,.1]],[[.1,0.],[0.,.1]],[[.05,0.],[0.,.05]]])
k = np.array([.2,.3,.3,.2])

k1,mean1,cov1=EM(data,mean,cov,k,12)    #train
print(k1)
print(mean1)
print(cov1)

c=classify(sets,mean1,cov1,k1)          
print(c)
plotfig(sets,c)
