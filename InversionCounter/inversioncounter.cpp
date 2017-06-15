/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Jordan Handwerger
 * Version     : 1.0
 * Date        : March 28, 2017
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

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	//Counts the number of inversions in an array in theta(n^2) time using a nested for loop.
	long count = 0;
	for (int i = 0; i < length - 1; i++) {
		for (int j = i + 1; j < length; j++) {
			if (array[i] > array[j]) { //every inversion increments the count
				count++;
			}
		}
	}
	return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */

static long mergesort(int array[], int scratch[], int low, int high,
		long &count) {
	//Counts the number of inversions in an array in theta(n lg n) time using an altered version of mergesort.
	if (low < high) {
		int mid = (low + high) / 2;
		mergesort(&array[0], &scratch[0], low, mid, count); //breaks down the left subarray
		mergesort(&array[0], &scratch[0], mid + 1, high, count); //breaks down the right subarray
		int L = low;
		int H = mid + 1;
		for (int k = low; k <= high; k++) {
			if ((L <= mid) && ((H > high) || (array[L] <= array[H]))) { //pulls a number from the right subarray
				scratch[k] = array[L];
				L++;
			} else { //pulls from the left results in the number the length of the left side inversions
				count += mid - L + 1;
				scratch[k] = array[H];
				H++;

			}
		}
		for (int k = low; k <= high; k++) { //copies back from the scratch array
			array[k] = scratch[k];
		}
	}
	return count;
}

long count_inversions_fast(int array[], int length) {
	//Counts the number of inversions in an array in theta(n lg n) time by calling an altered version of mergesort.
	vector<int> scratch; //creates and fills a dummy array
	for (int i = 0; i < length; i++) {
		scratch.push_back(0);
	}
	long count = 0;
	return mergesort(&array[0], &scratch[0], 0, length - 1, count);
}

int main(int argc, char *argv[]) {
	bool fast = true; //defaults the program to the fast version
	if (argc == 2) { //takes in a command line arg
		if (strcmp(argv[1], "slow") == 0) { //sets the program to use the slow algorithm
			fast = false;
		} else { //the user input a command line argument that is not 'slow'
			cout << "Error: Unrecognized option '" << argv[1] << "'." << "\n";
			return 1;
		}
	} else if (argc > 2) { //the user entered more than 1 argument in the command line
		cout << "Usage: ./inversioncounter [slow]";
		return 1;
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
	if (values.size() == 0) { //the user did not enter any intergers when prompted
		cout << "Error: Sequence of integers not received." << "\n";
		return 1;
	}
	string output;
	if (fast == true) { //runs the fast algorithm
		cout << "Number of inversions: "
				<< count_inversions_fast(&values[0], values.size()) << "\n";
	} else { //slow algorithm
		cout << "Number of inversions: "
				<< count_inversions_slow(&values[0], values.size()) << "\n";
	}
	return 0;
}
