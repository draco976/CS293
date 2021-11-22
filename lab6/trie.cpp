#include<iostream>
#include<string>
#include<fstream>
using namespace std ;

struct Node {
    int s_index ;
    int l ;
    int r ;
    Node *child[26] ;

    Node() {
        l=r=0 ;
    }
};

const int MAX = 10000 ;

class Trie {
    Node *root ;
    string s[MAX] ;
    int count ;
    
public:
    Trie() {
        root = new Node() ;
        count = 1 ;
    }

    void insert(string str) {
        if(s[find(str,2)->s_index]==str){
            // cout << "'" << str << "'" << " already in the trie" << endl ;
            count++ ;
            return ;
        }
        s[count] = str ; 
        int n = str.length() ;
        int i = 0 ;
        Node* node = root ;
        while(i!=n) {
            int j ;
            for (j=node->l;j<=node->r;) {
                if(s[node->s_index][j]==str[i]) {
                    i++ ;
                    j++ ;
                }
                else break ;
            }
            if(j!=node->r+1) {
                if(node->child[s[node->s_index][j]-'a']==nullptr) {
                    node->child[s[node->s_index][j]-'a'] = new Node ;
                }
                *node->child[s[node->s_index][j]-'a'] = *node ;
                node->child[s[node->s_index][j]-'a']->l = j ;
                Node * childptr = node->child[s[node->s_index][j]-'a'] ;
                node->r = j-1 ; 
                for (int k=0;k<26;k++) {
                    node->child[k] = nullptr ;
                }
                node->child[s[node->s_index][j]-'a'] = childptr ;
                node->child[str[i]-'a'] = new Node ;
                node->child[str[i]-'a']->s_index = count ;
                node->child[str[i]-'a']->l = i ;
                node->child[str[i]-'a']->r = n-1 ;
                i=n ;
            }
            else {
                if (node->child[(str[i]-'a')] == nullptr) {
                    node->child[(str[i]-'a')] = new Node ;
                    node->child[(str[i]-'a')]->s_index = count ;
                    node->child[(str[i]-'a')]->r = n-1 ;
                    node->child[(str[i]-'a')]->l = i ;
                    i=n ;
                }
                else node = node->child[(str[i]-'a')] ;
            }
        }
        count++ ;
    }

    Node* find (string str, int mode=1) {
        Node * node = root ;
        int n = str.length() ;
        int i=0 ;
        while(i!=n) {
            // cout << node->l << node->r << s[node->s_index] << endl ;
            int j ;
            for (j=node->l;j<=node->r;) {
                if(s[node->s_index][j]==str[i]) {
                    i++ ;
                    j++ ;
                }
                else break ;
            }
            if(j!=node->r+1) {
                break ;
            }
            else {
                if (node->child[(str[i]-'a')] == nullptr) {
                    break ;
                }
                else node = node->child[(str[i]-'a')] ;
            }
        }
        if(mode==1) {
            for(int k=0;k<i;k++) cout << str[k] ;
            cout <<  " : " << node->s_index ;
            cout << endl ;
        }
        
        return node ;
    }
};

int main() {
    
    // Trie trie ;
    // string s1 = "abcd" ;
    // trie.insert(s1) ;
    // string s2 = "aba" ;
    // trie.insert(s2) ;
    // string s3 = "abcrf" ;
    // trie.insert(s3) ;
    // string s4 = "abaz";
    // Node * node = trie.find(s4) ;
    // cout  << node->s_index ;


    // Input from a file 
    Trie trie ;
    ifstream fin ;
    fin.open("sample.txt");
    while (!fin.eof()) {
        string str ;
        fin >> str ;
        str += '$' ;
        trie.insert(str) ;
    }
    fin.close() ;

    string str ; 
    str = "videos" ;
    trie.find(str) ;
}