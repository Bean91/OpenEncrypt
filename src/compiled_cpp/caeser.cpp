#include <string>
#include <cctype>
#include <emscripten.h>

extern "C" {

// Encode message with single-letter Caesar key
EMSCRIPTEN_KEEPALIVE
const char* encode(char key, const char* message_c) {
    static std::string encoded;
    encoded.clear();

    if (!message_c) return "";

    int shift = std::tolower(key) - 'a';
    std::string message = message_c;

    for (char p : message) {
        if (std::isalpha(p)) {
            char base = std::isupper(p) ? 'A' : 'a';
            int shifted = ((p - base) + shift) % 26;
            encoded += base + shifted;
        } else {
            encoded += p;
        }
    }

    return encoded.c_str();
}

// Decode message with single-letter Caesar key
EMSCRIPTEN_KEEPALIVE
const char* decode(char key, const char* message_c) {
    static std::string decoded;
    decoded.clear();

    if (!message_c) return "";

    int shift = std::tolower(key) - 'a';
    std::string message = message_c;

    for (char p : message) {
        if (std::isalpha(p)) {
            char base = std::isupper(p) ? 'A' : 'a';
            int shifted = ((p - base) - shift + 26) % 26;
            decoded += base + shifted;
        } else {
            decoded += p;
        }
    }

    return decoded.c_str();
}

}  // extern "C"
