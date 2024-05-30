#include <string>
#include <iostream>

using namespace std;

class Trie {
private:
    Trie *children[26];
    bool word;
public:

    Trie *traverse(string prefix) {
        Trie *curNode = this;
        for (const auto &c: prefix) {
            if (curNode->children[c - 'a'] == 0)
                return nullptr;
            curNode = curNode->children[c - 'a'];
        }
        return curNode;
    }

    void insert(string word) {
        //CAT -> look for C go to C.
        Trie *curNode = this;
        for (int i = 0; i < word.length(); i++) {
            if (curNode->children[word[i] - 'a'] == nullptr) {
                curNode->children[word[i] - 'a'] = new Trie();
            }
            curNode = curNode->children[word[i] - 'a'];
        }
        curNode->word = true;
    }

    bool search(string word) {
        Trie *traverseNode = traverse(word);
        return traverseNode ? traverseNode->word : false;
    }

    bool startsWith(string prefix) {
        Trie *traverseNode = traverse(prefix);
        return traverseNode;
    }

};

int main() {
    Trie t;
    t.insert("apple");
    t.insert("bobby");
    t.insert("app");

    cout << std::boolalpha << t.search("bobby") << endl; //true
    cout << t.search("bob") << endl; //false
    cout << t.search("app") << endl; //true
    cout << t.search("appl") << endl; //false
    cout << t.startsWith("ap") << endl; // true
    cout << t.startsWith("boby") << endl; //false

}