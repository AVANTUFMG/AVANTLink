#pragma once

using namespace std;

class Telemetria
{
private:
	int bitRate;
	double velocity;		//speed?
	double batteryTension;
	double latitude;
	double longitude;
	double height;

public:
	Telemetria();

	void EstabelecerConexao();
	void InterromperConexao();

	int getBitRate() 
	{
		return bitRate;
	}

	double getVelocity() 
	{
		return velocity;
	}

	double getBatteryTension()
	{
		return batteryTension;
	}

	double getLongitude()
	{
		return longitude;
	}

	double getLatitude()
	{
		return latitude;
	}

	double getHeight()
	{
		return height;
	}

};

