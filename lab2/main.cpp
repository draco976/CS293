#include <iostream>
#include <cmath>
#include "Dictionary.h"
using namespace std ;

int main(){
    Dictionary dictionary ;
    
     for(int i=0;i<10;i++) {
         for(int j=0;j<2;j++) {
             char* z = new char [32] ;
             z[0]='a'+i ;
             z[1]='a'+j ;
             cout<<(char)('a'+i)<<(char)('a'+j)<<endl;
             Entry e(z,1) ;
             dictionary.put(e) ;
         }
     }

    while(true) {
        int z ;
        cout << "0 to quit , 1 to insert , 2 to remove , 3 to get" << endl ;
        cin >> z ;
        if(z==0) {
            break ;
        }
        else if(z==1) {
            cout << "word : " ;
            char* c = new char [32] ;
            cin >> c ;
            int freq ;
            cout << "frequency : " ;
            cin >> freq ;
            Entry e(c,freq) ;
            dictionary.put(e) ;
        }
        else if(z==2) {
            cout << "word : " ;
            char* c = new char [32] ;
            cin >> c ;
            bool p = dictionary.remove(c) ;
            if(p) cout << "Word Removed from Dictionary" << endl ;
            else cout << "Word not present" << endl  ;
        }
        else if(z==3) {
            cout << "word : " ;
            char* c = new char [32] ;
            cin >> c ;
            Entry * p = dictionary.get(c) ;
            if(p==nullptr) cout << "Word not present" << endl  ;
            else cout << "Freq of Word is " << p->count << endl ;
        }
        else {
            cout << "Enter valid input" << endl ;
        }
    }
}
