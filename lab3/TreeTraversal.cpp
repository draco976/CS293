#include <iostream>
#include <string.h>
#include "TreeTraversal.h"

using namespace std ;

Tree::Tree() {
    root = nullptr ;
}

struct Node* Tree::deduce_tree(char *pre_order, char *in_order, int N) {
    if(N==0) return nullptr ;

    Node * node = new Node ;
    node->value = pre_order[0] ;

    int c=0 ;
    while(in_order[c]!=pre_order[0]) {
        c++ ;
    }

    Node * z=deduce_tree(pre_order+1, in_order, c) ;
    if(z != nullptr) {
        node->LeftSubtree = new Tree() ;
        node->LeftSubtree->root = z ;
    }

    z=deduce_tree(pre_order+c+1, in_order+c+1, N-c-1) ;
    if(z != nullptr) {
        node->RightSubtree = new Tree() ;
        node->RightSubtree->root = z ;
    }

    // node->LeftSubtree = new Tree() ;
    // node->RightSubtree = new Tree() ;
    // node->LeftSubtree->root = deduce_tree(pre_order+1, in_order, c) ;
    // node->RightSubtree->root = deduce_tree(pre_order+c+1, in_order+c+1, N-c-1) ;

    return node ;
}

void Tree::external(TraversalType_e tt){
    cout << root->value ;
}

void Tree::left(TraversalType_e tt){
    if(tt==PRE_ORDER) cout << root->value ;
}

void Tree::right(TraversalType_e tt){
    if(tt==POST_ORDER) cout << root->value ;
}

void Tree::below(TraversalType_e tt){
    if(tt==IN_ORDER) cout << root->value ;
}

void Tree::traverse(TraversalType_e tt){
    // If the subtree is just a leaf , then external is called 
    if(root->LeftSubtree==nullptr && root->RightSubtree==nullptr) {
        external(tt) ;
        return ;
    }
    left(tt) ;
    if(root->LeftSubtree!=nullptr) root->LeftSubtree->traverse(tt) ;
    below(tt) ;
    if(root->RightSubtree!=nullptr) root->RightSubtree->traverse(tt) ;
    right(tt) ;
}

int main() {
    char * preorder = new char [100] ;
    char * inorder = new char [100] ;
    int N ;
    cout << "Preorder : " ;
    cin >> preorder ;
    cout << "Inorder : " ;
    cin >> inorder ;
    N = strlen(preorder) ;
    N = 9 ;
    Tree tree(preorder, inorder, N) ;
    tree.traverse(POST_ORDER) ;

    // Preorder Traversal: 1 2 4 7 9 5 3 6 8
    // Inorder Traversal: 7 9 4 2 5 1 3 6 8
    
}
