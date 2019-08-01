#pragma once
#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include <vector>
#include "FileIO.h"
#include <algorithm>

using namespace std;

class User {
private:
	string ID;
	string PWD;
public:
	User(string ID = "", string PWD = "");
	void setID(string userID);
	string getID();
	string getPWD();
	void setPWD(string userPWD);
	void login(string fileName, bool &login);
	virtual string printHeader();
	void checkDigit(string input, bool &invalid, int &wantDouble);
	struct InvalidNumberTypeException;
};


#endif
