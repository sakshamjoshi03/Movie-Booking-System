#ifndef PRICE_CALCULATOR_CPP
#define PRICE_CALCULATOR_CPP

#include <iostream>
#include <vector>
#include "ShowSeat.cpp"
using namespace std;

class PriceCalculator {
public:
    double calculateTotal(const vector<ShowSeat*>& seats) {
        double total = 0;
        for (size_t i = 0; i < seats.size(); i++) {
            if (seats[i] && seats[i]->getSeat()) {
                total += seats[i]->getSeat()->getPrice();
            }
        }
        return total;
    }

    double calculateTotal(ShowSeat* seat) {
        if (seat && seat->getSeat()) {
            return seat->getSeat()->getPrice();
        }
        return 0;
    }
};

#endif