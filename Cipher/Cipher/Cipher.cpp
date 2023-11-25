#include <iostream>
#include <string>

class Cipher {
public:
    virtual std::string encrypt(const std::string& text, int key) = 0;
    virtual std::string decrypt(const std::string& text, int key) = 0;
};

class CaesarCipher : public Cipher {
public:
    std::string encrypt(const std::string& text, int key) override {
        std::string result = text;

        for (char& ch : result) {
            if (std::isalpha(ch)) {
                char base = std::isupper(ch) ? 'A' : 'a';
                ch = static_cast<char>((ch - base + key) % 26 + base);
            }
        }

        return result;
    }

    std::string decrypt(const std::string& text, int key) override {
        return encrypt(text, 26 - key);
    }
};

int main() {
    std::cout << "Input text: ";
    std::string text;
    std::cin >> text;

    std::cout << "Input key: ";
    int key;
    std::cin >> key;

    CaesarCipher cc;
    std::string result = cc.encrypt(text, key);

    std::cout << "Encrypted text: " << result << std::endl;

    std::cout << "If you want to decrypt, input 'yes' or 'exit': ";
    std::cin >> text;

    if (text == "yes") {
        std::cout << "Decrypted text: " << cc.decrypt(result, key) << std::endl;
    }

    return 0;
}
