#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <utility>
#include <numeric>

using std::cout, std::cin, std::endl;

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; ++x)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

std::string encode(const std::pair<int, int>& key, const std::string& message) {
    std::string encoded = "";
    int a = key.first, b = key.second;

    for (char p : message) {
        if (std::isalpha(p)) {
            bool is_upper = std::isupper(p);
            char base = is_upper ? 'A' : 'a';
            int x = p - base;
            int shifted = (a * x + b) % 26;
            encoded += base + shifted;
        } else {
            encoded += p;
        }
    }

    return encoded;
}

std::string decode(const std::pair<int, int>& key, const std::string& message) {
    std::string decoded = "";
    int a = key.first, b = key.second;
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        return 2;
    }

    for (char p : message) {
        if (std::isalpha(p)) {
            bool is_upper = std::isupper(p);
            char base = is_upper ? 'A' : 'a';
            int y = p - base;
            int x = (a_inv * (y - b + 26)) % 26;
            decoded += base + x;
        } else {
            decoded += p;
        }
    }

    return decoded;
}

int main() {
    cout << "Welcome to the Affine Cipher Utilities!" << endl
         << "Would you like to (e)ncode or (d)ecode?" << endl;
    char choose;
    cin >> choose;
    choose = std::tolower(choose);

    int a, b;
    cout << "Please enter your key as two integers (a b): ";
    cin >> a >> b;
    std::pair<int, int> key = {a, b};

    if (std::gcd(a, 26) != 1) {
        cout << "Invalid key: 'a' must be coprime with 26!" << endl;
        return 1;
    }

    cout << "Please enter your message:" << endl;
    std::string message;
    cin.ignore();
    std::getline(cin, message);

    cout << "Your key: (" << a << ", " << b << ")" << endl;
    cout << "Your message:\n" << message << endl;

    if (choose == 'e') {
        std::string encoded = encode(key, message);
        cout << "Your encoded message:\n" << encoded << endl;
    } else if (choose == 'd') {
        std::string decoded = decode(key, message);
        cout << "Your decoded message:\n" << decoded << endl;
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}