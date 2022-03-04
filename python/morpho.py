#https://cloud.tencent.com/developer/article/1897397?from=article.detail.1900798
#based on morphology and connectivity
import numpy as np
import cv2

img = cv2.imread('5xm.png')
height,width,ch=img.shape

for i in range(height):
    for j in range(width):
        for k in range(ch):
            img[i,j,k]=255-img[i,j,k]
cv2.imshow('src', img)

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
ret, thres= cv2.threshold(gray, 71, 255, cv2.THRESH_BINARY)
#cv2.imshow('thres', thres)

KS=4  #use small kernel
k1=np.zeros((2*KS+1,2*KS+1), np.uint8)
cv2.circle(k1,(KS,KS),KS,(1,1,1),-1, cv2.LINE_AA)
erode = cv2.morphologyEx(thres, cv2.MORPH_ERODE, k1)#膨胀操作
#cv2.imshow('erode', erode)

# 连通域分析
num_labels, labels, stats, centers = cv2.connectedComponentsWithStats(erode, connectivity=8)

# 连通域数量
print('num_labels = ',num_labels)
# 连通域的信息：对应各个轮廓的x、y、width、height和面积
print('stats = ',stats)
# 连通域的中心点
print('centroids = ',centers)
# 每一个像素的标签1、2、3.。。，同一个连通域的标签是一致的
print('labels = ',labels)

# 不同的连通域赋予不同的颜色
output = np.zeros((img.shape[0], img.shape[1], 3), np.uint8)
for i in range(1, num_labels):
    mask = labels == i
    output[:, :, 0][mask] = np.random.randint(0, 255)
    output[:, :, 1][mask] = np.random.randint(0, 255)
    output[:, :, 2][mask] = np.random.randint(0, 255)

cv2.imwrite('output.png', output)
dilate = cv2.morphologyEx(output, cv2.MORPH_DILATE, k1)#膨胀操作
#cv2.imshow('dilate', dilate)

#k2=np.ones((3,3), np.uint8)
#dilate = cv2.morphologyEx(dilate, cv2.MORPH_GRADIENT, k2)#膨胀操作
result = cv2.addWeighted(img,0.8,dilate,0.5,0) #图像权重叠加
for i in range(1,len(centers)):
  cv2.drawMarker(result, (int(centers[i][0]),int(centers[i][1])),(0,0,255),1,20,2)

cv2.putText(result,"count=%d"%(len(centers)-1),(20,30),0,1,(0,255,0),2)
cv2.imwrite('result.png', result)

cv2.waitKey(0)
cv2.destroyAllWindows()