#include <string>
#include <cctype>
#include <emscripten.h>

extern "C" {

std::string sanitizeKey(const std::string& key) {
    std::string clean = "";
    for (char c : key) {
        if (std::isalpha(c)) {
            clean += std::tolower(c);
        }
    }
    return clean;
}

EMSCRIPTEN_KEEPALIVE
const char* encode(const char* key_c, const char* message_c) {
    static std::string encoded;
    encoded.clear();

    std::string key = sanitizeKey(key_c);
    std::string message = message_c;

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

    return encoded.c_str();
}

EMSCRIPTEN_KEEPALIVE
const char* decode(const char* key_c, const char* message_c) {
    static std::string decoded;
    decoded.clear();

    std::string key = sanitizeKey(key_c);
    std::string message = message_c;

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

    return decoded.c_str();
}
}