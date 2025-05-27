#include "Song.h"
#include "play_liste.h"
#include "list_lists.h"
#include <iostream>
#include <string>

using namespace std;

#ifndef USER_H
#define USER_H

class User {
private:
	string username;
	string password;
public:
	list_lists favorite_lists;
	list_lists playlists;
	play_list favoriteSongs;
	play_list seved_Songs;

	User();
	User(string username,string password);

	string getusername();
	string getpassword();

	void addSongToPlaylist(play_list list, Song Asong);
	void removeSongFromPlaylist(play_list list, string title);

	void addListToplaylists(list_lists lists, play_list newlist);
	void removeListFrom_Playlists(list_lists lists, string Name);

};

#endif

#ifndef User_list_H
#define User_list_H

class UNode {
public:
	User user;
	UNode* next;
	UNode* prev;
	UNode(User user) : user(user), next(nullptr), prev(nullptr) {}
};
class User_list {
public:
	string UName;
	UNode* head;
	int num_of_Users;
	UNode* tail;

	User_list();
	User_list(string UName);

	void addUser(User user);
	//void print_Artist_List();
	//void removeArtist(string Nname);
};

#endif