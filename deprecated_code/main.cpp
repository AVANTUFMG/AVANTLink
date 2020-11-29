#include <stdio.h>
#include <unistd.h>
#include <AVANTConnect.h>
#include <Print.h>
#include <AVANTLink.h>

//Configuração da conexão com o MAVProxy
const std::string ip_adress = "localhost";
const int in_port = 14551;
const int out_port = 14550;

int main(int argc, char* argv[])
{
    logcat_open("saida.txt");

    AVANTConnect s = AVANTConnect(ip_adress,in_port,out_port);

    s.open_connection(domain_UDP,type_UDP,protocol_UDP);

    Aircraft zagi;

    //zagi.send_heartbeat(s);
    //zagi.arm_throttle(s);
    //zagi.rc_override_ch3(s,1800);
    //zagi.set_relay(s,2,1);

	while(true)
    {
        //zagi.get_rc_ch3(s);
        zagi.get_altitude(s);
    }
}


