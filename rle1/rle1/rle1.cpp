#include <iostream>
#include <string>

class RLE {
public:
    std::string encode(const std::string& input) {
        std::string result;
        int count = 1;
        char prev = input[0];

        for (size_t i = 1; i < input.length(); i++) {
            if (input[i] == prev) {
                count++;
            }
            else {
                result += prev;
                result += std::to_string(count);
                count = 1;
                prev = input[i];
            }
        }

        result += prev;
        result += std::to_string(count);

        return result;
    }

    std::string decode(const std::string& input) {
        std::string result;
        for (size_t i = 0; i < input.length(); i += 2) {
            char c = input[i];
            int count = input[i + 1] - '0';
            for (int j = 0; j < count; j++) {
                result += c;
            }
        }
        return result;
    }
};

int main() {
    std::cout << "Input text: ";
    std::string input;
    std::cin >> input;

    RLE rle;
    std::string encoded = rle.encode(input);

    std::cout << "Encoded: " << encoded << std::endl;

    std::cout << "If you want to decode this text, enter 'yes': ";
    std::string choice;
    std::cin >> choice;

    if (choice == "yes") {
        std::cout << "Decoded: " << rle.decode(encoded) << std::endl;
    }

    return 0;
}
