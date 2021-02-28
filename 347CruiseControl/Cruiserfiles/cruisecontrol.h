#ifndef CRUISECONTROL_H_
#define CRUISECONTROL_H_

#include <unordered_map> 
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <cstdio>

#include "systemlog.h"
#include "brakesensor.h"
#include "speedsensor.h"
#include "enginesensor.h"
#include "output.h"
using namespace std;

class CruiseControl { //cruise control class
    private:
        BrakeSensor *brakeSen = new BrakeSensor();
        EngineSensor *engineSen  = new EngineSensor();
        SpeedSensor *speedSen = new SpeedSensor();
        System_log *syslog = new System_log();
        Output update;
        void updateSysLogSpeed() {
            syslog->writeSpeed(speedSen->getSpeed());
        }
        void updateSysLogBrake() {
            syslog->writeBrake(brakeSen->getBrake());
        }
        void updateSysLogEngine() {
            syslog->writeEngine(engineSen->GetEngine());
        }
    public:
        CruiseControl(){
            
        }
        void updateSpeed(double newspeed){
            if (brakeSen->getBrake() || !engineSen->GetEngine()) {
                cout << "Cannot set speeed since either engine is off or brake is on." << endl;
                return;
            }
            speedSen->setSpeed(newspeed);
            updateSysLogSpeed();
        }
        void updateBrake(bool newbrake){
            brakeSen->setBrake(newbrake);
            if (newbrake) {
                speedSen->setSpeed(0.0);
                updateSysLogSpeed();
            }
            updateSysLogBrake();
        }
        void updateEngine (bool newengine){
            engineSen->SetEngine(newengine);
            if (!newengine) {
                speedSen->setSpeed(0.0);
                updateSysLogSpeed();
            }
            updateSysLogEngine();
        }
        void showinformation() {
            update.setbrake(brakeSen->getBrake());
            update.setengine(engineSen->GetEngine());
            update.setspeed(speedSen->getSpeed());
            update.printEngine();
            update.printBrake();
            update.printSpeed();
        }
        void printLog(string arg) {
            update.setLog(*syslog);
            if (arg == "a") {
                update.printallLog();
            }
            else if (arg == "e") {
                update.printEngineLog();
            }
            else if (arg == "s") {
                update.printSpeedLog();
            }
            else if (arg == "b") {
                update.printBrakeLog();
            }
            else {
                throw "Not a command to show log.";
            }
        }
        void freeup() {
            delete brakeSen;
            delete engineSen;
            delete speedSen;
            delete syslog;
        }
};

#endif
