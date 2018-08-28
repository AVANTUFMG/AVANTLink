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

#include<mavlink.h>

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
    int temp = 0;
    socklen_t output_size;

    unsigned char buffer[buffer_size+1];
    logcatln("Sending message: ");

    int msg_size = mavlink_msg_to_send_buffer(buffer, &msg);
    //Imprimir msg aq (MAV decode)

    int sent = sendto(sock,buffer,msg_size, 0, (struct sockaddr*)&out_connection, sizeof(struct sockaddr_in));

    memset(buffer, 0, buffer_size);
    ssize_t received_msg_size = recvfrom(sock, (void *)buffer, buffer_size, 0, (struct sockaddr *)&out_connection, &output_size);

		memset(buffer, 0, buffer_size);
		//sleep(1); // Sleep one second

    //registraL(tam_recebido);
    memset(buffer, 0, buffer_size);

    return sent;
}

int AVANTConnect::receive_msg(int id,int field)
{
    mavlink_message_t msg;
    int temp = 0;
    socklen_t output_size;

    unsigned char buffer[buffer_size+1];
    logcatln("Receiving message: ");

    int msg_size = mavlink_msg_to_send_buffer(buffer, &msg);
    while(msg_size>1)
    {
    //Imprimir msg aq (MAV decode)
        int sent = sendto(sock,buffer,msg_size, 0, (struct sockaddr*)&out_connection, sizeof(struct sockaddr_in));

        memset(buffer, 0, buffer_size);

        ssize_t received_msg_size = recvfrom(sock, (void *)buffer, buffer_size, 0, (struct sockaddr *)&out_connection, &output_size);
            if (received_msg_size > 0)
            {
                // Something received - print out all bytes and parse packet
                mavlink_message_t a;
                mavlink_status_t status;

                //logcat("Bytes Received:");
                //ogcatln((int)received_msg_size);
                //logcat("Datagram: ");
                for (int i = 0; i < received_msg_size; ++i)
                {
                    temp = buffer[i];
                    //logcat((unsigned char)temp);
                    //logcat(" ");
                    if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &a, &status))
                    {
                        switch(a.msgid)
                        {
                            case 33:
                            switch(field)
                            {
                                case 4:
                                mavlink_global_position_int_t payload;
                                mavlink_msg_global_position_int_decode(&a,&payload);
                                logcat("ALTITUDE=");
                                logcatln(payload.relative_alt);
                                break;
                            }
                            break;
                        }


                        //logcat("MSG ID:");
                        //logcat(a.msgid);
                        //logcatln("");
                        // Packet received
                        /*logcat("\nReceived packet: LEN:");
                        logcat(a.sysid);*/
                    }
                }
                //logcatln("");
            }
            memset(buffer, 0, buffer_size);
    }
    return 0;
}


/*
    Caio TBC
    Universidade Federal de Minas Gerais
    AVANT-UFMG 2018
*/
