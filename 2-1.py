import numpy as np
import matplotlib.pyplot as plt 
from scipy.stats import multivariate_normal as mn

#生成原始点
mean = [0, 0]
cov = [[1, 0], [0, 1]]  # diagonal covariance
x= np.random.multivariate_normal(mean, cov, 50)

mean1 = [-0.55, 1]
cov1 = [[1, 0], [0, 1]]  # diagonal covariance
x1 = np.random.multivariate_normal(mean1, cov1, 50)
mean2 = [1 , 0.55]
cov2 = [[1, 0], [0, 1]]  # diagonal covariance
x2= np.random.multivariate_normal(mean2, cov2, 50)
x3=0.3*x1+0.7*x2

#查看点集
plt.figure(figsize=(6,6))
plt.plot(x[:,0],x[:,1] , 'bx')
plt.plot(x3[:,0], x3[:,1],'r.')
plt.show()
X=np.vstack((x,x3))

#画决策边界
def plot_decision_boundary():
 
    x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
    y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5
    h = 0.01
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
    
    point=np.c_[xx.ravel(), yy.ravel()]
    p1=mn.pdf(point,mean,cov)
    p2=0.3*mn.pdf(point,mean1,cov1) + 0.7*mn.pdf(point,mean2,cov2)  
    fp=p1-p2
    re=[];
    for temp in fp:
        if temp>0:
            re.append(0)
        else :
            re.append(1)
    re=np.array(re)
    re=re.reshape(xx.shape)

         
####画图
    plt.figure(figsize=(6,6))
    plt.contour(xx, yy, re, c='g')
    plt.plot(x[:,0],x[:,1] , 'bx')
    plt.plot(x3[:,0], x3[:,1],'r.')
    plt.title("KNN")
    plt.show()
    
    plt.figure(figsize=(6,6))
    plt.contourf(xx, yy, re, cmap=plt.cm.Spectral)
    plt.plot(x[:,0],x[:,1] , 'rx')
    plt.plot(x3[:,0], x3[:,1],'b.')
    plt.title("KNN")
    plt.show()
#调用函数
plot_decision_boundary()
