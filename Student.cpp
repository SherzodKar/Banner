#include "Student.h"
Student::Student(string ID){ setID(ID); }
string Student::get_major() { return major; }
string Student::get_GPA() { return GPA; }
string Student::get_total_hours() { return total_hours; }
void Student::setGPA(string userGPA) { GPA = userGPA; };
void Student::setMajor(string userMajor) { major = userMajor; };
void Student::setTotalHours(string userHours) { total_hours = userHours; };
//Its a function for polymorphism +overiding (override keyword in student.h)+ overloading
string Student::printHeader()
{
	string header = "\n-------------------- WELCOME STUDENT ------------------\n";
	return header;
}
//A function for overloading
string Student::printHeader(string ID)
{
	string header = "\t\t    WELCOME < " + ID + " >\n";
	return header;
}
//Perform all student jobs
void Student::studentJob() {

	map < string, vector<string>> stdsInfo;
	FileIO file("Data_students.txt");
	stdsInfo = file.get_all_student_map(file.readFile());
	get_all_std_info(stdsInfo);

	int option, userEnterDouble = 0;

	bool TF = true, invalid = false;
	string input, studentMenu = "\n******************** Student Menu *********************\n"
		"1. View Advisor\n"
		"2. Update/View My Information\n"
		"3. Sign Out\n*******************************************************\n\n";
	cout << printHeader(getID());
	while (TF)
	{
		cout << studentMenu << "Please enter your option: ";
		getline(cin, input);

		while (input == "") { getline(cin, input); }
		checkDigit(input, invalid, userEnterDouble);

		if (invalid) continue;
		else option = stoi(input);

		if (option < 1 || option>3) { cout << "Invalid! Option must be between 1 to 3.\n";continue; }

		switch (option) {
		case 1:view_adv();break;
		case 2:StudentUPdatedInfoSubMeun();break;
		case 3: cout << "\n...You have successfully logged out...Back to Main Menu...\n\n"; break;
		}
		if (option == 3) { TF = false; }
	}
}

void Student::view_adv()
{
	FileIO file;
	file.showAdvisorInfo(getID());
}

void Student::get_all_std_info(map<string, vector<string> > all_stds)
{
	for (auto std = all_stds.begin(); std != all_stds.end(); std++) {
		if (getID().compare(std->first) == 0) {
			vector<string> temp = std->second;
			for (int w = 0; w < temp.size(); w++) {
				switch (w) {
				case 0:setPWD(temp[w]); break;
				case 1:this->major = temp[w];break;
				case 2:this->total_hours = temp[w];break;
				case 3:this->GPA = temp[w];break;
				}
			}
		}
	}
}
//Add advising notes
void Student::add_advising_notes(string adv_ID, string date)
{
	string note;
	cout << "Please, enter your note: ";
	getline(cin, note);
	string full_note = "(" + adv_ID + " " + date + ")" + " " + getID() + " " + note;
	advising_notes.push_back(full_note);
	FileIO file("Data_advisingNotes.txt");
	file.save_note("\n" + full_note);
	cout << "-----Note added to the Data_advisingNotes.txt\n";
}
//Print advising notes
void Student::view_advising_notes()
{
	cout << "\n------The advising note for " << getID() << endl;
	FileIO file("Data_advisingNotes.txt");
	file.view_notes(getID());
}
//Print Student Current Info
void Student::printStudentInfo()
{
	cout << "\n  --------------------------------------------------\n"
		"  |        <" << getID() << "> YOUR CURRENT INFORMATION        |\n"
		"  |------------------------------------------------|\n"
		"  | GPA: " << right << setw(30) << get_GPA() << setw(12) << " " << "|\n"
		"  | Major: " << right << setw(28) << get_major() << setw(12) << " " << "|\n"
		"  | Total Earned Hours: " << right << setw(15) << get_total_hours() << setw(12) << " " << "|\n"
		"  --------------------------------------------------\n";
}
//Student UPdate their GPA
void Student::UpdateGPA(bool &invalid, int &Updated)
{
	string input;
	double newGPA;
	int userEnterDouble = 1;
	FileIO file;

	if (true) {
		cout << "[Update GPA] Enter Your New GPA: ";
		getline(cin, input);
		int dot = 0;
		checkDigit(input, invalid, userEnterDouble);
	}
	if (invalid) { Updated = 99; }
	else {
		newGPA = round(stod(input) * 100) / 100;
		if (newGPA < 0.00 || newGPA>4.00) {
			cout << "Invalid! GPA must be between 0.00 to 4.00 (Two decimals ONLY).\n";
			Updated = 99;
		}
		else {
			while (true) {
				cout << "VERIFY: <" << getID() << "> Are you sure update your GPA from " << get_GPA() << " to " << setprecision(2) << fixed << newGPA << "? (n/y): ";
				getline(cin, input);

				if (input.length() == 1) {
					input = tolower(input[0]);
					if (input[0] == 'y') {
						string storeGPA = to_string(newGPA).substr(0, 4);
						setGPA(storeGPA);
						Updated = 2;
						break;
					}
					else if (input[0] == 'n') { Updated = 99; cout << "***NO information Updated***\n"; break; }
					else continue;
				}
				else continue;
			}
		}
	}
	if (Updated == 2)file.studentUpdatedInfoInFile(Updated, getID(), getPWD(), get_major(), get_total_hours(), get_GPA());
}
//Student update their major
void Student::UpdatedMajor(int &Updated)
{
	FileIO file;
	string newMajor, input;
	cout << "[Update Major] Enter Your New Major: ";
	getline(cin, newMajor);

	for (int i = 0;i < newMajor.length();i++) { 
		if (isalpha(newMajor[i])) {newMajor[i] = toupper(newMajor[i]);}
		else newMajor[i] = newMajor[i];
	}

	while (true) {
		cout << "VERIFY: <" << getID() << "> you sure updated your MAJOR from " << get_major() << " to " << newMajor << "? (n/y): ";
		getline(cin, input);

		if (input.length() == 1) {
			input = tolower(input[0]);
			if (input[0] == 'y') {
				setMajor(newMajor);
				Updated = 3;
				break;
			}
			else if (input[0] == 'n') { Updated = 99; cout << "***NO information Updated***\n"; break; }
			else continue;
		}
		else continue;
	}
	if (Updated == 3)file.studentUpdatedInfoInFile(Updated, getID(), getPWD(), get_major(), get_total_hours(), get_GPA());
}
//Student update their hours
void Student::UpdatedHour(bool &invalid, int &Updated)
{
	string input;
	int newHour, userEnterDouble = 0;
	bool cont = true;
	FileIO file;

	if (true) {
		cout << "[Update Earned Hours] Enter Your New Earned Hour:";
		getline(cin, input);
		checkDigit(input, invalid, userEnterDouble);
	}
	if (invalid) { Updated = 99; }
	else {
		newHour = stoi(input);
		if (newHour < 0 || newHour>300) {
			cout << "Invalid! Earned Hours must be between 0 to 300.\n";
			Updated = 99;
		}
		else {
			while (true) {
				cout << "VERIFY: <" << getID() << "> you sure updated your EARNED HOUR from " << get_total_hours() << " to " << newHour << "? (n/y): ";
				getline(cin, input);

				if (input.length() == 1) {
					input = tolower(input[0]);
					if (input[0] == 'y') {
						setTotalHours(to_string(newHour));
						Updated = 4;
						break;
					}
					else if (input[0] == 'n') { Updated = 99;cout << "***NO information Updated.***\n"; break; }
					else continue;
				}
				else continue;
			}
		}
	}
	if (Updated == 4)file.studentUpdatedInfoInFile(Updated, getID(), getPWD(), get_major(), get_total_hours(), get_GPA());
}
//Sub menu for student to view and update their information
void Student::StudentUPdatedInfoSubMeun()
{
	FileIO file;
	int option, Updated = 0, userEnterDouble = 0;
	bool invalid = false;
	string input, sub2 = "\n******** Student Menu --> Update My Information *******\n1. View My Information\n2. Update GPA\n3. Update Major\n4. Update earned Hour\n5. Back to Previous (Student Menu) Menu\n*******************************************************\n";

	while (true) {
		cout << endl << sub2 << "\nEnter your option: ";
		getline(cin, input);

		while (input == "") { getline(cin, input); }
		checkDigit(input, invalid, userEnterDouble);

		if (invalid)continue;
		else option = stoi(input);

		if (option < 1 || option>5) { cout << "Invalid! Option must be between 1 to 5.\n";continue; }

		switch (option)
		{
		case 1: printStudentInfo(); Updated = 99;break;
		case 2: UpdateGPA(invalid, Updated); break;
		case 3: UpdatedMajor(Updated); break;
		case 4: UpdatedHour(invalid, Updated); break;
		case 5: Updated = 0; break;
		}

		if (Updated == 99) continue;
		else if (Updated == 0) break;

		if (Updated == 2) { cout << "\n                << !Your GPA Updated! >>";printStudentInfo(); }
		else if (Updated == 3) { cout << "\n               << !Your Major Updated! >>";printStudentInfo(); }
		else if (Updated == 4) { cout << "\n           << !Your Earned Hours Updated! >>";printStudentInfo(); }
	}
}