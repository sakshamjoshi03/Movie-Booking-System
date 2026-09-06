#ifndef SHOWSEAT_CPP
#define SHOWSEAT_CPP

#include <iostream>
#include <string>
#include "Seat.cpp"
#include "Types.h"
using namespace std;

class ShowSeat {
private:
    Seat* seat;
    string status;

public:
    ShowSeat(Seat* s = NULL) {
        seat = s;
        status = SHOW_SEAT_AVAILABLE;
    }

    Seat* getSeat() const {
        return seat;
    }

    bool isAvailable() const {
        return status == SHOW_SEAT_AVAILABLE;
    }

    string getStatus() const {
        return status;
    }

    bool bookSeat() {
        if (isAvailable()) {
            status = SHOW_SEAT_BOOKED;
            return true;
        }
        return false;
    }

    // Alias for backward compatibility
    bool book() {
        return bookSeat();
    }

    void cancelSeat() {
        status = SHOW_SEAT_AVAILABLE;
    }

    // Alias for backward compatibility
    void release() {
        cancelSeat();
    }
};

#endif