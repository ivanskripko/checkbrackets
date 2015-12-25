#include <iostream>
#include <stack>
#include <fstream>
#include "errors.h"

using namespace std;

bool isClosingBracket(char c);
bool isOpeningBracket(char c);
bool areBracketsEqual(char c1, char c2);

int main () 
{
	stack<char> st;
	Errors err; 	
	string buffer;

	string filename;
	cout << "Please input file name: "; 
	cin >> filename;
	fstream fileToCheck(filename.c_str(), ios::in);

	if(!fileToCheck.is_open()) {
		cerr << "Cannot open file: " << filename << endl;
		return -1;
	}

	int line = 0;
	
	while ( !fileToCheck.eof() ) {
		getline(fileToCheck, buffer);
		++line;

		char c = 0;
		for (int column = 0; buffer[column] != '\0'; ++column) {
			c = buffer[column];
			if (isOpeningBracket(c)) {
				st.push(c);
			} else if (isClosingBracket(c)) {
				bool isEmpty = st.empty();
				if ((!isEmpty) && areBracketsEqual(st.top(), c)) {
					st.pop();	
				} else {
					st.push(c); 
					err.addError(line, column + 1, c);					
				}
			}
		}			
	}

	if (st.empty()) {
		cout << "Brackets are OK!" << endl;
	} else {
		cout << "There are errors in the brackets expression!\n" << endl;
		err.printErrors();
	}

	fileToCheck.close();
	return 0;
}

bool isClosingBracket(char c) {
	return (c == ']' || c == ')' || c == '}');
}

bool isOpeningBracket(char c) {
	return (c == '[' || c == '(' || c == '{');
}

bool areBracketsEqual(char c1, char c2) {
	return ((c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}') || (c1 == '(' && c2 == ')'));
}