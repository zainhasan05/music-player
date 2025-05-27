#include "Song.h"
#include "play_liste.h"
#include <iostream>
#include <string>

using namespace std;

#ifndef ARTIST_H
#define ARTIST_H

class Artist {
	string name_artist;
	int albumsCount;
	int songsCount;
    
public:
    play_list songsList;
	Artist();
	Artist(string name_artist, int albumsCount, int songsCount, play_list songsList);
	void show_profile();
    string getname() {
        return name_artist;
    }
    void setname_artist(string name_artist) {
        this->name_artist = name_artist;
    }
    void setalbumsCount(int albumsCount) {
        this->albumsCount = albumsCount;
    }
    void setsongsCount(int songsCount) {
        this->songsCount = songsCount;
    }

};


#endif

#ifndef ARTIST_LIST
#define ARTIST_LIST
class ANode {
public:
    Artist artist;
    ANode* next;
    ANode* prev;
    ANode(Artist artist) : artist(artist), next(nullptr), prev(nullptr) {}
};

class Artist_list {
public:
    string AName;
    ANode* head;
    int num_of_Artist;
    ANode* tail;

    Artist_list();
    Artist_list(string AName);

    void addArtist(Artist artist);
    void print_Artist_List();
    void removeArtist(string name);
};
#endif