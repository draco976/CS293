#include<iostream>
#include <queue>
using namespace std ;

struct Event {
    double time ;
    int type ;
    // 1 for transmit and 2 for recieve
    bool error ;
    int t ; // transmitter
    int r ; // reciever

    Event(double time, int type, int t, int r) {
        this->time = time ;
        this->type = type ;
        this->t = t ;
        this->r = r ;
        error = false ;
    }

    Event() {
        this->time = 0 ;
        this->type = 0 ;
        this->t = 0 ;
        this->r = 0 ;
        error = false ;
    }
};

class Heap {
    Event arr[1<<18] ;
    int count ;
    int on_air ;

    public:

    Heap() {
        // for(int i=0;i<(1<<20);i++) {
        //     arr[i] = Event(0,0,0,0) ;
        // }
        count = 0 ;
        on_air = 0 ;
    }

    void insert(double time, int type, int t, int r) {
        arr[count] = Event(time, type, t, r) ;
        if(type==2) {
            on_air++ ;
            if(on_air>=2) {
                for(int i=0;i<=count;i++) {
                    if(arr[i].type==2) arr[i].error=true ;
                }
            }
        }
        int x = count ;
        count++ ;
        while(x>0 && arr[x].time<arr[(x-1)/2].time) {
            swap(arr[x],arr[(x-1)/2]) ;
            x=(x-1)/2 ;
        } 
    }

    Event min() {
        if(count==0) {
            cout << "Heap is empty" ;
            return Event(0,0,0,0) ;
        }
        return arr[0] ;
    }

    // CHANGES

    void heapify(int x) {
        if(2*x+3<=count) {
            if(arr[x].time<=std::min(arr[2*x+1].time,arr[2*x+2].time)) {
                return ;
            }
            if(arr[2*x+1].time<=arr[2*x+2].time) {
                swap(arr[x],arr[2*x+1]) ;
                heapify(2*x+1) ;
            }
            else {
                swap(arr[x],arr[2*x+2]) ;
                heapify(2*x+2) ;
            }
        }
        else if(2*x+2<=count) {
            if(arr[x].time>arr[2*x+1].time) {
                swap(arr[x],arr[2*x+1]) ;
                heapify(2*x+1) ;
            }
            else return ;
        }
        else return ;
    }

    Event delete_min() {
        if(count==0) {
            cout << "Heap is empty" ;
            return Event(0,0,0,0) ;
        }
        Event res = arr[0] ;
        if(res.type==2) on_air-- ;
        arr[0] = arr[count-1] ;
        count-- ;
        heapify(0) ;
        return res ;
    }
};


int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]) ;
    double T = atof(argv[2]) ;
    // cout << N << T ;
    if(N==1) return 0 ;

    Heap h ;
    double vtime = 0 ; 

    for(int i=1;i<=N;i++) {
        double time = (double)(rand()) / ((double)(RAND_MAX/(T/100))) ;
        // cout << time << endl;
        int r = rand()%N+1 ;
        while(r==i) {
            r = rand()%N+1 ;
        }
        h.insert(time,1,i,r) ;
    }


    while(true) {
        Event e = h.delete_min() ; 
        vtime = e.time ;
        // if(count==0) cout << e.type  << "  " << e.time ;
        if(vtime > T) break ;

        if(e.type==1) {
            // Package recieve Event
            int bytes = 50+rand()%951 ;
            h.insert(vtime+((double)bytes)/1000,2,e.t,e.r) ;


            // New Package Transmit event
            double time = (double)(rand()) / ((double)(RAND_MAX/(T/100))) ;
            int r = rand()%N+1 ;
            while(r==e.t) {
                r = rand()%N+1 ;
            }
            h.insert(vtime+time,1,e.t,r) ;

            // cout << "Package transmitted from " << e.t << " to " << e.r << " at " << e.time << endl ;
        }
        else if(e.type ==2) {
            cout << "Package recieved at " << e.r << " from " << e.t << " at " << e.time << " " ;
            if(e.error) cout << "with error" << endl ;
            else cout << "successfully" << endl ;
        }
    }
    return 0;
}
