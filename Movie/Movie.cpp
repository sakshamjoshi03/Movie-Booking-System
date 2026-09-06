#ifndef MOVIE_CPP
#define MOVIE_CPP

#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int duration;

public:
    Movie(string t = "", string l = "", int d = 0) {
        title = t;
        language = l;
        duration = d;
    }

    string getTitle() const {
        return title;
    }

    string getLanguage() const {
        return language;
    }

    int getDuration() const {
        return duration;
    }
};

#endif