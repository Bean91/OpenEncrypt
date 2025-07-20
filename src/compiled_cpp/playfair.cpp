#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>
#include <algorithm>
#include <emscripten.h>

constexpr int SQUARE_SIZE = 6;
const std::string VALID_CHARS = (SQUARE_SIZE == 6)
    ? "abcdefghijklmnopqrstuvwxyz0123456789"
    : "abcdefghiklmnopqrstuvwxyz"; // no 'j' in classic
const char PRIMARY_FILLER = 'x';
const char SECONDARY_FILLER = 'z';

struct MessageChar {
    char ch;
    bool isUpper;
    bool isPunct;
    size_t pos;
    char orig;
};

std::vector<char> bathKeyInRiverStyx(const std::string& key) {
    std::vector<char> cleansed;
    std::set<char> seen;
    for (char ch : key) {
        if (VALID_CHARS.find(std::tolower(ch)) == std::string::npos) continue;
        char lower = std::tolower(ch);
        if (SQUARE_SIZE == 5 && lower == 'j') lower = 'i';
        if (!seen.count(lower)) {
            seen.insert(lower);
            cleansed.push_back(lower);
        }
    }
    return cleansed;
}

std::pair<std::vector<std::vector<char>>, std::map<char, std::pair<int, int>>>
forgeSacredRunesOfAlphabetDoom(std::vector<char>& key) {
    std::vector<char> fullkey = key;
    std::set<char> exists(key.begin(), key.end());

    for (char c : VALID_CHARS) {
        if (SQUARE_SIZE == 5 && c == 'j') continue;
        char normalized = (SQUARE_SIZE == 5 && c == 'j') ? 'i' : c;
        if (!exists.count(normalized)) {
            fullkey.push_back(normalized);
            exists.insert(normalized);
        }
        if (fullkey.size() == SQUARE_SIZE * SQUARE_SIZE) break;
    }

    std::vector<std::vector<char>> square(SQUARE_SIZE, std::vector<char>(SQUARE_SIZE));
    std::map<char, std::pair<int, int>> coord_map;

    for (int i = 0; i < SQUARE_SIZE * SQUARE_SIZE; ++i) {
        int row = i / SQUARE_SIZE;
        int col = i % SQUARE_SIZE;
        char ch = fullkey[i];
        square[row][col] = ch;
        coord_map[ch] = {row, col};
    }

    return {square, coord_map};
}

std::vector<std::pair<char, char>> cleanMessage(const std::string& message, std::vector<MessageChar>& formatting, bool forEncoding) {
    std::vector<char> cleaned;
    for (size_t i = 0; i < message.size(); ++i) {
        char ch = message[i];
        if (std::isalnum(ch)) {
            char lower = std::tolower(ch);
            if (SQUARE_SIZE == 5 && lower == 'j') lower = 'i';
            formatting.push_back({lower, static_cast<bool>(std::isupper(ch)), false, i, ch});
            cleaned.push_back(lower);
        } else {
            formatting.push_back({0, false, true, i, ch});
        }
    }

    std::vector<std::pair<char, char>> digraphs;
    if (forEncoding) {
        for (size_t i = 0; i < cleaned.size(); ++i) {
            char first = cleaned[i];
            char second;
            if (i + 1 < cleaned.size()) {
                second = cleaned[i + 1];
                if (first == second) {
                    second = (first == PRIMARY_FILLER) ? SECONDARY_FILLER : PRIMARY_FILLER;
                } else {
                    ++i;
                }
            } else {
                second = (first == PRIMARY_FILLER) ? SECONDARY_FILLER : PRIMARY_FILLER;
            }
            digraphs.emplace_back(first, second);
        }
    } else {
        for (size_t i = 0; i + 1 < cleaned.size(); i += 2) {
            digraphs.emplace_back(cleaned[i], cleaned[i + 1]);
        }
    }

    return digraphs;
}

std::string encode(const std::vector<std::vector<char>>& square, const std::vector<std::pair<char, char>>& message, std::map<char, std::pair<int, int>>& coords) {
    std::string encoded;
    for (auto [a, b] : message) {
        auto [r1, c1] = coords[a];
        auto [r2, c2] = coords[b];
        if (r1 == r2) {
            encoded += square[r1][(c1 + 1) % SQUARE_SIZE];
            encoded += square[r2][(c2 + 1) % SQUARE_SIZE];
        } else if (c1 == c2) {
            encoded += square[(r1 + 1) % SQUARE_SIZE][c1];
            encoded += square[(r2 + 1) % SQUARE_SIZE][c2];
        } else {
            encoded += square[r1][c2];
            encoded += square[r2][c1];
        }
    }
    return encoded;
}

std::string decode(const std::vector<std::vector<char>>& square, const std::vector<std::pair<char, char>>& message, std::map<char, std::pair<int, int>>& coords) {
    std::string decoded;
    for (auto [a, b] : message) {
        auto [r1, c1] = coords[a];
        auto [r2, c2] = coords[b];
        if (r1 == r2) {
            decoded += square[r1][(c1 + SQUARE_SIZE - 1) % SQUARE_SIZE];
            decoded += square[r2][(c2 + SQUARE_SIZE - 1) % SQUARE_SIZE];
        } else if (c1 == c2) {
            decoded += square[(r1 + SQUARE_SIZE - 1) % SQUARE_SIZE][c1];
            decoded += square[(r2 + SQUARE_SIZE - 1) % SQUARE_SIZE][c2];
        } else {
            decoded += square[r1][c2];
            decoded += square[r2][c1];
        }
    }
    return decoded;
}

std::string stayNaturalNoBotox(const std::string& decoded) {
    std::string cleaned;
    size_t len = decoded.length();
    for (size_t i = 0; i < len; ++i) {
        char current = decoded[i];
        if (i == len - 1 && (current == PRIMARY_FILLER || current == SECONDARY_FILLER)) continue;
        if (i > 0 && i < len - 1) {
            char prev = decoded[i - 1];
            char next = decoded[i + 1];
            if ((current == PRIMARY_FILLER || current == SECONDARY_FILLER) && prev == next) continue;
        }
        cleaned += current;
    }
    return cleaned;
}

std::string reapplyFormatting(const std::string& result, const std::vector<MessageChar>& formatting) {
    std::string finalOutput(formatting.size(), ' ');
    size_t resultIndex = 0;
    for (const auto& fmt : formatting) {
        if (fmt.isPunct) {
            finalOutput[fmt.pos] = fmt.orig;
        } else {
            if (resultIndex < result.size()) {
                char ch = result[resultIndex++];
                finalOutput[fmt.pos] = fmt.isUpper ? std::toupper(ch) : ch;
            }
        }
    }
    return finalOutput;
}

static std::string staticResult;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* encode(const char* key_cstr, const char* message_cstr) {
    if (!key_cstr || !message_cstr) return "";

    std::string key(key_cstr), message(message_cstr);

    std::vector<char> cleansedKey = bathKeyInRiverStyx(key);
    auto [square, coords] = forgeSacredRunesOfAlphabetDoom(cleansedKey);

    std::vector<MessageChar> formatting;
    auto cleanedMessage = cleanMessage(message, formatting, true);
    std::string rawEncoded = encode(square, cleanedMessage, coords);
    std::string finalMessage = reapplyFormatting(rawEncoded, formatting);

    staticResult = finalMessage;
    return staticResult.c_str();
}

EMSCRIPTEN_KEEPALIVE
const char* decode(const char* key_cstr, const char* message_cstr) {
    if (!key_cstr || !message_cstr) return "";

    std::string key(key_cstr), message(message_cstr);

    std::vector<char> cleansedKey = bathKeyInRiverStyx(key);
    auto [square, coords] = forgeSacredRunesOfAlphabetDoom(cleansedKey);

    std::vector<MessageChar> formatting;
    auto cleanedMessage = cleanMessage(message, formatting, false);
    std::string rawDecoded = decode(square, cleanedMessage, coords);
    std::string noBotox = stayNaturalNoBotox(rawDecoded);
    std::string finalMessage = reapplyFormatting(noBotox, formatting);

    staticResult = finalMessage;
    return staticResult.c_str();
}

}
