#ifndef ENGINESENSOR_H_
#define ENGINESENSOR_H_

class EngineSensor
{
private:
    bool EngineSignal;


public:
    EngineSensor(){ 
        EngineSignal = false;
    }

    int GetEngine(){
        if (EngineSignal) {
            return 0;
        } else { 
            return 1;
        }
    }

    void SetEngine(bool newVal){ EngineSignal = newVal; }

};

#endif