#ifndef PAYMENT_TYPES_CPP
#define PAYMENT_TYPES_CPP

#include <iostream>
#include "Payment.cpp"
using namespace std;

// Inheritance and Runtime Polymorphism

class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        int choice;
        cout << "\n[UPI Payment]: Amount = Rs." << amount << endl;
        cout << "Enter 1 for successful payment, 0 for failed: ";
        cin >> choice;
        return choice == 1;
    }
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        int choice;
        cout << "\n[Card Payment]: Amount = Rs." << amount << endl;
        cout << "Enter 1 for successful payment, 0 for failed: ";
        cin >> choice;
        return choice == 1;
    }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        int choice;
        cout << "\n[Cash Payment]: Amount = Rs." << amount << endl;
        cout << "Enter 1 for successful payment, 0 for failed: ";
        cin >> choice;
        return choice == 1;
    }
};

#endif