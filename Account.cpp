#include <iostream>
#include <string>
#include "Account.h"
#include <fstream> 
#include <iomanip>
using namespace std;

//WORKS FOR READING DATA

//Error validation works! :)
Account* readData(Account* top){
  Account* head = top;
  int size;
  fstream fileIn;
  string fileName;
  cout << "Enter file name: ";
  cin >> fileName;
  fileIn.open(fileName);
  if (fileIn.fail()) {
    cout << "File failed to open. " << endl;
    return top;
  }
  fileIn >> size;
  int counter = getSize(top);
  
  bool before = false;
  if(top != nullptr){
    before = true;
    while(top->next != nullptr){
      top = top->next;
    }
  }

  int ssn, accNum, accType;
  double bal;
  string fName, lName, thisName, accName;
  for(int i = 0; i < size; i++){
    if(counter >= 20){
      return head;
    }
    fileIn >> ssn;
    fileIn >> fName;
    fileIn >> lName;
    fileIn >> accNum;
    fileIn >> accType;
    if(accType == 1){
      accName = "checking";
    }
    else{
      accName = "saving";
    }
    fileIn >> bal;
    if(top==nullptr){
      top = new Account;
      if(!before){
        head = top;
      }
      top->SSN = ssn;
      top->first = fName;
      top->last = lName;
      top->accountNum = accNum;
      top->accountType = accName;
      top->balance = bal;
      top->next = new Account;
      top = top->next;
      counter++;
    }
    else if(before){
      top->next = new Account;
      top = top->next;
      top->SSN = ssn;
      top->first = fName;
      top->last = lName;
      top->accountNum = accNum;
      top->accountType = accName;
      top->balance = bal;
      top->next = new Account;
      top = top->next;
      before = false;
      counter++;
    }
    else{
      Account* mover = head;
      bool failed = false;
      while(mover != nullptr){
        if(mover->SSN == ssn && mover->last != lName){
          cout << "Account Creation Failed – A customer with SSN " << ssn << " already exists." << endl;
          failed = true;
          break;
        }
        else if(mover->last == lName && mover->first == fName && mover->accountType == accName){
          cout << "Account Creation Failed – Tom Smith cannot have two " << accName << " accounts." << endl;
          failed = true;
          break;
        }
        else if(mover->accountNum == accNum){
          cout << "Account Creation Failed – Account number " << accNum << " already exists." << endl;
          failed = true;
          break;
        }
        mover = mover->next;
      }
      if(!failed){
        top->SSN = ssn;
        top->first = fName;
        top->last = lName;
        top->accountNum = accNum;
        top->accountType = accName;
        top->balance = bal;
        if(i+1 < size){
          top->next = new Account;
          top = top->next;
          counter++;
        }
        else{
          top->next = nullptr;
          break;
        }
      }
      else{
        if(mover->next->next == nullptr){
          top->next = nullptr;
          break;
        }
      }
    }
  }
  fileIn.close();
  cout << "Read data... \nDone." << endl;
  return head;
}

Account* closeAccount(Account* top){
  Account* tip = top;
  Account* prev = top;
  Account* head = top;
  Account* holder;
  int accNum, ssn, count = 0;
  bool ssnIn = false, accIn = false;
  cout << "Enter Account Number: ";
  cin >> accNum;
  cout << "Enter Customer SSN: ";
  cin >> ssn;
  while(top != nullptr){
    if(top->accountNum == accNum){
      accIn = true;
    }
    if(top->SSN == ssn){
      ssnIn = true;
    }
    if(accIn && ssnIn){
      holder = top;
      break;
    }

    if(count >= 1){
      prev = prev->next;
    }
    top = top->next;
  }
  if(accIn && ssnIn){
    ssnIn = true;
    cout << "Account Closed" << endl;
    cout << "\tName: " << top->first << " " << top->last << endl;
    cout << "\tAccount Number: " << top->accountNum << endl;
    cout << "\tAccount Type: " << top->accountType << endl;
    cout << "\tBalance: $" << top->balance << "\n\n";
    if(holder == tip){
      tip = tip->next;
      return tip;
    }
    else if(holder->next == nullptr){
      prev->next = nullptr;
    }
    else{
      prev->next = prev->next->next;
    }    
  }
  else if(!accIn && ssnIn){
    cout << "Incorrect Account Number" << endl;
  }
  else if(accIn && !ssnIn){
    cout << "Incorrect SSN" << endl;
  }
  else if(!accIn && !ssnIn){
    cout << "Incorrect SSN" << endl;
    cout << "Incorrect Account Number" << endl;
  }
  return tip;
}

void customerInfo(Account* top){
  int choice = 4, answer;
  string answerLast;
  do{
    cout << "SSN(1)/Last Name(2)/Account Number(3): ";
    cin >> choice;
    switch(choice){
      case 1:
        cout << "Enter SSN: ";
        cin >> answer;
        break;
      case 2:
        cout << "Enter Last Name: ";
        cin >> answerLast;
        break;
      case 3:
        cout << "Enter Account Number: ";
        cin >> answer;
        break;
      default:
        cout << "Choice invlad. Try again. \n";
        break;
    };
    while(top != nullptr){
      if(top->SSN == answer || top->accountNum == answer || top->last == answerLast){
        cout << "\tName: " << top->first << " " << top->last << endl;
        cout << "\tAccount Number: " << top->accountNum << endl;
        cout << "\tAccount Type: " << top->accountType << endl;
        cout << "\tBalance: $" << top->balance << "\n\n";
        
      }
      top = top->next;
    }
  }while(choice < 1 || choice > 3);
}

int getSize(Account* top){
  int count = 0;
  while(top != nullptr){
    count++;
    top = top->next;
  }
  return count;
}

void bankInfo(Account* top){
  double total = 0;
  Account* topCopy = top;
  Account* mover = top;
  int customers = 0;
  int size = getSize(top);
  
  cout << "Number of Accounts: " << size << endl;
  while(mover != nullptr){
    cout << "\t" << mover->accountNum << ": $" << mover->balance << " (" << mover->accountType << ") "  << endl;
    total += mover->balance;
    topCopy = mover;
    while(topCopy != nullptr){
      if(topCopy->first == mover->first && topCopy->last == mover->last && mover != topCopy){
        customers++;
      }
      topCopy = topCopy->next;
    }
    mover = mover->next;
  }
  int temp[size-customers];
  int count = 0;
  topCopy = top;
  mover = top;
  bool twoAcc = false, printQ = true;
  cout << "\nNumber of Customers: " << size-customers << endl;
  //for(int i = 0; i < size-customers; i++){
  while(topCopy != nullptr){
    twoAcc = false;
    mover = topCopy->next;

    while(mover != nullptr){
      if(topCopy->SSN == mover->SSN && topCopy != mover && topCopy->last == mover->last){
        twoAcc = true;
        break;
      }
      mover = mover->next;
    }
    printQ = true;
    for(int j = 0; j < count; j++){
      if(temp[j] == topCopy->SSN){
        printQ = false;
      }
    }
    if(printQ){
      cout << "\t" << topCopy->first << " " << topCopy->last << ": " << topCopy->SSN << " - " << topCopy->accountNum << "($" << topCopy->balance << ")";
      temp[count] = topCopy->SSN;
      count++;
      if(twoAcc){
        cout << ", " << mover->accountNum << "($" << mover->balance << ") " << endl;
        mover = mover->next;
      }
      else{
        cout << endl;
      }
    }
    topCopy = topCopy->next;
  }
  cout << "Total Balance: $" << total << endl;

  
}

void transferMoney(Account* top){
  bool fin1 = false, fin2 = false, diff = false;
  Account* mover = top;
  int source, destination, extra = 0;
  double amount;
  string p1, p2;
  cout << "Source Account: ";
  cin >> source;
  cout << "Destination Account: ";
  cin >> destination;
  cout << "Money Account: $";
  cin >> amount;

  while(mover != nullptr){
    if(mover->accountNum == source){
      fin1 = true;
      p1 = mover->first + " " + mover->last;
      
    }
    if(mover->accountNum == destination){
      p2 = mover->first + " " + mover->last;
      fin2 = true;
    }
    mover = mover->next;
  }
  if(p1 != p2){
    diff = true;
    if(diff){
      extra = 5;
    }
  }
  if(fin1 == true && fin2 == true){
    cout << "\nTransfer Succeed. ";
    cout << "\nNew Balance";
    while(top != nullptr){

      if(top->accountNum == source){
        top->balance = top->balance-amount-extra;
        cout << "\n\t" << top->accountNum << ": $" << top->balance;
      }
      if(top->accountNum == destination){
        top->balance = top->balance+amount;
        cout << "\n\t" << top->accountNum << ": $" << top->balance << endl; 
      }
      top = top->next;
    }
  }
  else{
    cout << "Transfer Fail – Incorrect account number. ";
  }
}


void customerList(Account* top){
  Account* topCopy = top;
  bool notIn = true;

  cout << "========== Customer List ==========" << endl;
  while(top != nullptr){
    notIn = true;
    if(top->next == nullptr){
      topCopy = top;
    }
    else{
      topCopy = top->next;
    }
    while(topCopy != nullptr){
      if(topCopy->first == top->first){
        notIn = false;
      }
      topCopy = topCopy->next;
    }
    if(notIn && top->SSN != 0){
      cout << "\n\tSSN: " << top->SSN << endl;
      cout << "\tName: " << top->first << " " << top->last << "\n"; 
    }
    top = top->next;
  }
  cout << "\n===================================" << endl;
}
