// Victoria Castillo

#include <string>
#include <vector>

using namespace std;

class SpellCheck{
    
public:
    struct Node
    {
        Node* children[26];
        bool is_word;
        
        Node() {
            for(int i = 0;i < 26;++i)
                children[i] = NULL;
            is_word = false;
        }
        
        ~Node() {
            for(int i = 0;i < 26;++i)
                if(children[i]) delete children[i];
        }
        
        Node*& child(char c) {
            return children[tolower(c)-'a'];
        }
    };
    
private:
    Node* root = new Node();
    
public:
    SpellCheck(string data[],int sz);
    void addWord(const string& newWord);
    bool lookup(const string& word) const;
    int suggest(const string& partialWord, string suggestions[]) const;
    void traverse(const string& partialWord, Node* node, vector<string>& wordList) const;
    ~SpellCheck();
};
