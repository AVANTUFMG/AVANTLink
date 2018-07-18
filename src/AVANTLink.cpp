#include "AVANTLink.h"
#include <mavlink.h>
#include <Print.h>
#include <AVANTConnect.h>

Aircraft::Aircraft()
{

}

Aircraft::~Aircraft()
{

}

int Aircraft::arm_throttle(AVANTConnect a)
{
    a.send_msg(ARM());
    return 0;
}

double Aircraft::get_altitude(AVANTConnect a)
{
    a.send_msg(GET_DEDICATED_AIRSPEED());
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

const int sID = 1;  //ID do sistema
const int cID = 200;//ID do componente

mavlink_message_t temp;

mavlink_message_t Aircraft::HEARTBEAT()
{
    mavlink_msg_heartbeat_pack(sID, cID, &temp, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
    return temp;
}

mavlink_message_t Aircraft::ARM()
{
    mavlink_msg_command_long_pack(sID, cID, &temp,1,1,400,0,1,0,0,0,0,0,0);
    return temp;
}

mavlink_message_t Aircraft::GET_DEDICATED_AIRSPEED()
{
    logcat("airspeed");
    return temp;
}
