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

int64_t backtrackSearch(Trie& trie, string& design, int from) {
    static map<int, int64_t> cache;
    if(from == 0)
        cache.clear();
    if(cache.contains(from))
        return cache[from];

    if(design.length() == from)
        return 1;
    vector<int> matchLengths = trie.matchPrefix(design, from);
    int64_t combinations = 0;
    for(auto it : matchLengths) {
        combinations += backtrackSearch(trie, design, from + it);
    }
    cache[from] = combinations;
    return combinations;
}

int main() {
    int64_t total = 0, combinations;
    string input;
    Trie trie{};
    
    getline(cin, input);
    stringstream ss(input);
    while(ss >> input) {
        if(input.back() == ',')
            input.pop_back();
        trie.insert(input);
    }

    getline(cin, input);
    while(getline(cin, input)) {
        if(combinations = backtrackSearch(trie, input, 0)) {
            cout << "Design \"" << input << "\" is possible in " << combinations << " ways" << endl;
            total += combinations;
        }
    }

    cout << total << endl;
    return 0;    
}