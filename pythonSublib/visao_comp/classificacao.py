import cv2
import numpy as np
import math
import matplotlib.pyplot as plt
from PIL import Image

nome  = "triangulo"
img_original = cv2.imread("entradas/" + nome + ".png")
#cv2.imshow('Imagem Original',img_original)

imagem_cinza = cv2.cvtColor(img_original, cv2.COLOR_BGR2GRAY)
#cv2.imshow('Imagem Original',imagem_cinza)

binarizada = cv2.threshold(imagem_cinza, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)[1]
contorno, hierarchy = cv2.findContours(binarizada, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
#cv2.imshow('Binarizada',binarizada)

imagem_s_bilateral = cv2.bilateralFilter(binarizada,9,75,75)

opening = cv2.morphologyEx(imagem_s_bilateral, cv2.MORPH_OPEN, np.ones((5,5),np.uint8))
#cv2.imshow('Opening',opening)
closing = cv2.morphologyEx(opening, cv2.MORPH_CLOSE, np.ones((5,5),np.uint8))
#cv2.imshow('Closing',closing)

linhas = cv2.Canny(closing,40,80)

contornos,h = cv2.findContours(linhas,1,2)


imagem_vazia = np.zeros(img_original.shape, np.uint8)


maior_contorno = max(contornos, key = cv2.contourArea)
area_maior_contorno = cv2.contourArea(maior_contorno)

#pega o Idx do maior contorno e desenha na imagem vazia
#lembrar que da pra guardar o idx pra usar dps
id_maior_contorno=0
for i in contornos:
    if cv2.contourArea(i)==area_maior_contorno:
        cv2.drawContours(imagem_vazia, contornos, id_maior_contorno, (255, 0, 0), 2)
    id_maior_contorno += 1
#centro do maior contorno
M = cv2.moments(maior_contorno)
cX = int(M["m10"] / M["m00"])
cY = int(M["m01"] / M["m00"])
cv2.circle(imagem_vazia, (cX, cY), 2, (0, 0, 255), 2)
print("Centro do Contorno: ",cX,cY)
print("Area do contorno: ",area_maior_contorno)

#desenhando o menor circulo em volta do contorno
#o circulo eh a melhor figura para se comparar
#o alvo a ser comparado pode estar em qualquer orientacao
(x,y),raio = cv2.minEnclosingCircle(maior_contorno)
centro = (int(x),int(y))
#calcular a area antes, com raio float
area_circulo = math.pi*pow(raio,2)#so pra comparar
raio = int(raio)
cv2.circle(imagem_vazia,centro,raio,(0,255,0),2)
cv2.circle(imagem_vazia, centro, 2, (0, 255, 0), 2)
razao_circular = area_circulo/area_maior_contorno
print("Centro do circulo minimo: ",centro)
print("Area do circulo minimo: ",area_circulo)
print("Razao Circular: ",razao_circular)

#distancia entre o centro do contorno e o centro do circulo minimo
#centros do trapezio e quarto de circulo nao coincidem (faltar provar pro trapezio)
diferenca_centro = math.sqrt(math.pow((cX-x),2)+math.pow((cY-y),2))
print("Distancia de centros: ",diferenca_centro)

#aproximando por linhas
#0.029 foi o melhor lambda ate agr, funcionou pra todas as imgs
#desde que a imagem binaria nao bugue 
aproximacao = cv2.approxPolyDP(maior_contorno,0.027*cv2.arcLength(maior_contorno,True),True)

#desenhando um retangulo minimo (area minima) no contorno
retangulo = cv2.minAreaRect(maior_contorno)
#pegando as dimensoes do retangulo(largura > altura)

if retangulo[1][0] >= retangulo[1][1]:
    w = retangulo[1][0]
    h = retangulo[1][1]
else:
    h = retangulo[1][0]
    w = retangulo[1][1]

proporcao = w / float(h)
ptns_retangulo = cv2.boxPoints(retangulo)
ptns_retangulo = np.int0(ptns_retangulo)
cv2.drawContours(imagem_vazia,[ptns_retangulo],0,(0,0,255),2)
razao_retangular = w*h/area_maior_contorno
print("Razao retangular: ",razao_retangular)
print("Largura: ",w)
print("Altura: ",h)
print("Proporcao: ",proporcao)
print("Area do minimo retangulo: ",cv2.contourArea(ptns_retangulo))
area_imaginaria = math.pi*math.pow(w/2,2)/2
print("Area imaginaria: ",area_imaginaria)

#pega o numero de lados da aproximacao
nr_pontos = len(aproximacao)
area_aproximada = cv2.contourArea(aproximacao)
print("Tamanho aproximado: ",area_aproximada)
print("Numero de pontos: ",nr_pontos)

if razao_circular >= 0.90 and razao_circular <= 1.10 and nr_pontos >= 4:
    print("Circulo")
    figura = "Circulo"
elif diferenca_centro >=5 and razao_circular >= 1.95 and razao_circular <= 2.05 or (area_imaginaria >= 0.9*area_aproximada and area_imaginaria <= 1.1*area_aproximada) and nr_pontos > 4 and nr_pontos <10:
    print("Semi-Circulo")
    figura = "Semi-Circulo"
elif nr_pontos == 3:
    print("Triangulo")
    figura = "Triangulo"
elif proporcao >= 0.90 and proporcao <= 1.10 and razao_circular >= 0.90*math.pi/2 and razao_circular <= 1.10*math.pi/2:
    print("Quadrado")
    figura = "Quadrado"
elif w*h >= 0.9*area_maior_contorno and razao_retangular >= 0.9 and razao_retangular <= 1.10:
    print("Retangulo")
    figura = "Retangulo"
elif diferenca_centro >= 5:#ou eh trapezio ou quartodecirculo
    if proporcao >= 0.90 and proporcao <= 1.10 and razao_retangular >= 0.9*4/math.pi and razao_retangular <= 1.10*4/math.pi:
        print("Quarto de Circulo")
        figura = "Quarto de Circulo"
    elif nr_pontos <= 5:
        print("Trapezio")
        figura = "Trapezio"
    else:
        print("Nao identificado")
        figura = "Nao identificado"
elif nr_pontos == 4:
    print("Losango")
    figura = "Losango"
elif nr_pontos == 5:
    print("Pentagono")
    figura = "Pentagono"
elif nr_pontos == 6:
    print("Hexagono")
    figura = "Hexagono"
elif nr_pontos == 10:
    print("Estrela")
    figura = "Estrela"
elif nr_pontos > 10:
    print("Cruz (Sinal de Mais+)")
    figura = "Cruz (Sinal de Mais+)"
else:
    print("Nao identificado")
    figura = "Nao identificado"
    

cv2.drawContours(imagem_vazia, aproximacao, -1, (0, 150, 100), 5)

#imagem colorida com contorno
#imagem auxiliar com o contorno branco e o restante preto
#depois sobrepoe a original
img_auxiliar = np.zeros(img_original.shape,np.uint8)
cv2.drawContours(img_auxiliar,[maior_contorno],0,[255,255,255],-1)
img_contorno_isolado = cv2.bitwise_and(img_original,img_auxiliar)

#pegando a cor
pixels = np.float32(img_contorno_isolado.reshape(-1, 3))
n_colors = 3
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 200, .1)
flags = cv2.KMEANS_RANDOM_CENTERS
_, labels, palette = cv2.kmeans(pixels, n_colors, None, criteria, 10, flags)
_, counts = np.unique(labels, return_counts=True)


preto_posicao = np.argmax(counts)
letra_posicao = np.argmin(counts)

if preto_posicao != 0 and letra_posicao != 0:
    bgr_figura = palette[0]
elif preto_posicao != 1 and letra_posicao != 1:
    bgr_figura = palette[1]
else:
    bgr_figura = palette[2]

vet_bgr_figura = np.uint8([[bgr_figura]])
vet_bgr_letra = np.uint8([[palette[letra_posicao]]])
hsv_figura = cv2.cvtColor(vet_bgr_figura, cv2.COLOR_BGR2HSV)
hsv_letra = cv2.cvtColor(vet_bgr_letra, cv2.COLOR_BGR2HSV)
h, s, v = hsv_figura[:, :, 0], hsv_figura[:, :, 1], hsv_figura[:, :, 2]
hl, sl, vl = hsv_letra[:, :, 0], hsv_letra[:, :, 1], hsv_letra[:, :, 2]
print("H antes de dobrar: ",h)
print("Hl antes de dobrar: ",hl)
h = 2.0 * h
hl = 2.0 * hl
s = s*(100/255)
v = v*(100/255)
sl = sl*(100/255)
vl = vl*(100/255)
print("H: ",h)
print("S: ",s)
print("V: ",v)
print("Hl: ",hl)
print("Sl: ",sl)
print("Vl: ",vl)
print(hsv_figura)

#comparando a cor da figura
cor_figura = "Cor nao identificada"
if h >=0 and h <= 360 and s >= 0 and s <= 100 and v <= 10:
    cor_figura = "Preto"
elif h >= 0 and h <= 360 and s < 15 and v >= 65:
    cor_figura = "Branco"
elif h >= 0 and h <= 360 and s < 15 and v > 10 and v < 65:
    cor_figura = "Cinza"
elif (h < 11 or h >= 351) and s > 45 and v > 10:
    cor_figura = "Vermelho"
elif ((h < 11 or h > 351) and s < 70 and v > 10) or (h > 310 and h < 351 and s > 15 and v > 10):
    cor_figura = "Rosa"
elif h > 11 and h < 45 and s > 15 and v > 75:
    cor_figura = "Laranja"
elif h > 11 and h < 45 and s > 15 and v < 10 and v > 75:
    cor_figura = "Marrom"
elif h > 45 and h < 64 and s > 15 and v > 10:
    cor_figura = "Amarelo"
elif h > 64 and h < 150 and s > 15 and v > 10:
    cor_figura = "Verde"
elif h > 150 and h < 180 and s > 15 and v > 10:
    cor_figura = "Entre verde e azul"
elif h > 180 and h < 255 and s > 15 and v > 10:
    cor_figura = "Azul"
elif h > 255 and h < 310 and s > 5 and v > 10:
    cor_figura = "Violeta"
elif h > 355 and h < 310 and s > 15 and s < 5 and v > 10:
    cor_figura = "Violeta tbm"

cv2.putText(img_contorno_isolado, "1: %s" % (figura), (0,10), cv2.FONT_ITALIC,0.4,(243, 229,28), 1)
cv2.putText(img_contorno_isolado, "2: %s" % (cor_figura), (0,25), cv2.FONT_ITALIC,0.4,(243, 229,28), 1)
print(cor_figura)


print("Cor Preta: ",palette[preto_posicao])
print("Cor da figura em BGR: ",bgr_figura)
print("Cor da letra: ",palette[letra_posicao])


#cv2.imshow('Imagem vazia com o contorno',imagem_vazia)
cv2.imshow('Imagem com contorno isolado',img_contorno_isolado)
img_original = cv2.imwrite("saidas/"+nome+".png",img_contorno_isolado)

#cv2.imshow('Somente Linhas + (Gauss e Bilateral antes)', linhas)
#cv2.imshow('Imagem com Suavizacao Bilateral', imagem_s_bilateral)



cv2.waitKey(0)
cv2.destroyAllWindows()
