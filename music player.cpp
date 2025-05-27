#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Admin.h"
#include "User.h"
#include "play_liste.h"
#include "Song.h"
#include "list_lists.h"
#include "Artist.h"

using namespace std;

bool AdminLogin(Admin admin, string username, string passward) {
	if (admin.getusername() == username && admin.getpassword() == passward) {
		return true;
	}
	return false;
}

bool UserLogin(User_list userList, string username, string password, User& found_User) {

    UNode* current = userList.head; 

    while (current != nullptr) {
        
        if (current->user.getusername() == username && current->user.getpassword() == password) {
            found_User = current->user; 
            return true; 
        }
        current = current->next; 
    }

    return false;
}

Song createSong(const string& title, const string& artist, int releaseYear, const string& genre) {
    return Song(title, artist, releaseYear, genre);
}

Song searchSong(const play_list& playlist, const string& title) {
    Node* current = playlist.head;
    while (current != nullptr) {
        if (current->song.title == title) {
            return current->song;
        }
        current = current->next;
    }
    throw runtime_error("Song not found in this playlist.");
}

Artist findArtistByName(Artist_list& artists_system, const string& name) {
    ANode* current = artists_system.head; 
    while (current != nullptr) {
        if (current->artist.getname() == name) {
            return current->artist; 
        }
        current = current->next; 
    }
    throw runtime_error("artist not found"); 
}

play_list& findPlayListByName(list_lists& lists, const string& name) {
    LNode* current = lists.head;
    while (current != nullptr) {
        if (current->list.Name == name) {
            return current->list;
        }
        current = current->next;
    }
    throw runtime_error("Playlist not found.");
}

void clearCin() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addOrRemoveSongFromPlaylist(play_list& playlist, play_list& allSongs) {
    int choice;
    bool innerLoop = true;
    while (innerLoop) {
        system("cls");
        cout << "Playlist: " << playlist.Name << endl;
        cout << "1- Add song to this playlist.\n";
        cout << "2- Remove song from this playlist.\n";
        cout << "3- Back to main menu.\n";
        cout << "Enter your choice: ";
        cin >> choice;
        clearCin();

        if (choice == 1) {
            system("cls");
            allSongs.printList();
            string titleToAdd;
            cout << "Enter the title of the song to add: ";
            getline(cin, titleToAdd);
            try {
                Song foundSong = searchSong(allSongs, titleToAdd);
                playlist.addSong(foundSong);
                cout << "Added song: " << foundSong.title << " by " << foundSong.artist << " to " << playlist.Name << endl;
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            cout << "Press Enter to continue...";
            cin.get();
        }
        else if (choice == 2) {
            system("cls");
            playlist.printList();
            string titleToRemove;
            cout << "Enter the title of the song to remove: ";
            getline(cin, titleToRemove);
            playlist.removeSong(titleToRemove);
            cout << "Press Enter to continue...";
            cin.get();
        }
        else if (choice == 3) {
            innerLoop = false;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
            cout << "Press Enter to continue...";
            cin.get();
        }
    }
}

void run_play_list(play_list list, int choice, play_list Songs_system) {
    srand((time(0))); // For generating random numbers

    if (choice == 1) {
        // Print songs randomly
        vector<Song> songs;
        Node* current = list.head;
        while (current != nullptr) {
            songs.push_back(current->song);
            current = current->next;
        }

        while (!songs.empty()) {
            int random_index = rand() % songs.size();
            cout << "Song Title: " << songs[random_index].title << endl;

            string user_choice;
            cout << "Do you want to continue? (yes/no): ";
            cin >> user_choice;

            if (user_choice != "yes") {
                break;
            }
            songs.erase(songs.begin() + random_index); // Remove the song that was played
        }
    }
    else if (choice == 2) {
        // Print songs sequentially
        Node* current = list.head;
        if (current == nullptr) {
            cout << "There are no songs in the playlist." << endl;
            return;
        }

        while (true) {
            cout << "Song Title: " << current->song.title << endl;

            string user_choice;
            cout << "Do you want the next or previous song? (next/previous/stop): ";
            cin >> user_choice;

            if (user_choice == "next") {
                current = current->next ? current->next : list.head; // Return to the beginning if at the end
            }
            else if (user_choice == "previous") {
                current = current->prev ? current->prev : list.tail; // Return to the end if at the beginning
            }
            else {
                break; // Stop
            }
        }
    }
    else if (choice == 3) {
        // Print all songs
        list.printList();

        string selected_title;
        cout << "Choose a song title to listen to: ";
        cin >> selected_title;

        bool found = false;
        Node* search_node = Songs_system.head;
        while (search_node != nullptr) {
            if (search_node->song.title == selected_title) {
                found = true;
                break;
            }
            search_node = search_node->next;
        }

        if (!found) {
            throw runtime_error("The song is not available in the system.");
        }

        // If the song is found, start listening to it
        while (true) {
            cout << "Now playing: " << selected_title << endl;

            string user_choice;
            cout << "Do you want to listen to the next song or stop? (next/stop): ";
            cin >> user_choice;

            if (user_choice == "next") {
                search_node = search_node->next ? search_node->next : Songs_system.head; // Return to the beginning if at the end
                cout << "Now playing: " << search_node->song.title << endl; // Print the next song
            }
            else {
                break; // Stop
            }
        }
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

void printSongs_by_artisrname(play_list Songs_System,string artistname){
    Node* tmp = Songs_System.head;
    
    while (tmp != nullptr) {
        if (tmp->song.artist == artistname) {
            tmp->song.showSong();
            cout << endl;
        }
        tmp = tmp->next;
    }

}

void printSongs_by_releaseYear(play_list Songs_System, int x){
    Node* tmp = Songs_System.head;

    while (tmp != nullptr) {
        if (tmp->song.releaseYear == x) {
            tmp->song.showSong();
            cout << endl;
        }
        tmp = tmp->next;
    }
}

void printSongs_by_genre(play_list Songs_System, string genre) {
    Node* tmp = Songs_System.head;

    while (tmp != nullptr) {
        if (tmp->song.genre == genre) {
            tmp->song.showSong();
            cout << endl;
        }
        tmp = tmp->next;
    }

}

void printSongs_by_firstliter(play_list Songs_System,char mychar){
    Node* tmp = Songs_System.head;

    while (tmp != nullptr) {
        if (tmp->song.title[0] == mychar) {
            tmp->song.showSong();
            cout << endl;
        }
        tmp = tmp->next;
    }
}

int main() {

    string username, password;
    bool loggedIn = false;
    bool programRunning = true;
    int A_or_U = 0;

    Admin admin("Zain", "4033");
    User found_User;

    User_list   users_System   ("users_System");
    play_list   Songs_System   ("Songs_System");
    list_lists  lists_System   ("lists_System");
    Artist_list Artists_System ("Artists_System");

    Song song1("title1", "artist1", 2025, "genre1");
    Song song2("title2", "artist2", 2024, "genre2");
    Song song3("title3", "artist3", 2023, "genre3");
    Song song4("title4", "artist4", 2022, "genre4");
    Song song5("title5", "artist5", 2021, "genre5");
    Song song6("title6", "artist6", 2020, "genre6");

    Songs_System.addSong(song1);
    Songs_System.addSong(song2);
    Songs_System.addSong(song3);
    Songs_System.addSong(song4);
    Songs_System.addSong(song5);
    Songs_System.addSong(song6);



    while (programRunning) {
        loggedIn = false; 

        while (!loggedIn) {
            system("cls");
            cout << "Enter your username: ";
            getline(cin, username);
            cout << "Enter your password: ";
            getline(cin, password);

            if (AdminLogin(admin, username, password)) {
                loggedIn = true;
                A_or_U = 1;
            }
            else if(UserLogin(users_System, username, password, found_User)) {
                loggedIn = true;
                A_or_U = 2;

            }
            else {

                int Lchoice;
                cout << "The password or username is unknown. Are you trying to create a new account ?\n";
                cout << "1 - Yes .\n";
                cout << "2 - NO .\n";
                cin >> Lchoice;
                clearCin();

                if (Lchoice == 1) {
                    system("cls");
                    string Xpassword;
                    cout << "enter password agine : ";
                    getline(cin, Xpassword);

                    if (password == Xpassword) {
                        loggedIn = true;
                        A_or_U = 2;

                    }
                    else {
                        cout << "There is no match between the passwords .\n";
                        cout << "system will return you to login page .\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                    }
                }
                else {
                    cout << "system will return you to login page .\n";
                    cout << "Press Enter to continue...";
                    cin.get();
                }

            }
            
        }
        if (A_or_U == 1) {

            int choice;
            bool mainMenu = true;
            while (mainMenu) {
                system("cls");
                cout << "Main Menu:\n";
                cout << "1- Add new Song to system.\n";
                cout << "2- Add new Playlist to system.\n";
                cout << "3- Add new Artist to system.\n";
                cout << "4- Manage Playlist.\n";
                cout << "5- Mandge artists.\n";
                cout << "6- Exit.\n";
                cout << "Enter your choice: ";
                cin >> choice;
                clearCin();

                if (choice == 1) {
                    system("cls");
                    string title, artist, genre;
                    int releaseYear;

                    cout << "Enter title of the new song: ";
                    getline(cin, title);
                    cout << "Enter artist of the new song: ";
                    getline(cin, artist);
                    cout << "Enter release year of the new song: ";
                    cin >> releaseYear;
                    clearCin();
                    cout << "Enter genre of the new song: ";
                    getline(cin, genre);

                    Song newSong = createSong(title, artist, releaseYear, genre);
                    Songs_System.addSong(newSong);
                    cout << "Added song: " << newSong.title << " by " << newSong.artist << " to the system.\n";
                    cout << "Press Enter to continue...";
                    cin.get();

                }
                else if (choice == 2) {
                    system("cls");
                    string playlistName;
                    cout << "Enter name of the new playlist: ";
                    getline(cin, playlistName);

                    play_list newPlaylist(playlistName);
                    lists_System.addlist(newPlaylist);

                    cout << "Created playlist: " << playlistName << endl;
                    addOrRemoveSongFromPlaylist(newPlaylist, Songs_System); 
                    cout << "Press Enter to continue...";
                    cin.get();

                }
                else if (choice == 3) {
                    system("cls");
                    string artistName;
                    cout << "Enter artist name: ";
                    getline(cin, artistName);

                    lists_System.printLists();
                    string listName;
                    cout << "Enter the name of the playlist for this artist: ";
                    getline(cin, listName);

                    try {
                        play_list& foundList = findPlayListByName(lists_System, listName);
                        Artist newArtist(artistName, 0, 0, foundList);
                        Artists_System.addArtist(newArtist);
                        cout << "\nArtist '" << artistName << "' with playlist '" << listName << "' added.\n";
                    }
                    catch (const runtime_error& e) {
                        cout << e.what() << endl;
                    }
                    cout << "Press Enter to continue...";
                    cin.get();

                }
                else if (choice == 4) {
                    system("cls");
                    lists_System.printLists();
                    string playlistToManage;
                    cout << "Enter the name of the playlist to manage: ";
                    getline(cin, playlistToManage);

                    try {
                        play_list& playlist = findPlayListByName(lists_System, playlistToManage);
                        addOrRemoveSongFromPlaylist(playlist, Songs_System); 
                        cout << "prosess acomplashe";
                    }
                    catch (const runtime_error& e) {
                        cout << e.what() << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                    }

                }
                else if (choice == 5) {
                    Artists_System.print_Artist_List();
                    string xstring;
                    cout << "entsr artist name : ";
                    getline(cin, xstring);
                    Artist foundartist = findArtistByName(Artists_System, xstring);
                    cout << "1- chinge name.\n";
                    cout << "2- chinge albumsCount.\n";
                    cout << "3- chinge songsCount.\n";
                    int Lchoice;
                    cin >> Lchoice;
                    clearCin();
                    if (Lchoice == 1) {
                        string zstring;
                        cout << "enter new name : ";
                        getline(cin, zstring);
                        foundartist.setname_artist(zstring);
                        cout << "\nDone.\n";

                    }
                    else if (Lchoice == 2) {
                        cout << "enter new albumsCount : ";
                        int newalbumsCount;
                        cin >> newalbumsCount;
                        clearCin();
                        foundartist.setalbumsCount(newalbumsCount);
                    }
                    else if (Lchoice == 3) {
                        cout << "enter new songsCount : ";
                        int newsongsCount;
                        cin >> newsongsCount;
                        clearCin();
                        foundartist.setalbumsCount(newsongsCount);
                    }
                    else {
                        cout << "invoived choice\n";
                    }

                }
                else if (choice == 6) {
                    mainMenu = false; 
                }
                else {
                    cout << "Invalid choice. Please try again.\n";
                    cout << "Press Enter to continue...";
                    cin.get();
                }

            } // Admin menu  


        } 
        else if (A_or_U == 2) {
            int choice;
            bool mainMenu = true;
            while (mainMenu) {
                system("cls");
                cout << "Main Menu:\n";
                cout << "1- Songs system .\n";
                cout << "2- lists system .\n";
                cout << "3- show favoriteSongs .\n";
                cout << "4- show seved_Songs .\n";
                cout << "5- show your favorite lists .\n";
                cout << "6- show your play lists .\n";
                cout << "7- run play list .\n";
                cout << "8- show artists .\n";
                cout << "9- serche in Song .\n";
                cout << "10- Exit.\n";

                cout << "Enter your choice: ";
                cin >> choice;
                clearCin();

                if (choice == 1) {
                    system("cls");
                    Songs_System.printList();

                    int Lchoice;

                    cout << "would you want to add Song to your play lists .\n";
                    cout << "1- favoriteSongs .\n";
                    cout << "2- seved_Songs .\n";
                    cout << "3- No .\n";
                    cin >> Lchoice;
                    clearCin();
                    if (Lchoice == 1|| Lchoice == 2) {

                        string xstring;
                        cout << "enter Song title :";
                        getline(cin, xstring);

                        try {
                            Song found_Sond = searchSong(Songs_System, xstring);

                            if (Lchoice == 1) {

                                found_User.addSongToPlaylist(found_User.favoriteSongs, found_Sond);
                                cout << "song added\n";

                            }
                            else if (Lchoice == 2) {

                                found_User.addSongToPlaylist(found_User.seved_Songs, found_Sond);

                            }
                            else {
                                cout << "system will return you to Main Menu .\n";
                                cout << "Press Enter to continue...";
                                cin.get();
                            }

                        }
                        catch (const runtime_error& e) {
                            cout << e.what() << endl;
                            cout << "Press Enter to continue...";
                            cin.get();
                        }


                    }
                    else {

                        cout << "system will return you to Main Menu .\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                    }
                }
                else if (choice == 2) {

                    system("cls");

                    lists_System.printLists();
                    string xstring;
                    cout << "enter name of list : ";
                    getline(cin, xstring);
                    try {
                        play_list found_playlist = findPlayListByName(lists_System, xstring);
                        found_playlist.printList();

                        int Lchoice;
                        cout << "\nwould you want to add this play list to your play lists .\n";
                        cout << "1- favorite_lists .\n";
                        cout << "2- playlists .\n";
                        cout << "3- No .\n";
                        cin >> Lchoice;
                        clearCin();

                        if (Lchoice == 1) {
                            found_User.addListToplaylists(found_User.favorite_lists, found_playlist);
                            cout << "list added";
                        }
                        else if (Lchoice == 2) {
                            found_User.addListToplaylists(found_User.playlists, found_playlist);
                            cout << "list added";
                        }
                        else {
                            cout << "system will return you to Main Menu .\n";
                            cout << "Press Enter to continue...";
                            cin.get();
                        }
                    }
                    catch (const runtime_error& e) {
                        cout << e.what() << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                    }


                }
                else if (choice == 3) {

                    found_User.favoriteSongs.printList();

                    cout << "\nwould you want remove song .\n";
                    cout << "1- Yes .\n";
                    cout << "2- No .\n";

                    int Lchoice;
                    cin >> Lchoice;
                    clearCin();

                    if (Lchoice == 1) {
                        string xstring;
                        cout << "enter Song title :";
                        getline(cin, xstring);

                        found_User.removeSongFromPlaylist(found_User.favoriteSongs, xstring);
                        cout << "removed\n";

                    }
                    
                        cout << "system will return you to Main Menu .\n";
                        cout << "Press Enter to continue...";
                        cin.get();

                    


                }
                else if (choice == 4) {

                    found_User.seved_Songs.printList();

                    cout << "\nwould you want remove song .\n";
                    cout << "1- Yes .\n";
                    cout << "2- No .\n";

                    int Lchoice;
                    cin >> Lchoice;
                    clearCin();

                    if (Lchoice == 1) {
                        string xstring;
                        cout << "enter Song title :";
                        getline(cin, xstring);

                        found_User.removeSongFromPlaylist(found_User.seved_Songs, xstring);
                        cout << "removed\n";

                    }
                    else {
                        cout << "system will return you to Main Menu .\n";
                        cout << "Press Enter to continue...";
                        cin.get();

                    }

                }
                else if (choice == 5) {
                    found_User.favorite_lists.printLists();

                    cout << "\nwould you want remove song .\n";
                    cout << "1- Yes .\n";
                    cout << "2- No .\n";

                    int Lchoice;
                    cin >> Lchoice;
                    clearCin();

                    if (Lchoice == 1) {
                        string xstring;
                        cout << "enter list name  :";
                        getline(cin, xstring);

                        found_User.removeListFrom_Playlists(found_User.favorite_lists, xstring);
                        cout << "removed\n";

                    }
                    cout << "system will return you to Main Menu .\n";
                    cout << "Press Enter to continue...";
                    cin.get();

                    


                }
                else if (choice == 6) {

                    found_User.playlists.printLists();

                    cout << "\nwould you want remove list .\n";
                    cout << "1- Yes .\n";
                    cout << "2- No .\n";

                    int Lchoice;
                    cin >> Lchoice;
                    clearCin();

                    if (Lchoice == 1) {
                        string xstring;
                        cout << "enter list name  :";
                        getline(cin, xstring);

                        found_User.removeListFrom_Playlists(found_User.playlists, xstring);
                        cout << "removed\n";

                    }
                    else {
                        cout << "system will return you to Main Menu .\n";
                        cout << "Press Enter to continue...";
                        cin.get();

                    }

                } //User menu
                else if (choice == 7) {
                    cout << "chose from your lists .\n";

                    cout << Songs_System.Name << endl;
                    cout << found_User.favoriteSongs.Name << endl;
                    cout << found_User.seved_Songs.Name << endl;
                    found_User.favorite_lists.printLists();

                    string xstring;
                    cout << "enter list name .";
                    getline(cin, xstring);

                    cout << "chose why run for play list .\n";

                    cout << "1- random\n";
                    cout << "2- sequential\n";
                    cout << "3- repeat one\n";
                    int Lchoice;
                    cin >> Lchoice;

                    try {
                        play_list found_list = findPlayListByName(lists_System, xstring);

                        try {
                            run_play_list(found_list, Lchoice, Songs_System);

                        }
                        catch (const runtime_error& e) {
                            cout << e.what() << endl;
                            cout << "Press Enter to continue...";
                            cin.get();
                        }

             
                    }
                    catch (const runtime_error& e) {
                        cout << e.what() << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                    }

                }
                else if (choice == 8) {
                    system("cls");
                    Artists_System.print_Artist_List();

                }
                else if (choice == 9){
                    system("cls");
                    cout << "1- by artist name .\n";
                    cout << "2- by releaseYear .\n";
                    cout << "3- by genre .\n";
                    cout << "4- by liter .\n";
                    int Lchoice;
                    cin >> Lchoice;
                    clearCin();
                    if(Lchoice == 1){
                        cout << "enter artist name : ";
                        string xstring;
                        getline(cin, xstring);
                        
                        printSongs_by_artisrname(Songs_System, xstring);
                    }
                    else if(Lchoice == 2){
                        cout << "entsr releaseYear .\n";
                        int LreleaseYear;
                        cin >> LreleaseYear;
                        clearCin();
                        printSongs_by_releaseYear(Songs_System, LreleaseYear);
                    }
                    else if(Lchoice == 3){
                        cout << "enter Song genre .\n";
                        string xstring;
                        getline(cin, xstring);
                        printSongs_by_genre(Songs_System, xstring); 
                    }
                    else if(Lchoice == 4){
                        cout << "enter first liter Songs : ";
                        char mychar;
                        cin >> mychar;
                        clearCin();
                        printSongs_by_firstliter(Songs_System, mychar);
                    
                    }
                    else {
                        cout << "involved choise .\n";
                    }
                    cout << "\nsystem will return you to Main Menu .\n";
                    cout << "Press Enter to continue...";
                    cin.get();
                }
                else if (choice == 10){
                mainMenu = false;
                }
                else {
                cout << "Invalid choice. Please try again.\n";
                cout << "Press Enter to continue...";
                cin.get();
                
}
                
            } // A_or_U
        }

    }//run while
    return 0;
}//main