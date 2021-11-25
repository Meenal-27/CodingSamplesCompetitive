#include <bits/stdc++.h>


int BFS(vector <pair<int,int>> adj[], int  root, int key){

    vector <bool> visited(100, false);
    deque <pair<int, int>> Q;
    Q.push_front(make_pair(root, 0));
    while(!Q.empty()){
        int node = Q.front().first, height = Q.front().second;
        Q.pop_front();
        if(node==key) return height;
        visited[node] = true;
        for(int i=0;i<adj[node].size();i++){
            if(!visited[adj[node][i].first]) {
                if(!adj[node][i].second)Q.push_front(make_pair(adj[node][i].first,height));
                else Q.push_back(make_pair(adj[node][i].first, height+1));
            }

        }
    }
    return -1;

}
int Solution::snakeLadder(vector<vector<int> > &A, vector<vector<int> > &B) {
    
    int n = A.size();
    int m = B.size();
    vector <pair<int, int>> adj[100];
    for(int i=0;i<100;i++){
        for(int j=i+1;j<=min(i+6,99);j++)adj[i].push_back(make_pair(j,1));
    }
    for(int i=0;i<n;i++){
        int source = A[i][0], dest = A[i][1];
        --source;--dest;
        adj[source].clear();
        adj[source].push_back(make_pair(dest, 0));
    }
    for(int i=0;i<m;i++){
        int source = B[i][0], dest = B[i][1];
        --source;--dest;
        adj[source].clear();
        adj[source].push_back(make_pair(dest, 0));
    }
    return BFS(adj, 0, 99);
}
