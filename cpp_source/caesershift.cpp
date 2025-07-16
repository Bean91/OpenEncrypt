#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using std::cout, std::cin, std::endl;

std::string encode(const char& key, const std::string& message) {
    std::string encoded = "";
    int shift = std::tolower(key) - 'a';

    for (char p : message) {
        if (std::isalpha(p)) {
            char base = std::isupper(p) ? 'A' : 'a';
            int shifted = ((p - base) + shift) % 26;
            encoded += base + shifted;
        } else {
            encoded += p;
        }
    }

    return encoded;
}

std::string decode(const char& key, const std::string& message) {
    std::string decoded = "";
    int shift = std::tolower(key) - 'a';

    for (char p : message) {
        if (std::isalpha(p)) {
            char base = std::isupper(p) ? 'A' : 'a';
            int shifted = ((p - base) - shift + 26) % 26;
            decoded += base + shifted;
        } else {
            decoded += p;
        }
    }

    return decoded;
}

int main() {
    cout << "Welcome to the Caesar Shift Utilities!" << endl
         << "Would you like to (e)ncode or (d)ecode?" << endl;
    char choose;
    cin >> choose;
    choose = std::tolower(choose);

    if (choose == 'e') {
        cout << "You chose to encode." << endl
             << "Please enter your key (one letter): ";
        char key;
        cin >> key;

        cout << "Please enter your message:" << endl;
        std::string message;
        cin.ignore();
        std::getline(cin, message);

        key = std::tolower(key);
        cout << "Your key: " << key << endl
             << "Your message:\n" << message << endl;

        std::string encoded = encode(key, message);
        cout << "Your encoded message:\n" << encoded << endl;

    } else if (choose == 'd') {
        cout << "You chose to decode." << endl
             << "Please enter your key (one letter): ";
        char key;
        cin >> key;

        cout << "Please enter your message:" << endl;
        std::string message;
        cin.ignore();
        std::getline(cin, message);

        key = std::tolower(key);
        cout << "Your key: " << key << endl
             << "Your message:\n" << message << endl;

        std::string decoded = decode(key, message);
        cout << "Your decoded message:\n" << decoded << endl;

    } else {
        cout << "You didn't choose one of the options. Goodbye." << endl;
    }

    return 0;
}
