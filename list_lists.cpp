#include "list_lists.h"

list_lists ::list_lists(){
    this->head = this->tail = nullptr;
    this->num_of_list = 0;
    this->NameL = "";

}


list_lists::list_lists(string NameL) {
    this->head = this->tail = nullptr;
    this->num_of_list = 0;
    this->NameL = NameL;
}

void list_lists::addlist(play_list list) {
    LNode* newLNode = new LNode(list);

    if (this->head == nullptr) {
        this->head = newLNode;
        this->tail = newLNode;
    }
    else {
        this->tail->next = newLNode;
        newLNode->prev = this->tail;
        this->tail = newLNode;
    }

    this->num_of_list++;
}

void list_lists::removelist(string Name) {
    LNode* Lcurrent = head;
    LNode* Lprevious = nullptr;

    while (Lcurrent != nullptr && Lcurrent->list.Name != Name) {
        Lprevious = Lcurrent;
        Lcurrent = Lcurrent->next;
    }

    if (Lcurrent == nullptr) {
        cout << "List not found!" << endl;
        return;
    }

    if (Lprevious == nullptr) {
        head = Lcurrent->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    }
    else {
        Lprevious->next = Lcurrent->next;
        if (Lcurrent == tail) {
            tail = Lprevious;
        }
    }

    delete Lcurrent;
    num_of_list--;
}

void list_lists::printLists() {
    LNode* newLNode = head;
    while (newLNode != nullptr) {
        newLNode->list.Name;
        cout << newLNode->list.Name << endl;
        newLNode = newLNode->next;
    }
}