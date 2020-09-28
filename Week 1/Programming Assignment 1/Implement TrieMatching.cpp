#include<bits/stdc++.h>
using namespace std;

vector<int> v;

// 0 - A
// 1 - C
// 2 - G
// 3 - T
int chIndex(char ch){
    switch(ch){
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
    }
}

class TrieNode {
    public:
    char data;
    TrieNode **children;
    vector<int> *indexes;

    TrieNode(char data){
        this->data = data;
        children = new TrieNode*[4];
        for(int  i = 0; i<4; i++)
            children[i] = NULL;
        indexes = new vector<int>();
    }
};

class Trie {
    TrieNode *root;

    public:

    Trie(){
        root = new TrieNode('\0');
    }

    void insertWord(TrieNode *root, string word, int wordIndexes[]){
        if(word.size() == 0){
            return;
        }

        int index = chIndex(word[0]);

        TrieNode *child;
        if(root -> children[index] != NULL){
            child = root -> children[index];
            child->indexes->push_back(wordIndexes[0]);
        }
        else{
            child = new TrieNode(word[0]);
            root -> children[index] = child;
            child->indexes->push_back(wordIndexes[0]);
        }

        insertWord(child, word.substr(1), 1+wordIndexes);
    }

    // User function
    void insertWord(string word){
        int wordIndexes[word.size()];
        for(int i = 0; i<word.size(); i++)
            wordIndexes[i] = i;
        for(int i = 0; i<word.size(); i++)    
            insertWord(root, word.substr(i), i+wordIndexes);
    }

    vector<int>* matchWord(TrieNode *root, string word){
        if(word.size() == 0)
            return root->indexes;
        
        int index = chIndex(word[0]);

        if(root->children[index] != 0)
            return matchWord(root->children[index], word.substr(1));

        return NULL;
    }

    // User function
    void matchWord(string word){
        vector<int> *ans = matchWord(root, word);
        if(ans != NULL)
            for(int i = 0; i<ans->size(); i++)
                v.push_back(ans->at(i)+1-word.size());
    }
    void print(TrieNode *root){
        for(int i = 0; i<root->indexes->size(); i++)
            cout<<root->indexes->at(i)<<' ';
        cout<<endl;
        for(int i = 0; i<4; i++){
            if(root->children[i] != NULL)
                print(root->children[i]);
        }
    }

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
    string text;
    cin>>text;

    Trie trie;
    trie.insertWord(text);

    int n;
    cin>>n;

    for(int i = 0; i<n; i++){
        string word;
        cin>>word;
        trie.matchWord(word);
    }

    // trie.print();

    sort(v.begin(), v.end());
    for(int i = 0; i<v.size(); i++)
        cout<<v[i]<<' ';

    return 0;
}