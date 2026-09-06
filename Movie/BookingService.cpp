#ifndef BOOKING_SERVICE_CPP
#define BOOKING_SERVICE_CPP

#include <iostream>
#include <vector>
#include <string>
#include "Cinema.cpp"
#include "Movie.cpp"
#include "Show.cpp"
#include "ShowSeat.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "PaymentTypes.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
using namespace std;

class BookingService {
private:
    Cinema* cinema;
    vector<Movie*> movies;
    vector<Show*> shows;
    vector<Booking*> bookings;
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

public:
    BookingService(Cinema* c = NULL) {
        cinema = c;
    }

    void setCinema(Cinema* c) {
        cinema = c;
    }

    void addMovie(Movie* movie) {
        movies.push_back(movie);
    }

    void addShow(Show* show) {
        shows.push_back(show);
    }

    vector<Movie*> getAllMovies() {
        return movies;
    }

    vector<Show*> getShows(string movieId) {
        vector<Show*> result;
        for (size_t i = 0; i < shows.size(); i++) {
            if (shows[i]->getMovie() != NULL && shows[i]->getMovie()->getTitle() == movieId) {
                result.push_back(shows[i]);
            }
        }
        return result;
    }

    void getSeatLayout(string showId) {
        for (size_t i = 0; i < shows.size(); i++) {
            if (shows[i]->getStartTime() == showId) {
                shows[i]->displaySeats();
                return;
            }
        }
        cout << "Show not found: " << showId << endl;
    }

    bool makePayment(Payment* payment, double amount) {
        if (payment == NULL) return false;
        return payment->pay(amount);
    }

    Booking* createBooking(Customer* customer, Show* show, ShowSeat* seat, double amount) {
        Booking* booking = new Booking(customer, show, seat, amount);
        return booking;
    }

    Booking* createBooking(Customer* customer, Show* show, vector<ShowSeat*> seats, double amount) {
        Booking* booking = new Booking(customer, show, seats, amount);
        return booking;
    }

    // Sequence Diagram interactive booking flow for 1 seat
    Booking* bookTicket(Customer* customer, Show* show, string seatId, Payment* payment) {
        if (customer != NULL) {
            customer->start();
        }

        if (show == NULL) {
            if (customer != NULL) customer->showError("Invalid show selected.");
            return NULL;
        }

        if (customer != NULL) {
            customer->selectShow(show->getStartTime());
        }

        // 19. checkAvailability(seatId)
        ShowSeat* seat = show->findSeat(seatId);
        if (seat == NULL || !seat->isAvailable()) {
            // 21a. showError("Seat already booked")
            if (customer != NULL) {
                customer->showError("Seat already booked");
            }
            return NULL;
        }

        // 21. bookSeat()
        seat->bookSeat();

        // 23. calculateTotal(seatId)
        double totalAmount = priceCalculator.calculateTotal(seat);
        cout << "\nTotal Calculated Amount: Rs." << totalAmount << endl;

        // 25. makePayment(payment, totalAmount)
        bool paymentSuccess = makePayment(payment, totalAmount);

        if (!paymentSuccess) {
            // 29a. cancelSeat()
            seat->cancelSeat();
            // 31a. showError("Payment failed, booking not confirmed")
            if (customer != NULL) {
                customer->showError("Payment failed, booking not confirmed");
            }
            return NULL;
        }

        // 29. <<create>> Booking(customer, show, seat, totalAmount)
        Booking* booking = createBooking(customer, show, seat, totalAmount);

        // 31. confirm()
        booking->confirm();
        bookings.push_back(booking);

        // 33. printTicket(booking)
        ticketPrinter.printTicket(booking);

        // 35. showTicket()
        if (customer != NULL) {
            customer->showTicket();
        }

        return booking;
    }

    // Multi-seat booking flow
    Booking* bookTicket(Customer* customer, Show* show, vector<string> seatNumbers, Payment* payment) {
        vector<ShowSeat*> selectedSeats;

        for (size_t i = 0; i < seatNumbers.size(); i++) {
            ShowSeat* seat = show->findSeat(seatNumbers[i]);

            if (seat == NULL) {
                if (customer != NULL) customer->showError("Invalid seat: " + seatNumbers[i]);
                return NULL;
            }

            if (!seat->isAvailable()) {
                if (customer != NULL) customer->showError("Seat already booked: " + seatNumbers[i]);
                return NULL;
            }

            selectedSeats.push_back(seat);
        }

        // Reserve seats
        for (size_t i = 0; i < selectedSeats.size(); i++) {
            selectedSeats[i]->bookSeat();
        }

        double total = priceCalculator.calculateTotal(selectedSeats);
        cout << "\nTotal Amount: Rs." << total << endl;

        bool paid = makePayment(payment, total);

        if (!paid) {
            for (size_t i = 0; i < selectedSeats.size(); i++)
                selectedSeats[i]->cancelSeat();

            if (customer != NULL) customer->showError("Payment failed, booking not confirmed");
            return NULL;
        }

        Booking* booking = createBooking(customer, show, selectedSeats, total);
        booking->confirm();
        bookings.push_back(booking);

        ticketPrinter.printTicket(booking);

        if (customer != NULL) customer->showTicket();

        return booking;
    }

    void bookTicket() {
        cout << "[BookingService] bookTicket() invoked.\n";
    }

    void cancelBooking(string id) {
        for (size_t i = 0; i < bookings.size(); i++) {
            if (bookings[i]->getBookingId() == id) {
                if (bookings[i]->getStatus() == BOOKING_CONFIRMED) {
                    bookings[i]->cancel();
                    cout << "Booking " << id << " cancelled successfully.\n";
                    cout << "Seats are AVAILABLE again.\n";
                } else {
                    cout << "Booking cannot be cancelled. Current status: " << bookings[i]->getStatus() << endl;
                }
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }
};

#endif