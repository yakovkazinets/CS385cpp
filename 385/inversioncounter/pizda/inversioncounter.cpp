/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Nicholas Szegheo
 * Version     : 1.0
 * Date        : 10/25/2019
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long inv = 0;
    for (long i = 0; i < length - 1; i++){
        for (long j = i + 1; j < length; j++){
            if(array[i] > array[j]){
                inv++;
            }
        }
    }

    return inv;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    
    int *scratch = new int[length];
    long inv = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return inv;
}



static long mergesort(int array[], int scratch[], int low, int high) {
    // Mergesort with return of number of inversions.
    // Implementation of pseudocode from Dr. B's Canvas post
    long inv = 0;
    if (low < high){
        int mid = low + (high - low) / 2;
        inv +=  mergesort(array, scratch, low, mid);
        inv +=  mergesort(array, scratch, mid + 1, high);
        int L = low;
        int H = mid + 1;
        for (int k = low; k <= high; k++){
            if (L <= mid && (H > high || array[L] <= array[H])){
                scratch[k] = array[L];
                L++;
            }else{
                scratch[k] = array[H];
				H++;
                inv += (mid - L + 1);
            }
        }
        for (int k = low; k <= high; k++){
            array[k] = scratch[k];
        }
    }
    return inv;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    bool slowmode = false;
    if (argc > 2){
        cerr << "Usage: ./inversioncounter [slow]";
        return 1;
    }
    if(argc == 2){
        if (strcmp(argv[1],"slow") != 0){
            // The arg isn't "slow"
            cerr << "Error: Unrecognized option '" << argv[1] << "'." ;
            return 1;
        }
        else{
            slowmode = true;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    if (values.empty()){
        cerr << "Error: Sequence of integers not received." <<endl;
        return 1;
    }

    // TODO: produce output



    long a;
    

    if (!slowmode){
        a = count_inversions_slow(&values[0],values.size());
    }else{
        a = count_inversions_fast(&values[0],values.size());
    }
    cout << "Number of inversions: " << a << endl;

    return 0;
}
