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
        int arm_throttle(AVANTConnect);
    private:
        double altitude;
        double latitude;
        double longitude;
        double dedicated_airspeed;
        double heading;

        mavlink_message_t HEARTBEAT();
        mavlink_message_t ARM();
        mavlink_message_t GET_DEDICATED_AIRSPEED();
    protected:
};



#endif // AVANTLINK_H
