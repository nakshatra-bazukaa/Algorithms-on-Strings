#include<bits/stdc++.h>
using namespace std;

class TrieNode {
    public:
    char data;
    TrieNode **children;
    bool isTerminal;
    int degree = 0;

    TrieNode(char data){
        this->data = data;
        children = new TrieNode*[26];
        for(int  i = 0; i<26; i++)
            children[i] = NULL;
        isTerminal = false;
    }
};

class Trie {
    TrieNode *root;
    int degree = 0;

    public:

    Trie(){
        root = new TrieNode('\0');
        root->degree = degree++;
    }

    void insertWord(TrieNode *root, string word){
        if(word.size() == 0){
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'A';
        TrieNode *child;
        if(root -> children[index] != NULL){
            child = root -> children[index];
        }
        else{
            child = new TrieNode(word[0]);
            root -> children[index] = child;
            child->degree = degree++;
        }

        insertWord(child, word.substr(1));
    }

    // User function
    void insertWord(string word){
        insertWord(root, word);
    }

    void print(TrieNode *root){
        for(int i = 0; i<26; i++){
            if(root->children[i] != NULL){
                cout
                    <<root->degree
                    <<"->"
                    <<root->children[i]->degree
                    <<':'
                    <<root->children[i]->data
                    <<endl;
                print(root->children[i]);
            }
        }
    }

    // User function
    void print(){
        print(root);
    }
};
void c_p_p(){
    #ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    #endif
}
int main(){
    // c_p_p();
    int n;
    cin>>n;
    Trie *trie = new Trie();
    for(int i = 0; i<n; i++){
        string word;
        cin>>word;
        trie->insertWord(word);
    }
    trie->print();

    return 0;
}