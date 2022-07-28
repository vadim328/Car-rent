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

int leap_year(int& year); // �������� �� ���������� ���

string rental_end_time(Time t); // ���������� ���� � ������� ��������� ������
	
void rented(const string car); // ������ ����������
	
void overwriting(set <string> c, const int& number, const string& type); // ������� ������������ ���������� � �������������� ��������� ���� � ����

set <string> ::iterator car_choise(const set <string>& c, const string& type); // ����� ����

set <string> reading(const string& type); // ���������� ���������� ����� � set

void welcome(); // ������� �������, ����� ���� ����������