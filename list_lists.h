#include <iostream>
#include <string>
#include "play_liste.h"

using namespace std;

#ifndef LNODE_H
#define LNODE_H
class LNode {
public:
    play_list list;
    LNode* next;
    LNode* prev;
    LNode(play_list list) : list(list), next(nullptr), prev(nullptr) {}
};

class list_lists {
public:
    string NameL;
    LNode* head;
    int num_of_list;
    LNode* tail;

    list_lists();
    list_lists(string NameL);

    void addlist(play_list list);
    void printLists();
    void removelist(string Name);
};

#endif