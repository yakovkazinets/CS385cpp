/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Yakov Kazinets 
 * Date        : September 11, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
	num_primes_ = count_num_primes();
}

void PrimesSieve::display_primes() const {
	int counter = 0; // used to count the spacings
	const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
	for (int i =2; i<= limit_; i++){
		if (is_prime_[i] == true){
			if (num_primes_> primes_per_row){ // tells whether or not there are multiple lines to be used
				if(counter == primes_per_row) {
					cout<<endl;
					counter = 0;
				}
				if(counter % primes_per_row == 0){
					cout << setw(max_prime_width)<<i;
					counter++;
				}
				else {
					cout << " " << setw(max_prime_width) << i;
					counter++;
				}
			} else {
				counter++;
				if (counter != num_primes_) {
					cout << i << " ";
				}
				else {
					cout << i; 
				}
			}
		}
		
	}
}

int PrimesSieve::count_num_primes() const {
    int j = 0; 
	for (int i = 2; i <= limit_; i++){
		if (is_prime_[i] == true){
			j++;
		}
	} 
	return j;
}

void PrimesSieve::sieve() {
    for (int i = 0; i<= limit_; i++){
		is_prime_[i] = true;
	}
	
	for (int i = 2; i <= sqrt(limit_*1.0); i++){ // requires a double so had to change the int into a double
		if (is_prime_[i] == true){
			for (int j = pow(i, 2); j<= limit_; j+=i ){
				is_prime_[j] = false;
			}
		}
	}
	
	
	for (int i = limit_; i >= 0 ; i--){
		if(is_prime_[i]){
			max_prime_ = i;
			break;
		}
	}
	
}

int PrimesSieve::num_digits(int num) {
    if (num < 10) {
		return 1;
	}
	else {
		return 1 + num_digits(num/10); 
	}
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;
	
    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);
	
    // Check for error.
	PrimesSieve Myprimes(limit);
	
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    } else {
		PrimesSieve Myprimes(limit);
		cout << endl;
		cout << "Number of primes found: " << Myprimes.num_primes()<< endl;
		cout << "Primes up to " << limit << ":" << endl;
		Myprimes.display_primes();
	}
	
    return 0;
}
