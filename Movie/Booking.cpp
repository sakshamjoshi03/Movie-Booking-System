#ifndef BOOKING_CPP
#define BOOKING_CPP

#include <iostream>
#include <vector>
#include <string>
#include "Customer.cpp"
#include "Show.cpp"
#include "ShowSeat.cpp"
#include "Types.h"
using namespace std;

class Booking {
private:
    static int nextBookingId;

    string bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> seats;
    double totalAmount;
    string status;

public:
    Booking(Customer* c = NULL, Show* s = NULL) {
        customer = c;
        show = s;
        totalAmount = 0;
        status = BOOKING_PENDING;

        bookingId = "BK" + to_string(nextBookingId++);
    }

    Booking(Customer* c, Show* s, ShowSeat* seat, double amount) {
        customer = c;
        show = s;
        if (seat != NULL) {
            seats.push_back(seat);
        }
        totalAmount = amount;
        status = BOOKING_PENDING;

        bookingId = "BK" + to_string(nextBookingId++);
    }

    Booking(Customer* c, Show* s, vector<ShowSeat*> sSeats, double amount) {
        customer = c;
        show = s;
        seats = sSeats;
        totalAmount = amount;
        status = BOOKING_PENDING;

        bookingId = "BK" + to_string(nextBookingId++);
    }

    void addSeat(ShowSeat* seat) {
        seats.push_back(seat);
    }

    void setTotalAmount(double amount) {
        totalAmount = amount;
    }

    void confirm() {
        status = BOOKING_CONFIRMED;
    }

    void fail() {
        status = BOOKING_FAILED;
    }

    void cancel() {
        status = BOOKING_CANCELLED;

        for (size_t i = 0; i < seats.size(); i++)
            seats[i]->cancelSeat();
    }

    string getBookingId() const {
        return bookingId;
    }

    string getStatus() const {
        return status;
    }

    double getTotalAmount() const {
        return totalAmount;
    }

    Show* getShow() const {
        return show;
    }

    Customer* getCustomer() const {
        return customer;
    }

    vector<ShowSeat*>& getSeats() {
        return seats;
    }

    const vector<ShowSeat*>& getSeats() const {
        return seats;
    }
};

// Static member
int Booking::nextBookingId = 1001;

#endif