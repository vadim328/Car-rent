#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <Windows.h>
#include <sstream>
#include <regex>

using namespace std;

struct Time {
	int year;
	int month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day;
	int hour;
};

int leap_year(int& year); // Checking for a leap year

string rental_end_time(Time t); // Calculation of the date and time of the end of the lease
	
void rented(const string car); // Car rental
	
void overwriting(set <string> c, const int& number, const string& type); // Delete the rented car and overwrite the rest of the cars in the file

set <string> ::iterator car_choise(const set <string>& c, const string& type); // Choosing a car

set <string> reading(const string& type); // Recording the contents of the file

void welcome(); // Choosing the type of car
