#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <vector>
#include <iostream>

class Errors 
{
private:
	struct Error
	{
		int line;
		int column;
		char bracket;
		
		Error()	{}
		Error(int l, int c, char b) : line(l), column(c), bracket(b) {}	
	};

	std::vector<Error> err;

public:
	void addError(int line, int column, char bracket) {
		err.push_back(Error(line, column, bracket));
	}

	void printErrors() {		
		for (std::vector<Error>::iterator it = err.begin(); it != err.end(); ++it) {
			std::cout << "Error on line #" << it->line << "; ";
			std::cout << "column #" << it->column << "; ";
			std::cout << "bracket: \'" << it->bracket << "\'.\n";
		}
	}
};

#endif