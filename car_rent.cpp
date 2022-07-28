#include "car_rent.h"

ifstream cars_read; // Чтение из файла
ofstream cars_write; // Запись в файл

int leap_year(int& year) { // Проверка на високосный год
	if (year % 4 == 0) {
		return 29;
	}
	return 28;
}

string rental_end_time(Time t) { // Вычисление даты и времени окончания аренды
	SYSTEMTIME st;
	GetLocalTime(&st);
	t.hour += st.wHour; // время окончания
	t.day += st.wDay; // день окончания
	int boundary_time = t.hour / 24;
	if (boundary_time >= 1) { // Если часы равны или больше 24
		t.hour -= boundary_time * 24;
		t.day += boundary_time;
	}
	t.year = st.wYear;
	t.month[1] = leap_year(t.year); // Если год високосный
	int m = st.wMonth; // Текущий месяц в массиве
	while (t.day > t.month[m - 1]) {
		t.day -= t.month[m - 1];
		if (m == 12) { // Переход на следующий год
			t.year++;
			t.month[1] = leap_year(t.year);
			m = 0;
		}
		m++;
	}
	stringstream ss;
	ss << " Start of lease: " << st.wDay << "." << st.wMonth << "." << st.wYear << " " << st.wHour << " ocloc'l " << st.wMinute << " minutes, "
		<< "еnd of lease: " << t.day << "." << m << "." << t.year << " " << t.hour << " ocloc'l " << st.wMinute << " minutes";
	string s;
	getline(ss, s);
	return s;
}

void rented(const string car) { // Аренда автомобиля
	cout << "How long will the car be rented for?" << endl
		<< "Enter the time in the format: X day(s) X hour(s)" << endl;
	Time t;
	cin >> t.day >> t.hour;
	cars_write.open("Rented.txt", ios::app);
	string rented_car;
	stringstream ss(car);
	getline(ss, rented_car, ',');
	if (!cars_write.is_open()) {
		cout << "Unexpected error, try again later" << endl;
		exit(0);
	}
	cars_write << rented_car << rental_end_time(t) << "\n";
	cars_write.close();

	string price;
	getline(ss, price);
	regex rg(R"(: ([0-9]+))");
	smatch m;
	regex_search(price, m, rg); // Извлекаем часовую стоимость авто из файла
	cout << "The amount of the rent will be: " << stoi(m[1]) * (t.day * 24 + t.hour) << " c.u., thanks for renting a car.";
}

void overwriting(set <string> c, const int& number, const string& type) { // Удаляем арендованный автомобиль и перезаписываем остальные авто в файл
	set <string> ::iterator it = c.begin();
	advance(it, number - 1);
	c.erase(it);
	it = c.begin();
	cars_write.open(type);
	if (!cars_write.is_open()) {
		cout << "Unexpected error, try again later" << endl;
		exit(0);
	}
		for (; it != c.end(); it++) {
			cars_write << *it + "\n";
		}
		cars_write.close();
}

set <string> ::iterator car_choise(const set <string>& c, const string& type) { // Выбор авто
	cout << "Choose a car:" << endl;
	set <string> ::iterator it = c.begin();
	for (int i = 1; it != c.end(); i++, it++) {
		cout << i << ". " << *it << endl;
	}
	cout << "Enter the serial number of the car: ";
	int number;
	cin >> number;
	it = c.begin();
	advance(it, number - 1);
	overwriting(c, number, type);
	return it;
}

set <string> reading(const string& type) { // Записываем содержимое файла в set
	set <string> c;
	string s;
	cars_read.open(type);
	if (!cars_read.is_open()) {
		cout << "Unexpected error, try again later" << endl;
		exit(0);
	}
	while (getline(cars_read, s)) {
		c.insert(s);
	}
	cars_read.close();
	return c;
}

void welcome() {
	cout << "What car do you want to rent?" << endl;
	vector<string> cars_type;
	string type;
	int i = 1;
	cars_read.open("Cars_type.txt");
	if (!cars_read.is_open()) {
		cout << "Unexpected error, try again later" << endl;
		exit(0);
	}
	while (getline(cars_read, type)) {
		cout << i << ". " << type << endl;
		cars_type.push_back(type);
		i++;
	}
	cars_read.close();
	cout << "Enter number: ";
	int number;
	cin >> number;
	type = cars_type[number - 1] + ".txt";
	cout << type;
	set <string> c = reading(type);
	set <string> ::iterator it = car_choise(c, type);
	rented(*it);
}