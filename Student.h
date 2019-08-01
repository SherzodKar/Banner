#pragma once
#ifndef STUDENT_H_
#define STUDENT_H_

using namespace std;
#include "User.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "FileIO.h"
#include <cstring>
#include <stdio.h>
#include <math.h>

class Student : public User {
private:
	string major;
	string total_hours;
	string GPA;
	vector<string> advising_notes;

public:
	Student(string ID = "");
	string get_major();
	string get_GPA();
	string get_total_hours();
	void setGPA(string userGPA);
	void setMajor(string userMajor);
	void setTotalHours(string userHours);
	string printHeader()override;
	string printHeader(string ID);
	void studentJob();
	void view_adv();
	void get_all_std_info(map<string, vector<string> > all_stds);
	void add_advising_notes(string adv_ID, string date);
	void view_advising_notes();
	void printStudentInfo();
	void UpdateGPA(bool &invalid, int &Updated);
	void UpdatedMajor(int &Updated);
	void UpdatedHour(bool &invalid, int &Updated);
	void StudentUPdatedInfoSubMeun();
};



#endif