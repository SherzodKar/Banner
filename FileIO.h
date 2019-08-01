#pragma once
#ifndef FILEIO_H_
#define FILEIO_H

#include <iostream>
#include<string>
#include<fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <array>
//#include <bits/stdc++.h> 

using namespace std;

class FileIO {
private:
	string where;

public:
	FileIO(string where = "");
	void filesLoaded();
	ifstream readFile();
	string checkPWD(ifstream fileName, string userID, string userPWD, bool &login);
	void showAdvisorInfo(string ID);
	vector<string> get_student_vector(ifstream fileName, string ID,bool &open);
	map<string, vector<string> >  get_all_student_map(ifstream fileName);
	void save_note(string full_note);
	void view_notes(string std_ID);
	string check_students(string std_ID);
	void write_advisee(string advisor_ID, string std_ID);
	int check_if_has_advisor(string std_ID, string advisor_ID);
	void studentUpdatedInfoInFile(int Updated, string ID, string PWD, string major, string total_hours, string GPA);
	int remove_if_my_advisee(string adv_ID, string std_ID,bool write);
	string check_std_advisor(string std_ID);
	map<string, vector<string> > get_all_advisors();
	void move_advising_notes(string ID, string moving_adv, string std_ID);
};

#endif

