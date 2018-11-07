import numpy as np
import matplotlib.pyplot as plt
#from matplotlib.colors import ListedColormap
from sklearn import neighbors

mean = [0, 0]
cov = [[1, 0], [0, 1]]  # diagonal covariance
x= np.random.multivariate_normal(mean, cov, 50)
y=np.ones(50)

plt.plot(x[:,0],x[:,1] , 'bx')
#plt.show()


mean1 = [1, 1]
cov1 = [[1, 0], [0, 1]]  # diagonal covariance
x1 = np.random.multivariate_normal(mean1, cov1, 50)
mean2 = [.5,.5]
cov2 = [[1, 0], [0, 1]]  # diagonal covariance
x2= np.random.multivariate_normal(mean2, cov2, 50)
x3=0.3*x1+0.7*x2
y3=np.zeros(50)

plt.plot(x3[:,0], x3[:,1],'r.')
plt.show()

X=np.vstack((x,x3))
Y=np.hstack((y,y3))

clf = neighbors.KNeighborsClassifier(n_neighbors = 10 , weights='distance')
clf.fit(X,Y)
print(clf.predict(([2,2],[1,1])))

# 咱们先顶一个一个函数来画决策边界
def plot_decision_boundary(pred_func):
 
    # 设定最大最小值，附加一点点边缘填充
    x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
    y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5
    h = 0.01
 
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
 
    # 用预测函数预测一下
    Z = pred_func(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
 
    # 然后画出图
    plt.contourf(xx, yy, Z, cmap=plt.cm.Spectral)
    plt.scatter(X[:, 0], X[:, 1], c=Y, cmap=plt.cm.Spectral)
    plt.plot(x[:,0],x[:,1] , 'bx')
    plt.plot(x3[:,0], x3[:,1],'r.')
#    plt.show()
    plt.title("KNN")
    plt.show()

    
plot_decision_boundary(lambda x: clf.predict(x))

#https://blog.csdn.net/qq_38120760/article/details/83269673
#https://www.cnblogs.com/pinard/p/6065607.html
#https://www.cnblogs.com/nolonely/p/6980160.html
#https://blog.csdn.net/dengjiaxing0321/article/details/70545740
