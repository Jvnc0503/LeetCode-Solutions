#define ALPHABET_SIZE 26
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;
   
public:
    Trie() {
        root = new TrieNode();
    }
   
    void insert(string word) {
        TrieNode* node = root;
        for (char ch: word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }
   
    bool search(string word) {
        TrieNode* node = root;
        for (char ch: word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }
   
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char ch: prefix) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }

    string LCP() {
        TrieNode* node = root;
        string prefix = "";
        while (true) {
            int count = 0;
            int index = 0;
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (node->children[i] != nullptr) {
                    ++count;
                    index = i;
                }
            }
            if (count != 1 || node->isEndOfWord) {
                break;
            }
            prefix += 'a' + index;
            node = node->children[index];
        }
        return prefix;
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        Trie trie;
        for (const auto& s: strs) {
            trie.insert(s);
        }
        return trie.LCP();
    }
};