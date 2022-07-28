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

int leap_year(int& year); // Проверка на високосный год

string rental_end_time(Time t); // Вычисление даты и времени окончания аренды
	
void rented(const string car); // Аренда автомобиля
	
void overwriting(set <string> c, const int& number, const string& type); // Удаляем арендованный автомобиль и перезаписываем остальные авто в файл

set <string> ::iterator car_choise(const set <string>& c, const string& type); // Выбор авто

set <string> reading(const string& type); // Записываем содержимое файла в set

void welcome(); // Вводная функция, выбор типа автомобиля