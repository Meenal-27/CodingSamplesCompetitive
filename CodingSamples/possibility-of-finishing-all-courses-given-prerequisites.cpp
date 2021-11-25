#include <bits/stdc++.h>



bool DFS(int root, vector <vector<int>> &adj, vector <bool> &visited, vector <bool> &recstack ){
    visited[root] = true;
    recstack[root] = true;
    for(int i=0;i<adj[root].size();i++){
        if(!visited[adj[root][i]] && DFS(adj[root][i], adj, visited, recstack)) return true;
        else if(recstack[adj[root][i]]) return true;
    }
    recstack[root] = false;
    return false;
}


bool checkforcycle(vector <vector<int>> &adj, int A){
    vector <bool> visited(A,false);
    vector <bool> recstack(A,false);
    for(int i=0;i<A;i++){
        if(!visited[i] && DFS(i, adj, visited, recstack)) return true;
    }
    return false;
}


int Solution::solve(int A, vector<int> &B, vector<int> &C) {
    //basically this problem is about detecting a cycle in the graph 
    // if there exists a cycle in the graph, then it is not possible to do any course in the cycle
    // therefore we cannot complete all the courses
    // hence, for a student to be able to complete all the courses, no cycle should exist in the graph which is going to be modeeling this problem
    vector <vector<int>> adj(A, vector<int>());
    int m = B.size();
    for(int i=0;i<m;i++){
        int source = B[i], dest= C[i];
        --source, --dest;
        adj[source].push_back(dest);
    }
    return !checkforcycle(adj, A);

}
