#ifndef SEAT_CPP
#define SEAT_CPP

#include <iostream>
#include <string>
#include "Types.h"
using namespace std;

class Seat {
private:
    string number;
    string type;
    double price;

public:
    Seat(string n = "", string t = SEAT_TYPE_SILVER) {
        number = n;
        type = t;

        if (type == SEAT_TYPE_SILVER)
            price = SILVER_PRICE;
        else if (type == SEAT_TYPE_GOLD)
            price = GOLD_PRICE;
        else if (type == SEAT_TYPE_PLATINUM)
            price = PLATINUM_PRICE;
        else
            price = SILVER_PRICE;
    }

    string getNumber() const {
        return number;
    }

    string getType() const {
        return type;
    }

    double getPrice() const {
        return price;
    }
};

#endif