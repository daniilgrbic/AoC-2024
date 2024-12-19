#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct TrieNode {
    bool end;
    map<char, unique_ptr<TrieNode>> next;
};

struct Trie {

    TrieNode root;

    void insert(string& word) {
        TrieNode* curr = &root;
        for(char ch : word) {
            if(!curr->next.contains(ch))
                curr->next[ch] = make_unique<TrieNode>();
            curr = curr->next[ch].get();
        }
        curr->end = true;
    }

    bool contains(string& word) {
        TrieNode* curr = &root;
        for (char ch : word) {
            if (!curr->next.contains(ch))
                return false;
            curr = curr->next[ch].get();
        }
        return curr->end;
    }

    vector<int> matchPrefix(string& word, int from) {
        vector<int> matchLengths;
        TrieNode* curr = &root;
        for(int i = from; i < word.length(); i++) {
            if(!curr->next.contains(word[i])) break;
            curr = curr->next[word[i]].get();
            if(curr->end) matchLengths.push_back(i - from + 1);
        }
        return matchLengths;
    }
};

bool backtrackSearch(Trie& trie, string& design, int from) {
    if(design.length() == from)
        return true;
    cout << design.substr(from) << endl;
    vector<int> matchLengths = trie.matchPrefix(design, from);
    bool any = false;
    for(auto it : matchLengths) {
        any = any || backtrackSearch(trie, design, from + it);
    }
    return any;
}

int main() {
    string input;
    Trie trie{};
    int total = 0;
    
    getline(cin, input);
    stringstream ss(input);
    while(ss >> input) {
        if(input.back() == ',')
            input.pop_back();
        trie.insert(input);
    }

    getline(cin, input);
    while(getline(cin, input)) {
        if(backtrackSearch(trie, input, 0)) {
            cout << "Design \"" << input << "\" is possible" << endl;
            total += 1;
        }
    }

    cout << total << endl;
    return 0;    
}