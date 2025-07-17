#include <string>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <emscripten.h>

extern "C" {

// Compute modular inverse of a mod m (m=26)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; ++x)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Encode affine cipher
EMSCRIPTEN_KEEPALIVE
const char* encode(int a, int b, const char* message_c) {
    static std::string encoded;
    encoded.clear();

    if (!message_c) return "";

    // Validate key (a and 26 coprime)
    if (std::gcd(a, 26) != 1) {
        return "Error: 'a' and 26 are not coprime!";
    }

    std::string message = message_c;

    for (char p : message) {
        if (std::isalpha(p)) {
            bool is_upper = std::isupper(p);
            char base = is_upper ? 'A' : 'a';
            int x = p - base;
            int shifted = (a * x + b) % 26;
            if (shifted < 0) shifted += 26;
            encoded += base + shifted;
        } else {
            encoded += p;
        }
    }
    return encoded.c_str();
}

// Decode affine cipher
EMSCRIPTEN_KEEPALIVE
const char* decode(int a, int b, const char* message_c) {
    static std::string decoded;
    decoded.clear();

    if (!message_c) return "";

    if (std::gcd(a, 26) != 1) {
        return "Error: 'a' and 26 are not coprime!";
    }

    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        return "Error: No modular inverse for 'a'!";
    }

    std::string message = message_c;

    for (char p : message) {
        if (std::isalpha(p)) {
            bool is_upper = std::isupper(p);
            char base = is_upper ? 'A' : 'a';
            int y = p - base;
            int x = (a_inv * (y - b + 26)) % 26;
            if (x < 0) x += 26;
            decoded += base + x;
        } else {
            decoded += p;
        }
    }
    return decoded.c_str();
}

}
