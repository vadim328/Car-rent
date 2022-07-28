#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

#include "car_rent.h"


map<string, string> accounts(); // ������ ������ �� �����

bool correct_login(const string& log); // �������� ������������ ���������� ������

void authorization(); // ����������� � �������

bool password_check(const string& pass1, const string& pass2); // �������� ������������ ���������� ������ ��� �������� ��������

bool unique_login(const string& log); // �������� ������������ ������

bool create_account(); // �������� ��������