#include <iostream>
#include <string>

using namespace std;
#ifndef SONH_H
#define SONH_H
class Song {
public:
    string title;
    string artist;
    int releaseYear;
    string genre;

    Song(string title = "", string artist = "", int releaseYear = 0, string genre = "");
    void showSong();
};
#endif // !SONH_H