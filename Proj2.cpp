#include <iostream>
#include "User.h"
#include "Advisor.h"
#include "Student.h"

using namespace std;

int main()
{	
	auto displayTitle = [](User& user) {cout << user.printHeader();};
	int option, userEnterDouble = 0;
	bool TF = true, loginOrNot = false, invalid = false;
	User user;
	Student std_usr;
	Advisor adv_usr;
	string input, ID, PWD, user_ID,mainMenu = "\n********** Main Menu **********\n1. Advisor Menu\n2. Student Menu\n3. Exit the Application\n*******************************\n\n";
	
	//load all the files
	FileIO file1("Data_advisees.txt");
	file1.filesLoaded();
	FileIO file2("Data_advisingNotes.txt");
	file2.filesLoaded();
	FileIO file3("Data_advisors.txt");
	file3.filesLoaded();
	FileIO file4("Data_students.txt");
	file4.filesLoaded();

	while (TF) {
		cout << mainMenu << "Please enter your option by number: ";
		getline(cin, input);

		while (input == "") { getline(cin, input); }
		user.checkDigit(input, invalid, userEnterDouble);

		if (invalid) continue;
		else option = stoi(input);

		if (option < 1 || option>3) {
			cout << "Invalid! Option must be between 1 to 3.\n";
			continue;
		}

		switch (option) {
		case 1:
			user.login("Data_advisors.txt", loginOrNot);
			if (loginOrNot == false)continue;
			displayTitle(adv_usr);
			adv_usr.setID(user.getID());
			adv_usr.get_all_advisees();
			adv_usr.advisorJob();
			break;
		case 2:
			user.login("Data_students.txt", loginOrNot);
			if (loginOrNot == false)continue;
			displayTitle(std_usr);
			std_usr.setID(user.getID());
			std_usr.studentJob();
			break;
		case 3:
			cout << "\n...Application END...\n";
			TF = false;
			break;
		}
	}
	return 0;
}