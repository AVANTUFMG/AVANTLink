import cv2
import numpy as np
import time 

ima = cv2.imread("1(8).jpg")
ima = imax = cv2.resize(ima,(640,480)) 
#ima= cv2.cvtColor(ima,cv2.COLOR_RGB2HSV)
new_img = np.zeros((480,640),np.uint8)

kernel = np.ones((5,5),np.float32)

t0 = time.time()
ima = cv2.medianBlur(ima,5) 
ima = cv2.bilateralFilter(ima,7,110,110)
ima = cv2.morphologyEx(ima,cv2.MORPH_DILATE,kernel)

contorno=cv2.Canny(ima,100,150)

im2,cnts,hi = cv2.findContours(contorno,cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

for cont in cnts:
    X,Y,W,H = cv2.boundingRect(cont)
    if W/H > 0.4 and W/H < 1.8 and W*H >30 :
        rect = cv2.minAreaRect(cont)
        box = cv2.boxPoints(rect)
        box = np.int0(box)
        cv2.drawContours(imax,[box],0,(255,0,0),1)
    

t1 = time.time()
x= str(round(t1-t0,5))
x="tempo: " + x
print (t1 -t0)


cv2.putText(imax, str(x),(5,450),cv2.FONT_HERSHEY_SIMPLEX,0.5,(255,0,0),1,cv2.LINE_AA)
#cv2.imshow("imagem", imax)
cv2.imwrite("8-m.png",imax)
cv2.waitKey(0)
cv2.destroyAllWindows()