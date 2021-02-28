#ifndef SPEEDSENSOR_H_
#define SPEEDSENSOR_H_

class SpeedSensor
{
private:
    double speed;

public:
    SpeedSensor(){
        speed = 0.0;
    }

    void setSpeed(double new_speed){
        speed = new_speed;
    }

    double getSpeed(){ return speed; }

};

#endif