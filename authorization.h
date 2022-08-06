#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

#include "car_rent.h"


map<string, string> accounts(); // Reading data from a file

bool correct_login(const string& log); // Checking the correctness of the entered login

void authorization(); // Authorization in the system

bool password_check(const string& pass1, const string& pass2); // Checking the correctness of the entered password when creating an account

bool unique_login(const string& log); // Checking the uniqueness of the login

bool create_account(); // Creating an account
