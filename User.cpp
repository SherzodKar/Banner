#include "User.h"

User::User(string ID, string PWD)
{
	this->ID = ID;
	this->PWD = PWD;
}
void User::setID(string userID) { ID = userID; };
string User::getID() { return this->ID; };
void User::setPWD(string userPWD) { PWD = userPWD; };
string User::getPWD() { return this->PWD; };

//Its a virtual function for polymorphism
string User::printHeader()
{
	string header = "\n-------- WELCOME TO APPLICATION -----------\n";
	return header;
}
//Ask user to login
void User::login(string fileName, bool &login)
{
	cout << "\nEnter your ID: ";
	getline(cin, ID);
	this->ID = ID;
	cout << "Enter your Password: ";
	getline(cin, PWD);
	this->PWD = PWD;
	FileIO file(fileName);
	this->ID = file.checkPWD(file.readFile(), ID, PWD, login);
}
//A custom exception for valid number type
struct User::InvalidNumberTypeException { string message; };

//Check to see if UserEnter is a digit/(it can check both double and int depends on third arugument 1=check double 0=check int)
void User::checkDigit(string input, bool &invalid, int &wantDouble) {
	try {
		int dot = 0, doubleOrNot = 0;
		invalid = false;
		InvalidNumberTypeException myex;
		for (int i = 0;i < (int)input.length();i++) {
			if (i == 0 && input[i] == '-') {
				invalid = false;
				continue;
			}
			if (wantDouble) {
				if (input[i] == '.')dot++;
				if (dot >= 2 || !(isdigit(input[i]) || input[i] == '.')) {
					invalid = true;
					myex.message = "EXCEPTION ERROR: ONLY accept Double and Integer value here, NOT accept String.\n";
					throw myex;
				}
			}
			else {
				if (!(isdigit(input[i]))) {
					doubleOrNot = 99;		//99=user enter double, 0=not double
					invalid = true;
					myex.message = "EXCEPTION ERROR: ONLY accept Integer value here, NOT accept Double and String.\n";
					throw myex;
				}
			}
		}
		wantDouble = doubleOrNot;
	}
	catch (InvalidNumberTypeException excep) { cout << excep.message; }
}