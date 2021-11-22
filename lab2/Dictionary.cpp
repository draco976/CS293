#include "Dictionary.h"
#include <iostream>
#include <cmath>
using namespace std ;

Entry :: Entry(char * key,int freq) {
    word = key ;
    count = freq ;
}

Entry :: Entry() {
    count = 0 ;
    word = new char [32] ;
}

Dictionary :: Dictionary() {
    A = new struct Entry [ARRAY_SIZE] ;
    N = ARRAY_SIZE ;
}

// A.count==0 will represent NULL entry && A.count==-1 will represent tombstone 

int Dictionary :: hashValue(char * key) {
    int i=0 ;
    double GoldenRatio = (sqrt(5.0)-1)/2 ;
    double hashvalue = 0 ;
    double z=GoldenRatio ;
    double int_value ;
    while(key[i]!='\0'){
        hashvalue += modf(z*(key[i]-'a'+1),&int_value) ;
        hashvalue = modf(hashvalue, &int_value) ;
        z=modf(z*31,&int_value) ;
        i++ ;
    }
    return (int)(N*hashvalue) ;
}

int Dictionary :: findFreeIndex(char * key) {
    int hash = hashValue(key) ;
    cout << "HASH : " << hash << endl ;
    int i=1 ;
    int tombstone=-1 ;

    while(A[hash].count != 0) {
        if(A[hash].count!=-1 && (string)A[hash].word == (string)key) {
            cout << "key found at " << hash << endl ;
            return hash ;
        }
        if(tombstone==-1 && A[hash].count==-1) {
            tombstone=hash ;
        }
        hash++ ;
        hash%=N ;
        cout << "searching at index " << hash << endl ;
        i++ ;
        if(i>N) {
            if(tombstone!=-1) {
                cout << "empty space at tombstone on index " << tombstone << endl ;
                return tombstone ;
            }
            cout << "no empty space not found" ;
            return -1 ;
        }
    }
    if(tombstone!=-1) {
        cout << "empty space at tombstone on index " << tombstone << endl ;
        return tombstone ;
    }
    cout << "empty space at index " << hash << endl ;
    return hash ;
}

struct Entry * Dictionary :: get(char * key) {
    int index = findFreeIndex(key) ;
    if(index!=-1 && (string)A[index].word == (string)key) {
        return &A[index] ;
    }
    return nullptr ;
}

bool Dictionary :: put(struct Entry e) {
    int index = findFreeIndex(e.word) ;
    if(index==-1) return false ;
    else if((string)A[index].word == (string)e.word) {
        A[index].count+=e.count ;
        return true ;
    }
    else {
        A[index]=e ;
        return true ;
    }
}

bool Dictionary :: remove(char * key) {
    int index = findFreeIndex(key) ;
    if(index==-1) return false ;
    else if((string)A[index].word == (string)key) {
        A[index].word = new char [32] ;
        A[index].count=-1 ;
        return true ;
    }
    else {
        return false ;
    }
}







