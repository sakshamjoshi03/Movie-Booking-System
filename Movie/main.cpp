#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Types.h"
#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "PaymentTypes.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"
#include "MainMenu.cpp"

int main() {
    // 1. Initialize Cinema & Screens
    Cinema cinema("PVR Cinema");

    Screen screen1(1);
    screen1.addSeat(Seat("A1", SEAT_TYPE_SILVER));
    screen1.addSeat(Seat("A2", SEAT_TYPE_SILVER));
    screen1.addSeat(Seat("B1", SEAT_TYPE_GOLD));
    screen1.addSeat(Seat("B2", SEAT_TYPE_GOLD));
    screen1.addSeat(Seat("C1", SEAT_TYPE_PLATINUM));
    screen1.addSeat(Seat("C2", SEAT_TYPE_PLATINUM));

    cinema.addScreen(screen1);
    cinema.listMovies();

    // 2. Initialize Movies
    Movie movie1("The Legends", "English", 170);
    Movie movie2("Hanuman", "Hindi", 159);

    // 3. Initialize Shows
    Show show1(&movie1, &cinema.getScreens()[0], "06:00 PM");
    Show show2(&movie1, &cinema.getScreens()[0], "09:00 PM");

    // 4. Initialize Customer & Booking Service
    Customer customer("Pulkit", "9876543210");

    BookingService service(&cinema);
    service.addMovie(&movie1);
    service.addMovie(&movie2);
    service.addShow(&show1);
    service.addShow(&show2);

    // 5. Initialize & Launch MainMenu
    MainMenu menu(&service, &customer);
    menu.setMovies(service.getAllMovies());
    menu.setShows(vector<Show*>{ &show1, &show2 });

    menu.run();

    return 0;
}