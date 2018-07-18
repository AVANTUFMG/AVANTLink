#ifndef SOQUETE_H
#define SOQUETE_H
#include<string>
#include<sys/socket.h>
#include<mavlink.h>

//Constantes globais para evitar confusões no programa principal (É gambiarra EU SEI,I'm sorry)

const int domain_UDP = AF_INET; //Modo ipv4, usar AF_INET6 pra ipv6
const int type_UDP = SOCK_DGRAM; //Família UDP
const int protocol_UDP = 0; //Também não entendi pq só dá certo com 0, mas parece funcionar

class AVANTConnect
{
    public:
        AVANTConnect(std::string,int,int);
        virtual ~AVANTConnect();
        void print_ip();
        void open_connection(int,int,int);
        int send_msg(mavlink_message_t mensagem);

    protected:

    private:
        int in_port;
        int out_port;
        char ip[100]; //Array de caracteres para guardar o ip
        unsigned int ip_size;
};

#endif
