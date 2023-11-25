#include <iostream>
#include <string>

class Visions {
public:
    static std::string encode(const std::string& plainText, const std::string& key) {
        std::string encoded;
        for (size_t i = 0; i < plainText.length(); ++i) {
            char currentChar = plainText[i];
            if (std::isalpha(currentChar)) {
                char encodedChar = static_cast<char>('a' + ((std::tolower(currentChar) - 'a') + (std::tolower(key[i % key.length()]) - 'a')) % 26);
                if (std::isupper(currentChar)) {
                    encodedChar = std::toupper(encodedChar);
                }
                encoded.push_back(encodedChar);
            }
            else {
                char character = static_cast<char>(currentChar + key.length());
                encoded.push_back(character);
            }
        }
        return encoded;
    }

    static std::string decode(const std::string& ciphertext, const std::string& key) {
        std::string decoded;
        for (size_t i = 0; i < ciphertext.length(); ++i) {
            char currentChar = ciphertext[i];
            if (std::isalpha(currentChar)) {
                char decodedChar = static_cast<char>('a' + ((std::tolower(currentChar) - 'a') - (std::tolower(key[i % key.length()]) - 'a') + 26) % 26);
                if (std::isupper(currentChar)) {
                    decodedChar = std::toupper(decodedChar);
                }
                decoded.push_back(decodedChar);
            }
            else {
                char character = static_cast<char>(currentChar - key.length());
                decoded.push_back(character);
            }
        }
        return decoded;
    }
};

int main() {
    std::string plainTxt = "ATTACK *-$ATDAWN";
    std::string key = "Lemon";

    std::string result = Visions::encode(plainTxt, key);
    std::cout << "Plaintext: " << plainTxt << std::endl;
    std::cout << "Encoded: " << result << std::endl;

    result = Visions::decode(result, key);
    std::cout << "Decoded: " << result << std::endl;

    return 0;
}
