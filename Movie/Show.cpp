#ifndef SHOW_CPP
#define SHOW_CPP

#include <iostream>
#include <vector>
#include <string>
#include "Movie.cpp"
#include "Screen.cpp"
#include "ShowSeat.cpp"
using namespace std;

class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(Movie* m = NULL, Screen* s = NULL, string time = "") {
        movie = m;
        screen = s;
        startTime = time;

        if (screen != NULL) {
            for (size_t i = 0; i < screen->getSeats().size(); i++) {
                showSeats.push_back(ShowSeat(&screen->getSeats()[i]));
            }
        }
    }

    Movie* getMovie() const {
        return movie;
    }

    Screen* getScreen() const {
        return screen;
    }

    string getStartTime() const {
        return startTime;
    }

    vector<ShowSeat>& getShowSeats() {
        return showSeats;
    }

    void displaySeats() const {
        for (size_t i = 0; i < showSeats.size(); i++) {
            cout << showSeats[i].getSeat()->getNumber();
            if (showSeats[i].isAvailable())
                cout << "[ ] ";
            else
                cout << "[X] ";
        }
        cout << endl;
    }

    // Alias for backward compatibility
    void showSeatsLayout() const {
        displaySeats();
    }

    vector<ShowSeat*> getAvailableSeats() {
        vector<ShowSeat*> available;
        for (size_t i = 0; i < showSeats.size(); i++) {
            if (showSeats[i].isAvailable()) {
                available.push_back(&showSeats[i]);
            }
        }
        return available;
    }

    ShowSeat* findSeat(string number) {
        for (size_t i = 0; i < showSeats.size(); i++) {
            if (showSeats[i].getSeat()->getNumber() == number)
                return &showSeats[i];
        }
        return NULL;
    }

    bool bookSeat(string seatNumber) {
        ShowSeat* s = findSeat(seatNumber);
        if (s != NULL && s->isAvailable()) {
            return s->bookSeat();
        }
        return false;
    }

    void releaseSeat(string seatNumber) {
        ShowSeat* s = findSeat(seatNumber);
        if (s != NULL) {
            s->cancelSeat();
        }
    }
};

#endif