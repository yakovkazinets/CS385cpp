#ifndef SYSTEMLOG_H_
#define SYSTEMLOG_H_

#include <unordered_map>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include <string>
#include <time.h>
#include <stdio.h>


using namespace std;

class System_log {
private:
	vector<string> enginetrack;
	vector<string> braketrack;
	vector<string> speedtrack;
public:
	System_log() {}
	void writeEngine(bool signal) {
		string str;
		string s;
		time_t ltime;
		struct tm  *timeinfo;

		time(&ltime);
		timeinfo = localtime(&ltime);
		if (signal) {
			s = " System has been activate.";
			str = asctime(timeinfo) + s;
			enginetrack.push_back(str);
		}
		else {
			s = " System has been disactivate.";
			str = asctime(timeinfo) + s;
			enginetrack.push_back(str);
		}
	}
	void writeBrake(bool signal) {
		string str;
		string s;
		time_t ltime;
		struct tm  *timeinfo;

		time(&ltime);
		timeinfo = localtime(&ltime);
		if (signal) {
			s = " Brake has been activate.";
			str = asctime(timeinfo) + s;
			braketrack.push_back(str);
		}
	}
	void writeSpeed(double speed) {
		string str;
		time_t ltime;
		struct tm  *timeinfo;
		string s;
		time(&ltime);
		timeinfo = localtime(&ltime);
		s = " speed has been set to ";
		str = asctime(timeinfo) + s + to_string(speed);
		speedtrack.push_back(str);
	}
	vector<string>  returnEngineLog() {
		return  enginetrack;
	}
	vector<string>  returnSpeedLog() {
		return  speedtrack;
	}
	vector<string>  returnBrakeLog() {
		return  braketrack;
	}
};
#endif
