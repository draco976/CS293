#include<iostream>
#include<vector> 
#include<fstream>
#include<queue>
#include<algorithm>
using namespace std;

const int lim = 1e4 ;

vector<vector<int> > adj(lim) ;
vector<bool> visited(lim) ;
vector<int> p(lim) ;

void bfs(int s) {
    queue<int> q ;
    q.push(s) ;
    visited[s]=1 ;
    while(!q.empty()) {
        int v = q.front() ;
        q.pop() ;
        for(auto u:adj[v]) {
            if(!visited[u]) {
                p[u]=v ;
                visited[u]=1 ;
                q.push(u) ;
            }
        }
    }
}

int main() {
    ifstream infile ;
    infile.open("input.txt") ;
    int n,m ;
    infile >> n >> m ;

    for(int i=0;i<n-1;i++) {
        for(int j=0;j<m-1;j++) {
            visited[i]=0 ;
        }
    }

    // Take input of horizontal edges
    for(int i=0;i<n;i++) {
        for (int j=0;j<m-1;j++) {
            int x ;
            infile >> x ;
            if(i==0 || i==n-1) continue ;
            if(x==0) {
                // cout << (i-1)*(m-1)+j << ',' << i*(m-1)+j << endl ;
                adj[i*(m-1)+j].push_back((i-1)*(m-1)+j) ;
                adj[(i-1)*(m-1)+j].push_back(i*(m-1)+j) ;
            }
        }
    }

    // Take input of vertical edges
    for(int i=0;i<n-1;i++) {
        for (int j=0;j<m;j++) {
            int x ;
            infile >> x ;
            if(j==0 || j==m-1) continue ;
            if(x==0) {
                adj[i*(m-1)+j-1].push_back((i)*(m-1)+j) ;
                adj[(i)*(m-1)+j].push_back(i*(m-1)+j-1) ;
            }
        }
    }

    bfs(0) ;

    if(!visited[(n-1)*(m-1)-1]) cout << "Path does not exist" << endl ;

    vector<int> path ;
    int x = (n-1)*(m-1)-1 ;
    while(x!=0) {
        path.push_back(x) ;
        x = p[x] ;
    }
    path.push_back(0) ;
    reverse(path.begin(),path.end()) ;

    for(auto u:path) {
        printf("(%d,%d) ", u/(m-1), u%(m-1)) ;
    }
    cout << endl ;

}