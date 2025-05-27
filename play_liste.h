#include <iostream>
#include <string>
#include "Song.h"

using namespace std;

#ifndef PLAY_H
#define PLAY_H

class Node {
public: 
    Song song;
    Node* next;
    Node* prev;
    Node(Song song) : song(song), next(nullptr),prev(nullptr) {}
};

class play_list {
public:
    string Name;
    Node* head;
    int num_of_Song;
    Node* tail;

    play_list();
    play_list(string Name);

    void addSong(Song song);
    void printList();
    void removeSong(string title);
};

#endif