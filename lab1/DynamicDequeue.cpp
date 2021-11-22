//
//  DynamicDequeue.cpp
//  
//
//  Created by Harshvardhan Agarwal on 05/08/21.
//


#include "DynamicDequeue.h"
using namespace std ;

DynamicDequeue :: DynamicDequeue() {
    N = INIT_SIZE ;
    A = new double [N] ;
    f=0 ;
    r=0 ;
}

void DynamicDequeue :: grow() {
    int newN = nextSizeLinear() ;
    // int newN = nextSizeExponential() ;

    // forming a new array B and shifting data of A to B
    double *B = new double [newN] ;
    if(f<r) {
        for(int i=f;i<r;i++) {
            B[i-f]=A[i] ;
        }
    }
    else {
        for(int i=f;i<N;i++) {
            B[i-f]=A[i] ;
        }
        for(int i=0;i<r;i++) {
            B[N-f+i]=A[i] ;
        }
    }

    r=size() ;
    f=0 ;
    
    N = newN ;
    A = B ;
}

unsigned int DynamicDequeue :: size() {
    return ((r+N)-f)%N ;
}

void DynamicDequeue :: insertFront(double x) {
    f = (f+N-1)%N ;
    A[f] = x ;
    if(size() == N-1) {
        grow() ;
    }
}

void DynamicDequeue :: insertRear(double x) {
    A[r] = x ;
    r = (r+1)%N ;
    if(size() == N-1) {
        grow() ;
    }
}

bool DynamicDequeue :: removeFront(double* x) {
    if(size() == 0) return false ;
    *x = A[f] ;
    A[f] = 0 ;
    f = (f+1)%N ;
    return true ;
}

bool DynamicDequeue :: removeRear(double* x) {
    if(size() == 0) return false ;
    r = (r+N-1)%N ;
    *x = A[r] ;
    A[r] = 0 ;
    return true ;
}

bool DynamicDequeue :: front(double *x) {
    if(size() == 0) return false ;
    *x = A[f] ;
    return true ;
}

bool DynamicDequeue :: rear(double *x) {
    if(size() == 0) return false ;
    *x = A[(r+N-1)%N] ;
    return true ;
}
