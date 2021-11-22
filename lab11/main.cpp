#include<iostream>
#include<queue>
using namespace std ;

int N ;
const int MAXN = 100 ;
bool adj[MAXN][MAXN] ;
bool visited[MAXN] ;
int d[MAXN] ;
int p[MAXN] ;


void bfs(int s, int type) {
    queue<int> q ;
    if(!visited[s]){
        d[s] = 0 ;
        q.push(s) ;
    }

    while(!q.empty()) {
        int v = q.front() ;
        q.pop() ;

        if(type == 0) {
            for (int u=0;u<N;u++) {
                if(adj[v][u]) {
                    if(!visited[u]) {
                        visited[u] = true ;
                        q.push(u) ;
                    }
                }
            }
        }
        if(type == 1) {
            for (int u=0;u<N;u++) {
                if(adj[u][v]) {
                    if(!visited[u]) {
                        visited[u] = true ;
                        q.push(u) ;
                    }
                }
            }
        }
        
    }
}

void checkStronglyConnected() {
    for(int i=0;i<N;i++) {
        visited[i] = 0 ;
    }
    bfs(0,0) ;
    for(int i=0;i<N;i++) {
        if(!visited[i]) {
            cout << "Not Strongly Connected " ;
            cout << 0 << " " << i << endl ;
            return  ;
        }
    }

    for(int i=0;i<N;i++) {
        visited[i] = 0 ;
    }
    bfs(0,1) ;
    for(int i=0;i<N;i++) {
        if(!visited[i]) {
            cout << "Not Strongly Connected " ;
            cout << endl << i << " " << 0 << endl ;
            return  ;
        }
    }

    cout << "Strongly Connected" << endl ;

}


void generate_graph() {
    N = 6 + rand()%5 ;
    cout << N << endl ;  

    //  Generating 3*n edges
    for(int i=0;i<3*N;i++) {

        int x = rand()%N ;
        int y = rand()%N ;

        while(adj[x][y]==1 || x==y) {
            x = rand()%N ;
            y = rand()%N ;
        }

        adj[x][y] = 1 ;
        
        printf("(%d,%d) ", x, y) ;
    }
    cout << endl ;
}

int main() {
    srand(1) ;
    int x=10 ;
    
    generate_graph() ;
    checkStronglyConnected() ;
}