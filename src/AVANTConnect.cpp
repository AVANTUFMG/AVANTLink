#include "AVANTConnect.h"
#include <Print.h>
#include <cstring> //Memset
#include <string>  //std::string
#include <sys/socket.h> //Tudo
#include <arpa/inet.h> //Estruturas adicionais
#include <mavlink.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define buffer_size 2041 //A documentação oficial do MAVLINK manda botar esse valor, mas tbm não sabem pq


int sock;
struct sockaddr_in out_connection;
struct sockaddr_in in_connection;


AVANTConnect::AVANTConnect(std::string str,int pi,int po)
{
    ip_size = str.length();
    for (int i=0;i<ip_size;i++) //Gambiarra pra converter string pra array de char :)
    {
        ip[i] = str[i];
    }
    in_port = pi;
    out_port = po;
}

AVANTConnect::~AVANTConnect()
{

}
void AVANTConnect::print_ip() //Imprime o ip
{
    for (int i=0;i<ip_size;i++)
    {
        logcat(ip[i]);
    }
    logcatln("");
}

void AVANTConnect::open_connection(int domain,int type, int protocol) //Cria um novo soquete com os argumentos especificados;
{
    sock = socket(domain,type,protocol); //De fato cria o soquete

    memset(&out_connection, 0, sizeof(out_connection)); //Inicializa a estrutura com 0 (Não necessariamente necessário mas vai que né)

	out_connection.sin_family = AF_INET; //Modo ipv4, usar AF_INET6 pra ipv6
	out_connection.sin_addr.s_addr = inet_addr(ip); //Seta o IP
	out_connection.sin_port = htons(out_port); //Porta de saída

    memset(&in_connection, 0, sizeof(in_connection));
	in_connection.sin_family = AF_INET;
	in_connection.sin_addr.s_addr = INADDR_ANY;
	in_connection.sin_port = htons(in_port);

	printf("port set\n");

	if (-1 == bind(sock,(struct sockaddr *)&in_connection, sizeof(struct sockaddr))) //Liga o soquete à porta de entrada para receber dados do MAVProxy
    {
		perror("error bind failed");
		close(sock);
		exit(EXIT_FAILURE);
    }


    logcatln("Socket created sucessfully");

}

int AVANTConnect::send_msg(mavlink_message_t msg)
{
    socklen_t output_size;

    unsigned char buffer[buffer_size+1];
    logcatln("Sending message: ");

    int msg_size = mavlink_msg_to_send_buffer(buffer, &msg);
    //Imprimir msg aq (MAV decode)

    int sent = sendto(sock,buffer,msg_size, 0, (struct sockaddr*)&out_connection, sizeof(struct sockaddr_in));

    memset(buffer, 0, buffer_size);
    ssize_t received_msg_size = recvfrom(sock, (void *)buffer, buffer_size, 0, (struct sockaddr *)&out_connection, &output_size);
    //registraL(tam_recebido);
    memset(buffer, 0, buffer_size);

    return sent;
}


/*
    Caio TBC
    Universidade Federal de Minas Gerais
    AVANT-UFMG 2018
*/
