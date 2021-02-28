/*******************************************************************************
 * Name          : waterjugpuzzle.cpp
 * Author        : Tae Hwan Kim and Yakov Kazinets
 * Date          : October 12, 2019
 * Description   : Water jug m8
 * Pledge		 : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
 
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

struct State { //Struct to represent state of water in the jugs.
    int a, b, c;
    vector<string> directions;
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { } // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
	vector<string> get_directions() {
		return directions;
	}
	bool operator==(const State &temp) {		//operator overload to compare between states
		return (a == temp.a && b == temp.b);	
	}
	void print_directions() {		//print direction
		for(const auto &d : directions) {
			cout<<d<<endl;
		}
	}
};
State goal(0,0,0);			//global goal so that it can be accessed everywhere
State capacity(0,0,0);		//global capacity so that the func pour have access to the capacity
void set_goal(int Ta, int Tb, int Tc) {		//set goal
	goal.a = Ta;
	goal.b = Tb;
	goal.c = Tc;
}
void set_capacity(int Ta, int Tb, int Tc) {		//set capacity
	capacity.a = Ta;
	capacity.b = Tb;
	capacity.c = Tc;
}
State pour(State x, int choice) {	//does pour according to what the choice is
	string d = "";  	//will append directions to here. 
	int amount = 0;     //the amount that will be poured, and this will be decided inside the nested if's
	if(choice == 0)  { //Pour C to A if valid
		if(x.a < capacity.a && x.c > 0) {		//if valid,
			int tempc = x.c;
			x.a += x.c;
			amount = x.c;
			x.c = 0;
			if(x.a > capacity.a) {	//if water overflowed, then adjust it
				x.c = x.a-capacity.a;
				x.a = capacity.a;
				amount = tempc - x.c;
			}
		}
		if(amount == 1) {
			d = "Pour 1 gallon from C to A. "+x.to_string();
		}
		else {
			d = "Pour "+to_string(amount)+" gallons from C to A. "+x.to_string();
		}
	}
	if(choice == 1)  { //Pour B to A if valid
		if(x.a < capacity.a && x.b > 0) {		//if valid,
			int tempb = x.b;
			x.a += x.b;
			amount = x.b;
			x.b = 0;
			if(x.a > capacity.a) {	//if water overflowed, then adjust it
				x.b = x.a-capacity.a;
				x.a=capacity.a;
				amount = tempb - x.b;
			}
		}
		if(amount == 1) {
			d = "Pour 1 gallon from B to A. "+x.to_string();
		}
		else {
			d = "Pour "+to_string(amount)+" gallons from B to A. "+x.to_string();
		}
	}
	if(choice == 2)  { //Pour C to B if valid
		if(x.b < capacity.b && x.c > 0) {		//if valid,
			int tempc = x.c;
			x.b += x.c;
			amount = x.c;
			x.c = 0;
			if(x.b > capacity.b) {	//if water overflowed, then adjust it
				x.c=x.b-capacity.b;
				x.b = capacity.b;
				amount = tempc - x.c;
			}
		}
		if(amount == 1) {
			d = "Pour 1 gallon from C to B. "+x.to_string();
		}
		else {
			d = "Pour "+to_string(amount)+" gallons from C to B. "+x.to_string();
		}
	}
	if(choice == 3)  { //Pour A to B if valid
		if(x.b < capacity.b && x.a > 0) {		//if valid,
			int tempa = x.a;
			x.b += x.a;
			amount = x.a;
			x.a = 0;
			if(x.b > capacity.b) {	//if water overflowed, then adjust it
				x.a = x.b-capacity.b;
				x.b = capacity.b;
				amount = tempa - x.a;
			}
		}
		if(amount == 1) {
			d = "Pour 1 gallon from A to B. "+x.to_string();
		}
		else {
			d = "Pour "+to_string(amount)+" gallons from A to B. "+x.to_string();
		}
	}
	if(choice == 4)  { //Pour B to C if valid
		if(x.c < capacity.c && x.b > 0) {		//if valid,
			int tempb = x.b;
			x.c += x.b;
			amount = x.b;
			x.b = 0;
			if(x.c > capacity.c) {	//if water overflowed, then adjust it
				x.b = x.c - capacity.c;
				x.c = capacity.c;
				amount = tempb - x.b;
			}
		}
		if(amount == 1) {
			d = "Pour 1 gallon from B to C. "+x.to_string();
		}
		else {
			d = "Pour "+to_string(amount)+" gallons from B to C. "+x.to_string();
		}
	}
	if(choice == 5)  { //Pour A to C if valid
		if(x.c < capacity.c && x.a > 0) {		//if valid,
			int tempa = x.a;
			x.c += x.a;
			amount = x.a;
			x.a = 0;
			if(x.c > capacity.c) {	//if water overflowed, then adjust it
				x.a = x.c - capacity.c;
				x.c = capacity.c;
				amount = tempa - x.a;
			}	
		}
		if(amount == 1) {
			d = "Pour 1 gallon from A to C. "+x.to_string();
		}
		else {
			d = "Pour "+to_string(amount)+" gallons from A to C. "+x.to_string();
		}
	}
	x.directions.push_back(d);
	return x;
}
void gooddope() {		//this finds the solution
	State initial(0,0, capacity.c);
	vector<State> dirty;     //dirty stores all combination of states
	bool **visited = new bool*[capacity.a+1];	//be able to check if visited, and [a][b] accordingly.  True = visited
	for(int i = 0; i < capacity.a+1; ++i) {
		visited[i] = new bool[capacity.b+1];
		fill(visited[i], visited[i] + capacity.b+1, false);
	}
	queue<State> clean;
	dirty.push_back(initial);
	clean.push(initial);
	visited[0][0] = true;
	bool found = false;  //bool for checking if no solution b/c i have to use break to delete matrix. False if not found
	while(!clean.empty()) {
		State temp = clean.front();
		for(int i = 0; i < 6; i++) {
			if(clean.front() == goal) {				//if find finish state, print 
				cout<<"Initial state. "<<initial.to_string()<<endl;
				temp.print_directions();
				found = true;
				break; 
			}
			dirty.push_back(pour(temp, i));
		}
		for(const auto &d : dirty) {
			if(!visited[d.a][d.b]) {	//if not visited,
				visited[d.a][d.b] = true;
				clean.push(d);
			}
		}
		clean.pop();
	}
	if(!found) {
		cout<<"No solution."<<endl;
	}	
	for(int i=0; i < capacity.a+1; ++i) {
		delete [] visited[i];
	}
	delete [] visited;
}			
int main(int argc, char * const argv[]) {
	int num;
	vector<int> values;
	if(argc != 7) {
		cerr<<"Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	for(int i = 1; i < 7; i++) {
		istringstream iss(argv[i]);
		if(!(iss>>num)) {
			if(i<4) {
				cerr<<"Error: Invalid capacity '"<<argv[i]<<"' for jug "<<(char)('A'+((i%4)-1))<<"."<<endl;
			}
			else {
				cerr<<"Error: Invalid goal '"<<argv[i]<<"' for jug "<<(char)('A'+((i%7)-4))<<"."<<endl;
			}
			return 1;
		}
		else {
			iss>>num;
			if(i < 4) {
				if(num<=0) {
					cerr<<"Error: Invalid capacity '"<<argv[i]<<"' for jug "<<(char)('A'+((i%4)-1))<<"."<<endl;
					return 1;
				}
				else {
					values.push_back(num);
				}
			}
			else {
				if(num < 0) {
					cerr<<"Error: Invalid goal '"<<argv[i]<<"' for jug "<<(char)('A'+((i%7)-4))<<"."<<endl;
					return 1;
				}
				else {
					values.push_back(num);
				}
			}
		}
	}
	for(int i = 3; i < 6; i++) {
		if(values[i] > values[i-3]) {
			cerr<<"Error: Goal cannot exceed capacity of jug "<<(char)('A'+((i%6)-3))<<"."<<endl;
			return 1;
		}
	}
	if(!(values[2] == values[3]+ values[4] + values[5])) {     
		cerr<<"Error: Total gallons in goal state must be equal to the capacity of jug C."<<endl;
		return 1;
	}
	set_goal(values[3], values[4], values[5]);
	set_capacity(values[0], values[1], values[2]);
	gooddope();
	return 0;
}