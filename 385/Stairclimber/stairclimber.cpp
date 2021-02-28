/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Yakov Kazinets
 * Date        : September 29, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways_possible; // A vector of vectors of all the ways possible
	vector<int> empty; 
	if(num_stairs <= 0){ // incase the number of stair is 0 or not possible in the sense it is negative 
		ways_possible.push_back(empty); 
	}else{
		for (int i = 1; i <= 3; i++){ 
			if (num_stairs >= i){
				vector<vector<int>> new_way = get_ways(num_stairs - i); 
				for (unsigned int j=0; j < new_way.size(); j++){
					new_way[j].insert(new_way[j].begin(), i);
				}
				ways_possible.insert(ways_possible.end(), new_way.begin(), new_way.end());
			}
		}
	}
	return ways_possible;
}
	


int display_ways_helper(int num) {   //A recursive helper function that helps to find the digit.
    if(num / 10 == 0){
		return 1;
	}
	else{
		return display_ways_helper(num/10) + 1;
	}
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	
	for(unsigned int i = 0; i < ways.size(); i++) {
		if(ways.size() >= 10) {								//if the number of ways possible is more than 1 digit, then everything will be aligned to the right correctly
			cout<< setw(display_ways_helper(ways.size()));
		}
		cout<< i+1 << ". " << "[";
		unsigned int j=0; 
		while(j < ways[i].size()-1) {
			cout<< ways[i][j] << ", ";
			j++;
		}
		cout<< ways[i][j];
		cout<< "]" << endl;
	}
}

int main(int argc, char * const argv[]) {

	int input_n; //the input integer 
	
	if(argc != 2){ 
		cerr<< "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	
	istringstream s(argv[1]);
	
	if(!(s>>input_n)){
		cerr<< "Error: Number of stairs must be a positive integer."<< endl;
		return 1;
	}
	
	if(input_n <=0){
		cerr<< "Error: Number of stairs must be a positive integer."<< endl;
		return 1;
	}
	
	int num_ways = get_ways(input_n).size();
	
	if(num_ways > 1){
		cout<< num_ways<< " ways to climb "<< input_n<< " stairs."<< endl;
	}
	
	else{
		cout<< num_ways<< " way to climb "<< input_n<< " stair."<< endl;
	}
	
	display_ways(get_ways(input_n));
	
	return 0;
}
