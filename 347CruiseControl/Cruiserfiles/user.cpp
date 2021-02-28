#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

#include "cruisecontrol.h"

enum string_code {
	help,
	engine,
	brake,
	speed,
	info,
	log_code,
	wrong
};

string_code hashit(string const& input) {
	if (input == "h") { return help; }
	else if (input == "e") { return engine; }
	else if (input == "b") { return brake; }
	else if (input == "s") { return speed; }
	else if (input == "i") { return info; }
	else if (input == "l") { return log_code; }
	else { return wrong; }
}

void displayHelpMessage() {
	cout << "h for helper massage" << endl;
	cout << "e to activate/disactivate engine"<<endl;
	cout << "b for brake" << endl;
	cout << "s to set speed" << endl;
	cout << "i to show information" << endl;
	cout << "l to show the log" << endl;
	cout << "type exit to close the cruise control exe";
}

int main() {
	string username;
	cout << "Welcome to the cruise control system. Please let me know your name: ";
	cin >> username;
	cout << endl;
	cout << "Welcome! " + username + "!"<< endl;
	CruiseControl cc;
	bool eng = false;
	bool bra = false;
	while (true) {
		string input;
		string check;
		cout << endl;
		cout << "Hi " + username+ "! What would you like to do?" << endl;
		displayHelpMessage();
		cout << endl;
		cout << "Command: ";
		cin >> input;
		if (input == "exit") {
			cout << "Thank you for using cruise control system. Goodbye!" << endl;
			break;
		}
		cout << endl;
		switch (hashit(input)) {
		case help:
			displayHelpMessage();
			break;
		case engine:
			if (eng) {
				eng = false;
			}
			else {
				eng = true;
			}
			cc.updateEngine(eng);
			cc.showinformation();
			break;
		case brake:
			if (bra) {
				bra = false;
			}
			else {
				bra = true;
			}
			cc.updateBrake(bra);
			cc.showinformation();
			break;
		case speed:
			double sp;
			cout << "input your speed: ";
			cin >> sp;
			while (sp > 125 || sp < 20) {
				cout << "invalid speed." << endl;
				cout << "input your speed: ";
				cin >> sp;
			}
			cc.updateSpeed(sp);
			cc.showinformation();
			break;
		case info:
			cc.showinformation();
			break;
		case log_code:
			cout << "Which log would you like to check?" << endl;
			cout << "a: all three logs" << endl;
			cout << "s: speed log" << endl;
			cout << "e: engine log" << endl;
			cout << "b: brake log" << endl;
			cout << "log: ";
			cin >> check;
			cc.printLog(check);
			break;
		default:
			cout << "invalid input." << endl;
			break;
		}

	}
	cc.freeup();
	return EXIT_SUCCESS;
}
