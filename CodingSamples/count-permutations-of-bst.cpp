#include <bits/stdc++.h>

int mod = 1000000007;
long long fact[51];
void fac(){
    fact[0] =1;
    for(int i=1;i<=50;i++){
        fact[i] = (fact[i-1]*1LL*i)%mod;
    }

}
long long power(long long a, long long n){
    long long res =1;
    while(n){
        if(n%2){
            res = (res*a)%mod;
            n--;
        }
        else{
            a = (a*a)%mod;
            n/=2;
        }
    }
    return res;
    
}

long long comb(int n, int r){
    long long num = fact[n];
    long long den = (fact[r]*1LL*fact[n-r])%mod;
    long long ncr = (num*power(den,mod-2))%mod;
    return ncr;
    

}

int Solution::cntPermBST(int A, int B) {

    fac();
    int count[A+1][A+1] ={0};
    int cumul[A+1][A+1]={0};
    for(int i=0;i<=A;i++){
        for(int j=0;j<=A;j++)
        {
            count[i][j]=0;
            cumul[i][j]=0;
        }
    }
    count[0][0]=1;
    for(int i=0;i<A+1;i++)cumul[i][0] =1;
    for(int j=1;j<A+1;j++){
        for(int i=0;i<log2(j);i++){count[i][j] = 0;cumul[i][j]=0;}
        for(int i=log2(j);i<A+1;i++){
            if(i==0){
                if(j==1)count[i][j]=1;
                else count[i][j]=0;
            }
            else if (i==1){
                if(j==2)count[i][j]=2;
                else if(j==3)count[i][j] =2;
                else count[i][j] =0;

            }
            else{
                for(int k=0;k<=j-1;k++){
                    long long plus=0;
                    plus = (plus+ (count[i-1][k]*1LL*cumul[i-2][j-1-k])%mod)%mod;
                    plus = (plus+ (count[i-1][j-1-k]*1LL*cumul[i-2][k])%mod)%mod;
                    plus = (plus+ (count[i-1][j-1-k]*1LL*count[i-1][k])%mod)%mod;
                    count[i][j] = (count[i][j] + (comb(j-1, k)*plus)%mod)%mod;
                }
            }
            if(i>0)cumul[i][j]= (count[i][j] + cumul[i-1][j])%mod;
            else cumul[i][j] = count[i][j];
        }


    }
    // for(int i=0;i<=A;i++){
    //     for(int j=0;j<=A;j++)cout<<count[i][j]<<" ";
    //     cout<<"\n";
    //     }
    
    // for(int i=0;i<=A;i++){
    //     for(int j=0;j<=A;j++)cout<<cumul[i][j]<<" ";
    //     cout<<"\n";
    // }
    return count[B][A];


}
