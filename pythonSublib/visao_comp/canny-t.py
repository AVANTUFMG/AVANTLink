import cv2
import numpy as np
import time 
import csv

altura  = 480
largura = 640

# calcula as distancias entre os pontos
def distancias(posições):

        a = ((((posições[0,0] - posições[1,0]) ** 2) + ((posições[0,1] - posições[1,1])**2))**(1/2))
        b = ((((posições[0,0] - posições[2,0])**2) + ((posições[0,1] - posições[2,1])**2))**(1/2))
        c = ((((posições[0,0] - posições[3,0])**2) + ((posições[0,1] - posições[3,1])**2))**(1/2))
        if a>b and a>c:
                dimens_obj = [b,c]
                return dimens_obj
        elif b>c:
                dimens_obj = [a,c]
                return dimens_obj
        else:
                dimens_obj= [a,b]
                return dimens_obj


#realizar cortes na imagem
def cut(pict,x1,y1,w1,h1,ach):
        original = cv2.imread(pict)
        height_ori,width_ori = original.shape[:2]
        constX = int(width_ori/largura) 
        constY = int(height_ori/altura)  
        X_ori=(x1)*(constX)
        Y_ori=(y1)*(constY)
        W_ori= X_ori + w1*(constX)
        H_ori= Y_ori + h1*(constY)
        k= 100

        if Y_ori-k <= 0 : Y_ori= 0
        if H_ori+k >= height_ori : H_ori = height_ori
        else: H_ori= H_ori+k
        if X_ori-k <=0 : X_ori = 0
        if W_ori+k >= width_ori : H_ori = width_ori
        else: W_ori= W_ori+k

        corte = original[(Y_ori):(H_ori),(X_ori):(W_ori)]
        cv2.imwrite("t1"+"-"+ pict +" -obj"+ str(ach)+".png",corte)

       
#importar dados para arquivo csv
def impcsv (pict,achados,encontrados,time):
        with open("dados.csv",'a', newline = '') as out :
                escrever = csv.writer(out)
                escrever.writerow([pict,achados,encontrados,time])


for j in range(1,39):
        picture= str(j) + ".jpg"
        ima = cv2.imread(picture)
        ima = imax = cv2.resize(ima,(largura,altura)) 

        kernel = np.ones((3,3),np.float32)

        t0 = time.time()
        
        #ima = cv2.GaussianBlur(ima,(5,5),0,1)
        ima = cv2.bilateralFilter(ima,7,110,110) #redução de ruídos
        ima = cv2.morphologyEx(ima,cv2.MORPH_DILATE,kernel) #tentar "consertar" objetos tratados
        
        #contorno=cv2.Canny(ima,100,150)
        contorno=cv2.Canny(ima,150,250,0,3,3)

        im2,cnts,hi = cv2.findContours(contorno,cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        achados = 0

        for cont in cnts:
                X,Y,W,H = cv2.boundingRect(cont) 
                rect = cv2.minAreaRect(cont)
                box = cv2.boxPoints(rect)
                box = np.int0(box)
                dimens = distancias(box)        
                if dimens[0]/dimens[1] > 0.5 and dimens[0]/dimens[1] < 1.9  and dimens[1]*dimens[0] >45 :   
                        cv2.drawContours(imax,[box],0,(255,0,0),1)
                        cut(picture,X,Y,W,H,achados)
                        achados +=1       

        t1 = time.time()
        #print (t1 -t0)

        cv2.imshow("imagem"+picture, imax)
        #cv2.imwrite("t1"+"-"+ picture,imax)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
        #obj_enc = input("quantos objetos encontrados")
        #impcsv(picture,achados,obj_enc,x)