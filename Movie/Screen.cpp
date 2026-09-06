#ifndef SCREEN_CPP
#define SCREEN_CPP

#include <iostream>
#include <vector>
#include "Seat.cpp"
using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int n = 0) {
        screenNumber = n;
    }

    void addSeat(Seat seat) {
        seats.push_back(seat);
    }

    int getScreenNumber() const {
        return screenNumber;
    }

    vector<Seat>& getSeats() {
        return seats;
    }

    const vector<Seat>& getSeats() const {
        return seats;
    }

    void showSeats() const {
        cout << "Screen " << screenNumber << " Seats:\n";
        for (size_t i = 0; i < seats.size(); i++) {
            cout << seats[i].getNumber() << " (" << seats[i].getType() << " - Rs." << seats[i].getPrice() << ") ";
        }
        cout << endl;
    }
};

#endif