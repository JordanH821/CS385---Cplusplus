/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Jordan Handwerger
 * Date        : February 6, 2017
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

	//Constructor with initializer list, sets all indexes in the boolean array to true
    PrimesSieve(int limit) : is_prime_(new bool[limit + 1]), limit_(limit) {
    	for(int i = 0; i <= limit + 1; ++i){
    	        	is_prime_[i] = true;
    	}
        sieve();
    }

    //destructor
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    //getter for num_primes_
    inline int num_primes() const {
        return num_primes_;
    }

    //displays all the primes up to the given limit, and formats the output to 80 characters per line
    void display_primes() const {
    	const int max_prime_width = num_digits(max_prime_),
    	primes_per_row = 80 / (max_prime_width + 1);
    	if(num_primes_ <= primes_per_row){//if only one row of primes, then only one space in between
    		cout << 2;//2 is prime and will always be output first without a preceding space
    		for(int i = 3; i <= limit_; i++){//prints all primes greater than 2 and less than limit_
    			if(is_prime_[i] == true){
    				cout << " " << i;
    			}
    		}
    	} else{//more than one row of output
    		int current_line = 0; //number of prints on the current output line
    		for(int i = 2; i <= limit_; ++i){//loops through boolean array and prints out primes
    			if(is_prime_[i] == true){
    				if(current_line >= primes_per_row){//current line is full move to next
    					cout << endl << setw(max_prime_width) << i;
    					current_line = 1;
    				} else {//print on current line
    					if(i == 2){//outputs 2 without a preceding space
    						cout << setw(max_prime_width) << i;
    						++current_line;
    					} else{//outputs a space and then next number
    						cout << " " << setw(max_prime_width) << i;
    						++current_line;
    					}
    				}
    			}
    		}
    	}
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    //counts and returns number of primes found
    int count_num_primes() const {
    	int num_primes = 0;
    	for(int i = 2; i < limit_; ++i){
    		if(is_prime_[i] == true){//increments the counter for every prime
    			num_primes += 1;
    		}
    	}
    	return num_primes;
    }

    //returns the number of digits in an integer
    int num_digits(int num) const {
    	int num_digits = 1;
    	while(num / 10 != 0){
    		num = num / 10;
    		num_digits += 1;
    	}
    	return num_digits;
    }

    //loops though a boolean array and marks every none prime value to false, leaving all primes marked true
    void sieve() {
    	//class attributes that need to be set
    	int num_primes = 0;
    	int max_prime = 0;

    	for(int i=2; i <= sqrt(limit_); i++){//marks all multiples of primes as false, leaving all primes as true
    		if(is_prime_[i] == true){
    			for(int j = i * i; j <= limit_ ; j += i){
    				is_prime_[j] = false;
    			}
    		}
    	}
    	for(int i=2; i <= limit_; i++){//counts the number of primes and finds the highest prime. Cannot be combined above because that loop only goes to sqrt(limit)
    		if(is_prime_[i] == true){
    			num_primes++;
    			max_prime = i;
    		}
    	}
    	//sets class attributes
    	num_primes_ = num_primes;
    	max_prime_ = max_prime;
    }
};

int main(void) {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    //initializes a need PrimesSieve object and calls the function which displays primes
    PrimesSieve prime(limit);
    cout << endl << "Number of primes found: " << prime.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    prime.display_primes();
    return 0;
}
