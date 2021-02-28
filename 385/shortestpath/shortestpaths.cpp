/*******************************************************************************
 * Name          : shortestpaths.cpp
 * Author        : Yakov Kazinets Tae Hwan Kim
 * Date          : December 1, 2019
 * Description   : Floyd's Algorithm finding shortest path
 * Pledge		 : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
 
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <algorithm>
 #include <vector>
 #include <iomanip>
 #include <iterator>
 #include <limits>
 
 using namespace std;
 
 long num_vert = 0;
 long INF = numeric_limits<long>::max();
 long** inter;
 long** d1;
 long** d2;
 long** d3;
 
 
 int len(long num) {
	 int digit = 1;
	 while(num > 9) {
		 digit++;
		 num/=10;
	 }
	 return digit;
 }

 vector<char>getpath(int x, int y) { 
	vector<char> ans;
	char c1, c2;
	if(d3[x][y] == INF) {
		c1 = 'A' + x;
		c2 = 'A' + y;
		ans.push_back(c2);
		if(c1 != c2){
			ans.push_back(c1);
		}
		return ans;
	}else{
		ans = getpath(x,d3[x][y]);
		vector<char> sub = getpath(d3[x][y],y);
		sub.insert(sub.end(),ans.begin()+1,ans.end());
		return sub;
	}
 }
/**
 * Displays the matrix on the screen formatted as a table.
 */
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vert; i++) {
		for (int j = 0; j < num_vert; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
    int max_cell_width = len(max(static_cast<long>(num_vert), max_val));
    cout << ' ';
    for (int j = 0; j < num_vert; j++) {
    	cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vert; i++) {
    	cout << static_cast<char>(i + 'A');
    	for (int j = 0; j < num_vert; j++) {
    		cout << " " << setw(max_cell_width);
    		if (matrix[i][j] == INF) {
    			cout << "-";
    		} else if (use_letters) {
    			cout << static_cast<char>(matrix[i][j] + 'A');
    		} else {
    			cout << matrix[i][j];
    		}
    	}
    	cout << endl;
    }
    cout << endl;
}
void printPath() {
	vector<char> path;
	for(int i = 0; i<num_vert;++i){
		for(int j = 0;j<num_vert;++j){
			path = getpath(i,j);
			reverse(path.begin(),path.end());
			cout << static_cast<char>('A'+i) << " -> " << static_cast<char>('A'+j) << ", distance: ";
			if(d2[i][j] < INF){
				cout << d2[i][j] << ", path: ";
				cout << path.at(0);
				for(unsigned int x = 1; x < path.size();++x){
					cout << " -> " << path.at(x);
				}
			}
			else{
				cout << "infinity, path: none";
			}
			cout << endl;
		}
	}
}
void deleteMatrix(){
	for (int i = 0; i < num_vert; ++i) {
	    delete [] d1[i];
	    delete [] d2[i];
	    delete [] d3[i];
		delete [] inter[i];
	}
	delete [] d1;
	delete [] d2;
	delete [] inter;
	delete [] d3;
}
void floyd(long** adjmatrix) {
	d1 = new long*[num_vert];
 	for(int x = 0; x < num_vert; x++) {
 		d1[x] = new long[num_vert];
 		fill_n(d1[x],num_vert,INF);
 	}
 	d2 = new long*[num_vert];
 	 for(int x = 0; x < num_vert; x++) {
 		d2[x] = new long[num_vert];
 		for(int y = 0; y<num_vert; ++y){
 			d2[x][y] = adjmatrix[x][y];
 		}
 	}
 	d3 = new long*[num_vert];
 	for(int x = 0; x < num_vert; x++) {
 	 	d3[x] = new long[num_vert];
 	 	fill_n(d3[x],num_vert,INF);
	}
 	for(int k = 0; k < num_vert; k++) {
 	    for(int i = 0; i < num_vert; i++) {
 	        for(int j = 0; j < num_vert; j++) {
 	            if(d2[i][k] != INF && d2[k][j] != INF && d2[i][j] > (d2[i][k] + d2[k][j])) {
	 	            	d2[i][j] = d2[i][k] + d2[k][j];
	 	            	d3[i][j] = k;
 	            }
 	            if(i == j){
 	            	adjmatrix[i][j] = 0;
 	            	d2[i][j] = 0;
 	            	d3[i][j] = INF;
 	            }
 	        }
 	    }
 	}
 	display_table(adjmatrix, "Distance matrix:" , false);
 	display_table(d2, "Path lengths:", false);
 	display_table(d3, "Intermediate vertices:", true);
 }
//	return adjmatrix;

void add_matrix(char c1, char c2, int weight) {
	inter[c1-'A'][c2-'A'] = weight;
}










bool check(string s, int num_line) {
	istringstream iss(s);
	vector<string> input;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(input));
	if(input.size() != 3){
		cerr << "Error: Invalid edge data '" << s << "' on line " << num_line<< "." << endl;
		return false;
	}
	char maxLetter = 'A' + num_vert - 1;
	int edgeWeight = 0;
	char V1, V2;
	for(int i = 0; i < 3; ++i){
		if(input[i].size() != 1){
			if(i == 0){
				cerr << "Error: Starting vertex '" << input[i] << "' on line " << num_line << " is not among valid values A-"<< maxLetter <<"."<<endl;
				return false;
			}else if(i==1){
				cerr << "Error: Ending vertex '" << input[i] << "' on line " << num_line << " is not among valid values A-"<< maxLetter <<"."<<endl;
				return false;
			}
		}
		if(input[i].at(0) < 'A' || input[i].at(0) > maxLetter){
			if(i == 0){
				cerr << "Error: Starting vertex '" << input[i] << "' on line " << num_line << " is not among valid values A-"<< maxLetter <<"."<<endl;
				return false;
			}else if(i==1){
				cerr << "Error: Ending vertex '" << input[i] << "' on line " << num_line << " is not among valid values A-"<< maxLetter <<"."<<endl;
				return false;
			}
		}
		istringstream iss;
		if(i==0){
			V1 = input[0].at(0);
		}
		else if(i==1){
			V2 = input[1].at(0);
		}
		else if(i==2){
			iss.str(input[i]);
			if(!(iss >> edgeWeight)){
				cerr << "Error: Invalid edge weight '" << input[2] << "' on line " << num_line << "." << endl;
				return false;
			}
			if(edgeWeight < 1){
				cerr << "Error: Invalid edge weight '" << input[2] << "' on line " << num_line << "." << endl;
				return false;
			}
		}
	}
	add_matrix(V1,V2,edgeWeight);
	return true;

}



int main(int argc, const char *argv[]) {
// Make sure the right number of command line arguments exist.
	if (argc != 2 ) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	// Create an ifstream object.
	ifstream input_file(argv[1]);
	// If it does not exist, print an error message.
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	// Add read errors to the list of exceptions the ifstream will handle.
	input_file.exceptions(ifstream::badbit);
	string line;
	try {
		unsigned int line_number = 1;
		// Use getline to read in a line.
		// See http://www.cplusplus.com/reference/string/string/getline/
		while (getline(input_file, line)) {
			//cout << line_number << ":\t" << line << endl;
			if(line_number == 1){
				//num_vert = stoi(line);
				istringstream iss;
				iss.str(line);
				if(! (iss >> num_vert)){
					cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number <<"." << endl;
					return 1;
				}
				if(num_vert < 1 || num_vert > 26){
					cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number <<"." << endl;
					return 1;
				}
				inter = new long*[num_vert];
				for(int i = 0; i < num_vert; ++i){
					inter[i] = new long[num_vert];
					fill_n(inter[i] , num_vert , INF);
				}
			}else{
				if(!check(line, line_number)){
					return 1;
				}
			}
			++line_number;
		}
		// Don't forget to close the file.
		
	    floyd(inter);
		printPath();
		input_file.close();
		deleteMatrix();
		
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	return 0;
}	
