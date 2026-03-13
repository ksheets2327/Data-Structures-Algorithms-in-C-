///////////////////////////////////////////////////////////////
// Name: Kassidie Sheets
// Filename: Trie.cpp
// Course: Data Structures  COP3415
// Last Modification: 4/11/2024
//////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#define ALPHABET_SIZE 26

//Trie Node Structure
class TrieNode {
public:
    TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
        endOfWord = false;
    }
    TrieNode* children[ALPHABET_SIZE];
    bool endOfWord;
};

//Trie structure
class Trie {
public:
    Trie();
    Trie(const vector<string>&);
    bool empty() const;
    void insert(const string& word);
    bool search(const string& word) const;

    int count_words() const;
    void print() const;
    int longest_word() const;

private:
    TrieNode* root;
    int wordcount;
    void printWord(TrieNode* node, string word) const;
    int findLongest(TrieNode* node) const;
};

//Default constructor
Trie::Trie() : root(nullptr), wordcount(0) { };

//Parameterized constructor
Trie::Trie(const vector<string>& vector) {
    for (string str : vector) {
        insert(str);
        wordcount++;
    }
};

//Check if Trie is empty
bool Trie::empty() const {
    return (root == nullptr);
};

//Insert a word into the trie
void Trie::insert(const string& word) {
    if (empty()) {
        root = new TrieNode();
    }
    TrieNode* cur = root;

    for (int i = 0; i < word.size(); i++) {
        int index = word[i] - 'a';
        if (!cur->children[index]) {
            cur->children[index] = new TrieNode();
        }

        cur = cur->children[index];
    }
    cur->endOfWord = true;
};

//Check if a word exists within the Trie
bool Trie::search(const string& word) const {
    if (empty()) {
        return false;
    }
    TrieNode* cur = root;

    for (int i = 0; i < word.size(); i++) {
        int index = word[i] - 'a';
        if (!cur->children[index]) {
            return false;
        }

        cur = cur->children[index];
    }

    return (cur->endOfWord);
};

//Returns the number of words in the Trie
int Trie::count_words() const { return wordcount; };

//Function to assist the print  Function using Recursion
void Trie::printWord(TrieNode* node, string word) const {
    if (node->endOfWord)
        cout << word << endl;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i] != nullptr)
            printWord(node->children[i], word + char('a' + i));
};

//Print all of the words from the Trie
void Trie::print() const {
    if (empty())
        return;
    printWord(root, "");
};

//Function to assist the longest_word function  using Recursion
int Trie::findLongest(TrieNode* node) const {
    int longest = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i] != nullptr) {
            int len = 1 + findLongest(node->children[i]);
            if (len > longest)
                longest = len;
        }
    return longest;
};

//Return the length of the longest word in the Trie
int Trie::longest_word() const {
    if (empty())
        return 0;
    return findLongest(root);
};

//Driver
int main() {
    vector<string> words = { "pickle", "squiggle", "bumblebee", "whippersnapper",
                             "jellybean", "noodle", "kerplunk", "giggle",
                             "muffin", "penguin" };

    Trie tr(words);
    cout << "There are " << tr.count_words() << " words in the Trie." << endl;
    cout << "Here are the words: " << endl;
    tr.print();

    cout << "The longest word has " << tr.longest_word() << " characters\n" << endl;

    return 0;
};