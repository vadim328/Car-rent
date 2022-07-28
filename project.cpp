#include "authorization.h"

void start() {
	ifstream start("Start.txt");
	string st;
	while (getline(start, st)) {
		cout << st << endl;
	}
	start.close();
	bool action;
	cout << endl << "If you want to create an account, write <0>, if you want to login, write <1>" << endl;
	cin >> action;
	if (action == 0) {
		action = create_account();
	}
	if (action == 1) {
		authorization();
	}
	else {
		cout << "Sorry something went wrong, try again later";
		exit(0);
	}
}

int main()
{
	start();
	return 0;
}