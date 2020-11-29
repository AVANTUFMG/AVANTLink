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

        ima = cv2.cvtColor(ima,cv2.COLOR_RGB2HSV_FULL)

        kernel = np.ones((5,5),np.float32)

        t0 = time.time()
        
        ima = cv2.GaussianBlur(ima,(3,3),0,1)
        ima = cv2.bilateralFilter(ima,5,80,80) #redução de ruídos
        ima = cv2.morphologyEx(ima,cv2.MORPH_DILATE,kernel) #tenta "consertar" objetos tratados
        

        for i in range(1,2):
                contorno=cv2.Canny(ima[:,:,i],120,220)
                contorno2 = cv2.Canny(ima[:,:,i+1],120,220)
                contorno3 = cv2.merge((contorno,contorno2,contorno2))
                contorno3 = cv2.cvtColor(contorno3,cv2.COLOR_RGB2GRAY)

                im2,cnts,hi = cv2.findContours(contorno3,cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

                if (i==1):
                        achados = 0

                for cont in cnts:
                        X,Y,W,H = cv2.boundingRect(cont) 
                        rect = cv2.minAreaRect(cont)
                        box = cv2.boxPoints(rect)
                        box = np.int0(box)
                        dimens = distancias(box)        
                        if dimens[0]/dimens[1] > 0.5 and dimens[0]/dimens[1] < 1.9  and dimens[1]*dimens[0] >100 :   
                                cv2.drawContours(imax,[box],0,(255,0,0),1)
                                #cut(picture,X,Y,W,H,achados)
                                achados +=1       

        t1 = time.time()
        x= str(round(t1-t0,5))
        x="tempo: " + x



        cv2.putText(imax, str(x),(5,450),cv2.FONT_HERSHEY_SIMPLEX,0.5,(255,0,0),1,cv2.LINE_AA)
        cv2.imshow("imagem"+picture, imax)
        cv2.imwrite("t6"+"-"+ picture,imax)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
        obj_enc = 0
        obj_enc = input("quantos objetos encontrados")
        impcsv(picture,achados,obj_enc,x)
        