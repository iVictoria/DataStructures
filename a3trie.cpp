// Victoria Castillo

#include "a3.h"
#include <string>
#include <vector>

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

SpellCheck::SpellCheck(string data[],int sz){
    for (int i = 0; i < sz; ++i) {
        addWord(data[i]);
    }
}

void SpellCheck::addWord(const string& newWord){
    Node* curr = root;
    
    for (unsigned int i = 0;i < newWord.length();++i) {
        char c = newWord[i];
        
        if (!curr->child(c))
            curr->child(c) = new Node();
        curr = curr->child(c);
    }
    
    curr->is_word = true;
}

bool SpellCheck::lookup(const string& word) const{
    Node* curr = root;
    for(unsigned int i = 0;i < word.length();++i) {
        char c = word[i];
        
        if(curr->child(c) == NULL)
            return false;
        curr = curr->child(c);
    }
    return curr->is_word;
}

int SpellCheck::suggest(const string& partialWord, string suggestions[]) const{
    
    int index;
    Node* curr = this->root;
    vector<string> wordList;
    
    for (unsigned int i = 0; i < partialWord.length(); ++i) {
        index = CHAR_TO_INDEX(partialWord.at(i));
        
        if (!curr->children[index]) {
            return -1;
        }
        curr = curr->children[index];
    }
    
    traverse(partialWord, curr, wordList);
    copy(wordList.begin(), wordList.end(), suggestions);
    
    return (int)wordList.size();
}

SpellCheck::~SpellCheck(){
    delete root;
}


void SpellCheck::traverse(const string& partialWord, Node* node, vector<string>& wordList) const {
    if (node->is_word) {
        wordList.push_back(partialWord);
    }
    
    for(int i = 0; i < 26; ++i) {
        if (node->children[i]) {
            traverse(partialWord + (char)('a' + i), node->children[i], wordList);
        }
    }
}
