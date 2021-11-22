#include<iostream>
#include <stdlib.h>
#include<chrono>
#include<fstream>
#include<algorithm>

using namespace std ;

int comparisons ;
int swaps ;

int Partition(double * a, int l, int r, int pivot){
    double z = a[pivot] ;
    int i = l ;
    int j = r ;
    while(true) {
        comparisons+=2 ;
        while(a[j]>z) {
            j-- ;
            comparisons++ ;
        }
        while(a[i]<z){
            i++ ;
            comparisons++ ;
        }
        if(i<j) {
            swap(a[i],a[j]) ;
            swaps++ ;
        }
        else return j ;
    }
}

void QSP1(double * a, int l, int r) {
    if(l<r) {
        int pivot = l ;
        int p = Partition(a, l, r, pivot) ;
        QSP1(a, l, p) ;
        QSP1(a, p+1, r) ;
    }
}

void QSRP(double * a, int l, int r) {
    if(l<r) {
        int pivot = rand()%(r-l+1) + l ;
        int p = Partition(a, l, r, pivot) ;
        QSRP(a, l, p) ;
        QSRP(a, p+1, r) ;
    }
}

void BuSo(double *a, int n) {
    for (int i=0;i<n-1;i++) {
        for(int j=0;j<n-1-i;j++) {
            comparisons++ ;
            if(a[j]>a[j+1]) {
                swaps++ ;
                swap(a[j],a[j+1]) ;
            }
        }
    }
}

int main() {

    ofstream myfile1 ;
    myfile1.open("comparisons.txt") ;
    ofstream myfile2 ;
    myfile2.open("swaps.txt") ;
    ofstream myfile3 ;
    myfile3.open("time.txt") ;

    for (int N=1000;N<10000;N+=1000) {
        double a[N], b[N], c[N];

        // Random Array ;
        for(int i=0;i<N;i++) {
            a[i] = b[i] = c[i] = rand() ;
        }

        // Almost Increasing ;
        // for(int i=0;i<N;i++) {
        //     a[i] = b[i] = c[i] = rand() ;
        // }
        // sort(a,a+9*N/10) ;
        // sort(b,b+9*N/10) ;
        // sort(c,c+9*N/10) ;

        // Almost Decreasing ;
        // for(int i=0;i<N;i++) {
        //     a[i] = b[i] = c[i] = rand() ;
        // }
        // sort(a,a+9*N/10) ;
        // sort(b,b+9*N/10) ;
        // sort(c,c+9*N/10) ;
        // reverse(a,a+9*N/10) ;
        // reverse(b,b+9*N/10) ;
        // reverse(c,c+9*N/10) ;

        clock_t start, end;
        comparisons = 0 ;
        swaps = 0 ;
        start = clock() ;
        QSP1(a,0,N-1) ;
        end = clock() ;
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC) ;
        myfile1 << comparisons << ',' ;
        myfile2 << swaps << ',' ;
        myfile3 << time_taken << ',' ;



        comparisons = 0 ;
        swaps = 0 ;
        start = clock() ;
        QSRP(b,0,N-1) ;
        end = clock() ;
        time_taken = double(end - start) / double(CLOCKS_PER_SEC) ;
        myfile1 << comparisons << ',' ;
        myfile2 << swaps << ',' ;
        myfile3 << time_taken << ',' ;


        comparisons = 0 ;
        swaps = 0 ;
        start = clock() ;
        BuSo(c,N) ;
        end = clock() ;
        time_taken = double(end - start) / double(CLOCKS_PER_SEC) ;
        myfile1 << comparisons << endl ;
        myfile2 << swaps << endl ;
        myfile3 << time_taken << endl ;
          
    } 
}

