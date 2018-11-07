import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from sklearn import neighbors,datasets
import pandas as pd


mean = [0, 0]
cov = [[1, 0], [0, 1]]  # diagonal covariance
x= np.random.multivariate_normal(mean, cov, 50).T
y=np.ones(50)
print(y)
plt.plot(x[0],x[1] , 'rx')
#plt.axis('equal')
#plt.show()


mean1 = [1, 1]
cov1 = [[1, 0], [0, 1]]  # diagonal covariance
x1 = np.random.multivariate_normal(mean1, cov1, 50).T
mean2 = [.5,.5]
cov2 = [[1, 0], [0, 1]]  # diagonal covariance
x2= np.random.multivariate_normal(mean2, cov2, 50).T

x3=0.3*x1+0.7*x2
y3=np.zeros(50)

print(y3)

plt.plot(x3[0], x3[1],'b.')
#plt.axis('equal')
plt.show()

print(x.shape)
X=x.tolist()
X.append(x3.tolist())
print(X)
y=y.tolist()
y.append(y3.tolist())
print(y)




clf = neighbors.KNeighborsClassifier(n_neighbors = 15 , weights='distance')
clf.fit()






https://blog.csdn.net/qq_38120760/article/details/83269673
https://www.cnblogs.com/pinard/p/6065607.html
https://www.cnblogs.com/nolonely/p/6980160.html
