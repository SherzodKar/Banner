#pragma once
#ifndef ADVISOR_H_
#define ADVISOR_H_

#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Student.h"
#include "FileIO.h"
#include<ctime>

using namespace std;

class Advisor : public User {

private:
	string room;
	string phone;
	vector<Student*> all_advisees;
public:
	void set_room(string room);
	void set_phone(string phone);
	string get_room();
	string get_phone();
	template<typename T>
	void display(T value);
	string printHeader()override;
	void advisorJob();
	void get_all_student_info_by_ID();
	void get_all_student_info_by_major();
	void get_all_student_info_by_hours();
	void sortAdviseeMenu();
	void searchAdviseeMenu();
	void AdvisingNotesMenu();
	bool get_all_advisees();
	void search_by_ID();
	void search_by_major();
	void search_by_range_total_hours();
	void search_by_major_range_total_hours();
	string get_current_date();
	void add_notes();
	void view_notes();
	void add_advisee();
	void delete_student();
	void check_who_is_advisor();
	void display_all_advisors();
	void view_count_and_GPA_of_major();
	void move_advisees();
};



#endif