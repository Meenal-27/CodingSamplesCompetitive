#include <bits/stdc++.h>


int BFSvalid(vector <vector<int>> adj, int source, int dest){
    int n = adj.size();
    vector <bool> visited(n, false);
    queue <pair<int, int>> Q;
    Q.push(make_pair(source, 1));
    visited[source]= true;
    while(!Q.empty()){
        int node = Q.front().first, dis = Q.front().second;
        Q.pop();
        if(node== dest) return dis;
        for(int i=0;i<adj[node].size();i++){
            if(!visited[adj[node][i]]){
                visited[adj[node][i]]= true;
                Q.push(make_pair(adj[node][i], dis+1));
            }
        }
    } 
    return -1;
}

int Solution::solve(string A, string B, vector<string> &C) {
    
    int n = C.size();
    vector<vector<int>> adj(n+2, vector<int> ());
    unordered_map <string, vector<int>> forms;
    for(int i=0;i<n;i++){
        string str = C[i];
        for(int j=0;j<str.size();j++){
            char temp = str[j];
            str[j] = '#';
            if(forms.find(str)!= forms.end())forms[str].push_back(i);
            else{
                vector <int> v= {i};
                forms[str] = v;
            }
            str[j] = temp;
        }
    }
    for(auto it= forms.begin();it!= forms.end();it++){
        vector <int> v= it->second;
        for(int i=0;i<v.size();i++){
            for(int j=0;j<v.size();j++){
                if(i!=j) adj[v[i]].push_back(v[j]);
            }
        }
    }
    // for(auto it = forms.begin();it!= forms.end();it++){
    //     cout<<it->first<<" ";
    // }
    //cout<<"\n";
    set <int> sA;
    set <int> sB;
    for(int i=0;i<A.size();i++){
        char temp = A[i];
        A[i]= '#';
        //cout<<A<<endl;
        if(forms.find(A)!= forms.end()){
            //cout<<"Hi"<<endl;
            for(int j=0;j<forms[A].size();j++){
                sA.insert(forms[A][j]);
            }
        }
        A[i]= temp;

    }
    for(int i=0;i<B.size();i++){
        char temp = B[i];
        B[i]= '#';
        if(forms.find(B)!= forms.end()){
            //cout<<"Hi"<<endl;
            for(int j=0;j<forms[B].size();j++){
                sB.insert(forms[B][j]);
            }
        }
        B[i]= temp;

    }
    for(auto it= sA.begin();it!= sA.end();it++){
        adj[n].push_back(*it);
        adj[*it].push_back(n);
    }
    for(auto it= sB.begin();it!= sB.end();it++){
        adj[n+1].push_back(*it);
        adj[*it].push_back(n+1);
    }
    // for(int i=0;i<n+2;i++){
    //     for(int j=0;j<adj[i].size();j++)cout<<adj[i][j]<<" ";
    //     cout<<"\n";
    // }
    return BFSvalid(adj, n, n+1);


}
