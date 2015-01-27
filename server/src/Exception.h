/*
 * DAO.h
 *
 *  Created on: Apr 8, 2013
 *      Author: nhsan
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <iostream>
using namespace std;

class Exception: public exception {
public:
	Exception(int type) {
		this->type = type;
		line = -1;
		file = "";
	}

	Exception(int type, int line, string file) {
		this->type = type;
		this->line = line;
		this->file = file;

		// FIXME
		cerr << "line = " << line << endl;
		cerr << "file = " << file << endl;
	}

	virtual ~Exception() throw () {

	}

	int get_type() {
		return type;
	}

	int get_line() {
		return line;
	}

	string get_file() {
		return file;
	}

protected:
	int type;
	int line;
	string file;
};

#define EXCEPTION(type) Exception(type, __LINE__, __FILE__)

#endif /* EXCEPTIONS_H_ */
