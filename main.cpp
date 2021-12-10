#include <iomanip>
#include <iostream>
#include "Account.h"
using namespace std;

int main() {
  cout.setf(ios::fixed); //turn on fixed notation
  cout.setf(ios::showpoint); // turn on - always display decimal point
  cout.precision(2);// use two decimal places

  Account* head = nullptr;
  int choice = 0;
  do{
    cout << "\nSelect your choice: ";
    cout << "\n\t1. Read customer data file \n\t2. Close an account \n\t3. Customer Info \n\t4. Bank Info \n\t5. Transfer Money \n\t6. Customer List \n\t7. Exit \n";
    cin >> choice;
    switch(choice){
      case 1: 
        head = readData(head);
        
        //cleaning(head);
        break;
      case 2:
        head = closeAccount(head);
        break;
      case 3:
        customerInfo(head);
        break;
      case 4:
        bankInfo(head);
  
        break;
      case 5:
        transferMoney(head);
        break;
      case 6:
        customerList(head);
        break;
      case 7:
        cout << "Bye!";
        break;
      default:
        cout << "Your choice is invalid. Try again. ";
        break;
    }

  }while(choice!=7);
  
} 