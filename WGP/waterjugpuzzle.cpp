/**
**Authors: Chris Landolfi and Jordan Handwerger
**Pledge: I pledge my honor that I have abided by the Stevens Honor System
**/
#include <iomanip>
#include <iostream>
#include <String>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

//Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	vector<string> directions;
	State(int _a, int _b, int _c) :
			a(_a), b(_b), c(_c) {
	}

	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

vector<State> possible_moves(State parent, vector<int> &input, bool **matrix) {
	vector<State> poss; //holds all possible moves from parent
	ostringstream oss1, oss2, oss3, oss4, oss5, oss6; //used to add moves to directions vector
	if (parent.a < input[0] && parent.c != 0) { //Checks move 1, pour C to A
		if (parent.c > (input[0] - parent.a)) { //Checks if the move will max out the jug
			if (matrix[input[0]][parent.b] == false) {//if this move hasn't been done before
				State move1(input[0], parent.b,
						parent.c - (input[0] - parent.a));
				if ((input[0] - parent.a) == 1) {//checks gallon vs gallons
					oss1 << "Pour 1 gallon from C to A. " << move1.to_string()
							<< endl;
				} else {
					oss1 << "Pour " << (input[0] - parent.a)
							<< " gallons from C to A. " << move1.to_string()
							<< endl;
				}

				move1.directions = parent.directions; //gets the path
				move1.directions.push_back(oss1.str());
				poss.push_back(move1);
				oss1.clear();
				matrix[input[0]][parent.b] = true;
			}
		} else { //Move will empty the jug
			if (matrix[parent.a + parent.c][parent.b] == false) {
				State move12(parent.a + parent.c, parent.b, 0);
				if (parent.c == 1) {
					oss1 << "Pour 1 gallon from C to A. " << move12.to_string()
							<< endl;
				} else {
					oss1 << "Pour " << parent.c << " gallons from C to A. "
							<< move12.to_string() << endl;
				}
				move12.directions = parent.directions;
				move12.directions.push_back(oss1.str());
				poss.push_back(move12);
				oss1.clear();
				matrix[parent.a + parent.c][parent.b] = true;
			}
		}
	}
	if (parent.a < input[0] && parent.b != 0) { //Checks move 2, pour B to A
		if (parent.b > (input[0] - parent.a)) { //Checks if the move will max out the jug
			if (matrix[input[0]][parent.b - (input[0] - parent.a)] == false) {
				State move2(input[0], parent.b - (input[0] - parent.a),
						parent.c);
				if ((input[0] - parent.a) == 1) {
					oss2 << "Pour 1 gallon from B to A. " << move2.to_string()
							<< endl;
				} else {
					oss2 << "Pour " << (input[0] - parent.a)
							<< " gallons from B to A. " << move2.to_string()
							<< endl;
				}
				move2.directions = parent.directions;
				move2.directions.push_back(oss2.str());
				poss.push_back(move2);
				oss2.clear();
				matrix[input[0]][parent.b - (input[0] - parent.a)] = true;
			}
		} else { //Move will empty the jug
			if (matrix[parent.a + parent.b][0] == false) {
				State move22(parent.a + parent.b, 0, parent.c);
				if (parent.b == 1) {
					oss2 << "Pour 1 gallon from B to A. " << move22.to_string()
							<< endl;
				} else {
					oss2 << "Pour " << parent.b << " gallons from B to A. "
							<< move22.to_string() << endl;
				}
				move22.directions = parent.directions;
				move22.directions.push_back(oss2.str());
				poss.push_back(move22);
				oss2.clear();
				matrix[parent.a + parent.b][0] = true;
			}
		}
	}
	if (parent.b < input[1] && parent.c != 0) { //Checks move 3, pour C to B
		if (parent.c > (input[1] - parent.b)) { //Checks if the move will max out the jug
			if (matrix[parent.a][input[1]] == false) {
				State move3(parent.a, input[1],
						parent.c - (input[1] - parent.b));
				if ((input[1] - parent.b) == 1) {
					oss3 << "Pour 1 gallon from C to B. " << move3.to_string()
							<< endl;
				} else {
					oss3 << "Pour " << (input[1] - parent.b)
							<< " gallons from C to B. " << move3.to_string()
							<< endl;
				}
				move3.directions = parent.directions;
				move3.directions.push_back(oss3.str());
				poss.push_back(move3);
				oss3.clear();
				matrix[parent.a][input[1]] = true;
			}
		} else { //Move will empty the jug
			if (matrix[parent.a][parent.b + parent.c] == false) {
				State move32(parent.a, parent.b + parent.c, 0);
				if (parent.c == 1) {
					oss3 << "Pour 1 gallon from C to B. " << move32.to_string()
							<< endl;
				} else {
					oss3 << "Pour " << parent.c << " gallons from C to B. "
							<< move32.to_string() << endl;
				}
				move32.directions = parent.directions;
				move32.directions.push_back(oss3.str());
				poss.push_back(move32);
				oss3.clear();
				matrix[parent.a][parent.b + parent.c] = true;
			}
		}
	}
	if (parent.b < input[1] && parent.a != 0) { //Checks move 4, pour A to B
		if (parent.a > (input[1] - parent.b)) { //Checks if the move will max out the jug
			if (matrix[parent.a - (input[1] - parent.b)][input[1]] == false) {
				State move4(parent.a - (input[1] - parent.b), input[1],
						parent.c);
				if ((input[1] - parent.b) == 1) {
					oss4 << "Pour 1 gallon from A to B. " << move4.to_string()
							<< endl;
				} else {
					oss4 << "Pour " << (input[1] - parent.b)
							<< " gallons from A to B. " << move4.to_string()
							<< endl;
				}

				move4.directions = parent.directions;
				move4.directions.push_back(oss4.str());
				poss.push_back(move4);
				oss4.clear();
				matrix[parent.a - (input[1] - parent.b)][input[1]] = true;
			}
		} else { //Move will empty the jug
			if (matrix[0][parent.b + parent.a] == false) {
				State move42(0, parent.b + parent.a, parent.c);
				if (parent.a == 1) {
					oss4 << "Pour 1 gallon from A to B. " << move42.to_string()
							<< endl;
				} else {
					oss4 << "Pour " << parent.a << " gallons from A to B. "
							<< move42.to_string() << endl;
				}
				move42.directions = parent.directions;
				move42.directions.push_back(oss4.str());
				poss.push_back(move42);
				oss4.clear();
				matrix[0][parent.b + parent.a] = true;
			}
		}
	}
	if (parent.c < input[2] && parent.b != 0) { //Checks move 5, pour B to C
		if (parent.b > (input[2] - parent.c)) { //Checks if the move will max out the jug
			if (matrix[parent.a][parent.b - (input[2] - parent.c)] == false) {
				State move5(parent.a, parent.b - (input[2] - parent.c),
						input[2]);
				if ((input[2] - parent.c) == 1) {
					oss5 << "Pour 1 gallon from B to C. " << move5.to_string()
							<< endl;
				} else {
					oss5 << "Pour " << (input[2] - parent.c)
							<< " gallons from B to C. " << move5.to_string()
							<< endl;
				}
				move5.directions = parent.directions;
				move5.directions.push_back(oss5.str());
				poss.push_back(move5);
				oss5.clear();
				matrix[parent.a][parent.b - (input[2] - parent.c)] = true;
			}
		} else { //Move will empty the jug
			if (matrix[parent.a][0] == false) {
				State move52(parent.a, 0, parent.c + parent.b);
				if (parent.b == 1) {
					oss5 << "Pour 1 gallon from B to C. " << move52.to_string()
							<< endl;
				} else {
					oss5 << "Pour " << parent.b << " gallons from B to C. "
							<< move52.to_string() << endl;
				}
				move52.directions = parent.directions;
				move52.directions.push_back(oss5.str());
				poss.push_back(move52);
				oss5.clear();
				matrix[parent.a][0] = true;
			}
		}
	}
	if (parent.c < input[2] && parent.a != 0) { //Checks move 6, pour A to C
		if (parent.a > (input[2] - parent.c)) { //Checks if the move will max out the jug
			if (matrix[parent.a - (input[2] - parent.c)][parent.b] == false) {
				State move6(parent.a - (input[2] - parent.c), parent.b,
						input[2]);
				if ((input[2] - parent.c) == 1) {
					oss6 << "Pour 1 gallon from A to C. " << move6.to_string()
							<< endl;
				} else {
					oss6 << "Pour " << (input[2] - parent.c)
							<< " gallons from A to C. " << move6.to_string()
							<< endl;
				}
				move6.directions = parent.directions;
				move6.directions.push_back(oss6.str());
				poss.push_back(move6);
				oss6.clear();
				matrix[parent.a - (input[2] - parent.c)][parent.b] = true;
			}
		} else { //Move will empty the jug
			if (matrix[0][parent.b] == false) {
				State move62(0, parent.b, parent.c + parent.a);
				if (parent.a == 1) {
					oss6 << "Pour 1 gallon from A to C. " << move62.to_string()
							<< endl;
				} else {
					oss6 << "Pour " << parent.a << " gallons from A to C. "
							<< move62.to_string() << endl;
				}
				move62.directions = parent.directions;
				move62.directions.push_back(oss6.str());
				poss.push_back(move62);
				oss6.clear();
				matrix[0][parent.b] = true;
			}
		}
	}
	return poss;
}

vector<State> BFS(State current, bool **matrix, State goal, vector<State> path,
		vector<int> &input) {
	if (current.to_string() == goal.to_string()) {//checks if the initial state is the goal
		return path;
	}
	queue<State> bfsQ;
	bfsQ.push(current);
	while (bfsQ.size() > 0) { //queue of a bfs
		State current = bfsQ.front(); //get the front of the queue
		if (current.to_string() == goal.to_string()) {//returns if the goal is found
			return path;
		}
		vector<State> possible = possible_moves(current, input, matrix); //vector of possible moves
		for (vector<State>::iterator it = possible.begin();
				it != possible.end(); ++it) {
			bfsQ.push(*it); //pushes into the queue
			path.push_back(*it);//pushes into the vector of states
			if (it->to_string() == goal.to_string()) {
				return path;
			}
		}
		bfsQ.pop(); //pop off the front of the queue, to find all moves
	}
	vector<State> empty;
	return empty;
}

bool valid_inputs(char * const array[], vector<int> &input) {
	int checkInt;
	istringstream iss;
	for (int i = 1; i < 7; i++) {
		iss.str(array[i]);
		if (iss >> checkInt && checkInt >= 0) {
			input.push_back(checkInt);
		} else {
			if (i < 4) {
				cout << "Error: Invalid capacity '" << array[i] << "' for jug ";
				if (i == 1) {
					cout << "A." << endl;
				} else if (i == 2) {
					cout << "B." << endl;
				} else {
					cout << "C." << endl;
				}
				return false;
			} else {
				cout << "Error: Invalid goal '" << array[i] << "' for jug ";
				if (i == 4) {
					cout << "A." << endl;
				} else if (i == 5) {
					cout << "B." << endl;
				} else {
					cout << "C." << endl;
				}
				return false;
			}
		}
		iss.clear();
	}
	for (int i = 0; i < 3; i++) {
		if (input[i] == 0) {
			cout << "Error: Invalid capacity '" << input[i] << "' for jug ";
			if (i == 0) {
				cout << "A." << endl;
			} else if (i == 1) {
				cout << "B." << endl;
			} else {
				cout << "C." << endl;
			}
			return false;
		}
	}
	for (int i = 3; i < 6; i++) {
		if (input[i] > input[i - 3]) {
			cout << "Error: Goal cannot exceed capacity of jug ";
			if (i == 3) {
				cout << "A." << endl;
			} else if (i == 4) {
				cout << "B." << endl;
			} else {
				cout << "C." << endl;
			}
			return false;
		}
	}
	if ((input[3] + input[4] + input[5]) != input[2]) {
		cout
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C."
				<< endl;
		return false;
	}
	return true;
}

int main(int argc, char * const argv[]) {
	vector<int> input;
	if (argc != 7) {//wrong number of inputs
		cout
				<< "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
				<< endl;
		return 1;
	} else if (valid_inputs(argv, input) == false) {//checks for valid input
		return 1;
	} else {//finds the path if possible
		// Declare a 2-dimensional array with 'some_size' rows.
		bool **array = new bool*[input[0] + 1];
		// For each row, make an array of 'some_other_size' booleans.
		for (int i = 0; i <= input[0]; ++i) {
			array[i] = new bool[input[1]];
			// Fill the array with zeros.
			fill(array[i], array[i] + input[1] + 1, false);
		}
		State initial(0, 0, input[2]); //start state
		State goal(input[3], input[4], input[5]); //goal state
		vector<State> path; //path to goal
		path.push_back(initial);
		array[0][0] = true;
		vector<State> answer = BFS(initial, array, goal, path, input);//gets answers
		if (answer.empty()) {
			cout << "No solution." << endl;
		} else if (answer.size() == 1) {
			cout << "Initial state. " << answer[0].to_string();
			return 0;
		} else {
			cout << "Initial state. " << initial.to_string() << endl;
			for (vector<string>::iterator it =
					answer[answer.size() - 1].directions.begin();
					it != answer[answer.size() - 1].directions.end(); ++it) {
				cout << *it;
			}
		}
		// Delete each array, that is, all the columns, first.
		for (int i = 0; i <= input[0]; ++i) {
			delete[] array[i];
		}
		// Delete the array itself.
		delete[] array;
		return 0;
	}
}
