#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <emscripten.h>

extern "C" {

// Helper to validate key (26 unique alphabetical letters)
bool valid_key(const std::string& key) {
    if (key.size() != 26) return false;
    if (!std::all_of(key.begin(), key.end(), ::isalpha)) return false;
    std::string sorted_key = key;
    std::transform(sorted_key.begin(), sorted_key.end(), sorted_key.begin(), ::tolower);
    std::sort(sorted_key.begin(), sorted_key.end());
    return std::unique(sorted_key.begin(), sorted_key.end()) == sorted_key.end();
}

EMSCRIPTEN_KEEPALIVE
const char* encode(const char* key_c, const char* message_c) {
    static std::string encoded;
    encoded.clear();

    if (!key_c || !message_c) return "";

    std::string key = key_c;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    if (!valid_key(key)) {
        return "Error: Invalid key! Must be 26 unique letters.";
    }

    std::string message = message_c;

    for (char p : message) {
        if (std::isalpha(p)) {
            bool is_upper = std::isupper(p);
            int index = std::tolower(p) - 'a';
            char mapped = key[index];
            encoded += is_upper ? static_cast<char>(std::toupper(mapped)) : mapped;
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

    if (!key_c || !message_c) return "";

    std::string key = key_c;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    if (!valid_key(key)) {
        return "Error: Invalid key! Must be 26 unique letters.";
    }

    std::vector<char> reverse_map(26);
    for (int i = 0; i < 26; ++i) {
        reverse_map[key[i] - 'a'] = 'a' + i;
    }

    std::string message = message_c;

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

    return decoded.c_str();
}

} // extern "C"
