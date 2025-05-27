#include "Artist.h"

Artist::Artist() {
	this->name_artist = "";
	this->albumsCount = 0;
	this->songsCount = 0;
	this->songsList;
}

Artist::Artist(string name_artist, int albumsCount, int songsCount, play_list songsList) {
	this->name_artist = name_artist;
	this->albumsCount = albumsCount;
	this->songsCount = songsCount;
	this->songsList=songsList;
	this->songsList.Name = name_artist + " songs";
}

void Artist::show_profile() {
	cout << "name artist : " << name_artist << " , albumsCount : " << albumsCount << " , songsCount : " << songsCount << " .\n";
	songsList.printList();
}

Artist_list::Artist_list() {
    this->head = this->tail = nullptr;
    this->num_of_Artist = 0;
    this->AName = "";

}

Artist_list::Artist_list(string AName) {
    this->head = this->tail = nullptr;
    this->num_of_Artist = 0;
    this->AName = AName;
}

void Artist_list::addArtist(Artist artist) {
    ANode* tmp = new ANode(artist);

    if (this->head == nullptr) {
        this->head = tmp;
        this->tail = tmp;
    }
    else {
        this->tail->next = tmp;
        tmp->prev = this->tail;
        this->tail = tmp;
    }

    this->num_of_Artist++;
}

void Artist_list::removeArtist(string name) {
    ANode* current = head;
    ANode* previous = nullptr;

    while (current != nullptr && current->artist.getname() != name) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Song not found!" << endl;
        return;
    }

    if (previous == nullptr) {
        head = current->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    }
    else {
        previous->next = current->next;
        if (current == tail) {
            tail = previous;
        }
    }

    delete current;
    num_of_Artist--;
}

void Artist_list::print_Artist_List() {
    ANode* tmp = head;
    while (tmp != nullptr) {
        
        tmp->artist.show_profile();
        cout << endl;
        tmp->artist.songsList.printList();
        tmp = tmp->next;
    }
}

