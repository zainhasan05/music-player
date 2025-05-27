#include "Admin.h"
#include "Song.h"
#include <iostream>
#include <string>

using namespace std;

Admin:: Admin (string username, string password) {
	this->username = username;
	this->password = password;
}

void Admin :: set_username(string x) {
	username = x;
}
void Admin :: set_password(string x) {
	password = x;
}

string Admin :: getusername() { 
	return username;
}
string Admin :: getpassword() {
	return password; 
}

Song Admin :: createSong(string title, string artist, int releaseYear, string genre) { //admin in main will create song
	 Song newSong(title, artist, releaseYear, genre);
	 return newSong;
};

