#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

uint32_t roundFunction(uint32_t right, uint64_t key) {
    right = (right & 0x0000fff) | (right & 0xfffff000);
    return right ^ static_cast<uint32_t>(key);
}

uint64_t feistelEncryption(uint64_t block, uint64_t key) {
    uint32_t left = block >> 32;
    uint32_t right = static_cast<uint32_t>(block);
    const int rounds{ 16 };
    for (int round = 0; round < rounds; ++round) {
        key = (key ^ 0x0000000f) | (key ^ 0xfffffff0);
        uint32_t temp = left;
        left = right;
        right = temp ^ roundFunction(right, key);
    }

    block = (static_cast<uint64_t>(right) << 32) | left;
    return block;
}

uint64_t feistelDecryption(uint64_t block, uint64_t key) {
    uint32_t left = block >> 32;
    uint32_t right = static_cast<uint32_t>(block);
    const int rounds{ 16 };
    // Reverse the key schedule
    for (int round = 0; round < rounds; ++round) {
        key = (key ^ 0x0000000f) | (key ^ 0xfffffff0);
        uint32_t temp = left;
        left = right;
        right = temp ^ roundFunction(right, key);
    }

    block = (static_cast<uint64_t>(right) << 32) | left;
    return block;
}

//divide text into blocks of size 64 bits
std::vector<uint64_t> textToBlocks(std::string txt) {
    while (txt.size() % 8 != 0) {
        txt.push_back('\0');
    }

    std::vector<uint64_t> blocks;


    for (size_t i = 0; i < txt.size(); i += 8) {
        uint64_t block = 0;
        for (int j = 0; j < 8; ++j) {
            block |= static_cast<uint64_t>(txt[i + j]) << (8 * j);
        }
        blocks.push_back(block);
    }

    return blocks;
}

std::string blocksToText(const std::vector<uint64_t>& blocks) {
    std::string encryptedText;
    for (uint64_t block : blocks) {
        for (int j = 0; j < 8; ++j) {
            encryptedText.push_back(static_cast<char>(block >> (8 * j)));
        }
    }

    return encryptedText;
}

int main() {
    std::string plaintext{ "This is Feistel cipher code" };
    uint64_t key{ 0xfed321683178ae51 };
    auto blocks = textToBlocks(plaintext);
    for (auto& block : blocks) {
        block = feistelDecryption(block, key);
    }

    std::string encoded = blocksToText(blocks);

    for (auto& block : blocks) {
        block = feistelDecryption(block, key);
    }

    std::string decoded = blocksToText(blocks);

    std::cout << "\n" << plaintext
        << "\n" << encoded
        << "\n" << decoded;
}