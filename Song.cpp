#include "Song.h"

Song::Song(string title, string artist, int releaseYear, string genre) {
    this->title = title;
    this->artist = artist;
    this->releaseYear = releaseYear;
    this->genre = genre;
}

void Song::showSong() {
    cout << "Title: " << title << ", Artist: " << artist << ", Release Year: " << releaseYear << ", Genre: " << genre << endl;
}
