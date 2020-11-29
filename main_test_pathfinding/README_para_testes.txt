-------*COMO TESTAR*-------

>Altere em main.cpp as coordenadas iniciais do drone se quiser

>Altere as distâncias x_metros e y_metros em relação ao drone. O drone está no centro de um plano cartesiano (x,y) = (0,0). Os pontos min e max default do plano é (-600,-600) e (600,600) portanto, não exceda.

>Altere o número de obstáculos

>Só rodar o código!


-------*LENDO OUTPUT*-------
>o output da última iteração está no arquivo output.txt

>A primeira linha informa o tamanho da da matriz.

>A segunda linha (e próximas) contém todos as posicoes em x y dos pontos que são obstáculos terminando com um \

>Depois do \ a próxima linha contém os pontos que são "olhados" pelo algoritmo e após essa linha o ponto escolhido (em x,y)


Ex:
90x90
45 45; 45 60;\
-15 0;15 0;0 -15;15 -15;-15 -15;0 15;-15 15;15 15;
15 15;
0 15;30 15;15 0;30 0;0 0;15 30;0 30;30 30;
30 30;
...

interpretacao:
90x90 é o tamanho da matriz, 90x90 pontos, sendo que cada ponto é espaçado 15 metros e não 1 metro. Portanto o ponto (0,0) o próximo ponto a direita é (15,0) e não (1,0).

45 45; 45 60;\ são os pontos que são obstáculos (x,y) = (45,45) e (x,y) = (45,60).

-15 0;15 0;0 -15;15 -15;-15 -15;0 15;-15 15;15 15; são os pontos procurados.
15 15; ponto escolhido da lista de pontos acima.

0 15;30 15;15 0;30 0;0 0;15 30;0 30;30 30; próximos pontos procurados a partir do ponto (15,15) escolhido anteriormente.
30 30; ponto escolhido da lista acima.


-------*OBSERVAÇÕES*-------
A precisão do algoritmo é de +-8 metros. Portanto escolhendo o ponto (400,400) como destino, ele pode chegar em (405,405) e considerar como destino.

Caso queira aumentar a malha, o plano cartesiano vá em Point.cpp->Malha::Malha e substitua os valores de N_lat, N_lon. O N_H é para altura, no caso do 2D não usamos.