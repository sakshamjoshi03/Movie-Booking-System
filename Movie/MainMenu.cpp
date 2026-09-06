#ifndef MAIN_MENU_CPP
#define MAIN_MENU_CPP

#include <iostream>
#include <vector>
#include <string>
#include "BookingService.cpp"
#include "Customer.cpp"
using namespace std;

class MainMenu {
private:
    BookingService* bookingService;
    Customer* customer;
    vector<Movie*> movies;
    vector<Show*> shows;

public:
    MainMenu(BookingService* service = NULL, Customer* cust = NULL) {
        bookingService = service;
        customer = cust;
    }

    void setMovies(const vector<Movie*>& m) {
        movies = m;
    }

    void setShows(const vector<Show*>& s) {
        shows = s;
    }

    void displayMenu() const {
        cout << "\n===============================\n";
        cout << "   MOVIE TICKET BOOKING SYSTEM   \n";
        cout << "===============================\n";
        cout << "1. Movies Playing\n";
        cout << "2. View Shows\n";
        cout << "3. Book Ticket (Single Seat - UPI Sequence Flow)\n";
        cout << "4. Book Ticket (Multi-Seat)\n";
        cout << "5. Cancel Booking\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
    }

    int readInput() const {
        int choice;
        cin >> choice;
        return choice;
    }

    void run() {
        int choice;
        Booking* lastBooking = NULL;

        do {
            displayMenu();
            choice = readInput();

            if (choice == 1) {
                cout << "\n--- Movies Playing ---\n";
                vector<Movie*> movieVec = bookingService->getAllMovies();
                if (movieVec.empty()) movieVec = movies;

                for (size_t i = 0; i < movieVec.size(); i++) {
                    cout << "[" << i + 1 << "] " << movieVec[i]->getTitle()
                         << " (" << movieVec[i]->getLanguage() << ") - "
                         << movieVec[i]->getDuration() << " mins\n";
                }
            }
            else if (choice == 2) {
                cout << "\n--- Available Shows ---\n";
                for (size_t i = 0; i < shows.size(); i++) {
                    cout << "[" << i + 1 << "] " << shows[i]->getMovie()->getTitle()
                         << " | Screen " << shows[i]->getScreen()->getScreenNumber()
                         << " | Time: " << shows[i]->getStartTime() << "\n";
                }
            }
            else if (choice == 3) {
                // Sequence Diagram Flow: Customer books 1 seat and pays by UPI
                cout << "\nSelect Show:\n";
                for (size_t i = 0; i < shows.size(); i++) {
                    cout << i + 1 << ". " << shows[i]->getMovie()->getTitle() << " (" << shows[i]->getStartTime() << ")\n";
                }
                cout << "Choose show: ";
                int showChoice = readInput();

                if (showChoice < 1 || showChoice > (int)shows.size()) {
                    customer->showError("Invalid show choice.");
                    continue;
                }

                Show* selectedShow = shows[showChoice - 1];

                cout << "\nSeat Layout for " << selectedShow->getStartTime() << ":\n";
                bookingService->getSeatLayout(selectedShow->getStartTime());

                string seatId;
                cout << "Enter seat ID to book (e.g. A1, B1): ";
                cin >> seatId;

                customer->selectSeat(seatId);

                cout << "\nPayment Options:\n";
                cout << "1. UPI\n2. Card\n3. Cash\nChoose payment mode: ";
                int payChoice = readInput();

                Payment* payment = NULL;
                if (payChoice == 1) payment = new UpiPayment();
                else if (payChoice == 2) payment = new CardPayment();
                else if (payChoice == 3) payment = new CashPayment();
                else {
                    customer->showError("Invalid payment option.");
                    continue;
                }

                lastBooking = bookingService->bookTicket(customer, selectedShow, seatId, payment);
                delete payment;
            }
            else if (choice == 4) {
                // Multi-seat booking
                cout << "\nSelect Show:\n";
                for (size_t i = 0; i < shows.size(); i++) {
                    cout << i + 1 << ". " << shows[i]->getMovie()->getTitle() << " (" << shows[i]->getStartTime() << ")\n";
                }
                cout << "Choose show: ";
                int showChoice = readInput();

                if (showChoice < 1 || showChoice > (int)shows.size()) {
                    customer->showError("Invalid show choice.");
                    continue;
                }

                Show* selectedShow = shows[showChoice - 1];

                cout << "\nSeat Layout:\n";
                selectedShow->displaySeats();

                int numSeats;
                cout << "How many seats? ";
                cin >> numSeats;

                vector<string> seatIds;
                for (int i = 0; i < numSeats; i++) {
                    string sId;
                    cout << "Enter seat " << i + 1 << ": ";
                    cin >> sId;
                    seatIds.push_back(sId);
                }

                cout << "\nPayment Options:\n1. UPI\n2. Card\n3. Cash\nChoose payment mode: ";
                int payChoice = readInput();

                Payment* payment = NULL;
                if (payChoice == 1) payment = new UpiPayment();
                else if (payChoice == 2) payment = new CardPayment();
                else if (payChoice == 3) payment = new CashPayment();
                else {
                    customer->showError("Invalid payment option.");
                    continue;
                }

                lastBooking = bookingService->bookTicket(customer, selectedShow, seatIds, payment);
                delete payment;
            }
            else if (choice == 5) {
                string bId;
                cout << "Enter Booking ID: ";
                cin >> bId;
                bookingService->cancelBooking(bId);
            }
            else if (choice == 0) {
                cout << "\nThank you for using Movie Ticket Booking System!\n";
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }
};

#endif
