#include "AVANTLink.h"
#include <mavlink.h>
#include <Print.h>
#include <AVANTConnect.h>

const int sID = 1;  //ID do sistema
const int cID = 200;//ID do componente
mavlink_message_t temp;

Aircraft::Aircraft()
{

}

Aircraft::~Aircraft()
{

}

void Aircraft::send_heartbeat(AVANTConnect a)
{
    a.send_msg(HEARTBEAT());
}

int Aircraft::arm_throttle(AVANTConnect a)
{
    mavlink_msg_command_long_pack(sID, cID, &temp,1,1,400,0,1,0,0,0,0,0,0);
    a.send_msg(temp);
    return 0;
}

double Aircraft::get_altitude(AVANTConnect a)
{
    altitude = a.receive_msg(33,4);
    return altitude;
}

void Aircraft::request_parameter_list(AVANTConnect a)
{
    a.send_msg(RPR());
}

void Aircraft::set_relay(AVANTConnect a,int relay, int state)
{
    a.send_msg(SET_RELAY(relay,state));
}


double Aircraft::get_latitude()
{

}

double Aircraft::get_longitude()
{

}

double Aircraft::get_dedicated_airspeed()
{

}

double Aircraft::get_heading()
{

}

void Aircraft::rc_override_ch3(AVANTConnect a,int value)
{
    mavlink_msg_rc_channels_override_pack(sID,cID,&temp,1,1,0,0,value,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    a.send_msg(temp);
}

int Aircraft::get_rc_ch3(AVANTConnect a)
{
    return a.receive_msg(35,4);
}




mavlink_message_t Aircraft::HEARTBEAT()
{
    mavlink_msg_heartbeat_pack(sID, cID, &temp, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
    return temp;
}

mavlink_message_t Aircraft::ARM()
{

}

mavlink_message_t Aircraft::GET_DEDICATED_AIRSPEED()
{
    logcat("airspeed");
    return temp;
}

mavlink_message_t Aircraft::SET_RELAY(int re,int st)
{
    mavlink_msg_command_long_pack(sID,cID,&temp,1,1,181,re,st,0,0,0,0,0,0);
    return temp;
}

mavlink_message_t Aircraft::RPR()
{
//    mavlink_msg_gps_ra&temp);
    return temp;
}
