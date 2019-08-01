#include "FileIO.h"

FileIO::FileIO(string where){this->where = where;}

ifstream FileIO::readFile()
{
	ifstream myfile;
	myfile.open(where);

	if (!myfile.is_open()) {
		cout << "<ERROR> File named " << where << " loading fails.\n";
	}
	return myfile;
}
void FileIO::filesLoaded()
{
	ifstream files(where);
	files.open(where);
	if (files.is_open()){}
	else { cout << "<ERROR> File named "<<where<<" loading fails.\n";}
	files.close();
}
//Check user ID and Password
string FileIO::checkPWD(ifstream fileName, string userID, string userPWD, bool &login)
{
	string extractID, extractPWD, line, temp;
	vector<string> oneLine;
	bool notMatch = true;
	login = false;

	if (fileName)
	{
		while (notMatch) {
			while (true) {
				if (fileName.fail()) {
					fileName.clear();
					fileName.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else if (fileName.eof())break;
				else
				{
					oneLine.clear();
					string line, word;
					getline(fileName, line);
					stringstream s(line);
					s >> line;
					stringstream ss(line);

					while (getline(ss, temp, ','))
					{
						oneLine.push_back(temp);
					}
					extractID = oneLine[0];
					extractPWD = oneLine[1];

					if (userID.compare(extractID) == 0 && userPWD.compare(extractPWD) == 0)
					{
						notMatch = false;
						break;
					}
				}
			}
			fileName.clear();
			fileName.seekg(0, ios::beg);
			if (notMatch == true)
			{
				cout << "!!!ID or Password Incorrect!!!\n\n";
				login = false;
			}
			else {login = true;}
			break;
		}
	}
	else cout << "<ERROR> Cannot login right now. Please try again later.\n";
	fileName.close();
	return userID;
}
//Get a vector of students 
vector<string> FileIO::get_student_vector(ifstream fileName, string ID,bool &open)
{
	vector<string> all_advisees;
	string line;
	string advisor_ID;
	string student_ID;
	bool not_match = true;
	if (fileName.is_open()) {
		open = true;
		while (!fileName.eof())
		{
			getline(fileName, line);
			vector <string> all_stds;
			string temp = "";
			stringstream iss(line);
			string saver;
			int comma = 0;
			for (int h = 0; h < line.length(); h++)
			{
				if (line[h] == ',')
					comma++;
			}
			if (comma == 0)
			{
				getline(iss, advisor_ID, '\n');
			}
			else
			{
				getline(iss, advisor_ID, ',');

				if (advisor_ID.compare(ID) == 0)
				{
					while (getline(iss, temp, ','))
					{
						char saver[temp.size()];
						if ((int)temp[temp.size() - 1] == 13)
						{
							int yr;
							for (yr = 0; yr < temp.size() - 1; yr++)
							{
								saver[yr] = temp[yr];
							}
							saver[yr] = '\0';
							all_advisees.push_back(saver);
						}
						else
						{
							all_advisees.push_back(temp);
						}
					}
				}
			}
		}
		fileName.close();
	}
	else {
		open = false;
	}
	return all_advisees;
}
map<string, vector<string> > FileIO::get_all_student_map(ifstream fileName)
{
	map<string, vector<string> > all_std_info;
	bool not_match = true;
	if (fileName.is_open()) {
		while (!fileName.eof())
		{
			string line;
			string student_ID;
			string temp;
			vector<string> information;
			vector<string> helper;
			getline(fileName, line);
			stringstream iss(line);

			getline(iss, student_ID, ',');
			while (getline(iss, temp, ','))
			{
				if (!temp.empty())
				{
					char saver[temp.size()];
					if ((int)temp[temp.size() - 1] == 13)
					{
						int yr;
						for (yr = 0; yr < temp.size() - 1; yr++)
						{
							saver[yr] = temp[yr];
						}
						saver[yr] = '\0';
						helper.push_back(saver);
					}
					else
					{
						helper.push_back(temp);
					}
				}
				else
					helper.push_back("[UNDECIDED]");
			}
			all_std_info.insert(make_pair(student_ID, helper));
		}
		//Sherzod: commented function is needed to print all std info
		/*for_each(all_std_info.begin(), all_std_info.end(), [&](pair<string, vector<string> > s){
			string p = s.first;
			vector<string> m = s.second;
			cout << p << " ";
			for(auto k: m)
			{
				cout << k << " ";
			}
			cout << endl;
		});*/
		fileName.close();
	}
	return all_std_info;
}
//Save student notes to file
void FileIO::save_note(string full_note)
{
	ofstream ofs(where, ios::app);
	if (ofs.is_open())
	{
		ofs << full_note;
		ofs.close();
	}
}
//View student's notes
void FileIO::view_notes(string std_ID)
{
	string advisor_ID, date;
	ifstream ifs(where);
	int count = 0;
	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			string line, student_ID;
			getline(ifs, line);
			istringstream iss(line);
			iss >> advisor_ID >> date;
			iss >> student_ID;
			if (student_ID.compare(std_ID) == 0)
			{
				cout << line << endl;
				count++;
			}
		}
		if (count == 0)
		{
			cout << "Student does not have any notes!" << endl;
		}
		ifs.close();
	}
}
//Check if student exist
string FileIO::check_students(string std_ID)
{
	ifstream ifs(where);
	int count = 0;
	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			string student_ID, line;
			getline(ifs, line);
			istringstream iss(line);
			getline(iss, student_ID, ',');

			if (student_ID.compare(std_ID) == 0)
			{
				count++;
				ifs.close();
				return line;
			}
		}
		if (count == 0) {
			ifs.close();
			return "<ERROR> NO such student!";
		}
	}
	else cout << "<ERROR> File named Data_students.txt loading fails.\n";
	return "End!";
}
//Add a advisee to a advisor
void FileIO::write_advisee(string advisor_ID, string std_ID)
{
	ifstream ifs(where);
	vector<string> all_lines;
	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			string adv_ID, line;
			getline(ifs, line);
			istringstream iss(line);
			getline(iss, adv_ID, ',');

			char saver[adv_ID.size()];
			if ((int)adv_ID[adv_ID.size() - 1] == 13)
			{
				int yr;
				for (yr = 0; yr < adv_ID.size() - 1; yr++)
				{
					saver[yr] = adv_ID[yr];
				}
				saver[yr] = '\0';
				adv_ID = saver;
			}

			if (adv_ID.compare(advisor_ID) == 0)
			{
				char saver[line.size()];
				if ((int)line[line.size() - 1] == 13)
				{
					int yr;
					for (yr = 0; yr < line.size() - 1; yr++)
					{
						saver[yr] = line[yr];
					}
					saver[yr] = '\0';
					line = saver;
				}
				all_lines.push_back(line + "," + std_ID + "\n");
			}
			else
			{
				all_lines.push_back(line + "\n");
			}
		}
		ifs.close();
		ofstream ofs(where, ios::trunc);
		for (auto i : all_lines)
		{
			ofs << i;
		}
		cout << "The advisee " << std_ID <<  " was added to " << advisor_ID << endl;
		ofs.close();
	}
}
//Check if a student have advisor
int FileIO::check_if_has_advisor(string std_ID, string advisor_ID)
{
	int result = 0;
	ifstream ifs(where);
	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			string adv_ID, line;
			getline(ifs, line);
			stringstream iss(line);
			getline(iss, adv_ID, ',');

			string std;
			if (adv_ID.compare(advisor_ID) == 0)
			{
				while (!iss.eof())
				{
					getline(iss, std, ',');
					char saver[std.size()];
					if ((int)std[std.size() - 1] == 13)
					{
						int yr;
						for (yr = 0; yr < std.size() - 1; yr++)
						{
							saver[yr] = std[yr];
						}
						saver[yr] = '\0';
						std = saver;
					}
					if (std.compare(std_ID) == 0)
					{
						result = 1;
					}
				}
			}
			else {
				while (!iss.eof())
				{
					getline(iss, std, ',');
					char saver[std.size()];
					if ((int)std[std.size() - 1] == 13)
					{
						int yr;
						for (yr = 0; yr < std.size() - 1; yr++)
						{
							saver[yr] = std[yr];
						}
						saver[yr] = '\0';
						std = saver;
					}
					if (std.compare(std_ID) == 0)
					{
						result = 2;
					}
				}
			}
		}
		ifs.close();
	}
	return result;
}
//Update student info to the file
void FileIO::studentUpdatedInfoInFile(int Updated, string ID, string PWD, string major, string total_hours, string GPA) {
	string line, info;
	ifstream myfile;

	myfile.open("Data_students.txt");

	if (myfile.is_open()) {
		ofstream newfile;
		newfile.open("temp.txt");

		while (getline(myfile, line)) {
			stringstream inSS;
			inSS.str(line);
			getline(inSS, info, ',');
			if (info.compare(ID) != 0) newfile << inSS.str() << endl;
			else newfile << ID << "," << PWD << "," << major << "," << total_hours << "," << GPA[0] << GPA[1] << GPA[2] << GPA[3] << "\n";
		}
		myfile.close();
		newfile.close();
		remove("Data_students.txt");
		rename("temp.txt", "Data_students.txt");
	}
	else cout << "<ERROR> File named Data_students.txt loading fails.\n";
}
//Show a student's advisor
void FileIO::showAdvisorInfo(string ID)
{
	ifstream in_file("Data_advisees.txt");
	string advisor, line, word;
	bool flag = true;
	if (in_file.is_open())
	{
		do {
			string line;
			while (getline(in_file, line, '\n'))
			{
				istringstream ss(line);
				string substr;
				getline(ss, advisor, ',');
				while (getline(ss, word, ','))
				{
					if (word == ID) {

						flag = false;
						break;
					}
				}
				if (flag == false) {break;}
			}
		} while (!in_file.eof() && flag);
		in_file.close();
		if(flag==true)cout<< "---You are NOT under any advisor---\n";
	}
	else cout << "<ERROR> File named Data_advisees.txt loading fails.\n";

	if (flag == false) {
		ifstream in_file2("Data_advisors.txt");
		string advisorID, room, telephone, info;
		bool found = false;
		if (in_file2.is_open()) {
			while (getline(in_file2, info, '\n')) {
				istringstream strings(info);
				while (getline(strings, word, ',')){
					if (word == advisor) {
						getline(strings, advisorID, ',');
						getline(strings, room, ',');
						getline(strings, telephone, ',');
						cout << "-------------------------------------------------------\n";
						cout << "\t\tYour Advisor Information\n-------------------------------------------------------\n";
						cout << "Advisor ID" << right << setw(12) << "Room" << setw(18) << "Telephone\n";
						cout << left << setw(18) << advisor << setw(12) << room << setw(18) << telephone << endl;
						cout << "-------------------------------------------------------" << endl;
						found = true;
						break;
					}
				}
			}
			in_file2.close();
		}
		else cout << "<ERROR> File named Data_advisors.txt loading fails.\n"
			"<ERROR> Unable to view your advisor right now. Please try again later.\n";
	}
}
//Remove advisee from a advisor
int FileIO::remove_if_my_advisee(string adv_ID, string std_ID,bool write)
{
	ifstream file(where);
	string line, std, adv;
	vector<string> all_lines;
	int result = 0;
	int has_advisees = 0;
	if (file.is_open()) {
		while (!file.eof())
		{
			getline(file, line, '\n');
			stringstream ss(line);
			getline(ss, adv, ',');
			char saver[adv.length()];
			if ((int)adv[adv.length() - 1] == 13)
			{
				int y;
				for (y = 0; y < adv.length() - 1; y++)
				{
					saver[y] = adv[y];
				}
				saver[y] = '\0';
				adv = saver;
			}
			if (adv.compare(adv_ID) == 0)
			{
				while (getline(ss, std, ','))
				{
					has_advisees++;
					char sv[std.length()];
					if ((int)std[std.length() - 1] == 13)
					{
						int yr;
						for (yr = 0; yr < std.length() - 1; yr++)
						{
							sv[yr] = std[yr];
						}
						sv[yr] = '\0';
						std = sv;
					}
					if (std.compare(std_ID) == 0)
					{
						result++;
						int in_indx;
						in_indx = line.find(std);
						char temp[line.length()];
						int k;
						for (k = 0; k < in_indx - 1; k++)
						{
							temp[k] = line[k];
						}
						if (k + 1 < line.length())
						{
							for (int u = in_indx + std.length(); u < line.length(); u++)
							{
								temp[k] = line[u];
								k++;
							}
						}
						temp[k] = '\0';
						line = temp;
					}
				}
			}
			all_lines.push_back(line + "\n");
		}
		if(has_advisees == 0)
		{
			cout << "The advisor does not have any students!" << endl;
		}
		else if (result == 0)
		{
			cout << "The student does not belong to you!" << endl;
		}
		//else cout << "The advisee " << std_ID << " was deleted from " << adv_ID << endl;
	}
	file.close();
	if (write == true) {
		ofstream ofs(where, ios::trunc);
		for (string i : all_lines)
		{
			ofs << i;
		}
		ofs.close();
		cout << "The advisee " << std_ID << " was deleted from " << adv_ID << endl;
	}
	return result;
}
//Check student advisor
string FileIO::check_std_advisor(string std_ID)
{
	string adv, std, line;
	ifstream ifs(where);
	int count = 0;
	if (ifs.is_open()) {
		while (!ifs.eof())
		{
			getline(ifs, line, '\n');
			stringstream ss(line);
			getline(ss, adv, ',');
			char saver[adv.length()];
			if ((int)adv[adv.length() - 1] == 13)
			{
				int y;
				for (y = 0; y < adv.length() - 1; y++)
				{
					saver[y] = adv[y];
				}
				saver[y] = '\0';
				adv = saver;
			}
			while (getline(ss, std, ','))
			{
				char sv[std.length()];
				if ((int)std[std.length() - 1] == 13)
				{
					int yr;
					for (yr = 0; yr < std.length() - 1; yr++)
					{
						sv[yr] = std[yr];
					}
					sv[yr] = '\0';
					std = sv;
				}
				if (std.compare(std_ID) == 0)
				{
					count++;
					break;
				}
			}
			if (count != 0)break;
		}
	}
	if(count != 0)
		return adv;
	else
		return "";
		
}
//A map that store all the advisor
map<string, vector<string> > FileIO::get_all_advisors()
{
	map<string, vector<string> > all_advisors;
	string line, adv, temp;
	ifstream ifs(where);
	if (ifs.is_open()) {
		while (!ifs.eof())
		{
			getline(ifs, line, '\n');
			stringstream ss(line);
			getline(ss, adv, ',');
			char saver[adv.length()];
			if ((int)adv[adv.length() - 1] == 13)
			{
				int y;
				for (y = 0; y < adv.length() - 1; y++)
				{
					saver[y] = adv[y];
				}
				saver[y] = '\0';
				adv = saver;
			}
			vector<string> all_info;
			while (getline(ss, temp, ','))
			{
				char sv[temp.length()];
				if ((int)temp[temp.length() - 1] == 13)
				{
					int yr;
					for (yr = 0; yr < temp.length() - 1; yr++)
					{
						sv[yr] = temp[yr];
					}
					sv[yr] = '\0';
					temp = sv;
				}
				all_info.push_back(temp);
			}
			if (adv.length() != 0)
			{
				all_advisors.insert(make_pair(adv, all_info));
			}
		}
	}
	return all_advisors;
}
//Move advising notes
void FileIO::move_advising_notes(string ID, string moving_adv, string std_ID)
{
	string line, adv, std, note, date;
	vector<string> all_lines;
	ifstream ifs(where);
	if (ifs.is_open()) {
		while (!ifs.eof())
		{
			getline(ifs, line, '\n');
			stringstream ss(line);
			getline(ss, adv, ' ');
			char tmp[adv.length() - 1];
			int i;
			for (i = 1; i < adv.length(); i++)
			{
				tmp[i - 1] = adv[i];
			}
			tmp[i - 1] = '\0';
			adv = tmp;

			string new_line;
			if (adv.compare(ID) == 0)
			{
				getline(ss, date, ' ');
				getline(ss, std, ' ');
				if (std.compare(std_ID) == 0)
				{
					getline(ss, note, '\0');

					new_line = "(" + moving_adv + " " + date + " " + std_ID + " " + note;
					line = new_line;
				}
			}
			all_lines.push_back(line);
		}
	}
	ifs.close();

	ofstream ofs(where, ios::trunc);
	for (string j : all_lines)
	{
		if (j.length() != 0)
			ofs << j << "\n";
	}
	ofs.close();
}