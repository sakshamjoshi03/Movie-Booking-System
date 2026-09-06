#ifndef CUSTOMER_CPP
#define CUSTOMER_CPP

#include <iostream>
#include <string>
using namespace std;

class Customer {
private:
    string name;
    string phone;

public:
    Customer(string n = "", string p = "") {
        name = n;
        phone = p;
    }

    string getName() const {
        return name;
    }

    string getPhone() const {
        return phone;
    }

    void start() const {
        cout << "\n[Customer] Customer " << name << " started booking flow.\n";
    }

    void selectMovie(string movieId) const {
        cout << "[Customer] Selected Movie ID: " << movieId << endl;
    }

    void selectShow(string showId) const {
        cout << "[Customer] Selected Show ID: " << showId << endl;
    }

    void selectSeat(string seatId) const {
        cout << "[Customer] Selected Seat ID: " << seatId << endl;
    }

    void showTicket() const {
        cout << "\n[Customer] Ticket generated successfully and received!\n";
    }

    void showError(string message) const {
        cout << "\n[ERROR]: " << message << "\n";
    }
};

#endif