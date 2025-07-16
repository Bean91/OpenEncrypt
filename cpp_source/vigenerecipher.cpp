#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using std::cout, std::cin, std::endl;

std::string sanitizeKey(const std::string& key) {
    std::string clean = "";
    for (char c : key) {
        if (std::isalpha(c)) {
            clean += std::tolower(c);
        }
    }
    return clean;
}

std::string encode(const std::string& key, const std::string& message) {
    std::string vec_key;
    int key_len = key.length();
    int msg_len = message.length();

    for (int i = 0, j = 0; i < msg_len; ++i) {
        if (std::isalpha(message[i])) {
            vec_key += key[j % key_len];
            ++j;
        } else {
            vec_key += ' ';
        }
    }

    std::string encoded = "";

    for (int i = 0; i < msg_len; ++i) {
        char p = message[i];
        char k = vec_key[i];

        if (std::isalpha(p)) {
            char base = std::isupper(p) ? 'A' : 'a';
            int shifted = ((std::tolower(p) - 'a') + (k - 'a')) % 26;
            encoded += base + shifted;
        } else {
            encoded += p;
        }
    }

    return encoded;
}

std::string decode(const std::string& key, const std::string& message) {
    std::string vec_key;
    int key_len = key.length();
    int msg_len = message.length();

    for (int i = 0, j = 0; i < msg_len; ++i) {
        if (std::isalpha(message[i])) {
            vec_key += key[j % key_len];
            ++j;
        } else {
            vec_key += ' ';
        }
    }

    std::string decoded = "";

    for (int i = 0; i < msg_len; ++i) {
        char p = message[i];
        char k = vec_key[i];

        if (std::isalpha(p)) {
            char base = std::isupper(p) ? 'A' : 'a';
            int shifted = ((std::tolower(p) - 'a') - (k - 'a') + 26) % 26;
            decoded += base + shifted;
        } else {
            decoded += p;
        }
    }

    return decoded;
}

int main() {
    cout << "Welcome to the Vigenère Cipher Utilities!" << endl << "Would you like to (e)ncode or (d)ecode?" << endl;
    char choose;
    cin >> choose;
    choose = std::tolower(choose);
    if (choose == 'e') {
        cout << "You chose to encode." << endl << "Please enter your key (one word, letters only): ";
        std::string key;
        cin >> key;
        key = sanitizeKey(key);
        cout << "Please enter your message:" << endl;
        std::string message;
        cin.ignore();
        std::getline(cin, message);
        cout << "Your key: " << key << endl << "Your message:" << endl << message << endl;
        std::string encoded = encode(key, message);
        cout << "Your encoded message: " << endl << encoded << endl;
    } else if (choose == 'd') {
        cout << "You chose to decode." << endl << "Please enter your key (one word, letters only): ";
        std::string key;
        cin >> key;
        key = sanitizeKey(key);
        cout << "Please enter your message:" << endl;
        std::string message;
        cin.ignore();
        std::getline(cin, message);
        cout << "Your key: " << key << endl << "Your message:" << endl << message << endl;
        std::string decoded = decode(key, message);
        cout << "Your decoded message: " << endl << decoded << endl;
    } else {
        cout << "You didn't choose one of the options. Goodbye.";
    }

    return 0;
}
