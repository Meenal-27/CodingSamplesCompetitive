#include <bits/stdc++.h>


int Solution::isInterleave(string A, string B, string C) {

    int n = A.size();
    int m = B.size();
    int l = C.size();
    //cout<<n<<" "<<m<<" "<<l<<"\n";
    if(n+m != l) return 0;
    bool dp[n+1][m+1];
    for(int i=0;i<n+1;i++){
        for(int j=0;j<m+1;j++) dp[i][j] = false;
    }
    dp[0][0] = true;
    for(int i=0;i<l;i++){
        
        int val = i+1;
        //cout<<val<<endl;
        for(int j=0;j<=val;j++){
    
            int a = j;
            int b = val-j;
            if(a>n || b>m) continue;
            if(a){
                if(A[a-1]== C[i] && dp[a-1][b]) {dp[a][b] =true;}
                //else cout<<A[a-1]<<" "<<C[i]<<" "<<dp[a-1][b]<<"\n";
            }
            if(b){
                if(B[b-1]==C[i] && dp[a][b-1]) {dp[a][b] = true;}
                //else cout<<B[b-1]<<" "<<C[i]<<" "<<dp[a][b-1]<<"\n";
            }
            //if(!a && !b) cout<<"Not possible\n";
        }
    }
    // for(int i=0;i<=n;i++){
    //     for(int j=0;j<=m;j++) cout<<dp[i][j]<<" ";
    //     cout<<"\n";
    // }

    return dp[n][m];
}