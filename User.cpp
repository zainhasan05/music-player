#include "User.h"
#include "play_liste.h"
#include "Song.h"


using namespace std;

User::User() {
	this->username = "";
	this->password = "";
	this->favoriteSongs;
	this->playlists;
}

User::User(string username, string password) {
	this->username = username;
	this->password = password;
	this->favoriteSongs;
	this->playlists;
}

string User::getusername() {
	return username;
}
string User::getpassword() {
	return password;
}

void User::addSongToPlaylist(play_list list,Song Asong) {
	list.addSong(Asong);
}

void User::removeSongFromPlaylist(play_list list, string title) {
	list.removeSong(title);
}

User_list::User_list() {
	this->head = this->tail = nullptr;
	this->num_of_Users= 0;
	this->UName = "";

}

User_list::User_list(string UName) {
	this->head = this->tail = nullptr;
	this->num_of_Users = 0;
	this->UName = UName;
}

void User_list::addUser(User user) {
	UNode* tmp = new UNode(user);

	if (this->head == nullptr) {
		this->head = tmp;
		this->tail = tmp;
	}
	else {
		this->tail->next = tmp;
		tmp->prev = this->tail;
		this->tail = tmp;
	}

	this->num_of_Users++;
}

void User::addListToplaylists(list_lists lists,play_list newlist) {
	lists.addlist(newlist);
}

void User::removeListFrom_Playlists(list_lists lists, string Name) {
	lists.removelist(Name);
}
