import cv2
im=cv2.imread('9.jpg')
g=cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
yz,t=cv2.threshold(g,200,255,cv2.THRESH_BINARY)
cv2.imwrite("4.png",t)

#yz,t2=cv2.threshold(g,200,255,cv2.THRESH_BINARY)
#cv2.imwrite("5.png",t2)

#yz,t3=cv2.threshold(g,250,255,cv2.THRESH_BINARY)
#cv2.imwrite("6.png",t3)
#cv2.waitKey()