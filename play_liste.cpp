#include "play_liste.h"
#include "Song.h"

play_list::play_list() {
    this->head = this->tail = nullptr;
    this->num_of_Song = 0;
    this->Name = "";

}

play_list :: play_list(string Name) {
    this->head = this->tail = nullptr;
    this->num_of_Song = 0;
    this->Name = Name;
}

void play_list::addSong(Song song) {
    Node* tmp = new Node(song);

    if (this->head == nullptr) {
        this->head = tmp;
        this->tail = tmp;
    }
    else {
        this->tail->next = tmp;
        tmp->prev = this->tail;
        this->tail = tmp;
    }

    this->num_of_Song++;
}

void play_list::removeSong(string title) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->song.title != title) {
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
    num_of_Song--; 
}

void play_list::printList() {
    Node* tmp = head;
    while (tmp != nullptr) {
        tmp->song.showSong();
        tmp = tmp->next;
    }
}