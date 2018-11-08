import numpy as np
import matplotlib.pyplot as plt 
from sklearn import neighbors

#生成原始点
mean = [0, 0]
cov = [[1, 0], [0, 1]]  # diagonal covariance
x= np.random.multivariate_normal(mean, cov, 50)
y=np.ones(50)

mean1 = [1, 1]
cov1 = [[1, 0], [0, 1]]  # diagonal covariance
x1 = np.random.multivariate_normal(mean1, cov1, 50)
mean2 = [1.1,1]
cov2 = [[1, 0], [0, 1]]  # diagonal covariance
x2= np.random.multivariate_normal(mean2, cov2, 50)
x3=0.3*x1+0.7*x2
y3=np.zeros(50)

#查看点集
plt.figure(figsize=(6,6))
plt.plot(x[:,0],x[:,1] , 'bx')
plt.plot(x3[:,0], x3[:,1],'r.')
plt.show()

#转化为数据集
X=np.vstack((x,x3))
Y=np.hstack((y,y3))
clf = neighbors.KNeighborsClassifier(n_neighbors = 9 )
clf.fit(X,Y)
#画决策边界
def plot_decision_boundary(pred_func):
 
    # 设定最大最小值
    x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
    y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5
    h = 0.01
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))

    # 预测
    Z = pred_func(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
    # 画图
    plt.figure(figsize=(6,6))
    plt.contour(xx, yy, Z, cmap=plt.cm.Spectral)
    plt.plot(x[:,0],x[:,1] , 'bx')
    plt.plot(x3[:,0], x3[:,1],'r.')
    plt.title("KNN")
    plt.show()
    
    plt.figure(figsize=(6,6))
    plt.contourf(xx, yy, Z, cmap=plt.cm.Spectral)
    plt.plot(x[:,0],x[:,1] , 'bx')
    plt.plot(x3[:,0], x3[:,1],'r.')
    plt.title("KNN")
    plt.show()
#调用函数
plot_decision_boundary(lambda x: clf.predict(x))
