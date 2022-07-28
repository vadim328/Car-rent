#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

#include "car_rent.h"


map<string, string> accounts(); // Чтение данных из файла

bool correct_login(const string& log); // Проверка корректности введенного логина

void authorization(); // Авторизация в системе

bool password_check(const string& pass1, const string& pass2); // Проверка корректности введенного пароля при создании аккаунта

bool unique_login(const string& log); // Проверка уникальности логина

bool create_account(); // Создание аккаунта