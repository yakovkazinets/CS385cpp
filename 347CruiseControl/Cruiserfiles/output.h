#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "systemlog.h"

using namespace std;

class Output
{
private:
    bool brakeSen;
    bool engineSen;
    double speedSen;
    System_log LogSen;

public:
    Output() {
        brakeSen = false;
        engineSen = false;
        speedSen = 0.0;
    }
    void setbrake(bool brake) {
        brakeSen = brake;
    }
    void setengine(bool engine) {
        engineSen = engine;
    }
    void setspeed(double speed) {
        speedSen = speed;
    }
    void printBrake()
    {
        if (brakeSen)
        {
            cout << "Break Applied" << endl;
        }
        else
        {
            cout << "Break Not Applied" << endl;
        }
    }

    void printEngine()
    {
        if (engineSen)
        {
            cout << "Engine On" << endl;
        }
        else
        {
            cout << "Engine Off" << endl;
        }
    }

    void printSpeed()
    {
        cout << "Current Speed Is: " << speedSen << endl;
    }


    void setLog(System_log log)
    {
        LogSen = log;
    }

    void printEngineLog()
    {
        for (const auto i : LogSen.returnEngineLog())
        {
            cout << "Engine Log: " << endl;
            cout << i << endl;
        }
    }

    void printSpeedLog()
    {
        for (const auto i : LogSen.returnSpeedLog())
        {
            cout << "Speed Log: "  << endl;
            cout << i << endl;
        }

    }

    void printBrakeLog()
    {
        for (const auto i : LogSen.returnBrakeLog())
        {
            cout << "Brake Log: " << endl;
            cout << i << endl;
        }

    }

    void printallLog()
    {
        printEngineLog();
        printSpeedLog();
        printBrakeLog();
    }
};
#endif
