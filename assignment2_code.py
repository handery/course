import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import random

#import data
data=pd.read_csv("TrainingData_GMM.csv",header=None)
data=data.values

#initialization
mean=np.array([[0.,0.],[-1.,1.],[1.,-1.],[1.,1.]])
cov = np.array([[[1.,0.],[0.,1.]],[[1.,0.],[0.,1.]],[[1.,0.],[0.,1.]],[[1.,0.],[0.,1.]]])
k = np.array([.25,.25,.25,.25])

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
#        gama1=gama.T
        print(gama)
        print(np.argmax(gama,axis=0))
    return k,mean,cov
#
#def classify(data,mean,cov,k):
#    
#
#def plotfig(data,c):
#    
#    return 

k1,mean1,cov1=EM(data,mean,cov,k,10)
sets=random.sample(data,500)
#plotfig(sets,c)
