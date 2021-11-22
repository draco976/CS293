#include<iostream>
#include<deque>
#include<vector>
using namespace std ;

const int MAXN = 100 ;

bool adj[MAXN][MAXN] ;
bool visited[MAXN] ;
int d[MAXN] ;
int p[MAXN] ;
int N ;

void checkOddcycle(int v, int u) {
    // cout << v << " " << u << endl ;
    if(d[v]>d[u]) {
        if((d[v]-d[u])%2==0) {
            cout << "Odd Cycle : " ;
            int x = v ;
            cout << x << " " ;
            while(x!=u) {
                x = p[x] ;
                cout << x << " " ;
            }
            cout << v << endl ;
        }
    }
}

// type = True/1 DFS
// type = False/0 BFS
void searchAlgo(int s, bool type) {
    deque<int> deq ;
    if(!visited[s]){
        d[s] = 0 ;
        deq.push_back(s) ;
    }

    while(!deq.empty()) {
        int v ;
        if(type==1) {   // DFS - stack like implementation
            v = deq.back() ;
            deq.pop_back() ;
        }
        else {  // BFS - queue like implementation
            v = deq.front() ;
            deq.pop_front() ;
        }
        if(!visited[v]) {
            visited[v] = 1 ;
        }
        else continue ;
        // cout << v << " " ;
        for (int u=0;u<N;u++) {
            if(adj[v][u]) {
                if(u==p[v]) continue ;
                if(!visited[u]) {
                    p[u] = v ;
                    d[u] = d[v]+1 ;
                    deq.push_back(u) ;
                }
                else if(type == 1) {
                    // cout << u <<  " " << v << " " << d[u] << d[v] << endl ;
                    checkOddcycle(v,u) ;
                }
            }
        }
    }
}

void generate_graph() {
    N = 6 + rand()%5 ;
    cout << N << endl ;  

    //  Generating 2*n edges
    for(int i=0;i<2*N;i++) {

        int x = rand()%N ;
        int y = rand()%N ;

        while(adj[x][y]==1 || x==y) {
            x = rand()%N ;
            y = rand()%N ;
        }

        adj[x][y] = adj[y][x] = 1 ;
        
        printf("(%d,%d) ", x, y) ;
    }
    cout << endl ;
}

int main() {
    generate_graph() ;
    for(int i=0;i<N;i++) {
        if(!visited[i]) {
            searchAlgo(i,1) ;
        }
    }
}