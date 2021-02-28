#ifndef BRAKESENSOR_H_
#define BRAKESENSOR_H_

class BrakeSensor
{
private:
    bool brake;

public:
    BrakeSensor(){
        brake = false;
    }

    void setBrake(bool newVal){
        brake = newVal;
    }

    bool getBrake(){ return brake; }

};

#endif