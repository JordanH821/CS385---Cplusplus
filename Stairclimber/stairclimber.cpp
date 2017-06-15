/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jordan Handwerger
 * Date        : February 21, 2017
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
    // Returns a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector< vector<int> > ways;
	if(num_stairs <= 0){ //base case
		vector<int> empty;
		ways.push_back(empty);
	}
	for(int i = 1; i <= 3; i++){ //creates a case for climbing 1,2, or 3 steps
		if(num_stairs >= i){ //prevents unnecessary recursion
			vector< vector<int> > result = get_ways(num_stairs - i); //up to 3 recursive calls
			for(size_t j = 0; j <= result.size() - 1; j++){ // appends the stairs climbed in that call to each internal vector
				result[j].push_back(i);
			}
			//appends the recursive results to the overall ways list
			ways.insert(ways.end(), result.begin(), result.end());
		}
	}
	return ways;
}

int num_digits(int num){
	//helper function for the output
	//returns the number of digits in a given int
	int digits = 1;
	while(num / 10 != 0) { //counts digits using int division
		num = num / 10;
		digits++;
	}
	return digits;
}


void display_ways(const vector< vector<int> > &ways) {
    // Displays the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int i = 1; // starts the count
	int spacing = num_digits(ways.size()); // spacing for the right alignment
	for(vector< vector<int> >::const_iterator it = ways.begin(); it != ways.end(); ++it){ // loop for the outer vector
		cout << setw(spacing) << i << ". "; // outputs the number correctly aligned
		i++; //increments counter
		cout << "["; // starts the output of the current way
		for(vector<int>::const_reverse_iterator it2 = it->rbegin(); it2 != it->rend(); ++it2){
			// loop for the inner vector,
			// it is backwards be organized by first step starting at 1
				cout << *it2; // outputs the integer
				if( it2 != it->rend() - 1){ //determines if there needs to be a comma after this integer
					cout << ", ";
				}
		}
		cout << "]" << endl; // closes the current way
	}

}

int main(int argc, char * const argv[]) {
	int stairs;
	istringstream iss;

	if(argc != 2){ // checks for improper input
		cout << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}

	iss.str(argv[1]); // places the argument in the string stream

	if( !(iss >> stairs)){ // checks the input is an integer
		cout << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	} else if( stairs < 1){ // checks for a positive number of stairs
		cout << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	} else {
		vector< vector<int> > i = get_ways(stairs);
		if(stairs == 1){ // check for one stair, so output is not '1 stairS'
			cout << "1 way to climb 1 stair." << endl;;
		} else { // outputs in the specified format
			cout << i.size() << " ways to climb " << stairs << " stairs." << endl;;
		}
		display_ways(i); // outputs the ways to climb the given amount of stairs
	}
	return 0;
}
