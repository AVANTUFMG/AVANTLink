#ifndef AVANTLINK_H
#define AVANTLINK_H
#include <mavlink.h>
#include <AVANTConnect.h>

class Aircraft
{
    public:
        Aircraft();
        virtual ~Aircraft();
        double get_altitude(AVANTConnect);
        double get_longitude();
        double get_latitude();
        double get_dedicated_airspeed();
        double get_heading();
        void request_parameter_list(AVANTConnect);
        void send_heartbeat(AVANTConnect);
        void set_relay(AVANTConnect,int,int);
        int arm_throttle(AVANTConnect);
        void rc_override_ch3(AVANTConnect,int);
        int get_rc_ch3(AVANTConnect);

    private:
        double altitude;
        double latitude;
        double longitude;
        double dedicated_airspeed;
        double heading;


        mavlink_message_t HEARTBEAT();
        mavlink_message_t ARM();
        mavlink_message_t GET_DEDICATED_AIRSPEED();
        mavlink_message_t RPR();
        mavlink_message_t SET_RELAY(int,int);
    protected:
};



#endif // AVANTLINK_H
