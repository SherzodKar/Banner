#include "Advisor.h"

void Advisor::set_room(string room) { this->room = room; }
void Advisor::set_phone(string phone) { this->phone = phone; }
string Advisor::get_room() { return room; }
string Advisor::get_phone() { return phone; }
//Function Template
template<typename T>
void Advisor::display(T value)
{
	cout << value;
}
//Function for Polymorphism + overriding (override keyword in Advisor.h)
string Advisor::printHeader()
{
	string header = "\n------------------ WELCOME ADVISOR -------------------\n";
	return header;
}
//Perform all advisor jobs
void Advisor::advisorJob()
{
	string advisorMenu = "\n******************** Advisor Menu ********************\n"
		"1. Display All Advisees\n"
		"2. Search Advisees\n"
		"3. Advising Notes\n"
		"4. Add Advisee\n"
		"5. Delete Advisee\n"
		"6. Move a collection of advisees to another advisor\n"
		"7. Check a student's Advisor\n"
		"8. Display ALL advisors who exist in the app\n"
		"9. View the count and average GPA for a specific major\n"
		"10. Sign Out\n"
		"******************************************************\n\n";
	string input;
	int option, userEnterDouble = 0;
	bool TF = true, invalid = false;

	while (TF)
	{
		display(advisorMenu);
		display("Please enter your option: ");
		getline(cin, input);

		while (input == "") { getline(cin, input); }
		checkDigit(input, invalid, userEnterDouble);

		if (invalid) continue;
		else option = stoi(input);

		if (option < 1 || option>10) {
			cout << "Invalid! Option must be between 1 to 10.\n";
			continue;
		}
		switch (option) {
		case 1: sortAdviseeMenu(); break;
		case 2: searchAdviseeMenu(); break;
		case 3: AdvisingNotesMenu(); break;
		case 4: this->add_advisee(); break;
		case 5: this->delete_student();break;
		case 6: this->move_advisees();break;
		case 7: this->check_who_is_advisor(); break;
		case 8: this->display_all_advisors();break;
		case 9: this->view_count_and_GPA_of_major(); break;
		case 10: display("\n...You have successfully logged out...Back to Main Menu...\n\n"); break;
		}

		if (option == 10) { 
			for(Student* st: all_advisees)
			{
				delete st;
			}	
			all_advisees.clear(); 
			TF = false; 
		}
	}
}
//Print all student's infor by ID under a advisor
void Advisor::get_all_student_info_by_ID()
{
	sort(all_advisees.begin(), all_advisees.end(), [](Student* inst1, Student* inst2) {
		return (inst1->getID() < inst2->getID());
	});
	cout << "\n-------------------------------------------------------\n--------Here are all your advisees SORTED by ID--------\n-------------------------------------------------------\n";
	cout << "ID" << right << setw(12) << "MAJOR" << setw(15) << "GPA" << setw(26) << "TOTAL EARNED HOURS\n";
	for_each(all_advisees.begin(), all_advisees.end(), [](Student* inst) {
		string id_num = inst->getID();
		cout << left << setw(9) << id_num << setw(17) << inst->get_major() << setw(17) << inst->get_GPA() << setw(9) << inst->get_total_hours() << endl;
	});
	cout << "-------------------------------------------------------\n";
}
//Print all student's infor by MAJOR under a advisor
void Advisor::get_all_student_info_by_major()
{
	sort(all_advisees.begin(), all_advisees.end(), [](Student* inst1, Student* inst2) {
		return (inst1->get_major() < inst2->get_major());
	});
	cout << "\n-------------------------------------------------------\n------Here are all your advisees SORTED by MAJOR-------\n-------------------------------------------------------\n";
	cout << "ID" << right << setw(12) << "MAJOR" << setw(15) << "GPA" << setw(26) << "TOTAL EARNED HOURS\n";
	for_each(all_advisees.begin(), all_advisees.end(), [](Student* inst) {
		cout << left << setw(9) << inst->getID() << setw(17) << inst->get_major() << setw(17) << inst->get_GPA() << setw(9) << inst->get_total_hours() << endl;
	});
	cout << "-------------------------------------------------------\n";
}
//Print all student's infor by HOURS under a advisor
void Advisor::get_all_student_info_by_hours()
{
	sort(all_advisees.begin(), all_advisees.end(), [](Student* inst1, Student* inst2) {
		return (stoi(inst1->get_total_hours()) > stoi(inst2->get_total_hours()));
	});
	cout << "\n-------------------------------------------------------\n---Here are all your advisees SORTED by CREDIT HOURS---\n-------------------------------------------------------\n";
	cout << "ID" << right << setw(12) << "MAJOR" << setw(15) << "GPA" << setw(26) << "TOTAL EARNED HOURS\n";
	for_each(all_advisees.begin(), all_advisees.end(), [](Student* inst) {
		cout << left << setw(9) << inst->getID() << setw(17) << inst->get_major() << setw(17) << inst->get_GPA() << setw(9) << inst->get_total_hours() << endl;
	});
	cout << "-------------------------------------------------------\n";
}
//Sub menu for sort advisee
void Advisor::sortAdviseeMenu()
{
	int end = -1, option, userEnterDouble = 0;
	bool invalid = false;
	string input, sub1Menu = "\n******** Advisor Menu --> Display ALL advisees *******\n1. Sort Advisees by ID\n"
		"2. Sort Advisees by major\n3. Sort Advisees by Total Earned Hours\n4. Back to Previous (Advisor Menu) Menu\n******************************************************\n";

	while (true) {
		cout << endl;
		display(sub1Menu);
		cout << "\nPlease enter your option: ";
		getline(cin, input);

		while (input == "") { getline(cin, input); }
		checkDigit(input, invalid, userEnterDouble);

		if (invalid)continue;
		else option = stoi(input);

		if (option < 1 || option>4) {
			cout << "Invalid! Option must be between 1 to 4.\n";
			continue;
		}

		switch (option) {
		case 1:
			if (all_advisees.empty()) { cout << "The advisor does not have any advisees!" << endl; }
			else { this->get_all_student_info_by_ID(); }
			end = 99;break;
		case 2:
			if (all_advisees.empty()) { cout << "The advisor does not have any advisees!" << endl; }
			else { this->get_all_student_info_by_major(); }
			end = 99;break;
		case 3:
			if (all_advisees.empty()) { cout << "The advisor does not have any advisees!" << endl; }
			else { this->get_all_student_info_by_hours(); }
			end = 99;break;
		case 4:end = 0;break;
		}

		if (end == 99)continue;
		else if (end == 0)break;
	}
}
//Sub menu for search advisees
void Advisor::searchAdviseeMenu()
{
	bool invalid = false;
	int end = -1, option, userEnterDouble = 0;
	string input, sub2Menu = "\n********** Advisor Menu --> Search Advisees ***********\n1. Search Advisee by an ID\n2. Search Advisee(s) by major (Enter [UNDECIDED] for undecided major)\n3. Search Advisee(s) by a range of total earned hours\n"
		"4. Search by major AND a range to total earned hours (Enter [UNDECIDED] for undecided major)\n5. Back to Previous (Advisor Menu) Menu\n*******************************************************\n";

	while (true) {
		cout << endl;
		display(sub2Menu);
		cout << "\nPlease enter your option: ";
		getline(cin, input);

		while (input == "") { getline(cin, input); }
		checkDigit(input, invalid, userEnterDouble);

		if (invalid)continue;
		else option = stoi(input);

		if (option < 1 || option>5) {
			cout << "Invalid! Option must be between 1 to 5.\n";
			continue;
		}

		switch (option) {
		case 1:this->search_by_ID();end = 99;break;
		case 2:this->search_by_major();end = 99;break;
		case 3:this->search_by_range_total_hours();end = 99;break;
		case 4:this->search_by_major_range_total_hours();break;
		case 5:end = 0; break;
		}

		if (end == 99)continue;
		else if (end == 0)break;
	}
}
//Sub menu for advising notes
void Advisor::AdvisingNotesMenu()
{
	int end = -1, option, userEnterDouble = 0;
	bool invalid = false;
	string input, sub3Menu = "\n*********** Advisor Menu --> Advising Notes **********\n1. View Adivising Notes\n"
		"2. Add advising Notes\n3. Back to Previous (Advisor Menu) Menu\n******************************************************\n";
	
	while (true) {
		cout << endl << sub3Menu << "\nPlease enter your option: ";
		getline(cin, input);

		while (input == "") { getline(cin, input); }
		checkDigit(input, invalid, userEnterDouble);

		if (invalid)continue;
		else option = stoi(input);

		if (option < 1 || option>3) {
			cout << "Invalid! Option must be between 1 to 3.\n";
			continue;
		}

		switch (option) {
		case 1:this->view_notes();end = 99;break;
		case 2:this->add_notes();end = 99;break;
		case 3:end = 0;break;
		}

		if (end == 99)continue;
		else if (end == 0)break;
	}
}
//Get all advisees
//void Advisor::get_all_advisees()
bool Advisor::get_all_advisees()
{
	bool open = false;
	FileIO file("Data_advisees.txt");
	vector<string> std_IDS = file.get_student_vector(file.readFile(), getID(),open);
	if (open) {
		if (!(std_IDS.empty()))
		{
			for_each(std_IDS.begin(), std_IDS.end(), [&](string str) {
				Student* student_inst = new Student(str);
				FileIO file1("Data_students.txt");
				map<string, vector<string> >  all_stds = file1.get_all_student_map(file1.readFile());
				student_inst -> get_all_std_info(all_stds);
				all_advisees.push_back(student_inst);
			});
		}
	}
	return open;
}
//Search advisee by ID
void Advisor::search_by_ID()
{
	string input;
	cout << "Please, input the ID of the student: ";
	getline(cin, input);

	int count = 0;
	cout << "\n-------------------------------------------------------\n----------------Search students by ID------------------\n-----------------------------------------------------\n";
	cout << "ID" << right << setw(12) << "MAJOR" << setw(15) << "GPA" << setw(26) << "TOTAL EARNED HOURS\n";
	for (Student* j : all_advisees)
	{
		if (input.compare(j->getID()) == 0)
		{
			cout << left << setw(9) << j->getID() << setw(17) << j->get_major() << setw(17) << j->get_GPA() << setw(9) << j->get_total_hours() << endl;
			count++;
		}
	}
	if (count == 0) { cout << "<ERROR> The student was not found!" << endl; }
	cout << "---------------------------------------------------------\n";
}
//Search advisee by major
void Advisor::search_by_major()
{
	string input;
	cout << "Please, input the major of the student: ";
	getline(cin, input);

	int count = 0;
	cout << "\n-------------------------------------------------------\n-------------Search students by Major------------------\n-------------------------------------------------------\n";
	cout << "ID" << right << setw(12) << "MAJOR" << setw(15) << "GPA" << setw(26) << "TOTAL EARNED HOURS\n";
	for (Student* j : all_advisees)
	{
		for (int i = 0; i < input.size(); i++) { 
			if (isalpha(input[i])) { 
				input.at(i) = toupper(input.at(i)); 
			} 
			else { input.at(i) = input.at(i); }
		}
		if (input.compare(j->get_major()) == 0)
		{
			cout << left << setw(9) << j->getID() << setw(17) << j->get_major() << setw(17) << j->get_GPA() << setw(9) << j->get_total_hours() << endl;
			count++;
		}
	}
	if (count == 0) { cout << "<ERROR> The student was not found!" << endl; }
	cout << "-------------------------------------------------------\n";
}
//Search advisee by total hours
void Advisor::search_by_range_total_hours()
{
	int input1,input2,ccount = 0,valid = 0;;
	string str_in1, str_in2;
	
	do
	{
		cout << "Please, input a valid MINIMUM range of hours (0-300) of the student: ";
		getline(cin, str_in1);
		while (str_in1 == "") { getline(cin, str_in1); }
		for (int h = 0; h < str_in1.length(); h++)
		{
			if (!isdigit(str_in1[h])){ccount++;}
		}
		if (ccount == 0)
		{
			input1 = stoi(str_in1);
			break;
		}
		ccount = 0;
	} while (true);

	ccount = 0;
	do
	{
		cout << "Please, input a valid MAXIMUM range of hours (0-300) of the student: ";
		getline(cin, str_in2);
		while (str_in2 == "") { getline(cin, str_in2); }
		for (int h = 0; h < str_in2.length(); h++)
		{
			if (!isdigit(str_in2[h])) { ccount++; }
		}
		if (ccount == 0)
		{
			input2 = stoi(str_in2);
			if (input2 >= input1)
				break;
		}
		ccount = 0;

	} while (true);

	int count = 0;
	cout << "\n-------------------------------------------------------\n----Search Students by a range of Total Earned Hours---\n-------------------------------------------------------\n";
	cout << "ID" << right << setw(12) << "MAJOR" << setw(15) << "GPA" << setw(26) << "TOTAL EARNED HOURS\n";
	for (Student* j : all_advisees)
	{
		if (input1 <= stoi(j->get_total_hours()) && input2 >= stoi(j->get_total_hours()))
		{
			cout << left << setw(9) << j->getID() << setw(17) << j->get_major() << setw(17) << j->get_GPA() << setw(9) << j->get_total_hours() << endl;
			count++;
		}
	}
	if (count == 0) { cout << "<ERROR> The student was not found!" << endl; }
	cout << "-------------------------------------------------------\n";
}
//Search advisee by major and total hours
void Advisor::search_by_major_range_total_hours()
{
	int input1,input2;
	string str_in1, str_in2,major_input;
	cout << "Please, input the major of the student: ";
	getline(cin, major_input);

	int ccount = 0;
	do
	{
		cout << "Please, input the MINIMUM range of hours (0-300) of the student: ";
		getline(cin, str_in1);
		while (str_in1 == "") { getline(cin, str_in1); }
		for (int h = 0; h < str_in1.length(); h++)
		{
			if (!isdigit(str_in1[h])) { ccount++; }
		}
		if (ccount == 0)
		{
			input1 = stoi(str_in1);
			break;
		}
		ccount = 0;

	} while (true);
	ccount = 0;

	do
	{
		cout << "Please, input the MAXIMUM range of hours (0-300) of the student: ";
		getline(cin, str_in2);
		while (str_in2 == "") { getline(cin, str_in2); }
		for (int h = 0; h < str_in2.length(); h++)
		{
			if (!isdigit(str_in2[h])) { ccount++; }
		}
		if (ccount == 0)
		{
			input2 = stoi(str_in2);
			if (input2 >= input1)
				break;
		}
		ccount = 0;

	} while (true);

	int count = 0;
	cout << "\n-------------------------------------------------------\n----Search students by major and total earned hours----\n-------------------------------------------------------\n";
	cout << "ID" << right << setw(12) << "MAJOR" << setw(15) << "GPA" << setw(26) << "TOTAL EARNED HOURS\n";
	for (Student* j : all_advisees)
	{
		for (int i = 0;i < major_input.size();i++) { major_input.at(i) = toupper(major_input.at(i)); }
		if (input1 <= stoi(j->get_total_hours()) && input2 >= stoi(j->get_total_hours()) && major_input.compare(j->get_major()) == 0)
		{
			cout << left << setw(9) << j->getID() << setw(17) << j->get_major() << setw(17) << j->get_GPA() << setw(9) << j->get_total_hours() << endl;
			count++;
		}
	}
	if (count == 0) { cout << "<ERROR> The student was not found!" << endl; }
	cout << "-------------------------------------------------------\n";
}
//Get current date for advising notes
string Advisor::get_current_date()
{
	time_t t = time(0);
	tm* now = localtime(&t);
	ostringstream oSS;
	string current_day;
	oSS << (now->tm_mon + 1) << '/' << (now->tm_mday) << '/' << (now->tm_year + 1900);
	current_day = oSS.str();
	return current_day;
}
//Add notes to a student
void Advisor::add_notes()
{
	string input;
	cout << "Please, enter the ID of the student to add notes to: ";
	getline(cin, input);

	int count = 0;
	for (Student* i : all_advisees)
	{
		if (input.compare(i->getID()) == 0)
		{
			count++;
			string date = this->get_current_date();
			i->add_advising_notes(getID(), date);
		}
	}
	if (count == 0) { cout << "<ERROR> Student was not found!" << endl; }
}
//View a student's advising notes
void Advisor::view_notes()
{
	string input;
	cout << "Please, enter the ID of the student to view notes: ";
	getline(cin, input);

	int count = 0;
	for (Student* i : all_advisees)
	{
		if (input.compare(i->getID()) == 0)
		{
			count++;
			i->view_advising_notes();
		}
	}
	if (count == 0) { cout << "<ERROR> Student was not found!" << endl; }
}
//Add a advisee to a advisor
void Advisor::add_advisee()
{
	string std_ID, answer;
	bool done = false;
	cout << "\n[Add advisee] Please, enter a student's ID: ";
	getline(cin, std_ID);

	FileIO file("Data_students.txt");
	string result = file.check_students(std_ID);

	if (true) {
		char sf[99];
		if ((int)std_ID[std_ID.length() - 1] == 13)
		{
			int yr;
			for (yr = 0; yr < std_ID.length() - 1; yr++)
			{
				sf[yr] = std_ID[yr];
			}
			sf[yr] = '\0';
			std_ID = sf;
		}
		Student* tmp = new Student(std_ID);
		FileIO file1("Data_students.txt");
		map<string, vector<string> >  all_stds = file1.get_all_student_map(file1.readFile());
		tmp->get_all_std_info(all_stds);
		FileIO file2("Data_advisees.txt");
		int res = file2.check_if_has_advisor(std_ID, getID());
		if (res == 2) { cout << "The student already has an advisor!" << endl; done = true; }
	}
	if (result.compare("<ERROR> NO such student!") == 0) { cout << result << endl; }
	else if (done == false) {
		cout << "\n--------------------------------------------\nID,PWD,MAJOR,EARNED HOURS,GPA";
		cout << endl << result << "\n--------------------------------------------\n\nDid you mean to add the above student? (y/n): ";
		getline(cin, answer);
		while (true)
		{
			if (answer.compare("y") == 0 || answer.compare("n") == 0 || answer.compare("Y") == 0 || answer.compare("N") == 0) { break; }
			cout << "Please, enter either y or n: ";
			getline(cin, answer);
		}
		if (answer.compare("y") == 0 || answer.compare("Y") == 0)
		{
			char sf[99];
			if ((int)std_ID[std_ID.length() - 1] == 13)
			{
				int yr;
				for (yr = 0; yr < std_ID.length() - 1; yr++)
				{
					sf[yr] = std_ID[yr];
				}
				sf[yr] = '\0';
				std_ID = sf;
			}

			Student* tmp = new Student(std_ID);
			FileIO file1("Data_students.txt");
			map<string, vector<string> >  all_stds = file1.get_all_student_map(file1.readFile());
			tmp->get_all_std_info(all_stds);
			FileIO file("Data_advisees.txt");
			int res = file.check_if_has_advisor(std_ID, getID());
			if (res == 0)
			{
				all_advisees.push_back(tmp);
				file.write_advisee(getID(), std_ID);
			}
			else if (res == 1)
			{
				string note = "***DOUBLE ADVISING REJECTED";
				cout << note << endl;
				string date = this->get_current_date();
				FileIO file("Data_advisingNotes.txt");
				file.save_note("\n(" + getID() + " " + date + ")" + " " + std_ID + " " + note);
			}
		}
		else { cout << "Sorry, try again later!" << endl; }
	}
}

//Delete a student from a advisor
void Advisor::delete_student()
{
	string std_ID,answer;
	bool done=false;
	cout << "\n[Delete Advisee] Please, enter student's ID: ";
	getline(cin, std_ID);

	FileIO file("Data_students.txt");
	string result = file.check_students(std_ID);
	
	FileIO file2("Data_advisees.txt");
	int res1 ;

	if (result.compare("<ERROR> NO such student!") == 0) { cout << result << endl; done = true; }
	else
	{
		res1 = file2.remove_if_my_advisee(getID(), std_ID,false);
	}
	if (res1!=0&&done==false){
		cout << "\n--------------------------------------------\nID,PWD,MAJOR,EARNED HOURS,GPA";
		cout << endl<<result<<"\n--------------------------------------------\n\nDid you mean to delete the above student? (y/n): ";
		getline(cin, answer);
		while (true)
		{
			if (answer.compare("y") == 0 || answer.compare("n") == 0|| answer.compare("Y") == 0|| answer.compare("N") == 0)
			{
				break;
			}
			cout << "Please, enter either y or n: ";
			getline(cin, answer);
		}
		if (answer.compare("y") == 0|| answer.compare("Y") == 0)
		{
			int res = file2.remove_if_my_advisee(getID(), std_ID, true);
			if (res != 0) {
				int c_num = 0;
				for (Student* i : all_advisees)
				{
					if (std_ID.compare(i->getID()) == 0) { break; }
					c_num++;
				}
				all_advisees.erase(all_advisees.begin() + c_num);
			}
		}
		else { cout << "Sorry, try again later!" << endl; }
	}
}
//Check a student's advisor
void Advisor::check_who_is_advisor()
{
	string std_ID;
	cout << "\n[Check Advisor] Please, enter the student ID: ";
	getline(cin, std_ID, '\n');

	FileIO file("Data_students.txt");
	string result = file.check_students(std_ID);
	if (result.compare("<ERROR> NO such student!") != 0)
	{
		FileIO ifile("Data_advisees.txt");
		string advisor_name = ifile.check_std_advisor(std_ID);
		if (advisor_name.length() != 0)
			cout << "The student's advisor is " << advisor_name << endl;
		else
			cout << "Student does not have an advisor! " << endl;

		if (getID().compare(advisor_name) == 0)
			cout << "Apparently, you are student's advisor!" << endl;
	}
	else
		cout <<result << endl;
}
//Display all advisors on the application
void Advisor::display_all_advisors()
{
	map<string, vector<string> > all_advisors;
	FileIO file("Data_advisors.txt");
	all_advisors = file.get_all_advisors();
	vector<Advisor> all_objects;

	for (auto adv = all_advisors.begin(); adv != all_advisors.end(); adv++)
	{
		Advisor obj;
		obj.setID(adv->first);
		vector<string> temp = adv->second;
		for (int w = 0; w < temp.size(); w++) {
			switch (w) {
			case 0:obj.setPWD(temp[w]); break;
			case 1:obj.set_room(temp[w]);break;
			case 2:obj.set_phone(temp[w]);break;
			}
		}
		all_objects.push_back(obj);
	}
	cout << "\n------------------------------------------------------\n"
		    "-----------------   ALL ADVISORS   -------------------";
	cout << setw(20)<<"\nADVISOR ID"<<setw(15)<<"ROOM"<<setw(15)<<"PHONE\n";
	for (Advisor i : all_objects)
	{
		cout <<setw(5)<<i.getID() << setw(22) << i.get_room() << setw(15) << i.get_phone() << endl;
	}
	cout << "------------------------------------------------------\n";

}
//View the count of a major and display average GPA of these advisees
void Advisor::view_count_and_GPA_of_major()
{
	string input;
	cout << "\nPlease, input the major of the student: ";
	getline(cin, input);
	for (int i = 0;i < input.size();i++) { input.at(i) = toupper(input.at(i)); }

	int count = 0;
	double total_GPA = 0.0, average_GPA = 0,gpa;

	for (Student* j : all_advisees)
	{
		if (input.compare(j->get_major()) == 0)
		{
			stringstream ss(j->get_GPA());
			ss >> gpa;
			total_GPA += gpa;
			count++;
		}
	}
	if (count == 0) { cout << "<ERROR> You don't have any advisee(s) major in "<<input << endl; }
	else
	{
		average_GPA = total_GPA / count;
		cout << "\n------   Count and Average GPA for major: " << input<<"   ------\n";
		cout << "-------------------------------------------------------\n";
		cout << "--> The total number of advisees with major " << input << " is " << count << endl;
		cout << "--> Average GPA of advisees with major " << input << " is " << average_GPA << endl;
		cout << "-------------------------------------------------------\n";
	}
}
//Move a collection of advisee to another advisor
void Advisor::move_advisees()
{
	string input, code, moving_adv, std_ID;
	cout << "Please, input the major of the student: ";
	getline(cin, input);
	for (int i = 0;i < input.size();i++) { input.at(i) = toupper(input.at(i)); }
	int count = 0;
	for (Student* i : all_advisees)
	{
		if (input.compare(i->get_major()) == 0){count++;}
	}
	if (count == 0)
	{
		cout << "<WARNING> The major entered is invalid or you do not have an advisee with this major!" << endl;
	}
	else
	{
		cout << "Enter special authorization code: ";
		getline(cin, code);
		if (code.compare("ENB#342") == 0)
		{
			map<string, vector<string> > all_advisors;
			FileIO ifile("Data_advisors.txt");
			all_advisors = ifile.get_all_advisors();
			int checking = 0;
			do {
				cout << "Please, enter the advisor ID to move the student(s) to: ";
				getline(cin, moving_adv);

				for (auto adv = all_advisors.begin(); adv != all_advisors.end(); adv++)
				{
					string current_adv = adv->first;
					if (current_adv.compare(moving_adv) == 0){checking++;}
				}
				if (checking == 0)
					cout << "<ERROR> The advisor was not found!" << endl;

			} while (checking == 0);

			sort(all_advisees.begin(), all_advisees.end(), [](Student* inst1, Student* inst2) {
				return (inst1->get_major() < inst2->get_major());
			});

			int count = 0;
			FileIO file("Data_advisees.txt");
			for (auto i = all_advisees.begin(); i != all_advisees.end(); i++)
			{
				if (input.compare((*i)->get_major()) == 0)
				{
					std_ID = (*i)->getID();
					file.remove_if_my_advisee(getID(), std_ID,true);
					file.write_advisee(moving_adv, std_ID);
					count++;
					FileIO ifl("Data_advisingNotes.txt");
					ifl.move_advising_notes(getID(), moving_adv, std_ID);
					string note = "***ADVISOR CHANGED FROM " + getID() + " TO " + moving_adv;
					string date = this->get_current_date();
					ifl.save_note("(" + moving_adv + " " + date + ") " + std_ID + " " + note);
				}
			}

			for (int nm = 0; nm < count; nm++)
			{
				for (auto i = all_advisees.begin(); i != all_advisees.end(); i++)
				{
					if (input.compare((*i)->get_major()) == 0)
					{
						all_advisees.erase(i);
						break;
					}
				}
			}
		}
		else{cout << "<ERROR> The entered authorization code is invalid!" << endl;}
	}
}