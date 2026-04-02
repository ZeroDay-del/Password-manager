#include <iostream>
#include "include/User.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

const string key = "CyberKey";
const string MASTER_PASSWORD = "123";
const string mainAccount = "Default User";

// Trim the Left side of the String
string ltrim(const string &str){
    int start = 0;
    while(start < str.length() && isspace(str[start])){
        start++;
    }
    return str.substr(start);
}

// Trim the right side of the String
string rtrim(const string &str){
    int theEnd = str.length() - 1;

    while(theEnd >= 0 && isspace(str[theEnd])){
        theEnd --;
    }
    return str.substr(0, theEnd + 1);
}

// Trim the both sides of the String
string trim(const string &str){
    return rtrim(ltrim(str));
}



void showMenu() {
    cout << "==================================================\n";
    cout << "                MAIN MENU                         \n";
    cout << "==================================================\n";

    cout << "[1] Add Credential\n";
    cout << "[2] View Credentials\n";
    cout << "[3] Search Credential\n";
    cout << "[4] Change A Site credential\n";
    cout << "[5] Exit\n";

    cout << "--------------------------------------------------\n";
    cout << "Select Option: ";
}



// THis function updates the password of the user
bool updatePasswowrd(){
        // Check which credential first
        string website;
        bool status = false;

        cout << "Enter Website To change its credentials: ";
        cin >> website;

        ifstream file("manager.txt");
        string line;

        cout << "Website | Username | Password" << endl;
        cout << " " << endl;

        while (getline(file, line)){
            stringstream ss(line);
             string site, value;
            getline(ss, value, '|');
            site = trim(value);

            if(website.compare(site) == 0){
                status = true;
                cout << "The site you want to change has been found" << endl;
                string newPassword;
                cout << "Enter new password: ";
                cin newPassword;
                break;


            }
        }

        void removeLine(const string &filename){
        ifstream inFile(filename);
        ofstream tempFile("temp.txt");


}
        if(status){
              const string filename = "";
        }

        file.close();
        cout << "The site you want to change not found" << endl;
        return false;

}



// This function displays the message generated at run time //
void loadingEffect(string message) {
    cout << message;
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    cout << endl;
}


bool login() {
    string input;

    cout << "==================================================\n";
    cout << "         Default User PASSWORD MANAGER v1.0             \n";
    cout << "==================================================\n\n";

    for (int attempt = 1; attempt <= 3; attempt++) {
        cout << "Enter Master Password: ";
        cin >> input;

        if (input == MASTER_PASSWORD) {
            loadingEffect("\nAccess Granted");
            cout << "Welcome," << mainAccount << "\n";
            return true;
        } else {
            cout << "Incorrect Password (" << attempt << "/3)\n\n";
        }
    }

    loadingEffect("Too many failed attempts");
    cout << "🚫 Access Denied\n";
    return false;
}


//Rotate bits to the LEFT
// Moves bits left and wraps overflow bits to the right side
unsigned char rotateLeft(unsigned char c, int shift) {
    return (c << shift) | (c >> (8 - shift));
}

// Rotate bits to the RIGHT
// Moves bits right and wraps overflow bits to the left side
unsigned char rotateRight(unsigned char c, int shift) {
    return (c >> shift) | (c << (8 - shift));
}

// This is The ENCRYPTION FUNCTION
// Combines XOR, bit rotation, and position-based mixing
string encrypt(const string &text, const string &key) {
    string result = text;

    for (int i = 0; i < text.size(); i++) {
            // Convert characters to unsigned to avoid negative values
        unsigned char t = static_cast<unsigned char>(text[i]);
        unsigned char k = static_cast<unsigned char>(key[i % key.size()]);

        unsigned char x = t ^ k; // XOR with key
        x = rotateLeft(x, 3); // will have to rotate the bits to the left
        x = static_cast<unsigned char>(x + (i % 7)); // will then have to add position-based variation

        result[i] = static_cast<char>(x); //store the char
    }

    return result;
}

// DECRYPTION FUNCTION
// Reverses all encryption steps in reverse order
string decrypt(const string &text, const string &key) {
    string result = text;

    for (int i = 0; i < text.size(); i++) {
        unsigned char t = static_cast<unsigned char>(text[i]);
        unsigned char k = static_cast<unsigned char>(key[i % key.size()]);

        unsigned char x = static_cast<unsigned char>(t - (i % 7));
        x = rotateRight(x, 3);
        x = x ^ k;

        result[i] = static_cast<char>(x);
    }

    return result;
}

string toHex(const string& input) {
    stringstream ss;

    for (unsigned char c : input) {
        ss << hex << setw(2) << setfill('0') << (int)c;
    }

    return ss.str();
}

string fromHex(const string& hex) {
    string result;

    for (int i = 0; i < hex.length(); i += 2) {
        string byte = hex.substr(i, 2);
        char chr = (char) strtol(byte.c_str(), nullptr, 16);
        result += chr;
    }

    return result;
}

int main()
{
    login();
    bool status = true;


    while(status){
        showMenu();

        string option;
        cin >> option;

        if(option == "1"){
            string website;
            string username;
            string password;

            cout << "Name of Website: ";
            cin >> website;

            cout << "Enter username: ";
            cin >> username;

            cout << "Enter password: ";
            cin >> password;

            string encrypted = toHex(encrypt(password, key));

            User* newUser = new User(username, encrypted, website);
            ofstream file("manager.txt", ios::app);

            file << newUser->publish();

            file.close();
            delete newUser;

        }else if(option == "2"){
            ifstream file("manager.txt");
            string line;

            cout << "Website | Username | Password" << endl;
            cout << " " << endl;

            while (getline(file, line)){
                cout << line << endl;
            }

            file.close();

        }else if(option == "5"){
            exit(0);

        }else if(option == "3"){
            string searchWeb;
            cout << " " << endl;
            cout << "Enter Website Name: ";
            cin >> searchWeb;

            ifstream file("manager.txt");
            string line;

            bool check = false;

            while (getline(file, line)){
                stringstream ss(line);
                string website, username, password;

                getline(ss, website, '|');
                website = trim(website);

                if(website == searchWeb){
                    cout << "Credentials have been found" << endl;
                    cout << " " << endl;

                    getline(ss, username, '|');
                    getline(ss, password, '|');

                    string decrypted = decrypt(fromHex(trim(password)), key);

                    User* user = new User(trim(username), decrypted, website);
                    user->display();

                    delete user;

                    cout << " " << endl;
                    check = true;
                    file.close();
                }
            }

            file.close();

            if(check == false){
                cout << "Credentials Not Found!" << endl;
            }
        }else if(option == "4"){
            updatePasswowrd();
        }
    }

    return 0;
}
