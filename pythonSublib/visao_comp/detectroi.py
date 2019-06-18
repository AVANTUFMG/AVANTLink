import cv2
import numpy as np
import time 


t0 = time.time()
ima = cv2.imread("7resize.jpg",0) 
#ima = cv2.resize(ima,(640,480)) #resize time = 0.005

kernel = np.ones((5,5),np.float32)

new_img = np.zeros(ima.shape,ima.dtype) #mascara onde serão salvos os pontos

ima = cv2.medianBlur(ima,5) # filtro time = 0.002
ima = cv2.morphologyEx(ima,cv2.MORPH_OPEN,kernel) # filtro time = 0.002
                                                  # ajuda a tirar ruidos para a detecção de circulos
#ima = cv2.bilateralFilter(ima,5,75,75)

gray= np.float32(ima)
corners = cv2.goodFeaturesToTrack(gray,15,0.01,0)
corners= np.int0(corners)
for corner in corners:
    x,y = corner.ravel()
    #cv2.rectangle(new_img,(x,y),(x+20,y+20),(255,255,255),-1)
    #cv2.rectangle(new_img,(x,y),(x-20,y-20),(255,255,255),-1)
    #cv2.rectangle(new_img,(x,y),(x+20,y-20),(255,255,255),-1)
    #cv2.rectangle(new_img,(x,y),(x-20,y+20),(255,255,255),-1)
    cv2.circle(new_img,(x,y),20,(255,255,255),-1)

cimg = cv2.cvtColor(ima,cv2.COLOR_GRAY2BGR)
circles= cv2.HoughCircles(ima,cv2.HOUGH_GRADIENT,1,20,param1=40,param2=20,minRadius=0,maxRadius=20) # time find circle = 0.07
circles = np.uint16(np.around(circles))

for i in circles[0,:]:
    cv2.circle(new_img,(i[0],i[1]),i[2],(255,255,255),-1)
                                                            #time até este parte-> media=0.015


t1 = time.time()
print (t1 -t0)


cv2.imshow("teste",new_img)
cv2.waitKey(0)
cv2.destroyAllWindows()


