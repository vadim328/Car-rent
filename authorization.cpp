#include "authorization.h"

ofstream acc;

// Чтение данных из файла
map<string, string> accounts() {
	map <string, string> accounts;
	string key, value;
	ifstream acc2("Accounts.txt");
	if (!acc2.is_open()) {
		cout << "Unexpected error, " << "try again later";
		exit(0);
	}
	while (acc2 >> key >> value) {
		accounts[key] = value;
	}
	return accounts;
}

// Проверка корректности введенного логина
bool correct_login(string& log) {
	regex rg1("([+]7|8)\\d{10}");
	regex rg2("\\w+@[a-z]+[.][a-z]{2,3}");
	if (regex_match(log, rg1)) {
		if (log[0] == '8') {
			log.erase(log.begin());
			log = "+7" + log;
		}
		return true;
	}
	else if (regex_match(log, rg2)) {
		if (log[0] >= 'a' && log[0] <= 'z') {
			log[0] = log[0] - 32;
		}
		return true;
	}
	return false;
}
// Авторизация в системе
void authorization() {
	cout << "Enter login and password to log in" << endl;
	string log, pass;
	cout << "Login: ";
	cin >> log;
	cout << "Password: ";
	cin >> pass;
	if (correct_login(log)) {
		map <string, string> account = accounts();
		if (pass == account[log]) {
			welcome();
		}
		else {
			cout << "Login or password is not correct, please try again";
			authorization();
		}
	}
	else {
		cout << "Invalid login format, please try again" << endl;
		authorization();
	}
}

// Проверка корректности введенного пароля при создании аккаунта
bool password_check(const string& pass1, const string& pass2) {
	if (pass1 != pass2) {
		return false;
	}
	return true;
}

// Проверка уникальности логина
bool unique_login(const string& log) {
	map <string, string> account = accounts();
	if (account.count(log) == 0) {
		return true;
	}
	return false;
}

// Создание аккаунта
bool create_account() {
	string log = "", pass1 = "", pass2 = ""; // Логин, пароль, повтор пароля
	cout << "Enter your email or phone number" << endl;
	cout << "Login: ";
	cin >> log;
	if (correct_login(log)) {
		if (unique_login(log)) {
			cout << "Enter the password: ";
			cin >> pass1;
			if (pass1.size() >= 6) {
				cout << "Enter the password again: ";
				cin >> pass2;
				if (password_check(pass1, pass2)) {
					acc.open("Accounts.txt", ios::app); // Текстовый файл с аккаунтами в режиме добавления в конец строки
					if (!acc.is_open()) {
						cout << "Unexpected error, try again later" << endl;
						exit(0);
					}
					acc << log + " " << pass1 + "\n";
					acc.close();
					cout << "Your account has been succesfully created, authorization is required to enter the system" << endl;
					return true;
				}
				else {
					cout << "Password do not match, re-enter your login and password" << endl;
					acc.close();
					create_account();
				}
			}
			else {
				cout << "Error, password must be atleast six characters long" << endl;
				acc.close();
				create_account();
			}
		}
		else {
			cout << "This is login is already in use, please enter another one" << endl;
			acc.close();
			create_account();
		}
	}
	else {
		cout << "Invalid login format entered, please try again" << endl;
		acc.close();
		create_account();
	}
}