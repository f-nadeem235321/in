
#include<iostream>
#include<limits>
using namespace std;




int main() {
	const int PIN = 3478;   
	int enteredPIN;
	int attempts = 0;
	float balance = 1000;    
	float Lastamount = 0.0;   
	char LastType = 'N';     
	bool running = true;
	//Welcome screen
	cout << "=======================" << endl;
	cout << "Welcome to Simple Atm" << endl;
	cout << "========================" << endl;
	cout << "Enter your pin to continue" << endl;


	
	while (attempts < 3) {

		cout << "Enter pin:";
		cin >> enteredPIN;
		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max(), '\n');
			cout << "Invalid input.Please enter numbers only" << endl;
			continue;
		}
		if (enteredPIN == PIN) {
			cout << "Access Granted\n\n";
			break;
		}
		else {
			attempts++;
			cout << "Invalid PIN. Try again" << endl;
		}
		if (attempts==3) {
			cout << "Atm locked. Too many failed attempts." << endl;
			return 0;
		}
	}


	
	do {
		int choice;
		cout << "Main menu" << endl;
		cout << "1.Check Balance" << endl;
		cout << "2. Deposit Money" << endl;
		cout << "3. Withdraw Money" << endl;
		cout << "4.Mini statement" << endl;
		cout << "5.exit" << endl;
		cout << "Enter your choice" << endl;
		cin >> choice;

		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice input. Try Again." << endl;
			continue;
		}
		switch (choice) {
		case 1: {
			cout << "Your current balance is: $" << balance << endl;
			break;
		}

		case 2: {
			float amount;
			cout << "enter amount to deposit:" << endl;
			cin >> amount;
			if (!cin || amount <= 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid amount" << endl;
			}
			else {
				balance += amount;  
				Lastamount = amount;
				LastType = 'D';
				cout << "Deposit succesful. New balance:$" << balance << endl;
			}
			break;
		}

		case 3: {
			float amount;
			cout << "Enter amount to withdraw:" << endl;
			cin >> amount;
			if (!cin || amount < 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "invalid amount " << endl;
				break;
			}


			if (amount > balance) {
				cout << "insufficent balance " << endl;
			}
			else {
				balance -= amount;
				Lastamount = amount;
				LastType = 'W';
				cout << "Withdrawal successful . New balance : $" << balance << endl;
			}
			break;
		}
		case 4: {
			if (LastType == 'N') {
				cout << "No transaction yet." << endl;
			}
			else {
				cout << "Last transaction:";
				if (LastType == 'D')
					cout << "Deposit of $" << Lastamount << endl;
				else
					cout << "Withdrawal of $" << Lastamount << endl;

				
				int demo = 5;
				cout << "Operator Demo (starting demo = 5 )" << endl;
				cout << "Prefix (++demo):" << ++demo << endl;  
				cout << "Postfix (demo++):" << demo++ << endl;   
				cout << "Final demo value :" << demo << endl;   
			}
			break;
		}

		case 5: {
			cout << "Thank you for using Simple Atm " << endl;
			cout << "Goodbye" << endl;
			running = false;
			break;
		}
		default:
			cout << "Invalid choice . PLease try again " << endl;
		}
	} while (running);
	return 0;

}
