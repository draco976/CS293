//
//  main.cpp
//  
//
//  Created by Harshvardhan Agarwal on 05/08/21.
//

#include <iostream>
#include <chrono> // chrono for calculating runtime
#include <iomanip> // fixed and setprecision
#include "DynamicDequeue.h"

using namespace std ;

int main() {
    // The commented script is for calculating runtime for various deque sizes

    int y=10000 ;
    for(int i=0;i<9;i++) {
        clock_t start, end;
        start = clock() ;

        DynamicDequeue deq ;
        for(int i=0;i<y;i++) deq.insertFront(41212) ;
        
        end = clock() ;

        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

        cout << fixed << time_taken << setprecision(9);
        cout << " " ;

        y+=10000 ;
    }    
    cout << endl ;



    // The following code will showcase some features of deque

    DynamicDequeue deq ;
    for(int i=0;i<5;i++) {
        deq.insertRear(i) ;
    } // deq = [ 0,1,2,3,4 ]

    for(int i=0;i<5;i++) {
        deq.insertFront(i+100) ;
    } // deq = [ 104,103,102,101,100,0,1,2,3,4 ]

    double x ;

    for(int i=0;i<7;i++) {
        deq.removeFront(&x) ;
        cout << x << endl ;
    } // deq = [ 2,3,4 ]

    deq.rear(&x) ;
    cout << x << endl ;

    // deq = [ 2,3,4 ]

    cout << deq.size() ;
    

    return 0;
}
