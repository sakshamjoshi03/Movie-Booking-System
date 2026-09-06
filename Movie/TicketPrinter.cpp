#ifndef TICKET_PRINTER_CPP
#define TICKET_PRINTER_CPP

#include <iostream>
#include <vector>
#include "Booking.cpp"
using namespace std;

class TicketPrinter {
public:
    void printTicket(Booking* booking) {
        if (booking == NULL) return;
        Show* show = booking->getShow();

        cout << "\n====================================\n";
        cout << "             TICKET                 \n";
        cout << "====================================\n";

        cout << "Booking ID : " << booking->getBookingId() << endl;
        if (booking->getCustomer() != NULL) {
            cout << "Customer   : " << booking->getCustomer()->getName() << endl;
        }
        if (show != NULL) {
            if (show->getMovie() != NULL)
                cout << "Movie      : " << show->getMovie()->getTitle() << endl;
            if (show->getScreen() != NULL)
                cout << "Screen     : Screen-" << show->getScreen()->getScreenNumber() << endl;
            cout << "Time       : " << show->getStartTime() << endl;
        }

        cout << "Seats      : ";
        vector<ShowSeat*>& seats = booking->getSeats();
        for (size_t i = 0; i < seats.size(); i++) {
            if (seats[i] && seats[i]->getSeat())
                cout << seats[i]->getSeat()->getNumber() << " ";
        }
        cout << endl;

        cout << "Amount     : Rs." << booking->getTotalAmount() << endl;
        cout << "Status     : " << booking->getStatus() << endl;
        cout << "====================================\n";
    }
};

#endif