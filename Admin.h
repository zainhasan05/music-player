#include <iostream>
#include<string>
#include "Song.h"

using namespace std;

#ifndef ADMIN_H
#define ADMIN_H

class Admin {
private:
	string username;
	string password;
public:
	Admin(string username = "", string password = "");
	void set_username(string x);
	void set_password(string x);

	string getusername();
	string getpassword();

	Song createSong(string title, string artist, int releaseYear, string genre);


};

#endif