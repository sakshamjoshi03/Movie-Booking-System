#ifndef CINEMA_CPP
#define CINEMA_CPP

#include <iostream>
#include <vector>
#include <string>
#include "Screen.cpp"
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens;

public:
    Cinema(string n = "") {
        name = n;
    }

    void addScreen(Screen screen) {
        screens.push_back(screen);
    }

    vector<Screen>& getScreens() {
        return screens;
    }

    string getName() const {
        return name;
    }

    void listMovies() const {
        cout << "Cinema: " << name << " - Screening movies across " << screens.size() << " screen(s).\n";
    }
};

#endif