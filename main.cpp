#include <stdio.h>
#include <unistd.h>
#include <AVANTConnect.h>
#include <Print.h>
#include <AVANTLink.h>

//Configuração da conexão com o MAVProxy
const std::string ip_adress = "192.168.0.24";
const int in_port = 14551;
const int out_port = 14550;

int main(int argc, char* argv[])
{
    logcat_open("saida.txt");

    AVANTConnect s = AVANTConnect(ip_adress,in_port,out_port);

    s.open_connection(domain_UDP,type_UDP,protocol_UDP);

    Aircraft zagi;

	while(true)
    {
        int a = zagi.arm_throttle(s);


		//printf("%d\n",bytes_sent);
		sleep(1); // Sleep one second
    }
}


