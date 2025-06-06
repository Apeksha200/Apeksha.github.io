#include <bits/stdc++.h>
using namespace std;

#define ALPHABET_SIZE 26
#define CHAR_TO_INDEX(c) ((int)(c) - (int)('a'))

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isWordEnd;

    TrieNode() {
        isWordEnd = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    void suggestionsRec(TrieNode* node, string prefix) {
        if (node->isWordEnd)
            cout << prefix << "\n";

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                char nextChar = 'a' + i;
                suggestionsRec(node->children[i], prefix + nextChar);
            }
        }
    }

    bool isLastNode(TrieNode* node) {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (node->children[i])
                return false;
        return true;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& key) {
        TrieNode* crawl = root;
        for (char c : key) {
            // Convert uppercase to lowercase for uniformity
            char lowerC = tolower(c);
            if (lowerC < 'a' || lowerC > 'z') {
                // skip chars not in a-z (optional: you can handle '.' '@' etc if needed)
                continue;
            }
            int index = CHAR_TO_INDEX(lowerC);
            if (!crawl->children[index])
                crawl->children[index] = new TrieNode();
            crawl = crawl->children[index];
        }
        crawl->isWordEnd = true;
    }

    void autoComplete(const string& prefix) {
        TrieNode* crawl = root;
        string filteredPrefix = "";
        // Filter prefix for only a-z lowercase to match insert logic
        for (char c : prefix) {
            char lowerC = tolower(c);
            if (lowerC >= 'a' && lowerC <= 'z') {
                filteredPrefix.push_back(lowerC);
            }
        }

        for (char c : filteredPrefix) {
            int index = CHAR_TO_INDEX(c);
            if (!crawl->children[index]) {
                cout << "[No suggestions found for prefix \"" << prefix << "\"]\n";
                return;
            }
            crawl = crawl->children[index];
        }

        // If prefix itself is a word and no further children
        if (crawl->isWordEnd && isLastNode(crawl)) {
            cout << prefix << "\n";
            return;
        }

        // Else print all suggestions below this prefix
        suggestionsRec(crawl, filteredPrefix);
    }
};

int main() {
    Trie trie;

    cout << "Enter number of email/contact entries to insert:\n";
    int n; cin >> n;
    cin.ignore();

    cout << "Enter each email/contact (only a-z characters will be stored):\n";
    for (int i = 0; i < n; i++) {
        string email;
        getline(cin, email);
        trie.insert(email);
    }

    cout << "\nAutocomplete queries: (enter 'exit' to quit)\n";
    while (true) {
        cout << "Enter prefix: ";
        string prefix;
        getline(cin, prefix);
        if (prefix == "exit")
            break;

        cout << "Suggestions:\n";
        trie.autoComplete(prefix);
        cout << "------------------\n";
    }

    return 0;
}


