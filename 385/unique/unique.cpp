/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Yakov Kazinets
 * Date        : September 20, 2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	for (size_t i = 0; i < s.size(); i++){
		if (isupper(s[i])){
			return false;
		}
	}
	return true;
	
	
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int bitset = 0;
	const int one = 1;
	for (size_t i =0; i < s.size(); i++) {
		int shifter = s[i] - 97;
		if (one << shifter & bitset){
			return false;
		} else {
			bitset = bitset | one << shifter;
		}
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	string in = "";
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <string>" <<endl;
		return 1;
	}
	
	if (argc > 2 ){
		cerr << "Usage: " << argv[0]<< " <string>" << endl;
		return 1;
	}
	in = argv[1];
	for (size_t i = 0; i < in.size(); i++){
		if (in[i] < 97 || in[i] > 122) {
			cerr << "Error: String must contain only lowercase letters." << endl;
			return 1;
		}
	}
	
	if (all_unique_letters(in)){
		cout << "All letters are unique." << endl;
	
	} else {
		cout << "Duplicate letters found." << endl;
	}
}
