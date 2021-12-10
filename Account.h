// A sample interface file for Account class.
#ifndef ACCOUNT_H
#define ACCOUNT_H 

#include <string>
using namespace std;


struct Account{ 
  string first;
  string last;
  string accountType;
  int SSN;
  int accountNum;
  double balance;
  Account *next;
};

int getCustomerCount(Account* top);
Account* readData(Account *top);
Account* closeAccount(Account* top);
void customerInfo(Account* top);
void bankInfo(Account* top);
void transferMoney(Account* top);
void customerList(Account* top);
int getSize(Account* top);

#endif    // end of ACCOUNT_H

