#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using std::cout, std::cin, std::endl;

std::string encode(const std::string& key, const std::string& message) {
    std::string encoded = "";

    for (char p : message) {
        if (std::isalpha(p)) {
            bool isupper = std::isupper(p);
            int index = std::tolower(p) - 'a';
            char mapped = key[index];
            encoded += isupper ? static_cast<char>(std::toupper(mapped)) : mapped;
        } else {
            encoded += p;
        }
    }

    return encoded;
}

std::string decode(const std::string& key, const std::string& message) {
    std::string decoded = "";
    std::string lower_key = key;
    std::transform(lower_key.begin(), lower_key.end(), lower_key.begin(), ::tolower);
    std::vector<char> reverse_map(26);
    for (int i = 0; i < 26; ++i) {
        reverse_map[lower_key[i] - 'a'] = 'a' + i;
    }
    for (char c : message) {
        if (std::isalpha(c)) {
            bool is_upper = std::isupper(c);
            char lower_c = std::tolower(c);
            char decoded_char = reverse_map[lower_c - 'a'];
            decoded += is_upper ? static_cast<char>(std::toupper(decoded_char)) : decoded_char;
        } else {
            decoded += c;
        }
    }
    return decoded;
}

int main() {
    cout << "Welcome to the Substitution Cipher Utilities!" << endl
         << "Would you like to (e)ncode or (d)decode?" << endl;
    char choose;
    cin >> choose;
    choose = std::tolower(choose);

    if (choose == 'e') {
        cout << "You chose to encode." << endl
             << "Please enter your key (26 letters in order): ";
        std::string key;
        cin.ignore();
        std::getline(cin, key);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        bool valid_key = key.size() == 26 &&
                         std::all_of(key.begin(), key.end(), ::isalpha) &&
                         std::unique(key.begin(), key.end()) == key.end();

        if (!valid_key) {
            cout << "Invalid key! Key must be 26 unique alphabetical letters." << endl;
            return 1;
        }

        cout << "Please enter your message:" << endl;
        std::string message;
        std::getline(cin, message);

        cout << "Your key: " << key << endl
             << "Your message:\n" << message << endl;

        std::string encoded = encode(key, message);
        cout << "Your encoded message:\n" << encoded << endl;

    } else if (choose == 'd') {
        cout << "You chose to decode." << endl
             << "Please enter your key (26 letters in order): ";
        std::string key;
        cin.ignore();
        std::getline(cin, key);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        bool valid_key = key.size() == 26 &&
                         std::all_of(key.begin(), key.end(), ::isalpha) &&
                         std::unique(key.begin(), key.end()) == key.end();

        if (!valid_key) {
            cout << "Invalid key! Key must be 26 unique alphabetical letters." << endl;
            return 1;
        }

        cout << "Please enter your message:" << endl;
        std::string message;
        std::getline(cin, message);

        cout << "Your key: " << key << endl
             << "Your message:\n" << message << endl;

        std::string decoded = decode(key, message);
        cout << "Your decoded message:\n" << decoded << endl;

    } else {
        cout << "You didn't choose one of the options. Goodbye." << endl;
    }

    return 0;
}
