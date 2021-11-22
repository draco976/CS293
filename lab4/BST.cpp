#include<iostream>
#include<string.h>
#include<fstream>
#include<chrono>
#include<iomanip>
#include<vector>
#include <assert.h>
#include "BST.h"

using namespace std ;

BST :: BST() {
    root = nullptr ;
}

void BST::external(TraversalType_e tt){
    cout << root->value << " " << root->height << endl ;
}

void BST::left(TraversalType_e tt){
    if(tt==PRE_ORDER) cout << root->value << " " << root->height << endl ;
}

void BST::right(TraversalType_e tt){
    if(tt==POST_ORDER) cout << root->value << " " << root->height << endl ;
}

void BST::below(TraversalType_e tt){
    if(tt==IN_ORDER) cout << root->value << " " << root->height << endl ;
}

void BST::traverse(TraversalType_e tt){
    // If the subtree is just a leaf , then external is called 
    if(root->LeftSubtree->root==nullptr && root->RightSubtree->root==nullptr) {
        external(tt) ;
        return ;
    }
    left(tt) ;
    if(root->LeftSubtree->root!=nullptr) root->LeftSubtree->traverse(tt) ;
    below(tt) ;
    if(root->RightSubtree->root!=nullptr) root->RightSubtree->traverse(tt) ;
    right(tt) ;
}

struct Node * BST::min(){
    if(root->LeftSubtree->root!=nullptr) return root->LeftSubtree->min() ;
    else return root ;
}

struct Node * BST::max(){
    if(root->RightSubtree->root!=nullptr) return root->RightSubtree->max() ;
    else return root ;
}

struct Node * BST::search(char* s){
    if(root==nullptr) {
        return nullptr ;  
    }
    int comp = strcmp(s,root->value) ;

    if(comp == 0) return root ;
    else if(comp > 0) {
        if(root->RightSubtree->root!=nullptr) return root->RightSubtree->search(s) ;
        else return nullptr ;
    }
    else {
        if(root->LeftSubtree->root!=nullptr) return root->LeftSubtree->search(s) ;
        else return nullptr ;
    }
}

bool BST::insert(struct Node n){
    
    if(root==nullptr) {
        root = new Node() ;
        root->value = n.value ;
        root->height = 1 ;
        root->LeftSubtree = new BST() ;
        root->RightSubtree = new BST() ;
        return true ;
    }

    int comp = strcmp(n.value,root->value) ;

    if(comp==0) return false ;
    else if(comp > 0) {
        if(root->RightSubtree->root!=nullptr) {
            bool b = root->RightSubtree->insert(n) ;
            if(b) {
                root->height = std::max(root->height, root->RightSubtree->root->height+1) ;
                return true ;
            }
            return false ;
        }
        else {
            root->RightSubtree = new BST() ;
            Node* rightNode = root->RightSubtree->root = new Node() ;
            rightNode->value = n.value ;
            rightNode->height = 1 ;
            rightNode->parent = root ;
            rightNode->LeftSubtree = new BST() ;
            rightNode->RightSubtree = new BST() ;
            root->height = std::max(root->height, root->RightSubtree->root->height+1) ;
            return true ;
        }
    }
    else {
        if(root->LeftSubtree->root!=nullptr) {
            bool b = root->LeftSubtree->insert(n) ;
            if(b) {
                root->height = std::max(root->height, root->LeftSubtree->root->height+1) ;
                return true ;
            }
            return false ;
        }
        else {
            root->LeftSubtree = new BST() ;
            Node * leftNode = root->LeftSubtree->root = new Node() ;
            leftNode->value = n.value ;
            leftNode->height = 1 ;
            leftNode->parent = root ;
            leftNode->LeftSubtree = new BST() ;
            leftNode->RightSubtree = new BST() ;
            root->height = std::max(root->height, root->LeftSubtree->root->height+1) ;
            return true ;
        }
    }
}

bool BST::remove(char *s) {

    Node * node = search(s) ;

    if(node == nullptr) return false ;
    if(node->LeftSubtree->root == nullptr && node->RightSubtree->root == nullptr) {
        Node * p = node->parent ;
        if(p == nullptr) {
            root = nullptr ;
        }
        else if(p->LeftSubtree->root == node) p->LeftSubtree->root = nullptr ;
        else p->RightSubtree->root = nullptr ;
        while(p!=nullptr) {
            p->height = 1 ;
            if(p->LeftSubtree->root != nullptr) p->height = std::max(p->LeftSubtree->root->height+1,p->height) ;
            if(p->RightSubtree->root != nullptr) p->height = std::max(p->RightSubtree->root->height+1,p->height) ;
            node = p ;
            p = node->parent ;
        }
        return true ;
    }
    else if(node->LeftSubtree->root == nullptr) {
        Node * p = node->parent ;
        if(p==nullptr) {
            root = node->RightSubtree->root ;
        }
        else if(p->LeftSubtree->root == node) p->LeftSubtree->root = node->RightSubtree->root ;
        else p->RightSubtree->root = node->RightSubtree->root ;
        while(p!=nullptr) {
            p->height = 1 ;
            if(p->LeftSubtree->root != nullptr) p->height = std::max(p->LeftSubtree->root->height+1,p->height) ;
            if(p->RightSubtree->root != nullptr) p->height = std::max(p->RightSubtree->root->height+1,p->height) ;
            node = p ;
            p = node->parent ;
        }
        return true ;
    }
    else if(node->RightSubtree->root == nullptr) {
        Node * p = node->parent ;
        if(p==nullptr) {
            root = node->LeftSubtree->root ;
        }
        else if(p->LeftSubtree->root == node) p->LeftSubtree->root = node->LeftSubtree->root ;
        else p->RightSubtree->root = node->LeftSubtree->root ;
        while(p!=nullptr) {
            p->height = 1 ;
            if(p->LeftSubtree->root != nullptr) p->height = std::max(p->LeftSubtree->root->height+1,p->height) ;
            if(p->RightSubtree->root != nullptr) p->height = std::max(p->RightSubtree->root->height+1,p->height) ;
            node = p ;
            p = node->parent ;
        }
        return true ;
    }
    else {
        Node * succ = successor(node) ;
        remove(succ->value) ;
        node->value = succ->value ;
        return true ;
    }
}

struct Node* BST::successor(struct Node* n) {
    if(n->RightSubtree->root != nullptr) return n->RightSubtree->min() ;
    Node * p = n->parent ;
    Node * node = n ;
    while(p!=nullptr && p->LeftSubtree->root != node) {
        node = p ;
        p = node->parent ;
    }
    return p ;
}

struct Node* BST::predecessor(struct Node* n) {
    if(n->LeftSubtree->root != nullptr) return n->LeftSubtree->max() ;
    Node * p = n->parent ;
    Node * node = n ;
    while(p!=nullptr && p->RightSubtree->root != node) {
        node = p ;
        p = p->parent ;
    }
    return p ;
}

char a[100000][32] ;
int rdm[3200000] ;

using namespace std::chrono;

int main() {
    BST bst ;
    Node m ;
    m.value = (char*)"gggg" ;
    bst.insert(m);
    m.value = (char*)"mnp" ;
    bst.insert(m);
    m.value = (char*)"fasfa" ;
    bst.insert(m);
    m.value = (char*)"zzzzzz" ;
    bst.insert(m);
    m.value = (char*)"zzzz" ;
    bst.insert(m);
    m.value = (char*)"abcd" ;
    bst.insert(m);
    m.value = (char*)"faff" ;
    bst.insert(m);
    m.value = (char*)"fasfa" ;
    bst.insert(m);
    m.value = (char*)"zxczx" ;
    bst.insert(m);
    m.value = (char*)"gfhf" ;
    bst.insert(m);
    bst.traverse(IN_ORDER) ;
    char* c = (char*)"fasfa" ;
    // cout << << c[3] << "KKK" ;
    cout << endl ;
    cout << endl ;
    bst.remove(c) ;
    bst.traverse(IN_ORDER) ;

    BST bst1 ;

    ofstream myfile ;
    myfile.open("data.txt") ;

    Node node ;

    for(int i=0;i<3200000;i++) {
        rdm[i]=rand()%10 ;
    }


    double total=0;
    
    for(int i=0;i<100000;i++) {
        for(int j=0;j<31;j++) {  
            a[i][j] = rdm[i*32+j]+'0' ;
        }
        a[i][31]='\n' ;
        node.value = a[i] ;
        
        clock_t start, end;
        start = clock() ;
        bst1.insert(node) ;
        end = clock() ;
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC) * 1e6;
        total+=time_taken ;
        if(i%1000==999) {
            myfile << i+1 << ',' << fixed << setprecision(9) << total << endl ;
        }
        
    }
}

