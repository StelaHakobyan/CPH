#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <functional>

class Node {
public:
    int frequency;
    Node* leftNode;
    Node* rightNode;

    Node(int frequency) : frequency(frequency), leftNode(nullptr), rightNode(nullptr) {}

    Node(Node* leftNode, Node* rightNode) : frequency(leftNode->frequency + rightNode->frequency),
        leftNode(leftNode), rightNode(rightNode) {}

    virtual ~Node() {}
};

class Leaf : public Node {
public:
    char character;

    Leaf(char character, int frequency) : Node(frequency), character(character) {}
};

class Huffman {
private:
    Node* root;
    std::string text;
    std::unordered_map<char, int> charFrequencies;
    std::unordered_map<char, std::string> huffmanCodes;

    void fillCharFrequenciesMap() {
        for (char character : text) {
            charFrequencies[character]++;
        }
    }

public:
    Huffman(const std::string& text) : text(text), root(nullptr) {
        fillCharFrequenciesMap();
    }

    void generateHuffmanCodes(Node* node, const std::string& code) {
        if (dynamic_cast<Leaf*>(node)) {
            huffmanCodes[static_cast<Leaf*>(node)->character] = code;
            return;
        }
        generateHuffmanCodes(node->leftNode, code + "0");
        generateHuffmanCodes(node->rightNode, code + "1");
    }

    std::string encode() {
        std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>> queue(
            [](Node* a, Node* b) { return a->frequency > b->frequency; });

        for (const auto& entry : charFrequencies) {
            queue.push(new Leaf(entry.first, entry.second));
        }

        while (queue.size() > 1) {
            Node* left = queue.top();
            queue.pop();
            Node* right = queue.top();
            queue.pop();

            queue.push(new Node(left, right));
        }

        generateHuffmanCodes(root = queue.top(), "");

        std::string encodedText;
        for (char character : text) {
            encodedText += huffmanCodes[character];
        }

        return encodedText;
    }

    std::string decode(const std::string& encodedText) {
        std::string decodedText;
        Node* current = root;

        for (char character : encodedText) {
            current = (character == '0') ? current->leftNode : current->rightNode;

            if (dynamic_cast<Leaf*>(current)) {
                decodedText += static_cast<Leaf*>(current)->character;
                current = root;
            }
        }

        return decodedText;
    }

    void printCodes() {
        for (const auto& entry : huffmanCodes) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }
};

int main() {
    Huffman huffman("aaaaaaaabbbbbbbccccdd");
    std::string encodedText = huffman.encode();
    std::cout << "Encoded text: " << encodedText << std::endl;

    huffman.printCodes();

    std::string originalText = huffman.decode(encodedText);
    std::cout << "Decoded text: " << originalText << std::endl;

    return 0;
}
