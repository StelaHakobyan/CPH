#include <iostream>
#include <string>

class RLE2 {
public:
    static std::string compress(const std::string& txt) {
        std::string res;
        int len = txt.length();
        int i = 0;

        while (i < len - 1) {
            int start = i;
            bool repetitive = false;

            if (i < len - 1 && txt[i + 1] == txt[start]) {
                repetitive = true;
                while (i < len && txt[i] == txt[start]) {
                    ++i;
                }
            }
            else {
                if (i < len - 1 && txt[i + 1] != txt[i]) {
                    while (i < len - 1 && txt[i] != txt[i + 1]) {
                        ++i;
                    }
                }
            }

            int count = i - start;
            if (repetitive) {
                count |= 0x80;
                char c = static_cast<char>(count);
                res.push_back(c);
                res.push_back(txt[start]);
            }
            else {
                res.push_back(static_cast<char>(count));
                for (int j = start; j < i; ++j) {
                    res.push_back(txt[j]);
                }
            }
        }

        return res;
    }

    static std::string decompress(const std::string& compressed) {
        std::string decompressed;
        int len = compressed.length();
        int i = 0;

        while (i < len) {
            int count = compressed[i];
            char c = compressed[i + 1];
            bool repetitive = (count & 0x80) != 0;

            if (repetitive) {
                count ^= 0x80;
                for (int j = 0; j < count; ++j) {
                    decompressed.push_back(c);
                }
                i += 2;
            }
            else {
                for (int j = 0; j < count; ++j) {
                    decompressed.push_back(compressed[i + 1]);
                    ++i;
                }
                i++;
            }
        }

        return decompressed;
    }
};

int main() {
    std::cout << "Input text: ";
    std::string txt;
    std::getline(std::cin, txt);

    std::string compressed = RLE2::compress(txt);
    std::cout << "Compressed: " << compressed << std::endl;

    std::string decompressed = RLE2::decompress(compressed);
    std::cout << "Decompressed: " << decompressed << std::endl;

    return 0;
}
