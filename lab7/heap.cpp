#include<iostream>
using namespace std ;

int swaps ;

class Heap {
    int arr[1<<20] ;
    int count ;

    public:

    Heap() {
        count = 0 ;
    }

    void insert(int val) {
        arr[count] = val ;
        int x = count ;
        count++ ;
        while(x>0 && arr[x]<arr[(x-1)/2]) {
            swap(arr[x],arr[(x-1)/2]) ;
            swaps++ ;
            x=(x-1)/2 ;
        }
    }

    int min() {
        if(count==0) {
            cout << "Heap is empty" ;
            return -1 ;
        }
        return arr[0] ;
    }

    // CHANGES

    void heapify(int x) {
        if(2*x+3<=count) {
            if(arr[x]<=std::min(arr[2*x+1],arr[2*x+2])) {
                return ;
            }
            if(arr[2*x+1]<=arr[2*x+2]) {
                swap(arr[x],arr[2*x+1]) ;
                swaps++ ;
                heapify(2*x+1) ;
            }
            else {
                swap(arr[x],arr[2*x+2]) ;
                swaps++ ;
                heapify(2*x+2) ;
            }
        }
        else if(2*x+2<=count) {
            if(arr[x]>arr[2*x+1]) {
                swap(arr[x],arr[2*x+1]) ;
                swaps++ ;
                heapify(2*x+1) ;
            }
            else return ;
        }
        else return ;
    }

    int delete_min() {
        if(count==0) {
            cout << "Heap is empty" ;
            return -1 ;
        }
        int res = arr[0] ;
        arr[0] = arr[count-1] ;
        count-- ;
        heapify(0) ;
        return res ;
    }

};

int main() {
    Heap heap ;
    heap.insert(3) ;
    heap.insert(23) ;
    heap.insert(312) ;
    heap.insert(32) ;
    heap.insert(31) ;
    heap.insert(3) ;
    heap.insert(83) ;
    heap.insert(1) ;
    heap.insert(2) ;
    heap.insert(0) ;
    heap.insert(299) ;

    for (int i=0;i<11;i++) {
        cout << heap.delete_min() << " " ;
    }

    // for(int N=1000;N<=1000000;N*=10) {
    //     Heap heap ;
    //     for(int i=0;i<N;i++) {
    //         int x = rand() ;
    //         heap.insert(x) ;
    //     }
    //     double time_insert = 0 ;
    //     int count_insert = 0 ;
    //     int swaps_insert = 0 ;
        
    //     double time_delete = 0 ;
    //     int count_delete = 0 ;
    //     int swaps_delete = 0 ;

    //     for(int i=0;i<N/5;i++) {
    //         clock_t start, end;
    //         swaps = 0 ;
    //         int c = rand()%2 ;
            
    //         if(c==0) {

    //             int x = rand() ;

    //             start = clock() ;
    //             heap.insert(x) ;
    //             end = clock() ;

    //             time_insert += double(end - start) / double(CLOCKS_PER_SEC) ;
    //             count_insert++ ;
    //             swaps_insert+=swaps ;

    //         }
    //         else {

    //             start = clock() ;
    //             heap.delete_min() ;
    //             end = clock() ;

    //             time_delete += double(end - start) / double(CLOCKS_PER_SEC) ;
    //             count_delete++ ;
    //             swaps_delete+=swaps ;
    //         }
    //     }

    //     cout << time_insert/count_insert << " " << ((double)swaps_insert)/count_insert << endl ;
    //     cout << time_delete/count_delete << " " << ((double)swaps_delete)/count_delete << endl ;
    //     cout << endl ;

    //     // cout << count_insert << " " << count_delete << endl ;
    // }
}